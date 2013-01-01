#ifndef LineEdit_hxx_INCLUDED
#define LineEdit_hxx_INCLUDED 1

#include <QtGui/QLineEdit>
#include <FocusItem.hxx>

class LineEdit : public QLineEdit, public FocusItem
{
  Q_OBJECT

  public:
    LineEdit(QWidget* parent)
      :QLineEdit(parent)
    {
      setFocusPolicy(Qt::StrongFocus);
    }
};


#endif
