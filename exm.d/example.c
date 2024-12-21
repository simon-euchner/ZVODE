/* -------------------------------------------------------------------------- *
 * Example code showing how to call the integrator from a C program           *
 *                                                                            *
 * We will solve the simple oscillator system                                 *
 *                                                                            *
 *     d2x/dt2 = -x ;   x(0) = 1 ;   dx/dt(0) = 0                             *
 *                                                                            *
 * We set x[0] = x and x[1] = dx/dt such that we obtain the system            *
 *                                                                            *
 *     dx[0]/dt = x[1]                                                        *
 *     dx[1]/dt = -x[0]                                                       *
 * -------------------------------------------------------------------------- */

#include "../cif.d/zvodeC.h"

static void F(int *,
              double *,
              double complex *,
              double complex *,
              double *,
              int *);
static void ptsr(ZVODE_data *, double complex *, double, char *);


int main(int argc, char **argv)
{
    (void)argc; (void)argv;

    // Format for pinting
    printf("%s\n", "TIME    X(T)            DX/DT(T)                \n");
    char fmt[] = "%1.2f    %+1.2f%+1.2f*I    %+1.2f%+1.2f*I\n";

    // Initialize integrator
    int neq = 2; // Number of equations
    int mf = 10; // Method flag (Adams)
    double rtol = 1e-10; // Relative tolerance
    double atol = 1e-10; // Absolute tolerance
    ZVODE_data *data = ZVODE_init(neq, mf, &F, rtol, atol);

    // Integrate from t=0 to t=tmax in steps dt
    double dt = .5;
    double t = 0;
    double tmax = 8;
    double complex x[] = {1.+I*0., 0.+I*0.};
    ptsr(data, x, t, fmt);
    while (t < tmax-dt*.01) {
        ZVODE_step(data, &t, dt, x);
        ptsr(data, x, t, fmt);
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
    xdot[0] = (1.+I*0.)*x[1];
    xdot[1] = (-1.+I*0.)*x[0];
}

// Print time step result
static void ptsr(ZVODE_data *data, double complex *x, double t, char *fmt) {
    printf(fmt,
           t,
           creal(x[0]),
           cimag(x[0]),
           creal(x[1]),
           cimag(x[1]));
}
