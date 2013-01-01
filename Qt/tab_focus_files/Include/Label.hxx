#ifndef Label_hxx_INCLUDED
#define Label_hxx_INCLUDED 1

#include <QtGui/QLabel>
#include <FocusItem.hxx>

class Label : public QLabel, public FocusItem
{
  Q_OBJECT

  public:
    Label(QWidget* parent)
      :QLabel(parent)
    {
    }
};


#endif
