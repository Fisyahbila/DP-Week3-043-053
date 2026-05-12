#include "BlindRule.h"
#include <iostream>

bool BlindRule::checkBlind(int score)
{
  std::cout << "[Blind Rule] Mengecek apakah skor (" << score << ") memenuhi target..." << std::endl;

  return score >= 100;
}