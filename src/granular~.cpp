#include "m_pd.h"
#include "AudioFile.h"

static t_class *granular_tilde_class;

typedef struct _granular_tilde {
  t_object  x_obj;

  AudioFile<float> sample;

  t_outlet*x_out;

} t_granular_tilde;

t_int *granular_tilde_perform(t_int *w)
{
  t_granular_tilde *x = (t_granular_tilde *)(w[1]);
  t_sample  *out =    (t_sample *)(w[2]);
  int          n =           (int)(w[3]);

  while (n--) *out++ = 0;

  return (w+4);
}

void granular_tilde_dsp(t_granular_tilde *x, t_signal **sp)
{
  dsp_add(granular_tilde_perform, 3, x,
          sp[0]->s_vec, sp[0]->s_n);
}

void granular_tilde_free(t_granular_tilde *x)
{
  outlet_free(x->x_out);
}

void *granular_tilde_new(t_floatarg f)
{
  t_granular_tilde *x = (t_granular_tilde *)pd_new(granular_tilde_class);

  x->x_out=outlet_new(&x->x_obj, &s_signal);

  return (void *)x;
}

extern "C" {
void granular_tilde_setup(void) {
  granular_tilde_class = class_new(gensym("granular~"),
        (t_newmethod)granular_tilde_new,
        0, sizeof(t_granular_tilde),
        CLASS_DEFAULT,
        A_GIMME, 0);

  class_addmethod(granular_tilde_class,
        (t_method)granular_tilde_dsp, gensym("dsp"), A_CANT, 0);
}
}
