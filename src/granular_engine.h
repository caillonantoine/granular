#pragma once

#include "AudioFile.h"
#define WINDOW_LUT_SIZE 10000

class GranularEngine
{
public:
  GranularEngine();
  void loadFile(const std::string filename);
  float* getNextGrain(const int hop, const int N);
  float window[WINDOW_LUT_SIZE];

private:
  int m_currentPosition;
  AudioFile<float> m_audio;
};
