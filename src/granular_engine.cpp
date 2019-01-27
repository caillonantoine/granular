#include "granular_engine.h"
#include "iostream"
#include <math.h>

GranularEngine::GranularEngine() :
m_currentPosition(0)
{
  //m_audio.load(filename);
  //m_audio.printSummary();

  for (int i(0); i < WINDOW_LUT_SIZE; i++)
  {
    window[i] = .5 * (1 - cos(2*3.14157*i/WINDOW_LUT_SIZE));
  }
}

float* GranularEngine::getNextGrain(const int hop, const int N)
{
  m_currentPosition = (m_currentPosition + N + hop > m_audio.getNumSamplesPerChannel())? 0 :
                      std::max(0, m_currentPosition + hop);

  return &m_audio.samples[0][m_currentPosition];

}

void GranularEngine::loadFile(const std::string filename)
{
  m_audio.load(filename);
  m_audio.printSummary();
}
