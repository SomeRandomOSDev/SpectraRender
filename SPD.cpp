#include "SPD.h"

#include "spectrums.h"
#include "util.h"

SPD::SPD()
{
    for (unsigned int i = 0; i < 32; i++)
        samples[i] = 0;
}

SPD::SPD(float value)
{
    for (unsigned int i = 0; i < 32; i++)
        samples[i] = value;
}

SPD::SPD(glm::vec3 rgb, SpectrumType type)
{
    fromRGB(rgb, type);
}

void SPD::fromXYZ(glm::vec3 xyz, SpectrumType type)
{
    fromRGB(XYZToRGB(xyz), type);
}

void SPD::fromRGB(glm::vec3 rgb, SpectrumType type)
{
    for (unsigned int i = 0; i < 32; i++)
    {
        double sample = 0;
        if (type == Reflective)
        {
            if ((rgb.x <= rgb.y) && (rgb.x <= rgb.z))
            {
                sample += rgb.x * RGBRefl2SpectWhite[i];
                if (rgb.y <= rgb.z)
                {
                    sample += (rgb.y - rgb.x) * RGBRefl2SpectCyan[i];
                    sample += (rgb.z - rgb.y) * RGBRefl2SpectBlue[i];
                }
                else
                {
                    sample += (rgb.z - rgb.x) * RGBRefl2SpectCyan[i];
                    sample += (rgb.y - rgb.z) * RGBRefl2SpectGreen[i];
                }
            }
            else if (rgb.y <= rgb.x && rgb.y <= rgb.z)
            {
                sample += rgb.y * RGBRefl2SpectWhite[i];
                if (rgb.x <= rgb.z) {
                    sample += (rgb.x - rgb.y) * RGBRefl2SpectMagenta[i];
                    sample += (rgb.z - rgb.x) * RGBRefl2SpectBlue[i];
                }
                else
                {
                    sample += (rgb.z - rgb.y) * RGBRefl2SpectMagenta[i];
                    sample += (rgb.x - rgb.z) * RGBRefl2SpectRed[i];
                }
            }
            else
            {
                sample += rgb.z * RGBRefl2SpectWhite[i];
                if (rgb.x <= rgb.y)
                {
                    sample += (rgb.x - rgb.z) * RGBRefl2SpectYellow[i];
                    sample += (rgb.y - rgb.x) * RGBRefl2SpectGreen[i];
                }
                else {
                    sample += (rgb.y - rgb.z) * RGBRefl2SpectYellow[i];
                    sample += (rgb.x - rgb.y) * RGBRefl2SpectRed[i];
                }
            }
            sample *= 0.94f;
        }
        else
        {
            if ((rgb.x <= rgb.y) && (rgb.x <= rgb.z))
            {
                sample += rgb.x * RGBIllum2SpectWhite[i];
                if (rgb.y <= rgb.z)
                {
                    sample += (rgb.y - rgb.x) * RGBIllum2SpectCyan[i];
                    sample += (rgb.z - rgb.y) * RGBIllum2SpectBlue[i];
                }
                else
                {
                    sample += (rgb.z - rgb.x) * RGBIllum2SpectCyan[i];
                    sample += (rgb.y - rgb.z) * RGBIllum2SpectGreen[i];
                }
            }
            else if (rgb.y <= rgb.x && rgb.y <= rgb.z)
            {
                sample += rgb.y * RGBIllum2SpectWhite[i];
                if (rgb.x <= rgb.z) {
                    sample += (rgb.x - rgb.y) * RGBIllum2SpectMagenta[i];
                    sample += (rgb.z - rgb.x) * RGBIllum2SpectBlue[i];
                }
                else
                {
                    sample += (rgb.z - rgb.y) * RGBIllum2SpectMagenta[i];
                    sample += (rgb.x - rgb.z) * RGBIllum2SpectRed[i];
                }
            }
            else
            {
                sample += rgb.z * RGBIllum2SpectWhite[i];
                if (rgb.x <= rgb.y) {
                    sample += (rgb.x - rgb.z) * RGBIllum2SpectYellow[i];
                    sample += (rgb.y - rgb.x) * RGBIllum2SpectGreen[i];
                }
                else
                {
                    sample += (rgb.y - rgb.z) * RGBIllum2SpectYellow[i];
                    sample += (rgb.x - rgb.y) * RGBIllum2SpectRed[i];
                }
            }
            sample *= 0.86445f;
        }
        samples[i] = (float)sample;
    }
}

void SPD::setSample(unsigned int sample, float val)
{
    samples[sample] = val;
}

float SPD::getSample(unsigned int sample)
{
    return samples[sample];
}

float SPD::getPowerFromWavelength(unsigned int wavelength)
{
    unsigned int sample = (wavelength - 380) * 32 / 400;
    if (sample < 0) return 0;
    if (sample >= 32) return 0;
    return samples[sample];
}

glm::vec3 SPD::toXYZ()
{
    glm::vec3 xyz(0, 0, 0);
    for (unsigned int i = 0; i < 32; i++)
    {
        unsigned int CIEIndex = i * 400 / 32 + 20;
        xyz.x += CIE_X[CIEIndex] * samples[i] * (400 / 32.f);
        xyz.y += CIE_Y[CIEIndex] * samples[i] * (400 / 32.f);
        xyz.z += CIE_Z[CIEIndex] * samples[i] * (400 / 32.f);
    }

    xyz /= CIE_Y_integral;

    return xyz;
}

glm::vec3 SPD::toRGB()
{
    glm::vec3 xyz = toXYZ();
    xyz = XYZToRGB(xyz);
    return xyz;
}