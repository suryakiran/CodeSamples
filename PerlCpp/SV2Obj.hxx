#ifndef SV2Obj_hxx_INCLUDED
#define SV2Obj_hxx_INCLUDED

#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/add_pointer.hpp>

template <class TargetType>
class sv_object_cast
{
  typedef typename boost::remove_pointer<TargetType>::type target_type;
  typedef typename boost::add_pointer<target_type>::type target_pointer;

  public:
    sv_object_cast (SV* p_perlSv)
      : m_sv(p_perlSv), m_target(0)
    {
    }

    target_pointer operator() ()
    {
      if (sv_isobject(m_sv) && (SvTYPE(SvRV(m_sv)) == SVt_PVMG)) {
        m_target = reinterpret_cast<target_pointer>(SvIV((SV*)SvRV(m_sv)));
      }

      return m_target;
    }

  private:
    SV* m_sv;
    target_pointer m_target;
};

#endif
