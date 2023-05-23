#include "codeuse.hpp"

Codeuse::Codeuse(uint8_t pinCodA, uint8_t pinCodB, int32_t ticksPerRound, float wheelDiameter, bool orientation) :
    ticksPerRound (ticksPerRound),
    wheelDiameter (wheelDiameter),
    orientation (orientation)
{
    encoder = new Encoder (pinCodA, pinCodB);
    ticks = 0;
    prev_ticks = 0;
    deltaAvance = 0.0f;
}

Codeuse::~Codeuse () {
    encoder->~Encoder ();
}

void Codeuse::update (){
    ticks = encoder->read();
    deltaAvance = (ticks - prev_ticks) * (PI * wheelDiameter) / ticksPerRound;
    prev_ticks = ticks;
}

float Codeuse::getDeltaAvance(){
    return deltaAvance;
}