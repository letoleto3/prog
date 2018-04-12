#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <math.h>
#include "head.h"

#if !RESIDUAL
static
double f1 (double x, double t)
{
  (void) x;
  (void) t;
  return - cos (M_PI * x / 2);
}
#endif

static
double u_0 (double x, double)
{
  return 0.9 * (1 - x * x);
}

#if RESIDUAL
static
double f1 (double x, double t)
{
  (void) x;
  (void) t;
  return -1.8 + u_0 (x, t) * u_0 (x, t) * u_0 (x, t);
}
#endif
#endif // FUNCTIONS_H
