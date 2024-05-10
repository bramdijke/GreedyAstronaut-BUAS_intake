#pragma once
#include "surface.h"

class Score {
public:
    Score() { scoreValue = 0; }
    void IncrementScore() { scoreValue++; }
    int GetScore() { return scoreValue; }

private:
    int scoreValue;
};