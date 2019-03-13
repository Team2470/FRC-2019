#include "encoder_helper.hpp"

Encoder::Encoder(int channelA, int channelB, double distanceMult, bool reversed, frc::Encoder::EncodingType encoderType)
{
    this->encoder = new frc::Encoder(channelA, channelB, reversed, encoderType);
    //encoder->SetDistancePerPulse(distanceMult);
    distanceMultiplier = distanceMult;
    currentDirection = reversed;
    defaultDirection = reversed;
}

int Encoder::getValue()
{
    currentDirection = encoder->GetDirection();
    return encoder->Get();
}

bool Encoder::getDirection()
{
    currentDirection = encoder->GetDirection();
    return currentDirection;
}

double Encoder::getDistance()
{
    encoder->GetDistance();
}

void Encoder::reset()
{
    encoder->Reset();
    currentDirection = defaultDirection;
}

void Encoder::reverseDirection()
{
    currentDirection = encoder->GetDirection();
    encoder->SetReverseDirection(!currentDirection);
    currentDirection = encoder->GetDirection();
}

void Encoder::setDistanceMultiplier(double newMultiplier)
{
    distanceMultiplier = newMultiplier;
    //encoder->SetDistancePerPulse(newMultiplier);
}
