#include <std.hxx>
#include <curl/curl.h>
#include <boost.hxx>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <tbb/task_scheduler_init.h>
#include <tbb/parallel_for.h>
using namespace boost::property_tree;

size_t writeFunction (void*, size_t, size_t, void*);


class Curl
{
  typedef CURL* Handle;

public:
  struct Result
  {
    Result()
      : m_success(false)
    {
      
    }

    operator bool() const {
      return m_success;
    }
    
    string m_title, m_isbn, m_isbn13, m_publisher;
    stl::StringVector m_authors;
    bool m_success;
  };
  
  Curl(const string& searchType, const string& url)
    : m_handle(curl_easy_init()),
      m_formPost(nullptr), m_lastPtr(nullptr)
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

  const Result& result() const {
    return m_result;
  }

  size_t writeData(void* buffer, size_t size, size_t nmemb)
    {
      size_t count = size * nmemb;
      cout.write(reinterpret_cast<const char*>(buffer), count);
      return count;
    }

    void operator()()
    {
      curl_easy_perform(m_handle.get());
    }
  
private:
  shared_ptr<void> m_handle;
  struct curl_httppost* m_formPost;
  struct curl_httppost* m_lastPtr;
  string m_searchString;
  Result m_result;
};

size_t writeFunction (void* buffer, size_t size, size_t nmemb, void* userp)
{
  Curl* curl = reinterpret_cast<Curl*> (userp);
  if (curl) {
    return curl->writeData(buffer, size, nmemb);
  }
  return 0;
}

struct Fetch
{
  Fetch(vector<Curl>& p_items) : m_items(p_items) {}
  
  void operator()(const tbb::blocked_range<size_t> p_range) const
    {
      for (size_t i = p_range.begin(); i != p_range.end(); ++i) {
        Curl& c = m_items[i];
        c();
      }
    }

private:
  vector<Curl>& m_items;
};

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
      DEFINE_VEC(Curl, CurlVec);
      CurlVec curls;
      for(const string& isbn: m_isbn)
      {
        Curl c("isbn", m_url);
        c.addValue(isbn);
        curls.push_back (c);
      }

      for(const string& title: m_titles)
      {
        Curl c("complete", m_url);
        c.addValue(title);
        curls.push_back(c);
      }

      tbb::parallel_for(tbb::blocked_range<size_t>(0, curls.size()), Fetch(curls), tbb::auto_partitioner());
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
  isbnDb.fetch();
  return 0;
}
