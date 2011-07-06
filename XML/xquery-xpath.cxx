#include <iostream>
#include <ParseArgs.hxx>
#include <boost/filesystem.hpp>
#include <xqilla/xqilla-simple.hpp>

using namespace std;
namespace fs = boost::filesystem;

int main (int argc, char** argv)
{
  Args args = ParseArgs(argc, argv)();
  fs::path siteInfoFile (args["cur_src_dir"]);
  siteInfoFile /= "SiteInfo.xml";

  XQilla xqilla;
  AutoDelete<XQQuery> query (xqilla.parse(X("/SiteInfo/Site/@Name|/SiteInfo/Site/@Type")));
  AutoDelete<DynamicContext> context (query->createDynamicContext());
  Sequence seq = context->resolveDocument(X(siteInfoFile.string().c_str()));

  if (!seq.isEmpty() && seq.first()->isNode()) {
    context->setContextItem(seq.first());
    context->setContextPosition(1);
    context->setContextSize(1);
  }

  Result result = query->execute(context);

  Item::Ptr item;
  while (item = result->next(context)) {
    cout << UTF8(item->asString(context)) << endl;
  }

  return 0;
}
