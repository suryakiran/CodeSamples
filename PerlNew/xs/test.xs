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

#include <Example.h>

MODULE = Example  PACKAGE = Example

INCLUDE_COMMAND: $^X -MExtUtils::XSpp::Cmd -e xspp -- --typemap=test.typemap test.xsp
