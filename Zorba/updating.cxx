#include <iostream>
#include <iostream>
#include <sstream>
using namespace std;

#include <zorba/zorba.h>
#include <zorba/serializer.h>
#include <zorba/singleton_item_sequence.h>
#include <zorba/store_manager.h>
#include <zorba/zorba_exception.h>
using namespace zorba;

int main (void)
{
  void* store = zorba::StoreManager::getStore();
  Zorba* zorba = Zorba::getInstance(store);

  ostringstream oss;
  oss 
    << "import module namespace file = 'http://expath.org/ns/file';\n"
    << "import schema namespace output = 'http://www.w3.org/2010/xslt-xquery-serialization';\n"
    << "\n"
    << "declare %private variable $serParamXml :=\n"
    << "  <output:serialization-parameters>\n"
    << "    <output:method value='xml'/>\n"
    << "    <output:indent value='yes'/>\n"
    << "    <output:omit-xml-declaration value='no'/>\n"
    << "  </output:serialization-parameters>;\n"
    << "\n"
    << "declare variable $context external;\n"
    << "declare variable $genreName external;\n"
    << "insert node <Genre>{$genreName}</Genre> into doc($context)/Config/Genres;\n"
    << "file:write ($context, doc($context), $serParamXml)"
    ;

  try
  {
    XQuery_t query = zorba->compileQuery(oss.str());

    DynamicContext* dctx = query->getDynamicContext();
    dctx->setVariable ("context", zorba->getItemFactory()->createString 
        ("/home/suki/Projects/SourceArea/mp3db/Share/Data/Mp3Config.xml"));
    dctx->setVariable ("genreName", zorba->getItemFactory()->createString ("New Age"));

    if( query->isUpdating() )
    {
      query->execute();
    }
    else
    {
      Iterator_t iter = query->iterator();
      iter->open();
      Item item;
      while (iter->next(item));
      //{
    //    cout << item.getStringValue() << endl;
      //}
      iter->close();
    }

    query->close();
  }
  catch( ZorbaException& e )
  {
    std::cerr << "exception thrown: " << e.what() << std::endl;
  }

  zorba->shutdown();
  StoreManager::shutdownStore(store);
  return 0;
}
