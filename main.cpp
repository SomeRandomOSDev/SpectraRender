#include "pathtrace.h"
#include "Sphere.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>
#include <vector>

int main()
{
	std::vector<Sphere> scene;
	scene.push_back(Sphere(glm::vec3(0, 0, 10), 2));
	sf::Image image = CPURender(scene, 1920, 1080, 256, 4);
	std::cout << "Saving..." << std::endl;
	image.saveToFile(
		"out/render" + std::to_string(time(0)) + ".png");
	std::cout << "Saved ! Press any to continue..." << std::endl;

	while (!_kbhit());
}