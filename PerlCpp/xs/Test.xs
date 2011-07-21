#include <iostream>
#include <string>

#include <Test.hxx>
#include <boost/property_tree/ptree.hpp>
using namespace boost::property_tree;

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

#ifdef WINDOWS
#undef XS
#ifndef XS
#  define XS(name) extern "C" DLLTest XSPROTO(name)
#endif
#endif

#include <Derived.h>

MODULE = Test

INCLUDE_COMMAND: $^X -MExtUtils::XSpp::Cmd -e xspp -- -t perlcpp.tsp Base.xsp
INCLUDE_COMMAND: $^X -MExtUtils::XSpp::Cmd -e xspp -- -t perlcpp.tsp Derived.xsp
INCLUDE_COMMAND: $^X -MExtUtils::XSpp::Cmd -e xspp -- -t perlcpp.tsp Ptree.xsp
