#include "granular_engine.h"
#include "iostream"

GranularEngine::GranularEngine(std::string filename)
{
  m_audio.load(filename);
  m_audio.printSummary();
}

float* GranularEngine::getNextGrain(int hop, int N)
{

}
