#pragma once

#include "AudioFile.h"

class GranularEngine
{
public:
  GranularEngine(const std::string filename);
  float* getNextGrain(const int hop, const int N);

private:
  int m_currentPosition;
  AudioFile<float> m_audio;
};
