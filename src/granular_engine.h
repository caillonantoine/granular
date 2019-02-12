#pragma once

#include "AudioFile.h"
#define WINDOW_LUT_SIZE 10000

struct GranularEngine
{
  GranularEngine();
  void loadFile(const std::string filename);
  void toogle_freeze();
  void getNextGrain(const int hop, const int N, float **grainL, float **grainR);
  float window[WINDOW_LUT_SIZE];
  int m_currentPosition;
  int m_freeze;
  int m_ready;
  AudioFile<float> m_audio;
};
