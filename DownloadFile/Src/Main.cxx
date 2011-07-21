#include <Poco/Foundation.h>
#include <Poco/Process.h>
#ifdef WINDOWS
#include <Poco/Util/WinRegistryKey.h>
#endif
#include <Poco/Debugger.h>

#include <MainWindow.hxx>

#include <vector>
#include <string>
#include <fstream>
using namespace std ;

int main (int argc, char** argv)
{
	QApplication app (argc, argv) ;

	MainWindow *mainw = new MainWindow ;
	mainw->show() ;
	return app.exec() ;
}
