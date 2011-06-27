#ifdef __cplusplus
extern "C" {
#endif

#include <EXTERN.h>
#include <perl.h>
#include <XSUB.h>

#include <ppport.h>

#ifdef __cplusplus
}
#endif

#include <Derived.h>

MODULE = Test

INCLUDE_COMMAND: $^X -MExtUtils::XSpp::Cmd -e xspp -- --typemap=perlcpp.tsp Base.xsp
INCLUDE_COMMAND: $^X -MExtUtils::XSpp::Cmd -e xspp -- --typemap=perlcpp.tsp Derived.xsp