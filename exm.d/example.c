/* -------------------------------------------------------------------------- *
 *                                                                            *
 * This file is part of the C language interface to ZVODE by Simon Euchner.   *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 *                                                                            *
 * LICENSE: GPL-3.0                                                           *
 *                                                                            *
 * IMPORTANT: THIS IS FREE SOFTWARE WITHOUT ANY WARRANTY. THE USER IS FREE TO *
 *            MODIFY AND REDISTRIBUTE THIS SOFTWARE UNDER THE TERMS OF THE    *
 *            LICENSE LISTED ABOVE PUBLISHED BY THE FREE SOFTWARE FOUNDATION. *
 *            THE PUBLISHER, SIMON EUCHNER, IS NOT RESPONSIBLE FOR ANY        *
 *            NEGATIVE EFFECTS THIS SOFTWARE MAY CAUSE.                       *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 *                                                                            *
 * Example code showing how to call the integrator from within a C program.   *
 *                                                                            *
 * We will solve the simple oscillator system                                 *
 *                                                                            *
 *     d2x/dt2 = -x ;   x(0) = 1 ;   dx/dt(0) = 0 .                           *
 *                                                                            *
 * We set x[0] = x and x[1] = dx/dt such that we obtain the system            *
 *                                                                            *
 *     dx[0]/dt = x[1]                                                        *
 *     dx[1]/dt = -alpha * n * x[0] ,                                         *
 *                                                                            *
 * where alpha is a positive number and n a positive integer.                 *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#include "../cif.d/zvodeC.h"


static field F;
static void ptsr(ZVODE_data *);


// Format for printing
const char fmt[] = "%1.2f    %+1.2f%+1.2f*I    %+1.2f%+1.2f*I\n";


// Main
int main(int argc, char **argv)
{
    (void)argc; (void)argv;

    // Initialize integrator
    int              neq  = 2       ; // Number of equations
    double           rtol = 1.e-10  ; // Relative tolerance
    double           atol = 1.e-10  ; // Absolute tolerance
    double complex x[neq]           ; // Vector at each time (will be updated)
    double             t0 = 0.      ; // Initial time
    double              t = t0      ; // Time (will be updated)
    double           tmax = 8.      ; // Final time
    double             dt =  .5     ; // Time step
    x[0]                  = 1.+I*0. ; // Position 1.
    x[1]                  = 0.+I*0. ; // Velocity 0.
    double          alpha =  .1     ; // Parameter alpha
    int                 n = 3       ; // Parameter n
    double        rpar[1]           ;
    int           ipar[1]           ;
                  rpar[0] = alpha   ;
                  ipar[0] = n       ;
    char              mf  = 'A'     ; // System not stiff -> use Adams
    ZVODE_data *data = ZVODE_init(neq, mf, &F, rtol, atol, &t, x, rpar, ipar);

    // Integration
    printf("%s\n", "TIME    X(T)            DX/DT(T)                \n");
    ptsr(data);
    while (*data->t < tmax-dt*.01) {
        ZVODE_step(data, dt);
        ptsr(data);
    }
    printf("%c", '\n');

    // Clean up
    ZVODE_clean(data);

    return 0;
}

// Vector field
static void F(int *neq,
              double *t,
              double complex *x,
              double complex *xdot,
              double *rpar,
              int *ipar) {
    (void)neq; (void)t; (void)rpar; (void)ipar;
    xdot[0] = (+1.+I*0.)*x[1];
    xdot[1] = rpar[0] * (double complex)ipar[0] * (-1.+I*0.)*x[0];
}

// Print time step result
static void ptsr(ZVODE_data *data) {
    printf(fmt,
           *data->t,
           creal(data->x[0]),
           cimag(data->x[0]),
           creal(data->x[1]),
           cimag(data->x[1]));
}
