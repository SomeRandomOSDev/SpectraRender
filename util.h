#pragma once

#include <glm/glm.hpp>
#include <algorithm>
#include <random>
#include "Sphere.h"

namespace
{
	std::default_random_engine re(0);
	std::uniform_real_distribution<double> random01(0, 1);

	inline glm::vec3 XYZToRGB(const glm::vec3& xyz)
	{
		glm::vec3 rgb;
		rgb.x = 3.240479f * xyz.x - 1.537150f * xyz.y - 0.498535f * xyz.z;
		rgb.y = -0.969256f * xyz.x + 1.875991f * xyz.y + 0.041556f * xyz.z;
		rgb.z = 0.055648f * xyz.x - 0.204043f * xyz.y + 1.057311f * xyz.z;
		return rgb;
	}

	inline glm::vec3 RGBToXYZ(const glm::vec3& rgb)
	{
		glm::vec3 xyz;
		xyz.x = 0.412453f * rgb.x + 0.357580f * rgb.y + 0.180423f * rgb.z;
		xyz.y = 0.212671f * rgb.x + 0.715160f * rgb.y + 0.072169f * rgb.z;
		xyz.z = 0.019334f * rgb.x + 0.119193f * rgb.y + 0.950227f * rgb.z;
		return xyz;
	}

	template<typename T>
	inline glm::vec3 SphericalToCartesian(float radius, T phi, T theta)
	{
		return glm::vec3(float(radius * sin(phi) * cos(theta)),
			float(radius * cos(phi)),
			float(radius * sin(phi) * sin(theta)));
	}

	glm::vec3 RandomVectorInHemisphere(glm::vec3 normal)
	{
		while (true)
		{
			glm::vec3 randomVec((float)random01(re) * 2.f - 1.f, (float)random01(re) * 2.f - 1.f, (float)random01(re) * 2.f - 1.f);
			float norm2rv = glm::dot(randomVec, randomVec);
			if (norm2rv <= 1 && dot(randomVec, normal) != 0 && norm2rv != 0)
			{
				randomVec /= sqrt(norm2rv);

				if (dot(randomVec, normal) < 0)
					randomVec *= -1;

				return randomVec;
			}
		}
	}

	glm::vec3 RandomVector()
	{
		while (true)
		{
			glm::vec3 randomVec((float)random01(re) * 2.f - 1.f, (float)random01(re) * 2.f - 1.f, (float)random01(re) * 2.f - 1.f);
			float norm2rv = glm::dot(randomVec, randomVec);
			if (norm2rv <= 1 && norm2rv != 0)
			{
				randomVec /= sqrt(norm2rv);

				return randomVec;
			}
		}
	}
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html
	bool RaySphereIntersection(
		const glm::vec3& rayPos, const glm::vec3& rayDir,
		const glm::vec3& sphereOrigin, const float sphereRadius,
		float& t, glm::vec3& pos, glm::vec3& normal)
	{
		glm::vec3 oc = rayPos - sphereOrigin;
		float b = 2 * glm::dot(rayDir, oc);
		float c = glm::dot(oc, oc) - sphereRadius * sphereRadius;
		float delta = b * b - 4 * c;
		if (delta < 0) return false;
		float sqrtDelta = sqrt(delta);
		float t2 = (-b + sqrtDelta) / 2;

		if (t2 < 0) return false;

		float t1 = (-b - sqrtDelta) / 2;

		t = (t1 < 0) ? t2 : std::min(t1, t2);

		if (t < 0) return false;

		pos = rayPos + (rayDir * t);
		normal = normalize(pos - sphereOrigin);

		return true;
	}

	bool RaySceneIntersection(
	const glm::vec3& rayPos, const glm::vec3& rayDir, std::vector<Sphere> scene,
	float& t, glm::vec3& pos, glm::vec3& normal)
	{
		t = 10000;

		bool inter = false;

		for (unsigned int i = 0; i < scene.size(); i++)
		{
			float currT = 10000;
			glm::vec3 currPos, currNormal;
			if (RaySphereIntersection(rayPos, rayDir, glm::vec3(0, 0, 10), 1, currT, currPos, currNormal))
			{
				inter = true;

				if (currT < t)
				{
					t = currT;
					pos = currPos;
					normal = currNormal;
				}
			}
		}
		return inter;
	}
}