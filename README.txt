o ---------------------------------------------------------------------------- o
| Interface for the ZVODE ODE integrator for the C programming language        |
|                                                                              |
| This program provides a conveniant interface to call the ZVODE ODE           |
| integrator program from within C. ZVODE is written in FORTRAN and the source |
| code is taken from --- https://netlib.org/ode/ ---. The interface is created |
| by Simon Euchner --- https://github.org/simon-euchner ---                    |
|                                                                              |
| Please note that I did not create the interface to give full configurability |
| offered by the FORTRAN code, becuase this way it is more simple to use in C  |
| and I personally do not make use of the full functionality. Hence, this      |
| 'sacrafice' is intended.                                                     |
o ---------------------------------------------------------------------------- o


LICENSE NOTICE.

    LICENSES: GPL-3.0

    IMPORTANT: THIS IS FREE SOFTWARE WITHOUT ANY WARRANTY. THE USER IS FREE TO
               MODIFY AND REDISTRIBUTE THIS SOFTWARE UNDER THE TERMS OF THE
               LICENSE LISTED ABOVE PUBLISHED BY THE FREE SOFTWARE FOUNDATION.
               THE PUBLISHER, SIMON EUCHNER, IS NOT RESPONSIBLE FOR ANY NEGATIVE
               EFFECTS THIS SOFTWARE MAY CAUSE.


Contents.

    isr.d    : Directory for FORTRAN source code
    obj.d    : Object code
    lib.d    : Place for shared library
    cif.d    : Source code of C interface
    exm.d    : Example call to integrator from within C
    bin.d    : Resulting binary from example
    Makefile : Create shared library and C interface


Branches.

    main: Main branch, from which releases are taken
    curr: Branch to work on


Installation instructions.

    Download the latest release on this repository.

    Step 1. Make sure you have *cmake* installed to run the Makefile

    Step 2. Run the Makefile

    Step 3. OPTIONAL Build the example and run it by running the Makefile in
            *exm.d*.

    Step 4. If you plan on using this library regularly, it may be a good idea
            to place it in one of the default location your compiler is looking
            for shared ibraries.
