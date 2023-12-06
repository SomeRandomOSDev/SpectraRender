#pragma once

#include <glm/vec3.hpp>
#include "Material.h"

class Sphere
{
public:
	Sphere(glm::vec3 pos, float rad, Material* mat = NULL)
		: origin(pos), radius(rad), material(mat) {}

public:
	glm::vec3 origin;
	float radius;
	Material* material;
};