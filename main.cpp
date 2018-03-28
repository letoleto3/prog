#include <time.h>
#include "head.h"

void my_sleep (double c)
{
  double t0, t = 0;
  t0 = clock ();
  while (t < c)
    {
      t = (clock () - t0) / CLOCKS_PER_SEC;
    }
}

int MAX_M = 100;
int MAX_N = 100;

int main (int argc, char *argv[])
{
  (void) argc;
  (void) argv;
  int it_t;

  if (argc == 3)
    {
      if ((MAX_M = atoi (argv[1])) <= 0 || (MAX_N = atoi (argv[2])) <= 0)
        {
          printf ("Error: Cannot read [n] or [m]\n");
          return 1;
        }
    }
  else
    {
      printf ("Default [n] and [m]\n");
    }
  task_parametrs p_g;
  init_task (&p_g);

  scheme_parametrs p_s;
  one_step (&p_g, &p_s, 1);
  double x, t;
  double h = p_s.h;
  double tau = p_s.tau;
  int N = p_s.N, M = p_s.M;
  int cnt = M + 1;
  double *u = new double [cnt];
  double *workspace = new double [6 * cnt];
  double *val = new double [cnt];

  int res;
  (void) res;

  FILE *fp_u;
  const char *filename_u = "data_u.txt";
  const char *filename_com = "gnuplot.txt";

  for (int i = 0; i < 6 * cnt; i++)
    {
      workspace[i] = 0;
    }

  init_arrays (&p_g, &p_s, u);
  int i;
#if DRAW3D
  fp_u = fopen (filename_u, "w");

  for (i = 0, x = 0; i <= M; i++, x += h)
    {
      fprintf (fp_u, "%e ", u[i]);
    }
  fprintf (fp_u, "\n");
#endif

  for (it_t = 1, t = tau; it_t <= N; it_t++, t += tau)
    {
      res = scheme (&p_g, &p_s, u, workspace, it_t);
#if DRAW3D
      for (i = 0, x = 0; i <= M; i++, x += h)
        {
          fprintf (fp_u, "%e ", u[i]);
        }
      fprintf (fp_u, "\n");
#else
      fp_u = fopen (filename_u, "w");
      fprintf (fp_u, "X T Z\n");
      for (i = 0, x = 0; i <= M; i++, x += h)
        {
          fprintf (fp_u, "%e %e %e\n", x, t, u[i]);
        }
      fprintf (fp_u, "\n");
      fclose (fp_u);
#if COS
      draw ("u-cos", filename_com, it_t);
#else
      draw ("u", filename_com, it_t);
#endif
#endif
    }

#if DRAW3D
  fprintf (fp_u, "\n");
  fclose (fp_u);
#if COS
  draw ("u-cos", filename_com, it_t);
#else
  draw ("u", filename_com, it_t);
#endif
  my_sleep (1e-3);
#endif

  (void) N;
  delete [] u;
  delete [] workspace;
  delete [] val;

  return 0;
}

