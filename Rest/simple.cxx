#include <std.hxx>
#include <curl/curl.h>
#include <boost.hxx>
#include <boost/thread/thread.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
using namespace boost::property_tree;

struct UserData
{
  UserData(ptree& pt, bool isXml)
    :m_pt(pt), m_xml(isXml) {}

  ptree& m_pt;
  bool m_xml;
};

size_t writeData(void* buffer, size_t size, size_t nmemb, void* userp)
{
  ostringstream o_stream;
  size_t count = size * nmemb;
  o_stream.write(reinterpret_cast<const char*>(buffer), count);
  istringstream i_stream;
  i_stream.str(o_stream.str());
  
  UserData& ud = *(reinterpret_cast<UserData*>(userp));
  if (ud.m_xml) {
    read_xml(i_stream, ud.m_pt);
    write_xml(cout, ud.m_pt);
  } else {
    read_json(i_stream, ud.m_pt);
    write_json(cout, ud.m_pt);
  }
  return count;
}

struct GetIsbnData
{
  GetIsbnData ()
    :m_open_lib("http://openlibrary.org/api/books"),
     m_isbn_db("http://isbndb.com/api/books.xml")
  {}

  void operator()(const string& isbn) {
    ptree pt;
    getDataFromOpenLib(isbn, pt);
  }

private:
  void getDataFromIsbnDb(const string& isbn, ptree& pt)
  {
    UserData ud(pt, true);
    auto handle = curl_easy_init();
    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;

    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "access_key",
                 CURLFORM_COPYCONTENTS, "ZB4GTWMM",
                 CURLFORM_END);
    
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "index1",
                 CURLFORM_COPYCONTENTS, "isbn",
                 CURLFORM_END);
  
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "value1",
                 CURLFORM_COPYCONTENTS, isbn.c_str(),
                 CURLFORM_END);
    curl_easy_setopt(handle, CURLOPT_URL, m_isbn_db.c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, writeData);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &ud);
    curl_easy_setopt(handle, CURLOPT_HTTPPOST, formpost);
    curl_easy_perform(handle);
  }

  void getDataFromOpenLib(const string& isbn, ptree& pt)
  {
    UserData ud(pt, false);
    auto handle = curl_easy_init();
    fmt s = fmt ("%1%?bibkeys=ISBN:%2%&jscmd=data&format=json") % m_open_lib % isbn;
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, writeData);
    curl_easy_setopt(handle, CURLOPT_URL, s.str().c_str());
    curl_easy_setopt(handle, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &ud);
    curl_easy_perform(handle);
  }

  string m_open_lib, m_isbn_db;
};

int main (void)
{
  curl_global_init(CURL_GLOBAL_ALL);
  GetIsbnData gid;
  boost::thread t(gid, "3540323430");
  t.join();
  curl_global_cleanup();
  return 0;
}
