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
  string m_isbn;
};

size_t writeData(void* buffer, size_t size, size_t nmemb, void* userp)
{
  ostringstream o_stream;
  size_t count = size * nmemb;
  o_stream.write(reinterpret_cast<const char*>(buffer), count);
  istringstream i_stream;
  i_stream.str(o_stream.str());
  
  UserData& ud = *(reinterpret_cast<UserData*>(userp));
  ptree pt;
  if (ud.m_xml) {
    read_xml(i_stream, pt);
    string title = pt.get<string>("ISBNdb.BookList.BookData.Title");
    string titleLong = pt.get<string>("ISBNdb.BookList.BookData.TitleLong");
    cout << title << '\t' << titleLong << endl;
    xml_writer_settings<char> settings(' ', 4);
    // write_xml(cout, pt, settings);
  } else {
    read_json(i_stream, pt);
    // write_json(cout, pt);
    
  }
  // for(auto iter = pt.begin(); iter != pt.end(); ++iter) {
  //   cout << iter->first << endl;
  // }
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
    // getDataFromOpenLib(isbn, pt);
    getDataFromIsbnDb(isbn, pt);
  }

private:
  void getDataFromIsbnDb(const string& isbn, ptree& pt)
  {
    UserData ud(pt, true);
    ud.m_isbn = isbn;
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
    ud.m_isbn = isbn;
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
  // boost::thread t(gid, "3540323430");
  // boost::thread t(gid, "0123820103");
  boost::thread t(gid, "9780123820105");
  t.join();
  curl_global_cleanup();
  return 0;
}
