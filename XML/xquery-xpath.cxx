#include <iostream>
#include <ParseArgs.hxx>
#include <boost/filesystem.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xqilla/xqilla-dom3.hpp>

using namespace std;
namespace fs = boost::filesystem;

ostream& operator<< (ostream& p_os, const XMLCh* p_char)
{
  p_os << UTF8(p_char);
  return p_os;
}

int main (int argc, char** argv)
{
  Args args = ParseArgs(argc, argv)();
  fs::path siteInfoFile (args["cur_src_dir"]);
  siteInfoFile /= "SiteInfo.xml";

  XQillaPlatformUtils::initialize();

  xercesc::DOMImplementation* impl = 
    xercesc::DOMImplementationRegistry::getDOMImplementation(X("XPath2 3.0"));

  try {

    AutoRelease<xercesc::DOMLSParser> parser (impl->createLSParser (xercesc::DOMImplementationLS::MODE_SYNCHRONOUS, 0));
    parser->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMNamespaces, true);
    parser->getDomConfig()->setParameter(xercesc::XMLUni::fgXercesSchema, true);
    parser->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMValidateIfSchema, true);

    xercesc::DOMDocument* document = parser->parseURI (siteInfoFile.string().c_str());

    AutoRelease<xercesc::DOMXPathExpression> expression 
      (document->createExpression (X("/SiteInfo/Site/@Name"), 0));

    AutoRelease<xercesc::DOMXPathResult> result 
      (expression->evaluate(document, xercesc::DOMXPathResult::ITERATOR_RESULT_TYPE, 0));

    while (result->iterateNext()) {
      xercesc::DOMNode* node = result->getNodeValue();

      if (node) {

        if (node->getNodeType() == xercesc::DOMNode::ATTRIBUTE_NODE) {
          xercesc::DOMAttr* attrNode = dynamic_cast<xercesc::DOMAttr*> (node);
          xercesc::DOMElement* elem = attrNode->getOwnerElement();
          cout << elem->getAttributeNode(X("Type"))->getValue() << endl;
        }

#if 0
        if (nodeMap) {
          cout << "Node Map Present" << endl;
        } else {
          cout << "Node Map Absent" << endl;
        }
#endif
      }
    }

  } catch (XQillaException& e) {
    cout << "Exception: " << e.getString() << endl;
  }

  XQillaPlatformUtils::terminate();

  return 0;
}
