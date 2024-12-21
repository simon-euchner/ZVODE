This is an implementation of the ADAMS and BDF multistep ODE integrator. Code is
taken from https://netlib.org and only nessesary code is copied from there. This
implementation is stand-alone and ready to use. The integrator is implemented in
FORTRAN, fixed form.

Table of contents.

    isr.d    : Directory where FORTRAN source code is stored for the integrator
    obj.d    : Object code
    lib.d    : Place for shared library
    cif.d    : C interface source code
    exm.d    : Example call to integrator from C
    bin.d    : Resulting binary from example in C
    Makefile : Creates shared library and C interface

Usage.

    For usage directly in FOTRAN and general information, please refere to the
    file *isr.d/zvode.f*.

    For the C interface, an example is provided in *exm.d*.

Installation.

    To build the C interface, please run *make* within this directory.
    For the example, navigate to *exm.d* and run *make*
