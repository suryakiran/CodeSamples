#include <Python.h>
#include <boost/python.hpp>
#include <iostream>
#include "first.hpp"

BOOST_PYTHON_MODULE(modfirst)
{
    namespace python = boost::python;
    python::def("greet", greet);
}
