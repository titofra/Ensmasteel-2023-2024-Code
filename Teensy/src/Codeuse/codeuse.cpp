#include "Codeuse/codeuse.hpp"

Codeuse::Codeuse(uint8_t pinCodA, uint8_t pinCodB, int32_t ticksPerRound, float wDiam, bool orientation) :
    ticksPerRound (ticksPerRound),
    wheelDiameter (wheelDiameter),
    orientation (orientation)
{
    encoder = Encoder (pinCodA, pinCodB);
    ticks = 0;
    prev_ticks = 0;
    v = 0.0f;
    deltaAvance = 0.0f;
}

void Codeuse::actuate(float dt){
    ticks = encoder.read();
    deltaAvance = (ticks - prev_ticks) * (PI * wheelDiameter) / ticksPerRound;
    v = deltaAvance / dt;
    prev_ticks = ticks;
}

float Codeuse::getTranslationSpeed(){
    return v;
}

float Codeuse::getDeltaAvance(){
    return deltaAvance;
}