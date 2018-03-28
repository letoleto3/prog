#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <math.h>
#include "head.h"

static
double f1 (double x, double t)
{
  (void) x;
  (void) t;
  return - cos (M_PI * x / 2);
}

static
double u_0 (double x, double)
{
  return 0.9 * (1 - x * x);
}

#endif // FUNCTIONS_H
