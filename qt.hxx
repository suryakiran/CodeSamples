#ifndef QT_HXX
#define QT_HXX

#include <QtGui>

inline ostream& operator<< (ostream& os, const QString& s)
{
  os << s.toStdString();
  return os;
}


#endif
