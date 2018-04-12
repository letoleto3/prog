#include "head.h"


void print_table_begin (FILE **fp, const char *param, const char *norm, double h)
{
  fprintf (*fp, "\\begin{center}\n");
  fprintf (*fp, "\\begin{tabular}{|c|c|c|c|c|}\n");
  fprintf (*fp, "\\hline\n");
  fprintf (*fp, "\\multicolumn{5}{|c|}{$\\|%s \\| _{%s}$}\\\\ \n", param, norm);
  fprintf (*fp, "\\hline\n");
  fprintf (*fp, "$\\tau \\backslash h$ & %f & %f & %f & %f \\\\ \n",
           h, h / DEN, h / (DEN * DEN), h / (DEN * DEN * DEN));
}

void print_table (FILE **fp, double *norm, scheme_parametrs *p_s)
{
  fprintf (*fp, "\\hline\n");
  fprintf (*fp, "%f & %e & %e & %e & %e \\\\ \n",
           p_s->tau, norm[0], norm[1], norm[2], norm[3]);
}

void print_table_end (FILE **fp)
{
  fprintf (*fp, "\\hline\n");
  fprintf (*fp, "\\end{tabular}\n");
  fprintf (*fp, "\\end{center}\n");
  fclose (*fp);
}

void begin_print_norms (FILE **fp)
{
  fprintf (*fp, "\\documentclass[a4paper,12pt]{article}\n");
  fprintf (*fp, "\\usepackage[english,russian]{babel}\n");
  fprintf (*fp, "\\usepackage[utf8]{inputenc}\n");
  fprintf (*fp, "\\usepackage{amsmath, amsfonts,amssymb}\n");
  fprintf (*fp, "\\begin{document}\n");
}

void reprint_table (FILE **from, FILE **to)
{
  char str[LEN_BUF];
  fgets (str, LEN_BUF, *from);
  while (!feof (*from))
    {
      fprintf (*to, "%s", str);
      fgets (str, LEN_BUF, *from);
    }
}

void end_print_norms (FILE **fp)
{
  fprintf (*fp, "\\end{document}\n");
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

