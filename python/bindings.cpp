// #include <pybind11/pybind11.h>
// #include <pybind11/functional.h>
// #include <pybind11/stl.h>
// #include <units.h>

// #include "physics_backend/euler.hpp"

// namespace py = pybind11;

// PYBIND11_MODULE(physics_backend, m) {
//     m.def("euler_factory", &physics_backend::eulerFactory);
//     py::class_<physics_backend::EulerParticle>(m, "EulerParticle")
//         .def_readonly("mass", &physics_backend::EulerParticle::mass)
//         .def_readonly("position", &physics_backend::EulerParticle::position)
//         .def_readonly("velocity", &physics_backend::EulerParticle::velocity)
//         .def_readonly("forces", &physics_backend::EulerParticle::forces);
// }
