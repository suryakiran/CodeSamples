#include <SearchWidget.hxx>
#include <QFile>
#include <iostream>
using namespace std;

SearchWidget::SearchWidget(QWidget* parent)
  :QWidget(parent)
{
  setupUi(this);
  m_qnam = new QNetworkAccessManager(this);
  m_proxy.setPort(3128);
  m_proxy.setHostName("proxysg.ddu-india.com");
  m_proxy.setType(QNetworkProxy::HttpCachingProxy);
  m_proxy.setPassword("siri@1429_ky22");
  m_proxy.setUser("sgullapal");
  QNetworkProxy::setApplicationProxy(m_proxy);
  connect(m_close, SIGNAL(clicked()), qApp, SLOT(quit()));
  connect(m_search, SIGNAL(clicked()), this, SLOT(initiateSearch()));
  m_url.setUrl("http://isbndb.com/api/books.xml");
  m_url.addQueryItem("access_key", "ZB4GTWMM");
  m_url.addQueryItem("index1", "isbn");
  m_url.addQueryItem("value1", "9780123820105");
}

void
SearchWidget::initiateSearch()
{
  QFile *file = new QFile("test.xml", this);
  file->open(QIODevice::WriteOnly);
  m_request.setUrl(m_url);
  m_reply = m_qnam->post(m_request, file);

  connect(m_reply, SIGNAL(finished()), this, SLOT(httpFinished()));
  connect(m_reply, SIGNAL(readyRead()), this, SLOT(httpRead()));
  connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(httpError(QNetworkReply::NetworkError)));
  
  file->close();
}

void
SearchWidget::httpFinished()
{
  QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
  cout << "Finished" << endl;
}

void
SearchWidget::httpRead()
{
  QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
  cout << "read" << endl;
}

void
SearchWidget::httpError(QNetworkReply::NetworkError error)
{
  QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
  cout << "Error: " << error << endl;
}
