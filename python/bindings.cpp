#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include "usecases/step.hpp"

namespace py = pybind11;

int add(int i, int j) 
{
    return i + j;
}

PYBIND11_MODULE(physics, m) {
    m.def("step", &add, "Returns an updated range of particles");
}
