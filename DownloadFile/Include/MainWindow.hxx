#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX 1

#include <QtCore/QDateTime>
#include <QtCore/QPointer>
#include <QtCore/QSignalMapper>
#include <QtCore/QTimer>

#include <QtGui/QStackedLayout>
#include <QtGui/QProgressBar>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QSystemTrayIcon>
#include <QtGui/QKeyEvent>

#include <ui_MainWindow.h>
#include <boost/shared_ptr.hpp>	

#include <PropertyTree.hxx>

using boost::shared_ptr ;

#include <set>
#include <string>
#include <map>
using namespace std ;

class QFileDialog ;

DERIVE_FROM_PROPERTY_TREE(DownloadProperties, "DownloadFileConfiguration") ;
DECLARE_PROPERTY_TREE_TEMPLATE_FUNCTIONS(DownloadProperties, QString) ;

class MainWindow : public QMainWindow, private Ui::MainWindow, public DownloadProperties
{
	Q_OBJECT

	typedef pair<string, string> StringPair ;
	public:
		MainWindow (QWidget* p_parent = 0) ;

	private:
		void connectSignals      (void) ;
		void saveConfiguration   (void) ;
		void showConfigurations  (void) ;
		void updateDownloadStatus(bool p_success) ;
		void updateDetails       (const pt::ptree&);
		vector<StringPair> getFormData (void) ;

	private Q_SLOTS:
		QTreeWidgetItem* addFormField (void) ;
		void removeFormField (void) ;
		void selectFile (void) ;
		void downloadFile (void) ;
		void loadConfiguration   (const QString& p_conf) ;

	private:
		QFileDialog *m_fileDlg ;
		string m_configurationFile ;
} ;

#endif
