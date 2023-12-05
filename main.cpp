#include "pathtrace.h"
//#include "Sphere.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>

int main()
{
	sf::Image image = CPURender(1920, 1080, 16, 4);
	std::cout << "Saving..." << std::endl;
	image.saveToFile(
		"out/render" + std::to_string(time(0)) + ".png");
	std::cout << "Saved ! Press any to continue..." << std::endl;

	while (!_kbhit());
}