#ifndef SearchWidget_hxx_INCLUDED
#define SearchWidget_hxx_INCLUDED

#include <ui_SearchWidget.h>
#include <QObject>
#include <std.hxx>
#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

class SearchWidget : public QWidget, public Ui::SearchWidget
{
  Q_OBJECT

public:
  SearchWidget(QWidget* parent);

private:
  QNetworkAccessManager* m_qnam;
  QNetworkProxy m_proxy;
  QNetworkRequest m_request;
  QUrl m_url;
  QNetworkReply* m_reply;
                                
private Q_SLOTS:
  void initiateSearch();
  void httpFinished();
  void httpRead();
  void httpError(QNetworkReply::NetworkError);
};

#endif
