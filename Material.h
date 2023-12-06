#pragma once

#include "SPD.h"
#include <glm/vec3.hpp>

class Material
{
public:
	Material() : albedo(glm::vec3(0.8, 0.8, 0.8), Reflective), emission(0) {}
	Material(SPD albedo, float emission = 0) : albedo(albedo), emission(emission) {}
	Material(glm::vec3 albedo, SpectrumType spdType, float emission = 0) : 
	albedo(albedo, spdType), emission(emission) {}

public:
	SPD albedo;
	float emission;
};