#pragma once

#include <SFML/Graphics.hpp>
#include <glm/vec3.hpp>
#include <algorithm>
#include "util.h"
#include "SPD.h"
#include <iostream>
#include <vector>
#include "Sphere.h"

namespace
{
	float Li(
	std::vector<Sphere> scene, 
	glm::vec3 rayOrigin, glm::vec3 rayDir, 
	unsigned int lambda)
	{
		float t;
		glm::vec3 pos, normal;
		Material* mat = NULL;
		if (RaySceneIntersection(rayOrigin, rayDir, scene, t, pos, normal, mat))
			return mat->albedo.getPowerFromWavelength(lambda);
		return 0;
	}

	sf::Image CPURender(std::vector<Sphere> scene, 
		unsigned int width, unsigned int height, 
		unsigned int samples, unsigned int bounces)
	{
		samples -= samples % 32;
		std::cout << "Rendering ... [" << samples << " samples, " << bounces << " bounces]" << std::endl;
		std::cout << "[--------------------------------------------------]\r[";
		sf::Image render;
		render.create(width, height);
		unsigned int lastCompletion = 0;
		sf::Clock timer;
		for (unsigned int i = 0; i < height; i++)
		{
#pragma omp parallel for
			for (int j = 0; j < (int)width; j++)
			{
				SPD spdColor(0);
				for (unsigned int k = 0; k < samples; k++)
				{
					float offsetX = (float)random01(re), offsetY = (float)random01(re);
					glm::vec3 cameraPosisition(0, 0, 0), 
					rayDir(normalize(glm::vec3(j - (width / 2.f) + offsetX, -(i - (height / 2.f)) + offsetY, height)));
					unsigned int spdSample = k % 32;// int(random01(re) * 32);
					unsigned int lambda = spdSample * 400 / 32 + 380;
					spdColor.setSample(spdSample, 
					spdColor.getSample(spdSample) + 
					Li(scene, cameraPosisition, rayDir, lambda) * 32);
				}
				spdColor = spdColor / (float)samples;
				glm::vec3 color(spdColor.toRGB());

				color.x = std::clamp(color.x, 0.f, 1.f);
				color.y = std::clamp(color.y, 0.f, 1.f);
				color.z = std::clamp(color.z, 0.f, 1.f);

				color.x = std::pow(color.x, 1 / 2.2f);
				color.y = std::pow(color.y, 1 / 2.2f);
				color.z = std::pow(color.z, 1 / 2.2f);

				render.setPixel(j, i, sf::Color(int(color.x * 255), int(color.y * 255), int(color.z * 255)));
			}
			unsigned int temp = i * 50 / height;
			if (lastCompletion < temp)
			{
				lastCompletion++;
				std::cout << '=';
			}
		}
		std::cout << '=' << std::endl;
		std::cout << "Finished in " << timer.getElapsedTime().asSeconds() << 's' << std::endl;
		return render;
	}
}