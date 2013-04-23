#include <std.hxx>
#include <curl/curl.h>
#include <boost.hxx>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <tbb/task_scheduler_init.h>
#include <tbb/parallel_for.h>
#include <boost/type_traits/add_reference.hpp>
#include <tbb/spin_mutex.h>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

size_t writeFunction (void*, size_t, size_t, void*);

namespace {

 template <class T>
 T getAttributeValue(const boost::property_tree::ptree& pt, const string& attr, const T& defaultValue)
    {
      ostringstream os;
      os << defaultValue ;
      auto key = pt.get_child_optional(attr);
      if (!key) {
        return defaultValue;
      }

      T value(defaultValue);
      try {
        value = boost::lexical_cast<T>(key->get_value<string>(os.str()));
      } catch (boost::bad_lexical_cast&) { }
      return value;
    }

  void write(const boost::property_tree::ptree& pt)
  {
    boost::property_tree::xml_writer_settings<char> settings(' ', 4);
    boost::property_tree::write_xml(cout, pt, settings);
  }
}

struct Book
{
  string title;
  stl::StringVector authors;
  pair<string, string> isbn; //(isbn, isbn13)
  string publisher;
  bool valid;

  bool operator<(const Book& other)
    {
      return isbn.second < other.isbn.second;
    }

  bool operator== (const Book& other)
    {
      return (isbn.second == other.isbn.second);
    }

  Book (const boost::property_tree::ptree& pt)
    : valid(true)
    {
      isbn.first = getAttributeValue<string>(pt, "<xmlattr>.isbn", "");
      isbn.second = getAttributeValue<string>(pt, "<xmlattr>.isbn13", "");
      if (isbn.first.empty() && isbn.second.empty())
      {
        valid = false;
        return;
      }

      title = pt.get<string>("TitleLong");
      if (title.empty()) {
        title = pt.get<string>("Title");
      }
      publisher = pt.get<string>("PublisherText");
      string authorsText(pt.get<string>("AuthorsText"));
      str::split(authors, authorsText, str::is_any_of(","), str::token_compress_on);
      boost::for_each(authors,
               [](string& s){
                 str::trim(s);
               });
      boost::remove_erase(authors, "");
    }
};

class Curl
{
public:
  typedef CURL* Handle;
  typedef boost::property_tree::ptree Result;
  typedef boost::shared_ptr<boost::property_tree::ptree> ResultPtr;
  typedef boost::add_reference<Result>::type ResultReference;
  typedef const ResultReference ResultConstReference;

public:
  Curl(const string& searchType, const string& url, const string& searchString)
    : m_handle(curl_easy_init()),
      m_formPost(nullptr), m_lastPtr(nullptr),
      m_url(url),
      m_searchString(searchString),
      m_searchType(searchType),
      m_result(new Result)
    {
      init();
    }

  Curl(const Curl& other)
    : m_handle(curl_easy_init()),
      m_formPost(nullptr), m_lastPtr(nullptr),
      m_url(other.m_url),
      m_searchString(other.m_searchString),
      m_searchType(other.m_searchType),
      m_result(new Result)
    {
      init();
    }

  void setPageNumber(int pageNum)
    {
      ostringstream os ;
      os << pageNum;
      curl_formadd(
        &m_formPost,
        &m_lastPtr,
        CURLFORM_COPYNAME, "page_number",
        CURLFORM_COPYCONTENTS, os.str().c_str(),
        CURLFORM_END
        );
    }

  size_t writeData(void* buffer, size_t size, size_t nmemb)
    {
      size_t count = size * nmemb;
      fstream fout;
      ostringstream os;
      os.write(reinterpret_cast<const char*>(buffer), count);
      m_outputString += os.str();
    
      return count;
    }

  int numResults() {
    return getAttributeValue(*m_result, "ISBNdb.BookList.<xmlattr>.total_results", 0);
  }

  int pageSize() {
    return (getAttributeValue(*m_result, "ISBNdb.BookList.<xmlattr>.page_size", 10));
  }
  
  bool isDone() {
    int pageNumber(getAttributeValue(*m_result, "ISBNdb.BookList.<xmlattr>.page_number", 1));

    return (numResults() <= (pageSize() * pageNumber));
  }

  void readData() {
    istringstream is;
    is.str(m_outputString);
    boost::property_tree::read_xml(is, *m_result, 
                                   boost::property_tree::xml_parser::trim_whitespace |
                                   boost::property_tree::xml_parser::no_comments);
  }


  ResultConstReference& results() const {
    return m_result->get_child("ISBNdb.BookList");
  }

  void operator()() {
    CURLcode res = curl_easy_perform(m_handle.get());
    if (res == CURLE_OK){
      readData();
      m_outputString.clear();
    }
  }

private:
  void init() {
    curl_formadd(
      &m_formPost,
      &m_lastPtr,
      CURLFORM_COPYNAME, "access_key",
      CURLFORM_COPYCONTENTS, "ZB4GTWMM",
      CURLFORM_END
      );

    curl_formadd(
      &m_formPost,
      &m_lastPtr,
      CURLFORM_COPYNAME, "index1",
      CURLFORM_COPYCONTENTS, m_searchType.c_str(),
      CURLFORM_END
      );

    curl_formadd(
      &m_formPost,
      &m_lastPtr,
      CURLFORM_COPYNAME, "value1",
      CURLFORM_COPYCONTENTS, m_searchString.c_str(),
      CURLFORM_END
      );

    curl_easy_setopt(m_handle.get(), CURLOPT_URL, m_url.c_str());
    curl_easy_setopt(m_handle.get(), CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(m_handle.get(), CURLOPT_WRITEDATA, this);
    curl_easy_setopt(m_handle.get(), CURLOPT_HTTPPOST, m_formPost);
  }
  
private:
  shared_ptr<void> m_handle;
  struct curl_httppost* m_formPost;
  struct curl_httppost* m_lastPtr;
  string m_url, m_searchString, m_searchType;
  ResultPtr m_result;
  string m_outputString;
};

size_t writeFunction (void* buffer, size_t size, size_t nmemb, void* userp)
{
  Curl* curl = reinterpret_cast<Curl*> (userp);
  if (curl) {
    return curl->writeData(buffer, size, nmemb);
  }
  return 0;
}

class IsbnDb
{
public:
  IsbnDb()
    : m_url("http://isbndb.com/api/books.xml")
    {
      curl_global_init(CURL_GLOBAL_ALL);
    }

  ~IsbnDb()
    {
      curl_global_cleanup();
    }

  void addIsbn(const string& isbn)
    {
      m_isbn.push_back(isbn);
    }

  void addTitle(const string& title)
    {
      m_titles.push_back(title);
    }


  void fetch()
    {
      boost::ptr_vector<Curl> curls, newCurls;
      for(const string& isbn: m_isbn)
      {
        Curl* c = new Curl("isbn", m_url, isbn);
        curls.push_back (c);
      }

      for(const string& title: m_titles)
      {
        Curl* c = new Curl("combined", m_url, title);
        curls.push_back(c);
      }

      tbb::parallel_for(tbb::blocked_range<size_t>(0, curls.size()),
                        [&](const tbb::blocked_range<size_t>& range) {
                          for(size_t i = range.begin(); i != range.end(); ++i) {
                            Curl& c = curls[i];
                            c();
                            Curl::ResultReference& res = c.results();
                            BOOST_FOREACH(auto& a, res)
                            {
                              Book b(a.second);
                            }
                            if (!c.isDone()) {
                              int numPages = (c.numResults() / c.pageSize()) + 1;
                              for (int i = 2; i <= numPages; ++i) {
                                Curl* nc = new Curl(c);
                                nc->setPageNumber(i);
                                newCurls.push_back(nc);
                              }
                            }
                          }
                        });

      // tbb::parallel_for(tbb::blocked_range<size_t>(0, newCurls.size()),
      //                   [&](const tbb::blocked_range<size_t>& range) {
      //                     for(size_t i = range.begin(); i != range.end(); ++i) {
      //                       Curl& c = newCurls[i];
      //                       c();
      //                     }
      //                   });

    }

private:
  stl::StringVector m_isbn, m_titles;
  string m_url;
};

int main (void)
{
  tbb::task_scheduler_init init;
  IsbnDb isbnDb;
  // isbnDb.addIsbn("3540323430");
  // isbnDb.addIsbn("0123820103");
  // isbnDb.addTitle("Tarrasch");
  isbnDb.addTitle("Chess Strategy");
  isbnDb.fetch();
  return 0;
}
