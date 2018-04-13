#ifndef HEAD_H
#define HEAD_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "options.h"

#define LEN 500
#define DEN 2
#define DEN_TAU 4

#define EPS 10e-16

#define RESIDUAL 0

struct task_parametrs
{
  double Segm_T;
  double Segm_X;
  double (*f1)(double, double);

  double (*u_0)(double, double);
};

struct scheme_parametrs
{
  int M;
  int N;
  int Dim;
  double h;
  double tau;
};

void fill_matrix_u (task_parametrs *p_g,
                    scheme_parametrs *p_s,
                    double *arr_u);
void fill_rhs_u (task_parametrs *p_g,
                 scheme_parametrs *p_s,
                 double *vect,
                 double *u,
                 int it_t);
void init_arrays (task_parametrs *p_g,
                  scheme_parametrs *p_s,
                  double *u);



void print_tridiag_matrix (double *array, int size);
void print_matrix (double *array, int heignt, int width);
void print_vector (double *vector, int size);
int solve_tridiag_matrix (double *a,         // [3 * n]
           double *b,         // [n]
           double *c,         // [n]
           double *workspace, // [2 * n]
           int n);
void product (double *A, // [3 * n]
              double *b, // [n]
              double *x,
              int n);


double norm_C_h  (double *arr, int n, double h);
double norm_L2_h (double *arr, int n, double h);
double norm2_C_h  (double *x, double *y, int n, double h);
double norm2_L2_h (double *x, double *y, int n, double h);
double norm2_21_h (double *x, double *y, int n, double h);


void init_task (task_parametrs *p_g);
void one_step (task_parametrs *p_g, scheme_parametrs *p_s, int num);
void div_tau (scheme_parametrs *p_s, int den);
void div_h (scheme_parametrs *p_s, int den);
void set_h (task_parametrs *p_g, scheme_parametrs *p_s);


void calculate_u (task_parametrs *p_g, scheme_parametrs *p_s, double *val_u);


int scheme (task_parametrs *p_g,
            scheme_parametrs *p_s,
            double *u,
            double *workspace,
            int it_t);




void print_table_begin (FILE **fp);
void print_table_begin (FILE **fp, const char *param, const char *norm, double h);
void print_table (FILE **fp, double t, double mass);
void print_table (FILE **fp, double *norm, scheme_parametrs *p_s);
void print_table_end (FILE **fp);

#define LEN_BUF 256
void begin_print_norms (FILE **fp);
void reprint_table (FILE **from, FILE **to);
void end_print_norms (FILE **fp);

void draw (const char *parametr, const char *file_name, int it_t, double max = 0);
#endif // HEAD_H
