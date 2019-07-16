#pragma once

#include <cstdint>
#include <cstddef>

#define DISABLEAVRMIN
#include <Pokitto.h>

#include "Grid.h"

class Game
{
private:
	std::size_t tileWidth = 16;
	std::size_t tileHeight = 16;
	std::size_t tileTypes = 6;

private:
	std::size_t selectorX;
	std::size_t selectorY;
	Grid<std::uint8_t, 10, 10> grid;

public:
	void run();
	void update();
	void render();
};