/* -------------------------------------------------------------------------- *
 *                                                                            *
 * This file is part of the application *calendar* by Simon Euchner.          *
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


#ifndef ZVODE_H
#define ZVODE_H

#include <stdlib.h>
#include <stdio.h>
#include <complex.h>

// Type for vector field
typedef void (field)(int *,
                   double *,
                   double complex *,
                   double complex *,
                   double *,
                   int *);

// ZVODE subroutine from *../lib.d/zvode.so*
extern void zvode_(field *,
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

// Data for integration process
typedef struct _ZVODE_data {
    field *F;
    double *t;
    double complex *x;
    int mf;
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
    double *rpar;
    int *ipar;
} ZVODE_data;

ZVODE_data *ZVODE_init(int,
                       int,
                       field *,
                       double,
                       double,
                       double *,
                       double complex *,
                       double *,
                       int *);
void ZVODE_step(ZVODE_data *, double);
void ZVODE_clean(ZVODE_data *);

#endif
