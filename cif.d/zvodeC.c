/* -------------------------------------------------------------------------- *
 *                                                                            *
 * This file is part of the C language interface to ZVODE by Simon Euchner.   *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 *                                                                            *
 * LICENSES: GPL-3.0                                                          *
 *                                                                            *
 * IMPORTANT: THIS IS FREE SOFTWARE WITHOUT ANY WARRANTY. THE USER IS IF FREE *
 *            TO MODIFY AND REDISTRIBUTE THIS SOFTWARE UNDER THE TERMS OF THE *
 *            LICENSE LISTED ABOVE PUBLISHED BY THE FREE SOFTWARE FOUNDATION. *
 *            THE PUBLISHER, SIMON EUCHNER, IS NOT RESPONSIBLE FOR ANY        *
 *            NEGATIVE EFFECTS THIS SOFTWARE MAY CAUSE.                       *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 *                                                                            *
 *  C language interface to the ZVODE ODE integrtor from                      *
 *  --- https://netlib.org/ode ---. This is the main source file to generate  *
 * the shared library *../bin.d/libzvode.so* allowing calls to the FORTRAN    *
 * routines in *zvode.f* from within C.                                       *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#include "zvodeC.h"


static void ZVODE_errmessg(int);


/* Function to initialize an ODE system of the form: dx/dt = F(x, t)          *
 *                                                                            *
 * neq: Number of equations in the system                                     *
 * mf: Method flag, mf='A' (Adams, non-stiff), mf='B' (BDF, stiff)            *
 * rtol: Relative tolernace                                                   *
 * atol: Aboslute tolernace                                                   *
 * t0: Initial time (will be updated upon evolution)                          *
 * x0: Initial vector (will be updated upon evolution)                        */
ZVODE_data *ZVODE_init(int neq,
                       int mf,
                       field *F,
                       double rtol,
                       double atol,
                       double *t0,
                       double complex *x0,
                       double *rpar,
                       int *ipar) {

    // Allocate memory for result
    ZVODE_data *data = (ZVODE_data *)malloc(sizeof(ZVODE_data));

    // Length of zwork and iwork
    int n_zwork, n_iwork;
    switch (mf) {
        case 'A': n_zwork = 15*neq;
                  n_iwork = 30;
                  mf = 10;
                  break;
        case 'B': n_zwork = (8+2*neq)*neq;
                  n_iwork = 30+neq;
                  mf = 22;
                  break;
        default: printf("Method flag must be 'A' or 'B'\n"); break;
    }

    // Method flag
    data->mf = mf;

    // Initialize data for integration
    data->t       = t0;
    data->x       = x0;
    data->neq     = neq;
    data->itask   = 1;
    data->itol    = 1;
    data->rtol    = rtol;
    data->atol    = atol;
    data->istate  = 1;
    data->iopt    = 0;
    data->zwork   = (double complex *)malloc(sizeof(double complex)*n_zwork);
    data->lzw     = n_zwork;
    data->rwork   = (double *)malloc(sizeof(double)*(20+neq));
    data->lrw     = 20+neq;
    data->iwork   = (int *)malloc(sizeof(int)*n_iwork);
    data->liw     = n_iwork;
    data->rpar    = rpar;
    data->ipar    = ipar;

    // Hand function pointer to vector field, F
    data->F = F;

    return data;
}

/* Function to integrate the system ONE time step                             *
 *                                                                            *
 * data: This should be the pointer returned by *ZVODE_init*                  *
 * dt: Time step                                                              *
 *                                                                            *
 * After this call, data->t will be updated to data->t+dt and data->x(t) to   *
 * data->x(t+dt).                                                             */
void ZVODE_step(ZVODE_data *data, double dt) {

    // Call ZVODE from *../lib.d/zvode.so*
    double tout = *data->t+dt;
    zvode_(data->F,
           &data->neq,
           data->x,
           data->t,
           &tout,
           &data->itol,
           &data->rtol,
           &data->atol,
           &data->itask,
           &data->istate,
           &data->iopt,
           data->zwork,
           &data->lzw,
           data->rwork,
           &data->lrw,
           data->iwork,
           &data->liw,
           NULL,
           &data->mf,
           data->rpar,
           data->ipar);

    // Print error message if nessesary
    ZVODE_errmessg(data->istate);
}

// Clean up after integration
void ZVODE_clean(ZVODE_data *data) {
    free(data->zwork);
    free(data->rwork);
    free(data->iwork);
    free(data);
}

// Function printing error messages of zvode
static void ZVODE_errmessg(int istate) {

    // Copy message
    int quit = 0;
    switch (istate) {
        case  2: break;
        case -1: printf("Excess work done on this call. (Perhaps wrong MF.)\n");
                 quit = 1;
                 break;
        case -2: printf("Excess accuracy requested. (Tolerances too small.)\n");
                 quit = 1;
                 break;
        case -3: printf("Illegal input detected. (See printed message.)\n");
                 quit = 1;
                 break;
        case -4: printf("Repeated error test failures. (Check all input.)\n");
                 quit = 1;
                 break;
        case -5: printf("Repeated convergence failures.\n");
                 quit = 1;
                 break;
        case -6: printf("Error weight became zero during problem. (Solution"
                        "component i vanished, and ATOL or ATOL(i) = 0.)\n");
                 quit = 1;
                 break;
        default: break;
    }

    // Exit if nessesary
    if (quit) exit(0);
}
