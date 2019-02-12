#include "m_pd.h"
#include "granular_engine.h"
#include "AudioFile.h"
#include <iostream>

#define SLOT_NUMBER 4

static t_class *granular_tilde_class;

typedef struct _granular_tilde {
  t_object  x_obj;

  GranularEngine GE;

  float* grainL[4];
  float* grainR[4];

  int    grainHead[4];
  int    grainSize[4];
  int    nextGrainSlot;

  int    slot[SLOT_NUMBER];

  int      hopHead;
  float    playHopSize;
  float    readHopSize;
  float    currentGrainSize;

  t_inlet* x_in_play_hop_size;
  t_inlet* x_in_read_hop_size;
  t_inlet* x_in_current_grain_size;

  t_outlet *x_outL;
  t_outlet *x_outR;


} t_granular_tilde;

t_int *granular_tilde_perform(t_int *w)
{
  t_granular_tilde *x = (t_granular_tilde *)(w[1]);
  t_sample  *outL =    (t_sample *)(w[2]);
  t_sample  *outR =    (t_sample *)(w[3]);
  int          n =           (int)(w[4]);

  for (int i(0); i < n; i++)
  {
    outL[i] = 0;
    outR[i] = 0;

    if (x->GE.m_ready) {
    if (x->hopHead++ >= int(std::max(x->currentGrainSize / 4, x->playHopSize)))
    {
      x->hopHead = 0;
      
      x->GE.getNextGrain(int(x->readHopSize),
                         int(x->currentGrainSize),
                         &x->grainL[x->nextGrainSlot],
                         &x->grainR[x->nextGrainSlot]);

      x->grainHead[x->nextGrainSlot] = 0;
      x->grainSize[x->nextGrainSlot] = x->currentGrainSize;
      x->nextGrainSlot = (x->nextGrainSlot + 1) % 4;
    }
    for (int g(0); g < 4; g++)
    {
      //Pour chaque grain on ajoute la valeur correspondane, et on incrémente grainHead
      outL[i] += x->grainHead[g] >= x->grainSize[g]? 0 :
              x->grainL[g][x->grainHead[g]] * x->GE.window[(WINDOW_LUT_SIZE * x->grainHead[g]) / x->grainSize[g]];
      outR[i] += x->grainHead[g] >= x->grainSize[g]? 0 :
              x->grainR[g][x->grainHead[g]] * x->GE.window[(WINDOW_LUT_SIZE * x->grainHead[g]) / x->grainSize[g]];
      x->grainHead[g] ++;
    }
}
  }



  return (w+5);
}

void granular_tilde_dsp(t_granular_tilde *x, t_signal **sp)
{
  dsp_add(granular_tilde_perform, 4, x,
          sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void granular_tilde_load(t_granular_tilde *x, t_symbol *sym)
{
  x->GE.loadFile(sym->s_name);
}

void granular_tilde_freeze(t_granular_tilde *x, t_symbol *sym)
{
  x->GE.toogle_freeze();
}

void granular_tilde_pin(t_granular_tilde *x, t_floatarg f)
{
  x->slot[int(f)] = x->GE.m_currentPosition;
}

void granular_tilde_goto(t_granular_tilde *x, t_floatarg f)
{
  x->GE.m_currentPosition = x->slot[int(f)];
}

void granular_tilde_free(t_granular_tilde *x)
{
  outlet_free(x->x_outL);
  outlet_free(x->x_outR);
}

void *granular_tilde_new(t_floatarg f)
{
  t_granular_tilde *x = (t_granular_tilde *)pd_new(granular_tilde_class);

  x->GE = GranularEngine();

  *x->grainHead = {0};
  *x->grainSize = {0};
  x->nextGrainSlot = 0;

  x->hopHead = 0;
  x->playHopSize = 4096;
  x->readHopSize = 256;
  x->currentGrainSize = 4096;

  x->x_in_play_hop_size = floatinlet_new (&x->x_obj, &x->playHopSize);
  x->x_in_read_hop_size = floatinlet_new(&x->x_obj, &x->readHopSize);
  x->x_in_current_grain_size = floatinlet_new(&x->x_obj, &x->currentGrainSize);
  x->x_outL = outlet_new(&x->x_obj, &s_signal);
  x->x_outR = outlet_new(&x->x_obj, &s_signal);

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
  class_addmethod(granular_tilde_class,
        (t_method)granular_tilde_load, gensym("load"), A_SYMBOL, A_NULL);
  class_addmethod(granular_tilde_class,
        (t_method)granular_tilde_freeze, gensym("freeze"), A_DEFFLOAT, 0);
  class_addmethod(granular_tilde_class,
        (t_method)granular_tilde_pin, gensym("pin"), A_DEFFLOAT, 0);
  class_addmethod(granular_tilde_class,
        (t_method)granular_tilde_goto, gensym("goto"), A_DEFFLOAT, 0);
}
}
