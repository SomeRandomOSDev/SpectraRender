#pragma once

#include <SFML/Graphics.hpp>
#include <glm/vec3.hpp>
#include <algorithm>
#include "util.h"
#include "SPD.h"
#include <iostream>

namespace
{
	sf::Image CPURender(unsigned int width, unsigned int height, unsigned int samples, unsigned int bounces)
	{
		std::cout << "Rendering ..." << std::endl;
		std::cout << "[--------------------------------------------------]\r[";
		sf::Image render;
		render.create(width, height);
		unsigned int lastCompletion = 0;
		for (unsigned int i = 0; i < height; i++)
		{
			for (unsigned int j = 0; j < width; j++)
			{
				SPD spdColor(glm::vec3(i / (float)height, j / (float)width, 1), Reflective);
				glm::vec3 color(spdColor.toRGB());
				//glm::vec3 color = glm::vec3(i / (float)height, j / (float)width, 1);
				color.x = std::clamp(color.x, 0.f, 1.f);
				color.y = std::clamp(color.y, 0.f, 1.f);
				color.z = std::clamp(color.z, 0.f, 1.f);
				render.setPixel(j, i, sf::Color(int(color.x * 255), int(color.y * 255), int(color.z * 255)));
			}
			unsigned int temp = i * 50 / height;
			if (lastCompletion != temp)
			{
				lastCompletion = temp;
				std::cout << '=';
			}
		}
		std::cout << '=' << std::endl;
		return render;
	}
}