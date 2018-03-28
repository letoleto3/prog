#include "head.h"

extern int MAX_M;
extern int MAX_N;

int scheme (task_parametrs *p_g, scheme_parametrs *p_s, double *u, double *workspace, int it_t)
{
  int M = p_s->M;
  int res;
  double *arr = workspace;
  double *vect = arr + 3 * (M + 1);
  double *work = vect + M + 1;

  fill_matrix_u (p_g, p_s, arr);
  fill_rhs_u (p_g, p_s, vect, u, it_t);

  res = solve_tridiag_matrix (arr, vect, u, work, M + 1);
  if (res)
    {
      fprintf (stdout, "Cannot solve matrix!\n");
      return res;
    }

  return 0;
}

void draw (const char *parametr, const char *file_name, int it_t)
{
  (void) it_t;
  char path_dest [LEN_BUF];
  FILE *fp;
  fp = fopen (file_name, "w");
  fprintf (fp, "set terminal jpeg size 1024, 768\n");
#if DRAW3D
#if PM3D
  fprintf (fp, "set output '%s/pm%dx%d.jpg'\n", parametr, MAX_M, MAX_N);
#else
  fprintf (fp, "set output '%s/lines%dx%d.jpg'\n", parametr, MAX_M, MAX_N);
#endif
  fprintf (fp, "set grid\n");
  fprintf (fp, "set xrange [0:%d]\n", MAX_M);
  fprintf (fp, "set yrange [0:%d]\n", MAX_N);
  fprintf (fp, "set zrange [0:1.]\n");
  fprintf (fp, "set xlabel 'x'\n");
  fprintf (fp, "set ylabel 't'\n");
  fprintf (fp, "set zlabel 'u (x, t)'\n");
  fprintf (fp, "set xtics ('' 0, ''1)\n");
  fprintf (fp, "set ytics ('' 0, ''1)\n");
  fprintf (fp, "set palette defined (0 \"dark-turquoise\", 1 \"yellow\")\n");
#if PM3D
  fprintf (fp, "splot 'data_u.txt' matrix with pm3d\n");
#else
  fprintf (fp, "set pm3d at b\n");
  fprintf (fp, "splot 'data_u.txt' matrix with lines %c", '\0');
#endif
#else
  fprintf (fp, "set output '%s/u%d.jpg'\n", parametr, it_t);
  fprintf (fp, "set grid x y\n");
  fprintf (fp, "set xrange [0:1]\n");
  fprintf (fp, "set yrange [0:1.]\n");
  fprintf (fp, "plot 'data_u.txt' using 1:3 with lines%c", '\0');
#endif

  fclose (fp);
  sprintf (path_dest, "\"gnuplot\" %s%c\"", file_name,'\0');
  system (path_dest);
}


void print_table_begin (FILE **fp)
{
  fprintf (*fp, "\\documentclass[a4paper,12pt]{article}\n");
  fprintf (*fp, "\\usepackage[english,russian]{babel}\n");
  fprintf (*fp, "\\usepackage[utf8]{inputenc}\n");
  fprintf (*fp, "\\usepackage{amsmath, amsfonts,amssymb}\n");
  fprintf (*fp, "\\usepackage{longtable}\n");

  fprintf (*fp, "\\begin{document}\n");
  fprintf (*fp, "\\begin{center}\n");
  fprintf (*fp, "\\begin{longtable}{|c|c|}\n");
  fprintf (*fp, "\\hline\n");
  fprintf (*fp, "$t$ & $m$ \\\\ \n");
}

void print_table (FILE **fp, double t, double mass)
{
  fprintf (*fp, "\\hline\n");
  fprintf (*fp, "%.6f & %.6f \\\\ \n", t, mass);
}

void print_table_end (FILE **fp)
{
  fprintf (*fp, "\\hline\n");
  fprintf (*fp, "\\end{longtable}\n");
  fprintf (*fp, "\\end{center}\n");
  fprintf (*fp, "\\end{document}\n");
}
