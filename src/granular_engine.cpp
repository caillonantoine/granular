#include "granular_engine.h"
#include "iostream"

GranularEngine::GranularEngine(const std::string filename) :
m_currentPosition(0)
{
  m_audio.load(filename);
  m_audio.printSummary();
}

float* GranularEngine::getNextGrain(const int hop, const int N)
{
  m_currentPosition = (m_currentPosition + N + hop > m_audio.getNumSamplesPerChannel())? 0 : m_currentPosition + hop;
  
  return &m_audio.samples[0][m_currentPosition];

}
