#include "granular_engine.h"
#include "iostream"
#include <stdlib.h>
#include <math.h>

#define SPREAD 256

//==============================================================================

GranularEngine::GranularEngine() :
m_currentPosition(0), m_freeze(0), m_ready(0)
{
  for (int i(0); i < WINDOW_LUT_SIZE; i++)
  {
    window[i] = .5 * (1 - cos(2*3.14157*i/WINDOW_LUT_SIZE));
  }
}

//==============================================================================

float* GranularEngine::getNextGrain(const int hop, const int N)
{
  switch (m_freeze) {
      case 0:
        m_currentPosition = (m_currentPosition + N + hop > m_audio.getNumSamplesPerChannel())? 0 :
                            std::max(0, m_currentPosition + hop);
        return &m_audio.samples[0][m_currentPosition];

      case 1:
        return &m_audio.samples[0][std::max(0,m_currentPosition + std::rand()%SPREAD - SPREAD/2)];
  }
}

//==============================================================================

void GranularEngine::loadFile(const std::string filename)
{
  if (m_audio.load(filename))
  {
      m_audio.printSummary();
      m_ready = 1;
  }

}

//==============================================================================

void GranularEngine::toogle_freeze()
{
  m_freeze = ++m_freeze % 2;
}
