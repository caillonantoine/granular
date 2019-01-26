#pragma once

#include "AudioFile.h"

class GranularEngine
{
public:
  GranularEngine(std::string filename);
  float* getNextGrain(int hop, int N);

private:
  int m_currentPosition;
  AudioFile<float>m_audio;
};
