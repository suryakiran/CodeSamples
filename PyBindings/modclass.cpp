#include <Python.h>
#include <boost/python.hpp>
#include <iostream>
#include "class.hpp"
namespace python = boost::python;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(defargs_overloads, Class::defargs, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(defargs_return_overloads, Class::defargsreturn, 1, 3)

BOOST_PYTHON_MODULE(modclass)
{
    python::return_value_policy<python::return_by_value> returnByValue;
    
    python::class_<Class> ("Class")
        .def("test", &Class::test)
        .def("args", &Class::args, python::args("self", "a", "b"))
        .def("defargs", &Class::defargs, defargs_overloads(python::args("self", "a", "b")))
        .def("defargsreturn", &Class::defargsreturn, defargs_return_overloads(python::args("self", "a", "b", "c")))
        ;
}
