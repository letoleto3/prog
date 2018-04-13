#include "head.h"

extern int MAX_M;
extern int MAX_N;

int scheme (task_parametrs *p_g, scheme_parametrs *p_s, double *u, double *workspace, int it_t)
{
  int M = p_s->M;
  int res = 0;
  double *arr = workspace;
  double *vect = arr + 3 * (M + 1);
  double *work = vect + M + 1;

#if SCHEME || RESIDUAL
  fill_matrix_u (p_g, p_s, arr);
  fill_rhs_u (p_g, p_s, vect, u, it_t);

  res = solve_tridiag_matrix (arr, vect, u, work, M + 1);
  if (res)
    {
      fprintf (stdout, "Cannot solve matrix!\n");
      return res;
    }

  return 0;
#else

  (void) work;
  (void) it_t;
  (void) p_g;
  double h = p_s->h;
  double gamma = p_s->tau / h;
  for (int i = 0; i < M; i++)
    vect[i] = u[i];
  u[M] = 0;
  for (int i = M - 1; i > 0; i--)
    {
      u[i] = vect[i-1] * gamma / h
          + vect[i] * (1. - 2. * gamma / h)
          + vect[i + 1] * gamma / h;
    }
  u[0] = u[1];
  return res;

#endif
}

void draw (const char *parametr, const char *file_name, int it_t, double max)
{
  (void) it_t;
  char path_dest [LEN_BUF];
  FILE *fp;
  fp = fopen (file_name, "w");
  fprintf (fp, "set terminal jpeg size 1024, 768\n");
#if DRAW3D
#if PM3D
#if SCHEME
  fprintf (fp, "set output '%s/pm%dx%d.jpg'\n", parametr, MAX_M, MAX_N);
#else
  fprintf (fp, "set output '%s/non-stab/pm%dx%d.jpg'\n", parametr, MAX_M, MAX_N);
#endif
#else
#if SCHEME
  fprintf (fp, "set output '%s/lines%dx%d.jpg'\n", parametr, MAX_M, MAX_N);
#else
  fprintf (fp, "set output '%s/non-stab/lines%dx%d.jpg'\n", parametr, MAX_M, MAX_N);
#endif
#endif
  fprintf (fp, "set grid\n");
  fprintf (fp, "set xrange [0:%d]\n", MAX_M);
  fprintf (fp, "set yrange [0:%d]\n", MAX_N);
  if (strcmp (parametr, "res"))
    fprintf (fp, "set zrange [0:1.]\n");
  else
    fprintf (fp, "set zrange [0:%e]\n", max);

  fprintf (fp, "set xlabel 'x'\n");
  fprintf (fp, "set ylabel 't'\n");

  fprintf (fp, "set xtics ('' 0, ''1)\n");
  fprintf (fp, "set ytics ('' 0, ''1)\n");
  if (!strcmp (parametr, "res"))
    {
      fprintf (fp, "set ticslevel 0.\n");
      fprintf (fp, "splot 'data_%s.txt' matrix with lines linetype rgb'#FF0000' %c", parametr, '\0');
    }
  else
    {
      fprintf (fp, "set zlabel 'u (x, t)'\n");
      fprintf (fp, "set ticslevel 0.8\n");
      fprintf (fp, "set palette defined (0 \"dark-turquoise\", 1 \"yellow\")\n");
#if PM3D
      fprintf (fp, "splot 'data_%s.txt' matrix with pm3d\n", parametr);
#else
      fprintf (fp, "set pm3d at b\n");
      fprintf (fp, "splot 'data_%s.txt' matrix with lines %c", parametr, '\0');
#endif
    }
#else
#if SCHEME
  fprintf (fp, "set output '%s/u%d.jpg'\n", parametr, it_t);
#else
  fprintf (fp, "set output '%s/non-stab/u%d.jpg'\n", parametr, it_t);
#endif
  fprintf (fp, "set grid x y\n");
  fprintf (fp, "set xrange [0:1]\n");
  fprintf (fp, "set yrange [0:1.]\n");
  fprintf (fp, "plot 'data_u.txt' using 1:3 with lines%c", '\0');
#endif

  fclose (fp);
  sprintf (path_dest, "\"gnuplot\" %s%c\"", file_name,'\0');
  system (path_dest);
}

void calculate_u (task_parametrs *p_g, scheme_parametrs *p_s, double *val_u)
{
  double t = p_g->Segm_T;
  double h = p_s->h;
  double (*f_u)(double, double) = p_g->u_0;
  int M = p_s->M;

  for (int m = 0; m <= M; m++)
    val_u[m] = f_u (m * h, t);
}
