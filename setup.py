from setuptools import setup

from pybind11.setup_helpers import Pybind11Extension, build_ext

__version__ = "0.0.1"

# Pybind11 extension
ext_modules = [
    Pybind11Extension(
        "python_example",
        ["python/bindings.cpp"],
        # Example: passing in the version to the compiled code
        define_macros=[("VERSION_INFO", __version__)],
    ),
]

setup(
    name="physics",
    version=__version__,
    author="Jordan Hayes",
    author_email="jordanhayes98@gmail.com",
    url="https://github.com/hayesHowYaDoin/physics_backend",
    description="",
    long_description="Backend for use in physics simulations ",
    ext_modules=ext_modules,
    install_requires=["pybind11~=2.6.1"],
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
