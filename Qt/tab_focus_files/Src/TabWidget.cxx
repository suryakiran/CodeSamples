#include <TabWidget.hxx>
#include <boost/format.hpp>

namespace {
  struct ValueSetter : public boost::static_visitor<>
  {
    ValueSetter(QObject* obj)
      : mObj(obj)
    {
    }

    void operator()(bool b)
    {
      QCheckBox* check = qobject_cast<QCheckBox*>(mObj);
      if(check) {
        check->setChecked(b);
      } else {
        cout << "Invalid Data Type" << endl;
      }
    }

    void operator()(int i)
    {
      QSlider* slider = qobject_cast<QSlider*>(mObj);
      QComboBox* combo = qobject_cast<QComboBox*> (mObj);
      if(slider) {
        slider->setValue(i);
      } else if (combo) {
        int idx = combo->findText(QString::number(i));
        combo->setCurrentIndex(idx);
      }
    }

    void operator()(const std::string& s)
    {
      stringFun(QString::fromStdString(s));
    }

    void operator()(const charp s)
    {
      stringFun(QString(s));
    }

    void operator()(const QString& s)
    {
      stringFun(s);
    }

    void stringFun(const QString& s)
    {
      QComboBox* combo = qobject_cast<QComboBox*>(mObj);
      if (!combo) {
        return;
      }

      int index = combo->findText(s);
      combo->setCurrentIndex(index);
    }

    private:
      QObject* mObj;
  };

  void setValue (QObject* obj, const TabWidget::Value& val)
  {
    ValueSetter vs(obj);
    boost::apply_visitor(vs, val);
  }

  template <class T>
  void printType(const T& t)
  {
    cout << typeid(t).name() << endl;
  }
}

TabWidget::TabWidget(QWidget* parent)
  :QWidget(parent)
{
  setupUi(this);
  connect(treeWidget->selectionModel(), 
      SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), 
      this, 
      SLOT(itemSelectionChanged(const QModelIndex&, const QModelIndex&)));
  connect(save, SIGNAL(clicked()), this, SLOT(saveChanges()));
  connect(load, SIGNAL(clicked()), this, SLOT(loadChanges()));
  loadDefaults();
}

void
TabWidget::loadDefaults()
{
  mMap[CheckLeft] = false;
  mMap[CheckRight] = true;
  mMap[SliderLeft] = 10;
  mMap[SliderRight] = 90;
  mMap[Combo] = QString("Item 5");
  mMap[ComboEdit] = 5;
}

void
TabWidget::itemSelectionChanged(const QModelIndex& cur, const QModelIndex& prev)
{
  cout << "Number of items: " << treeWidget->model()->rowCount() << endl;
  cout << boost::format("Current: (%1%, %2%), Previous: (%3%, %4%)")
    % cur.row() % cur.column()
    % prev.row() % prev.column()
    << endl;
}

void
TabWidget::saveChanges()
{
  mMap[CheckLeft] = vCheckLeft->isChecked();
  mMap[CheckRight] = vCheckRight->isChecked();
  mMap[Combo] = vCombo->currentText();
  mMap[ComboEdit] = vComboEdit->currentText();
  mMap[SliderLeft] = vSliderLeft->value();
  mMap[SliderRight] = vSliderRight->value();
}

void
TabWidget::loadChanges()
{
  setValue(vCheckLeft, mMap[CheckLeft]);
  setValue(vCheckRight, mMap[CheckRight]);
  setValue(vSliderLeft, mMap[SliderLeft]);
  setValue(vSliderRight, mMap[SliderRight]);
  setValue(vCombo, mMap[Combo]);
  setValue(vComboEdit, mMap[ComboEdit]);
}

void
TabWidget::showEvent(QShowEvent* event)
{
  loadChanges();
  QWidget::showEvent(event);
}
