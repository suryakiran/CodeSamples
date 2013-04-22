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
using namespace boost::property_tree;

size_t writeFunction (void*, size_t, size_t, void*);

class Curl
{
  typedef CURL* Handle;
  typedef boost::property_tree::ptree Result;
  typedef boost::shared_ptr<boost::property_tree::ptree> ResultPtr;
  typedef boost::add_reference<Result>::type ResultReference;
  typedef const ResultReference ResultConstReference;

public:
  Curl(const string& searchType, const string& url)
    : m_handle(curl_easy_init()),
      m_formPost(nullptr), m_lastPtr(nullptr),
      m_result(new Result)
  {
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
                 CURLFORM_COPYCONTENTS, searchType.c_str(),
                 CURLFORM_END
                 );

    curl_easy_setopt(m_handle.get(), CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_handle.get(), CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(m_handle.get(), CURLOPT_WRITEDATA, this);
    curl_easy_setopt(m_handle.get(), CURLOPT_HTTPPOST, m_formPost);
  }

  void addValue(const string& searchString)
  {
    m_searchString = searchString;
    curl_formadd(
                 &m_formPost,
                 &m_lastPtr,
                 CURLFORM_COPYNAME, "value1",
                 CURLFORM_COPYCONTENTS, m_searchString.c_str(),
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

  void readData() {
    istringstream is;
    is.str(m_outputString);
    boost::property_tree::read_xml(is, *m_result, 
                                   boost::property_tree::xml_parser::trim_whitespace |
                                   boost::property_tree::xml_parser::no_comments);
    boost::property_tree::xml_writer_settings<char> settings(' ', 2);
    boost::property_tree::write_xml(cout, *m_result, settings);
  }

  ResultConstReference& result() const {
    return *m_result;
  }

  void operator()() {
    CURLcode res = curl_easy_perform(m_handle.get());
    if (res == CURLE_OK){
      readData();
      m_outputString.clear();
    }
  }

private:
  shared_ptr<void> m_handle;
  struct curl_httppost* m_formPost;
  struct curl_httppost* m_lastPtr;
  string m_searchString;
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
    boost::ptr_vector<Curl> curls;
    for(const string& isbn: m_isbn)
    {
      Curl* c = new Curl("isbn", m_url);
      c->addValue(isbn);
      curls.push_back (c);
    }

    for(const string& title: m_titles)
    {
      Curl* c = new Curl("combined", m_url);
      c->addValue(title);
      curls.push_back(c);
    }

    tbb::parallel_for(tbb::blocked_range<size_t>(0, curls.size()),
                      [&](const tbb::blocked_range<size_t>& range) {
                        for(size_t i = range.begin(); i != range.end(); ++i) {
                          Curl& c = curls[i];
                          c();
                        }
                      });
  }

private:
  stl::StringVector m_isbn, m_titles;
  string m_url;
};

int main (void)
{
  tbb::task_scheduler_init init;
  IsbnDb isbnDb;
  isbnDb.addIsbn("3540323430");
  isbnDb.addIsbn("0123820103");
  isbnDb.addTitle("Chess Strategy");
  isbnDb.fetch();
  return 0;
}
