#pragma once

#include <glm/vec3.hpp>

class Sphere
{
public:
	Sphere(glm::vec3 pos, float rad) : origin(pos), radius(rad) {}

public:
	glm::vec3 origin;
	float radius;
};