#ifndef SV2Obj_hxx_INCLUDED
#define SV2Obj_hxx_INCLUDED

template <class TargetType>
class sv_object_cast
{
  public:
    sv_object_cast (SV* p_perlSv)
      : m_sv(p_perlSv), m_target(0)
    {
    }

    TargetType* operator() ()
    {
      if (sv_isobject(m_sv) && (SvTYPE(SvRV(m_sv)) == SVt_PVMG)) {
        m_target = (TargetType *)SvIV((SV*)SvRV(m_sv));
      }

      return m_target;
    }

  private:
    SV* m_sv;
    TargetType* m_target;
};

#endif
