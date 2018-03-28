#include "head.h"

double norm_C_h  (double *arr, int n, double h)
{
  (void) h;
  double max = fabs (arr[0]);
  for (int idx = 1; idx < n; idx++)
    {
      double val = fabs (arr[idx]);
      if (val > max)
        max = val;
    }
  return max;
}

double norm_L2_h (double *arr, int n, double h)
{
  double sum = 0;
  for (int idx = 0; idx < n; idx++)
    {
      sum += arr[idx] * arr[idx];
    }
  sum *= h;
  sum = sqrt (sum);
  return sum;
}

double norm2_C_h  (double *x, double *y, int n, double h)
{
  (void) h;
  double max = fabs (x[0] - y[0]);
  for (int idx = 1; idx < n; idx++)
    {
      double val = fabs (x[idx] - y[idx]);
      if (val > max)
        max = val;
    }
  return max;
}

double norm2_L2_h (double *x, double *y, int n, double h)
{
  double sum = 0;
  for (int idx = 0; idx < n; idx++)
    {
      sum += (y[idx] - x[idx]) * (y[idx] - x[idx]);
    }
  sum *= h;
  sum = sqrt (sum);
  return sum;
}

double norm2_21_h (double *x, double *y, int n, double h)
{
  double res, part, prev, cur;
  part = norm2_L2_h (x, y, n, h);
  res = part * part;

  part = 0;
  prev = x[0] - y[0];
  for (int idx = 1; idx < n; idx++)
    {
      cur = x[idx] - y[idx];
      part += (cur - prev) * (cur - prev);
      prev = cur;
    }

  part /= h;

  res += part;
  res = sqrt (res);

  return res;
}

