#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/util/XMLString.hpp>
using namespace xercesc;

#include <iostream>
using namespace std;

class DOMPrintErrorHandler : public DOMErrorHandler
{
public:

    DOMPrintErrorHandler(){};
    ~DOMPrintErrorHandler(){};

    /** @name The error handler interface */
    bool handleError(const DOMError& domError)
    {
      // Display whatever error message passed from the serializer
      if (domError.getSeverity() == DOMError::DOM_SEVERITY_WARNING)
        cerr << "\nWarning Message: ";
      else if (domError.getSeverity() == DOMError::DOM_SEVERITY_ERROR)
        cerr << "\nError Message: ";
      else
        cerr << "\nFatal Message: ";

      char *msg = XMLString::transcode(domError.getMessage());
      cerr<< msg << endl;
      XMLString::release(&msg);
      // Instructs the serializer to continue serialization if possible.
      return true;
    }


    void resetErrors(){};

private :
    /* Unimplemented constructors and operators */
    DOMPrintErrorHandler(const DOMErrorHandler&);
    void operator=(const DOMErrorHandler&);

};

int main (void)
{
  XMLPlatformUtils::Initialize();
  const XMLCh ls_id [] = {chLatin_L, chLatin_S, chNull};
  DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(ls_id);

  DOMDocument* doc = impl->createDocument (0, XMLString::transcode("Test"), 0);
  DOMElement* element = doc->getDocumentElement();

  DOMElement* sel = doc->createElement(XMLString::transcode("Surya"));
  element->appendChild (sel);

  DOMElement *abc = doc->createElement (XMLString::transcode("abc"));
  element->appendChild (abc);

  DOMElement *def = doc->createElement (XMLString::transcode("def"));
  abc->appendChild (def);

  DOMLSSerializer* ser = impl->createLSSerializer();
  DOMConfiguration* serializerConfig=ser->getDomConfig();
  serializerConfig->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

  DOMErrorHandler *myErrorHandler = new DOMPrintErrorHandler();
  serializerConfig->setParameter(XMLUni::fgDOMErrorHandler, myErrorHandler);

  DOMLSOutput* output = impl->createLSOutput();
  output->setEncoding (XMLString::transcode("UTF-8"));
  XMLFormatTarget *myFormTarget=new StdOutFormatTarget(); //("/home/suki/xerces-test.xml");
  output->setByteStream (myFormTarget);

  ser->write (element, output);
  output->release();
  ser->release();
  delete myFormTarget;
  XMLPlatformUtils::Terminate();
}
