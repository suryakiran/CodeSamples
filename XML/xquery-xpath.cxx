#include <iostream>
#include <ParseArgs.hxx>
#include <boost/filesystem.hpp>
#include <xqilla/xqilla-simple.hpp>
#include <Node.h>

using namespace std;
namespace fs = boost::filesystem;

map<string, string>
getAttributes (Node::Ptr parent, const AutoDelete<DynamicContext>& context, const Result& result)
{
  map<string, string> attrs;
  Sequence attributes = parent->dmAttributes(context, result.get())->toSequence(context);

  for (size_t i = 0; i < attributes.getLength(); ++i) {
    const Node* attrNode = dynamic_cast<const Node*>(attributes.item(i).get());
    attrs[UTF8(attrNode->dmNodeName(context)->getName())] = 
      UTF8(attrNode->dmStringValue(context));
  }

  return attrs;
}

map<string, string>
getChildren (Node::Ptr parent, const AutoDelete<DynamicContext>& context, const Result& result)
{
  map<string, string> rv;

  Sequence children = parent->dmChildren (context, result.get())->toSequence(context);

  for (size_t i = 0; i < children.getLength(); ++i) {
    const Node* childNode = dynamic_cast<const Node*>(children.item(i).get());
    if (string(UTF8(childNode->dmNodeKind())) == string(UTF8(Node::element_string))) {
      rv[UTF8(childNode->dmNodeName(context)->getName())] =
        UTF8(childNode->dmStringValue(context));
    }
  }

  return rv;
}

int main (int argc, char** argv)
{
  Args args = ParseArgs(argc, argv)();
  fs::path siteInfoFile (args["cur_src_dir"]);
  siteInfoFile /= "SiteInfo.xml";

  XQilla xqilla;
  AutoDelete<XQQuery> query (xqilla.parse(X("/SiteInfo/Site/@Name")));
  AutoDelete<DynamicContext> context (query->createDynamicContext());
  Sequence seq = context->resolveDocument(X(siteInfoFile.string().c_str()));

  if (!seq.isEmpty() && seq.first()->isNode()) {
    context->setContextItem(seq.first());
  }

  Result result = query->execute(context);

  Item::Ptr item;
  while (item = result->next(context)) {
    Xqilla::Node node (item, context, result.get());
  }
  return 0;
}
