#pragma once

#include "SPD.h"
#include <glm/vec3.hpp>

class Material
{
public:
	Material() : albedo(glm::vec3(0.8, 0.8, 0.8), Reflective) {}
	Material(SPD albedo) : albedo(albedo) {}
	Material(glm::vec3 albedo, SpectrumType spdType) : albedo(albedo, spdType) {}

public:
	SPD albedo;
};