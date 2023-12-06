#pragma once

#include <glm/vec3.hpp>

enum SpectrumType
{
    Emissive,
    Reflective
};

class SPD
{
public:
    SPD();
    SPD(float value);
    SPD(glm::vec3 rgb, SpectrumType type);

    glm::vec3 toXYZ();
    glm::vec3 toRGB();

    void fromXYZ(glm::vec3 xyz, SpectrumType type);
    void fromRGB(glm::vec3 rgb, SpectrumType type);

    void setSample(unsigned int sample, float val);
    float getSample(unsigned int sample);
    float getPowerFromWavelength(unsigned int wavelength);

private:
    float samples[32]; // 380 - 780
};

namespace
{
    SPD operator*(SPD s, SPD s1)
    {
        for (unsigned int i = 0; i < 32; i++)
            s.setSample(i, s.getSample(i) * s1.getSample(i));
        return s;
    }

    SPD operator*(SPD s, float k)
    {
        for (unsigned int i = 0; i < 32; i++)
            s.setSample(i, s.getSample(i) * k);
        return s;
    }

    SPD operator*(float k, SPD s)
    {
        for (unsigned int i = 0; i < 32; i++)
            s.setSample(i, s.getSample(i) * k);
        return s;
    }

    SPD operator+(SPD s, SPD s1)
    {
        for (unsigned int i = 0; i < 32; i++)
            s.setSample(i, s.getSample(i) + s1.getSample(i));
        return s;
    }

    SPD operator+(SPD s, float k)
    {
        for (unsigned int i = 0; i < 32; i++)
            s.setSample(i, s.getSample(i) + k);
        return s;
    }

    SPD operator+(float k, SPD s)
    {
        for (unsigned int i = 0; i < 32; i++)
            s.setSample(i, s.getSample(i) + k);
        return s;
    }

    SPD operator/(SPD s, float k)
    {
        for (unsigned int i = 0; i < 32; i++)
            s.setSample(i, s.getSample(i) / k);
        return s;
    }
}