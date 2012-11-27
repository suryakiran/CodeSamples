#ifndef TabWidget_hpp_INCLUDED
#define TabWidget_hpp_INCLUDED

#include <ui_TabWidget.h>
#include <QObject>
#include <boost/variant.hpp>
#include <std.hxx>

typedef char* charp;

class TabWidget : public QWidget, public Ui::TabWidget
{
  Q_OBJECT

public:
  TabWidget(QWidget* parent = 0);

private:
  void loadDefaults();

public Q_SLOTS:
  void itemSelectionChanged(const QModelIndex& cur, const QModelIndex& prev);
  void saveChanges();
  void loadChanges();

  protected:
  virtual void showEvent (QShowEvent* event);

public:
  typedef boost::variant<
    int,
    bool,
    QString
      > Value;

  enum Settings {
    CheckLeft = 0,
    CheckRight,
    ComboLeft,
    ComboRight,
    SliderLeft,
    SliderRight,
    Combo,
    ComboEdit
  };

  DEFINE_MAP(Settings, Value, SettingsMap);
  SettingsMap mMap;
};

#endif
