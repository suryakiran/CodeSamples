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

int main (void)
{
  Poco::Net::HTTPStreamFactory::registerFactory();
  Poco::URI uri("http://isbndb.com/api/books.xml");
  string path(uri.getPath());
  Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
  session.setProxy("http://proxy.ddu-india.com:3128", 3128);
  Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST,
                                 path,
                                 Poco::Net::HTTPMessage::HTTP_1_1);
  Poco::Net::HTMLForm form;
  form.set("access_key", "ZB4GTWMM");
  form.set("index1", "isbn");
  form.set("value1", "9780123820105");

  form.prepareSubmit(request);
  std::ostream& ostr = session.sendRequest(request);
  form.write(ostr);

  // Poco::Net::HTTPResponse response;
  // std::istream& istr = session.receiveResponse(response);

  // Poco::StreamCopier::copyStream(istr, cout);
}
