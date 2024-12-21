/* -------------------------------------------------------------------------- *
 * C-interface to the ZVODE ODE integrator                                    *
 * I have decided not to allow the Jacobian as an argument as it is only      *
 * needed in the stiff case, which I usually do not need.                     *
 * -------------------------------------------------------------------------- */

#include "zvodeC.h"

static void ZVODE_errmessg(int);


// Initialize the system dx/dt = F(x, t)
ZVODE_data *ZVODE_init(int neq, // Number of equations
                       int mf, // 10 for *Adams*, 22 for *BDF* without Jacobian
                       void (*F)(int *,
                                 double *,
                                 double complex *,
                                 double complex *,
                                 double *,
                                 int *),
                       double rtol, // Relative tolerance
                       double atol) { // Absolute tolerance

    // Allocate memory for result
    ZVODE_data *data = (ZVODE_data *)malloc(sizeof(ZVODE_data));

    // Length of zwork
    int n_zwork;
    switch (mf) {
        case 10: n_zwork = 15 * neq; break;
        case 22: n_zwork = (8 + 2 * neq) * neq; break;
        default: printf("Method flag must be 10 or 22\n"); break;
    }

    // Length of iwork
    int n_iwork;
    switch (mf) {
        case 10: n_iwork = 30; break;
        case 22: n_iwork = 30 + neq; break;
        default: break;
    }

    // Method flag
    data->mf = mf;

    // Initialize data for integration
    data->neq     = neq;
    data->itask   = 1;
    data->itol    = 1;
    data->rtol    = rtol;
    data->atol    = atol;
    data->istate  = 1;
    data->iopt    = 0;
    data->zwork   = (double complex *)malloc(sizeof(double complex) * n_zwork);
    data->lzw     = n_zwork;
    data->rwork   = (double *)malloc(sizeof(double) * (20 + neq));
    data->lrw     = 20 + neq;
    data->iwork   = (int *)malloc(sizeof(int) * n_iwork);
    data->liw     = n_iwork;
    data->IPAR    = NULL;
    data->RPAR    = NULL;

    // Hand function pointer to vector field, F
    data->F = F;

    return data;
}

// Do time step; take t, x(t) and overwrite it with t+dt, x(t+dt)
void ZVODE_step(ZVODE_data *data, double *t, double dt, double complex *x) {

    // Call ZVODE from *../lib.d/zvode.so*
    double tout = *t+dt;
    zvode_(data->F,
           &data->neq,
           x,
           t,
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
           data->RPAR,
           data->IPAR);

    // Print errormessage if nessesary
    ZVODE_errmessg(data->istate);
}

// Clean up after integration
void ZVODE_clean(ZVODE_data *data) {
    free(data->zwork);
    free(data->rwork);
    free(data->iwork);
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
