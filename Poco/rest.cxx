#include <std.hxx>
#include <Poco/Foundation.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPBasicCredentials.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/URI.h>
#include <Poco/URIStreamOpener.h>
#include <Poco/Net/HTTPStreamFactory.h>
#include <Poco/StreamCopier.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
using namespace boost::property_tree;

const string proxyHost("proxysg.ddu-india.com");
const size_t proxyPort(3128);

int main (void)
{
  Poco::URIStreamOpener::defaultOpener().registerStreamFactory (
    "http",
    new Poco::Net::HTTPStreamFactory (proxyHost, proxyPort)
    );
  Poco::URI uri("http://isbndb.com/api/books.xml");
  string path(uri.getPath());
  Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
  session.setProxyHost(proxyHost);
  session.setProxyPort(proxyPort);
  cout << "No Problem Here" << endl;
  // Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST,
  //                                path,
  //                                Poco::Net::HTTPMessage::HTTP_1_1);
  Poco::Net::HTTPRequest req("HTTP/1.1");
  req.setURI(uri.getPathEtc());
  req.setMethod("POST");
  Poco::Net::HTMLForm form;
  form.set("access_key", "ZB4GTWMM");
  form.set("index1", "combined");
  // form.set("value1", "9780123820105");
  form.set("value1", "Chess Strategy");

  form.prepareSubmit(req);
  req.setContentType(form.getEncoding());
  std::ostream& ostr = session.sendRequest(req);
  form.write(ostr);

  Poco::Net::HTTPResponse response;
  std::istream& istr = session.receiveResponse(response);
  ptree pt;
  read_xml(istr, pt);
  write_xml(cout, pt, xml_writer_settings<char>(' ', 4));

  Poco::StreamCopier::copyStream(istr, cout);
}
