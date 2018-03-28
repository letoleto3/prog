#include "head.h"

int solve_tridiag_matrix (double *a, double *b, double *x, double *workspace, int n)
{
  int i, idx;
  double d;
  double *alpha = workspace;
  double *betta = alpha + n;

  if (fabs (a[1]) < EPS)
    return -1;
  alpha[1] = - a[2] / a[1];
  betta[1] =   b[0] / a[1];

  for (i = 1, idx = 3; i < n - 1; i++, idx += 3)
    {
      d = a[idx] * alpha[i];
      d += a[idx + 1];
      if (fabs (d) < EPS)
        return -1;
      alpha[i + 1] = - a[idx + 2] / d;
      betta[i + 1] = (b[i] - a[idx] * betta[i]) / d;
    }
  d = a[idx] * alpha[i] + a[idx + 1];
  if (fabs (d) < EPS)
    return -1;
  x[i] = (b[i] - a[idx] * betta[i]) / d;

  for (i = n - 2; i >= 0; i--)
    {
      x[i] = alpha[i + 1] * x[i + 1] + betta[i + 1];
    }
  return 0;
}

void print_tridiag_matrix (double *array, int size)
{
  int ptr = 3;
  fprintf (stdout, "%f %f ", array[1], array[2]);
  for (int idx2 = 2; idx2 < size; idx2++)
    fprintf (stdout, "%f ", 0.);
  fprintf (stdout, "\n");

  for (int idx1 = 1, ptr = 3; idx1 < size - 1; idx1++, ptr += 3)
    {
      for (int idx2 = 0; idx2 < idx1 - 1; idx2++)
        fprintf (stdout, "%f ", 0.);

      fprintf (stdout, "%f ", array[ptr]);
      fprintf (stdout, "%f ", array[ptr + 1]);
      fprintf (stdout, "%f ", array[ptr + 2]);

      for (int idx2 = idx1 + 2; idx2 < size; idx2++)
        fprintf (stdout, "%f ", 0.);

      fprintf (stdout, "\n");
    }

  for (int idx2 = 0; idx2 < size - 2; idx2++)
    fprintf (stdout, "%f ", 0.);

  fprintf (stdout, "%f %f ", array[ptr], array[ptr + 1]);
  fprintf (stdout, "\n");
}

void print_matrix (double *array, int heignt, int width)
{
  for (int idx_row = 0; idx_row < heignt; idx_row++)
    {
      for (int idx_row = 0; idx_row < width; idx_row++)
        fprintf (stdout, "%f ", array[idx_row * width + idx_row]);
      fprintf (stdout, "\n");
    }
}

void print_vector (double *vector, int size)
{
  for (int idx = 0; idx < size; idx++)
    fprintf (stdout, "%f\n", vector[idx]);
}

void product (double *a, double *b, double *x, int n)
{
  double c;
  x[0] = a[1] * b[0] + a[2] * b[1];
  for (int i = 1; i < n - 1; i++)
    {
      c = 0;
      c += a[3 * i]     * b[i - 1];
      c += a[3 * i + 1] * b[i];
      c += a[3 * i + 2] * b[i + 1];
      x[i] = c;
    }
  x[n - 1] = a[3 * n - 3] * b[n - 2] + a[3 * n - 2] * b[n - 1];
}
