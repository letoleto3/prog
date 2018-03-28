#include "head.h"
#include "functions.h"

extern int MAX_M;
extern int MAX_N;

void init_task (task_parametrs *p_g)
{

  p_g->Segm_T = 1.;
  p_g->Segm_X = 1.;
  p_g->f1 = f1;
  p_g->u_0 = u_0;
}

void one_step (task_parametrs *p_g, scheme_parametrs *p_s, int num)
{
  (void) num;
  p_s->M = MAX_M;
  p_s->N = MAX_N;
  p_s->Dim = (p_s->M + 1) * (p_s->N + 1);
  p_s->h = p_g->Segm_X / p_s->M;
  p_s->tau = p_g->Segm_T / p_s->N;
}


void div_tau (scheme_parametrs *p_s, int den)
{
  p_s->N *= den;
  p_s->tau /= den;
}

void div_h (scheme_parametrs *p_s, int den)
{
  p_s->M *= den;
  p_s->h /= den;
}

void set_h (task_parametrs *p_g, scheme_parametrs *p_s)
{
  p_s->M = MAX_M;
  p_s->h = p_g->Segm_X / MAX_M;
}

