#include "MainWindow.hxx"
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
using boost::lexical_cast ;
using boost::format ;
using namespace boost::algorithm ;

#include <iostream> 
#include <iomanip>
using namespace std ; 

#include <QtGui/QFileDialog>
#include <DownloadFile.hxx>

template <> void
DownloadProperties :: setValue (const std::string& p_key, const QString& p_value)
{ setValue (p_key, p_value.toStdString()) ; }

template <> QString
DownloadProperties :: getValue (const std::string& p_key) const
{ return QString (getValue<string>(p_key).c_str()) ; }

template <> QString
DownloadProperties :: getValue (const std::string& p_key, const QString& p_defaultValue) const
{
	return QString (getValue<string>(p_key, p_defaultValue.toStdString()).c_str()) ;
}

MainWindow :: MainWindow (QWidget* p_parent)
	: QMainWindow (p_parent)
{
	setupUi(this) ;
	QDir::setCurrent (QDir::homePath()) ;
	m_configurationFile = QDir::current().absoluteFilePath ("DownloadConfiguration.xml").toStdString() ;
	m_fileDlg = (QFileDialog*) 0 ;

	connectSignals () ;
	showConfigurations() ;
}

void MainWindow :: showConfigurations (void)
{
	try
	{
		loadTree (m_configurationFile) ;
		BOOST_FOREACH (const pt::ptree::value_type& v, get_child ("DownloadFileConfiguration"))
			oldConfName->addItem (v.first.c_str()) ;
	}
	catch(std::exception& e)
	{
		cout << e.what() << endl ;
	}
}

void MainWindow :: connectSignals (void)
{
	connect (buttonBox, SIGNAL(rejected()), qApp, SLOT(quit())) ;
	connect (buttonBox, SIGNAL(accepted()), this, SLOT(downloadFile())) ;
	connect (addField, SIGNAL(clicked()), this, SLOT(addFormField())) ;
	connect (removeField, SIGNAL(clicked()), this, SLOT(removeFormField())) ;
	connect (fileSelector, SIGNAL(clicked()), this, SLOT(selectFile())) ;
	connect (oldConfName, SIGNAL(currentIndexChanged(QString)), this, SLOT(loadConfiguration(QString))) ;
}

void MainWindow :: loadConfiguration (const QString& p_conf)
{
	newConfName->clear();
	if (p_conf == "New Configuration") 
		updateDetails(pt::ptree());
	else 
	{
		newConfName->setText (p_conf);
		const pt::ptree& curTree = get_child 
			((format("DownloadFileConfiguration.%1%") % p_conf.toStdString()).str()) ;
		updateDetails(curTree);
	}
}

QTreeWidgetItem* MainWindow :: addFormField (void)
{
	QTreeWidgetItem *item = new QTreeWidgetItem 
		(formDetails, QStringList() << "Field Name" << "Value") ;
	item->setFlags (item->flags() | Qt::ItemIsEditable) ;
	return item ;
}

void MainWindow :: removeFormField (void)
{
	BOOST_FOREACH (QTreeWidgetItem* item, formDetails->selectedItems())
		delete formDetails->takeTopLevelItem (formDetails->indexOfTopLevelItem (item)) ;
}

void MainWindow :: selectFile (void)
{
	if (!m_fileDlg)
	{
		m_fileDlg = new QFileDialog (this, "Save File As...") ;
		m_fileDlg->setViewMode (QFileDialog::Detail) ;
		m_fileDlg->setNameFilter ("HTML Files (*.html *.htm)") ;
		m_fileDlg->setFileMode (QFileDialog::AnyFile) ;
		connect (m_fileDlg, SIGNAL(fileSelected(QString)), saveFile, SLOT(setText(QString))) ;
	}
	QString curFileName (saveFile->text()) ;

	if (!curFileName.isEmpty()) 
	{
		QDir d ;
		do
		{
			curFileName += "/..";
		}while (!d.setCurrent(curFileName));
		m_fileDlg->setDirectory (d);
	}

	m_fileDlg->exec() ;
}

vector<StringPair> MainWindow :: getFormData (void)
{
	vector<StringPair> formData ;

	QTreeWidgetItemIterator iter (formDetails) ;
	while (*iter)
	{
		QTreeWidgetItem* item = *iter ;
		formData.push_back(make_pair(item->text(0).toStdString(), item->text(1).toStdString())) ;
		++iter ;
	}

	return formData ;
}

void MainWindow :: downloadFile (void)
{
	saveConfiguration () ;
	vector<StringPair> formData (getFormData()) ;
	string site (siteAddr->text().trimmed().toStdString()) ;
	string outFile (saveFile->text().trimmed().toStdString()) ;

	if (outFile.empty() || site.empty())
		return ;

	DownloadFile df (site) ;
	df.signal<DownloadFile::Status>().connect (MEM_FUN(MainWindow, updateDownloadStatus, 1)) ;
	df.setOutputFile (outFile) ;
	df.setGetMethod (httpMethod->currentText() == "Get") ;
	BOOST_FOREACH (StringPair sp, formData) 
		df.addPostField (sp.first, sp.second) ;

	df.download() ;
}

void MainWindow :: saveConfiguration (void)
{
	oldConfName->blockSignals(true);
	string oldConf (oldConfName->currentText().trimmed().toStdString()) ;
	string newConfStripped (newConfName->text().trimmed().toStdString()) ;
	if (newConfStripped.empty())
		return ;
	else if(oldConfName->findText(newConfStripped.c_str()) == -1)
		oldConfName->addItem(newConfStripped.c_str());

	string newConf (getKey(newConfStripped));
	get_child ("DownloadFileConfiguration").erase(oldConf) ;
	pt::ptree& newConfTree = put_child (newConf, pt::ptree()) ;

	{
		pt::ptree& curTree = newConfTree.put_child ("FormData", pt::ptree()) ; 
		vector<StringPair> formData (getFormData()) ;
		BOOST_FOREACH (StringPair sp, formData)
			curTree.put (sp.first, sp.second) ;
	}

	newConfTree.put ("Site", siteAddr->text().trimmed().toStdString()) ;
	newConfTree.put ("HTTPMethod", httpMethod->currentText().toStdString()) ;
	newConfTree.put ("OutFile", saveFile->text().trimmed().toStdString()) ;

	printTree (m_configurationFile) ;

	oldConfName->setCurrentIndex(oldConfName->findText(newConfStripped.c_str()));
	oldConfName->blockSignals(false);
}

void MainWindow :: updateDownloadStatus (bool p_success)
{
	if (p_success)
		statusBar()->showMessage ("Download Success", 1000) ;
	else
		statusBar()->showMessage ("Download Failure", 1000) ;
}

void MainWindow :: updateDetails (const pt::ptree& p_tree)
{
	siteAddr->setText(p_tree.get<string>("Site", "").c_str()) ;
	int curIdx (httpMethod->findText(p_tree.get<string>("HTTPMethod", "").c_str()));
	httpMethod->setCurrentIndex ((curIdx == -1) ? 0 : curIdx);
	saveFile->setText(p_tree.get<string>("OutFile","").c_str()) ;

	formDetails->clear() ;
	boost::optional<const pt::ptree&> formData = p_tree.get_child_optional ("FormData") ;
	if (formData)
	{
		BOOST_FOREACH (const pt::ptree::value_type& f, formData.get())
		{
			QTreeWidgetItem* item = addFormField() ;
			item->setText(0, f.first.c_str()) ;
			item->setText(1, f.second.data().c_str()) ;
		}
	}
}
