#include "pathtrace.h"
#include "Sphere.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>
#include <vector>

int main()
{
	std::vector<Material> materials;
	std::vector<Sphere> scene;

	materials.push_back(Material());

	materials.push_back(Material(glm::vec3(1, 0, 0), Reflective));
	materials.push_back(Material(glm::vec3(0, 1, 0), Reflective));
	materials.push_back(Material(glm::vec3(0, 0, 1), Reflective));
	materials.push_back(Material(glm::vec3(1, 0, 1), Reflective));
	materials.push_back(Material(glm::vec3(0, 1, 1), Reflective));

	materials.push_back(Material(glm::vec3(1, 1, 1), Emissive, 50));

	scene.push_back(Sphere(glm::vec3(0, 0, 10), 2, &materials[0]));
	scene.push_back(Sphere(glm::vec3(0, 0, 1015), 1000, &materials[1]));
	scene.push_back(Sphere(glm::vec3(1005, 0, 0), 1000, &materials[2]));
	scene.push_back(Sphere(glm::vec3(0, 1005, 0), 1000, &materials[3]));
	scene.push_back(Sphere(glm::vec3(0, -1005, 0), 1000, &materials[4]));
	scene.push_back(Sphere(glm::vec3(-1005, 0, 0), 1000, &materials[5]));
	scene.push_back(Sphere(glm::vec3(-3, 2, 4), 1, &materials[6]));

////////////////////////////////////////////////////////////////////////

	sf::Image image = CPURender(scene, 1920, 1080, 1024, 3);
	std::cout << "Saving..." << std::endl;
	image.saveToFile(
	"out/render" + std::to_string(time(0)) + ".png");
	std::cout << "Saved ! Press any to continue..." << std::endl;

	while (!_kbhit());
}