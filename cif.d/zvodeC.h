/* -------------------------------------------------------------------------- *
 * C interface to the ZVODE ODE integrator code                               *
 * I have decided not to allow the Jacobian as an argument as it is only      *
 * needed in the stiff case, which I usually do not need.                     *
 * -------------------------------------------------------------------------- */

#ifndef ZVODE_H
#define ZVODE_H

#include <stdlib.h>
#include <stdio.h>
#include <complex.h>

// ZVODE subroutine from *../lib.d/zvode.so*
extern void zvode_(void (*)(int *,
                            double *,
                            double complex *,
                            double complex *,
                            double *,
                            int *),
                   int *,
                   double complex *,
                   double *,
                   double *,
                   int *,
                   double *,
                   double *,
                   int *,
                   int *,
                   int *,
                   double complex *,
                   int *,
                   double *,
                   int *,
                   int *,
                   int *,
                   void *,
                   int *,
                   double *,
                   int *);

// Data for the integrator
typedef struct _ZVODE_data {
    void (*F)(int *,
              double *,
              double complex *,
              double complex *,
              double *,
              int *);
    int neq;
    int itask;
    int itol;
    double rtol;
    double atol;
    int istate;
    int iopt;
    double complex *zwork;
    int lzw;
    double *rwork;
    int lrw;
    int *iwork;
    int liw;
    int mf;
    int *IPAR;
    double *RPAR;
} ZVODE_data;

ZVODE_data *ZVODE_init(int,
                       int,
                       void (*)(int *,
                                double *,
                                double complex *,
                                double complex *,
                                double *,
                                int *),
                       double,
                       double);
void ZVODE_step(ZVODE_data *, double *, double, double complex *);
void ZVODE_clean(ZVODE_data *);

#endif
