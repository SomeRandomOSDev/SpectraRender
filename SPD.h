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

