#pragma once

#include <iostream>

#include <engine/node.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include <glm/glm.hpp>

class AudioSource : public Node
{
private:
    ALuint source;
    ALuint buffer;

    glm::vec3 velocity;
    glm::vec3 direction;

    float pitch;
    float gain;

public:
    AudioSource(glm::vec3 velocity, glm::vec3 direction, float pitch, float gain) : velocity(velocity), direction(direction), pitch(pitch), gain(gain)
    {
        alGenSources(1, &source);
        alGenBuffers(1, &buffer);

        alSourcef(source, AL_PITCH, pitch);
        alSourcef(source, AL_GAIN, gain);
        alSource3f(source, AL_POSITION, position.x, position.y, position.z);
        alSource3f(source, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
        alSource3f(source, AL_DIRECTION, direction.x, direction.y, direction.z);
    }

    ~AudioSource()
    {
        alDeleteSources(1, &source);
        alDeleteBuffers(1, &buffer);
    }

    void play()
    {
        alSourcePlay(source);
    }

    void pause()
    {
        alSourcePause(source);
    }

    void stop()
    {
        alSourceStop(source);
    }

    void setPitch(float pitch)
    {
        this->pitch = pitch;
        alSourcef(source, AL_PITCH, pitch);
    }

    void setGain(float gain)
    {
        this->gain = gain;
        alSourcef(source, AL_GAIN, gain);
    }

    void setPosition(glm::vec3 position)
    {
        this->position = position;
        alSource3f(source, AL_POSITION, position.x, position.y, position.z);
    }

    void setVelocity(glm::vec3 velocity)
    {
        this->velocity = velocity;
        alSource3f(source, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
    }

    void setDirection(glm::vec3 direction)
    {
        this->direction = direction;
        alSource3f(source, AL_DIRECTION, direction.x, direction.y, direction.z);
    }
};
