#pragma once

#include "SPD.h"
#include <glm/vec3.hpp>

class Material
{
public:
	Material() : albedo(0.8f) {}

public:
	SPD albedo;
};