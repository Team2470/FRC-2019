#include "encoder_helper.hpp"

Encoder::Encoder(int channelA, int channelB, bool reversed = false, frc::Encoder::EncodingType encoderType = frc::Encoder::k4X)
{
    this->encoder = new frc::Encoder(channelA, channelB, reversed, encoderType);
    currentDirection = reversed;
}

int Encoder::getValue()
{
}

bool Encoder::getDirection()
{
}

double Encoder::getDistance()
{
}

void Encoder::reset()
{
    encoder->Reset();
}

void Encoder::reverseDirection()
{
    encoder->SetReverseDirection(!currentDirection);
    //currentDirection = getDirection();
}

