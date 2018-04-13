#include <time.h>
#include "functions.h"

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
  int cnt = (p_s.M + 1) * 8;
  double *u = new double [cnt];
  double *workspace = new double [6 * cnt];
  double *val = new double [cnt];

  int res;
  (void) res;

  FILE *fp_u, *fp_res, *fp_u_res;
  const char *filename_u = "data_u.txt";
  const char *filename_res = "data_res.txt";
  const char *filename_com = "gnuplot.txt";

  for (int i = 0; i < 6 * cnt; i++)
    {
      workspace[i] = 0;
    }
#if RESIDUAL
  FILE *fp_C_u, *fp_L2_u, *fp_21_u,
      *fp;
  fp_C_u  = fopen ("norm_C_u.txt", "w");
  fp_L2_u = fopen ("norm_L2_u.txt", "w");
  fp_21_u = fopen ("norm_21_u.txt", "w");
  print_table_begin (&fp_C_u, "u - V", "C", h);
  print_table_begin (&fp_L2_u, "u - V", "L_2", h);
  print_table_begin (&fp_21_u, "u - V", "v_2^1", h);
  for (int step_tau = 1; step_tau <= 4; step_tau++)
    {
      double norm_C_u [4] = {0, 0, 0, 0};
      double norm_L2_u [4] = {0, 0, 0, 0};
      double norm_21_u [4] = {0, 0, 0, 0};

      for (int step_h = 0; step_h <= 3; step_h++)
        {
          cnt = p_s.M + 1;

          init_arrays (&p_g, &p_s, u);

          printf ("STEP: tau-%d; h-%d\n", step_tau, step_h);

          int N = p_s.N;
          for (it_t = 1; it_t <= N; it_t++)
            {
              res = scheme (&p_g, &p_s, u, workspace, it_t);
              if (res)
                {
                  fprintf (stdout, "Exit programm!\n");
                  delete [] u;
                  delete [] workspace;
                  delete [] val;
                  fclose (fp_C_u);
                  fclose (fp_L2_u);
                  fclose (fp_21_u);
                  fclose (fp);
                  return -1;
                }
            }

          calculate_u (&p_g, &p_s, val);
          norm_C_u[step_h] = norm2_C_h (val, u, cnt, p_s.h);
          norm_L2_u[step_h] = norm2_L2_h (val, u, cnt, p_s.h);
          norm_21_u[step_h] = norm2_21_h (val, u, cnt, p_s.h);
          div_h (&p_s, DEN);
        }
      print_table (&fp_C_u, norm_C_u, &p_s);
      print_table (&fp_L2_u, norm_L2_u, &p_s);
      print_table (&fp_21_u, norm_21_u, &p_s);

      div_tau (&p_s, DEN_TAU);
      set_h (&p_g, &p_s);
    }
  print_table_end (&fp_C_u);
  print_table_end (&fp_L2_u);
  print_table_end (&fp_21_u);

  fp_C_u  = fopen ("norm_C_u.txt", "r");
  fp_L2_u = fopen ("norm_L2_u.txt", "r");
  fp_21_u = fopen ("norm_21_u.txt", "r");
  fp = fopen ("norms.tex", "w");
  begin_print_norms (&fp);
  reprint_table (&fp_C_u, &fp);
  reprint_table (&fp_L2_u, &fp);
  reprint_table (&fp_21_u, &fp);
  end_print_norms (&fp);
  fclose (fp_C_u);
  fclose (fp_L2_u);
  fclose (fp_21_u);
  fclose (fp);
  remove ("norm_C_u.txt");
  remove ("norm_L2_u.txt");
  remove ("norm_21_u.txt");

#endif

  double max = -1;
  init_task (&p_g);
  one_step (&p_g, &p_s, 1);
  h = p_s.h;
  tau = p_s.tau;
  N = p_s.N; M = p_s.M;
  cnt = M + 1;
  for (int i = 0; i < 6 * cnt; i++)
    {
      workspace[i] = 0;
    }

  init_arrays (&p_g, &p_s, u);
  int i;
#if DRAW3D
  fp_u = fopen (filename_u, "w");
  fp_res = fopen (filename_res, "w");
  fp_u_res = fopen ("data_u-res.txt", "w");

  for (i = 0, x = 0; i <= M; i++, x += h)
    {
      fprintf (fp_u, "%e ", u[i]);
      fprintf (fp_u_res, "%e ", u[i]);
      fprintf (fp_res, "0 ");
    }
  fprintf (fp_u, "\n");
  fprintf (fp_u_res, "\n");
  fprintf (fp_res, "\n");
#endif


  for (it_t = 1, t = tau; it_t <= N; it_t++, t += tau)
    {
      res = scheme (&p_g, &p_s, u, workspace, it_t);
#if DRAW3D
      for (i = 0, x = 0; i <= M; i++, x += h)
        {
          fprintf (fp_u, "%e ", u[i]);
          fprintf (fp_u_res, "%e ", u[i]);
          double cur = fabs (u[i] - u_0 (x, t));
          fprintf (fp_res, "%e ", cur);
          if (cur > max)
            max = cur;
        }
      fprintf (fp_u, "\n");
      fprintf (fp_u_res, "\n");
      fprintf (fp_res, "\n");
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
#if RESIDUAL
  fprintf (fp_res, "\n");
  fclose (fp_res);
  fprintf (fp_u_res, "\n");
  fclose (fp_u_res);
#endif
#if COS
  draw ("u-cos", filename_com, it_t);
#else
  draw ("u", filename_com, it_t);
#if RESIDUAL
  int pow = 0;
  double deg = 1.;
  int man = 0;
  if (max >= 1)
    {
      while (max > deg)
        {
          deg *= 10;
          pow++;
        }
      pow--;
      deg /= 10;
      while (man * deg < max)
        {
          man++;
        }
    }
  else
    {
      while (max < deg)
        {
          deg /= 10;
          pow--;
        }
      while (man * deg < max)
        {
          man++;
        }
    }
  draw ("u-res", filename_com, it_t, deg * man);
  draw ("res", filename_com, it_t, deg * man);
#endif
#endif
  my_sleep (1e-3);
#endif

  (void) N;
  delete [] u;
  delete [] workspace;
  delete [] val;

  return 0;
}

