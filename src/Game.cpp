#include "Game.h"

#include "Tiles.h"

void Game::run()
{
	using Pokitto::Core;
	using Pokitto::Display;

	Core::begin();

	Display::load565Palette(Images::tilesPalette);

	while (Core::isRunning())
		if (Core::update())
		{
			this->update();
			this->render();
		}
}

void Game::update()
{
	using Pokitto::Buttons;

	if(Buttons::leftBtn())
		if(this->selectorX > 0)
			--this->selectorX;

	if(Buttons::rightBtn())
		if(this->selectorX < (this->grid.getWidth() - 1))
			++this->selectorX;

	if(Buttons::upBtn())
		if(this->selectorY > 0)
			--this->selectorY;

	if(Buttons::downBtn())
		if(this->selectorY < (this->grid.getHeight() - 1))
			++this->selectorY;

	auto & selectedTile = this->grid.get(this->selectorX, this->selectorY);

	if(Buttons::aBtn())
	{
		if(selectedTile > 0)
			--selectedTile;
		else
			selectedTile = (tileTypes - 1);
	}

	if(Buttons::bBtn())
	{
		if(selectedTile < (tileTypes - 1))
			++selectedTile;
		else
			selectedTile = 0;
	}
}

void Game::render()
{
	using Pokitto::Display;

	for(std::size_t y = 0; y < this->grid.getHeight(); ++y)
	{
		const int drawY = (y * tileHeight);

		for(std::size_t x = 0; x < this->grid.getWidth(); ++x)
		{
			const int drawX = (x * tileWidth);

			const std::uint8_t index = this->grid.get(x, y);

			Display::drawBitmap(drawX, drawY, Images::tiles, index);

			if((this->selectorX == x) && (this->selectorY == y))
				Display::drawRect(drawX, drawY, tileWidth, tileHeight);
		}
	}
}