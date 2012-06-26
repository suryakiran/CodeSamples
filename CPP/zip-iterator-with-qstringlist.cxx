#include "std.hxx"

#include <QtCore/QStringList>
#include <boost/iterator/zip_iterator.hpp>

ostream& operator<< (ostream& os, const QString& q)
{
  os << q.toStdString();
  return os;
}

struct printFunc : public std::unary_function <const boost::tuple <const QString&, const QString&>&, void>
{
  void operator() (const boost::tuple <const QString&, const QString&>& t) const
  {
    cout << t.get<0>() << '\t' << t.get<1>() << endl;
  }
};

int main (void)
{
  QStringList name, company;
  name << "Surya" << "Kiran" << "Gullapalli";
  company << "DreamWorks" << "SKG" ;

  QStringList::iterator nameBeg (name.begin()), nameEnd(name.end());
  QStringList::iterator companyBeg (company.begin()), companyEnd(company.end());

  std::for_each (
      boost::make_zip_iterator (boost::make_tuple (nameBeg, companyBeg)),
      boost::make_zip_iterator (boost::make_tuple (nameEnd, companyEnd)),
      printFunc()
      );
}
