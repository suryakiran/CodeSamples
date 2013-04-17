#include <std.hxx>
#include <curl/curl.h>
#include <boost.hxx>
#include <boost/thread/thread.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
using namespace boost::property_tree;

size_t writeFunction (void*, size_t, size_t, void*);

class Curl
{
  typedef CURL* Handle;

public:
  Curl(const string& searchType, const string& url)
    : m_handle(curl_easy_init())
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

      curl_easy_setopt(m_handle, CURLOPT_URL, url.c_str());
      curl_easy_setopt(m_handle, CURLOPT_WRITEFUNCTION, writeFunction);
      curl_easy_setopt(m_handle, CURLOPT_WRITEDATA, this);
    }

  void addValue(const string& searchString)
    {
      curl_formadd(
        &m_formPost,
        &m_lastPtr,
        CURLFORM_COPYNAME, "value1",
        CURLFORM_COPYCONTENTS, searchString.c_str(),
        CURLFORM_END
        );
      curl_easy_setopt(m_handle, CURLOPT_HTTPPOST, m_formPost);

    }

  size_t writeData(void* buffer, size_t size, size_t nmemb)
    {
      size_t count = size * nmemb;
      ostringstream os;
      os.write(reinterpret_cast<const char*>(buffer), count);
      cout << os.str() << endl;
      return count;
    }

  void operator()()
    {
      curl_easy_perform(m_handle);
    }
  
private:
  struct curl_httppost* m_formPost;
  struct curl_httppost* m_lastPtr;
  Handle m_handle;
  boost::shared_ptr<Handle> m_handles;
  
};

size_t writeFunction (void* buffer, size_t size, size_t nmemb, void* userp)
{
  Curl* curl = reinterpret_cast<Curl*> (userp);
  return curl->writeData(buffer, size, nmemb);
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
      DEFINE_VEC(Curl, CurlVec);
      CurlVec curls;
      for(const string& isbn: m_isbn)
      {
        Curl c("isbn", m_url);
        c.addValue(isbn);
        c();
        // curls.push_back (c);
      }

      for(const string& title: m_titles)
      {
        Curl c("complete", m_url);
        c.addValue(title);
        curls.push_back(c);
      }

      for(Curl& curl: curls)
      {
        curl();
      }
    }

private:
  stl::StringVector m_isbn, m_titles;
  string m_url;
};

int main (void)
{
  IsbnDb isbnDb;
  isbnDb.addIsbn("3540323430");
  // isbnDb.addIsbn("0123820103");
  isbnDb.fetch();
  return 0;
}
