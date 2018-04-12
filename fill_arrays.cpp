#include "head.h"

void fill_matrix_u (task_parametrs *p_g,
                    scheme_parametrs *p_s,
                    double *arr_u
                    )
{
  (void) p_g;
  int M = p_s->M;
  int m, i;
  double h = p_s->h;
  double tau = p_s->tau;
  double gamma = tau / h;

  arr_u[0] = arr_u[2] = arr_u[3 * M] = arr_u[3 * M + 2] = 0;
  arr_u[1] = -1;
  arr_u[2] = 1;
  arr_u[3 * M + 1] = 1;

  for (m = 1, i = 3; m < M; m++, i += 3)
    {
      arr_u[i]     = gamma / h;
      arr_u[i + 1] = -1. - 2. * gamma / h;
      arr_u[i + 2] = gamma / h;
    }
}

void fill_rhs_u (task_parametrs *p_g,
                 scheme_parametrs *p_s,
                 double *vect,
                 double *u,
                 int it_t)
{
  (void) p_g;
  (void) it_t;
  int M = p_s->M;
  int m;
  double h = p_s->h;
  double tau = p_s->tau;

  double x = h;
  double (*f1)(double, double) = p_g->f1;
  (void) f1;
  vect[0] = 0;//[0];
  vect[M] = 0;

  // m = 1 ... M - 1
  for (m = 1, x = h; m < M; m++, x += h)
    {
      vect[m] = -u[m]
          - tau * u[m] * u[m] * u[m]
#if COS || RESIDUAL
          + tau * f1 (m * h, tau * it_t);
#else
          ;
#endif
    }
}

void init_arrays (task_parametrs *p_g,
                  scheme_parametrs *p_s,
                  double *u)
{
  double (*f_u)(double, double) = p_g->u_0;
  int M = p_s->M;
  double h = p_s->h;
  u[0]   = f_u (0., 0.);
  for (int i = 1; i <= M; i++)
   {
    u[i] = f_u (i * h, 0.);
   }
}
