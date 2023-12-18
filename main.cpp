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

	materials.push_back(Material(glm::vec3(0.7, 0.7, 0.7), Reflective));

	materials.push_back(Material(glm::vec3(0.8, 0, 0), Reflective));
	materials.push_back(Material(glm::vec3(0, 0.8, 0), Reflective));
	materials.push_back(Material(glm::vec3(0, 0, 0.8), Reflective));
	materials.push_back(Material(glm::vec3(0.8, 0, 0.8), Reflective));
	materials.push_back(Material(glm::vec3(0, 0.8, 0.8), Reflective));

	materials.push_back(Material(glm::vec3(1, 1, 1), Emissive, 50));

	scene.push_back(Sphere(glm::vec3(0, 0, 10), 2, &materials[0]));
	scene.push_back(Sphere(glm::vec3(0, 0, 1015), 1000, &materials[1]));
	scene.push_back(Sphere(glm::vec3(1005, 0, 0), 1000, &materials[2]));
	scene.push_back(Sphere(glm::vec3(0, 1005, 0), 1000, &materials[3]));
	scene.push_back(Sphere(glm::vec3(0, -1005, 0), 1000, &materials[4]));
	scene.push_back(Sphere(glm::vec3(-1005, 0, 0), 1000, &materials[5]));
	scene.push_back(Sphere(glm::vec3(-3, 2, 4), 1, &materials[6]));

////////////////////////////////////////////////////////////////////////

	unsigned int width = 1920, height = 1080;
	unsigned int samples = 32, passesSamples = 128;
	int bounces = 4;
	unsigned int name = (unsigned int)time(0);

////////////////////////////////////////////////////////////////////////

	sf::Image image_combined = CPURender(scene, width, height, samples,           bounces, Combined);
	sf::Image image_albedo =   CPURender(scene, width, height, passesSamples,     1,       Albedo);
	sf::Image image_normal =   CPURender(scene, width, height, passesSamples,     1,       Normal);

	std::cout << "Saving..." << std::endl;
	image_combined.saveToFile(
	"out/render" + std::to_string(name) + "_0combined.png");
	image_albedo.saveToFile(
		"out/render" + std::to_string(name) + "_1albedo.png");
	image_normal.saveToFile(
		"out/render" + std::to_string(name) + "_2normal.png");
	std::cout << "Saved ! Press any to continue..." << std::endl;

	while (!_kbhit());
}