/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Level.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 03:42:59 by injah             #+#    #+#             */
/*   Updated: 2026/04/06 09:40:58 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Level.hpp"

void	Level::loadTiles(const std::vector<int> &tileIdTab, const std::string &layerName)
{
	SDL_Rect	srcRect;
	SDL_Rect	dstRect;
	Sprite		*tile;
	int			tileId;
	const int	columns = this->tiled_map.tileset.columns;
	const int	srcSize = this->tiled_map.tileset.tileSize;

	for (size_t y = 0; y < this->tiled_map.height; y++)
	{
		for (size_t x = 0; x < this->tiled_map.width; x++)
		{
			tileId = tileIdTab[y * this->tiled_map.width + x];
			tileId -= 1;
			if (tileId == -1)
			{
				if (layerName == "Collisions")
				{
					tiles.push_back(NULL);
				}
				continue;
			}
			srcRect.x = (tileId % columns) *  srcSize;
			srcRect.y = (tileId / columns) *  srcSize;
			srcRect.w = srcSize;
			srcRect.h = srcSize;

			dstRect.x = x * this->tileSize;
			dstRect.y = y * this->tileSize;
			dstRect.w = this->tileSize;
			dstRect.h = this->tileSize;
			if (layerName == "Collisions")
			{
				tile = new Sprite(this->tileset, srcRect, dstRect);
				this->actors.push_back(tile);
				tiles.push_back(tile);
			}
			else
				actors.push_back(new Sprite(this->tileset, srcRect, dstRect));
		}
	}
}



void	Level::loadMap(SDL_Renderer *renderer, std::string levelName)
{
	std::string	tilesetPath;
	for (size_t i = 0; i < this->actors.size(); i++)
	{
		delete (this->actors[i]);
	}
	this->tiles.resize(0);
	this->actors.resize(0);
	this->enemies.resize(0);
	this->playerStarts.resize(0);
	this->tiled_map = loadTiledShort(LEVELSPATH + levelName + ".tmj");
	tilesetPath = LEVELSPATH + this->tiled_map.tileset.image;
	this->tileset = IMG_LoadTexture(renderer, tilesetPath.c_str());
	if (!this->tileset)
		throw std::runtime_error("failed to load tileset: " + tilesetPath);
	this->tileSize = 100;
	this->mapRatio = (float)this->tileSize / this->tiled_map.tileset.tileSize;
	this->mapWidth = this->tiled_map.width * this->tileSize;
	this->mapHeight = this->tiled_map.height * this->tileSize;
	for (size_t i = 0; i < this->tiled_map.tileLayers.size(); i++)
	{
		std::cout << i << std::endl;
		this->loadTiles(this->tiled_map.tileLayers[i].data, this->tiled_map.tileLayers[i].name);
	}
	for (size_t i = 0; i < this->tiled_map.points.size(); i++)
	{
		if (this->tiled_map.points[i].type == "PlayerStart")
		{
			t_player_start	playerStart;

			playerStart.x = this->tiled_map.points[i].x * this->mapRatio;
			playerStart.y = this->tiled_map.points[i].y * this->mapRatio;
			playerStart.name = this->tiled_map.points[i].name;
			std::cout << "saved playerstart: " << this->tiled_map.points[i].name << std::endl;
			this->playerStarts.push_back(playerStart);
		}
		if (this->tiled_map.points[i].name == "Enemy")
		{
			Enemy	*enemy = new  Slime(this->tiled_map.points[i].x * this->mapRatio, this->tiled_map.points[i].y * this->mapRatio, this->slimeTexture);
			std::cout << "enemy pushed" << std::endl;
			this->actors.push_back(enemy);
			this->enemies.push_back(enemy);
		}
	}
	for (size_t i = 0; i < this->tiled_map.rectangles.size(); i++)
	{
		SDL_Rect	rect;
		std::cout << "found trigger" << std::endl;
		rect.x = this->tiled_map.rectangles[i].x  * this->mapRatio;
		rect.y = this->tiled_map.rectangles[i].y  * this->mapRatio;
		rect.w = this->tiled_map.rectangles[i].width * this->mapRatio;
		rect.h = this->tiled_map.rectangles[i].height * this->mapRatio;
		if (this->tiled_map.rectangles[i].type == "NextLevelZone")
			this->actors.push_back(new NextLevelZone(rect, this->tiled_map.rectangles[i].name, this->tiled_map.rectangles[i].sproperties["PlayerStart"]));
	}
	for (size_t i = 0; i < this->tiled_map.sprites.size(); i++)
	{
		SDL_Rect	srcRect;
		SDL_Rect	dstRect;

		srcRect.x = ((this->tiled_map.sprites[i].gid - 1) % this->tiled_map.tileset.columns) * this->tiled_map.tileset.tileSize;
		srcRect.y = ((this->tiled_map.sprites[i].gid - 1) / this->tiled_map.tileset.columns) * this->tiled_map.tileset.tileSize;
		srcRect.w = this->tiled_map.tileset.tileSize;
		srcRect.h = this->tiled_map.tileset.tileSize;
		dstRect.x = this->tiled_map.sprites[i].x * this->mapRatio;
		dstRect.y = (this->tiled_map.sprites[i].y - this->tiled_map.sprites[i].height) * this->mapRatio;
		dstRect.w = this->tiled_map.sprites[i].width * this->mapRatio;
		dstRect.h = this->tiled_map.sprites[i].height * this->mapRatio;
		this->actors.push_back(new Sprite(this->tileset, srcRect, dstRect));
	}
}

Level::Level(SDL_Renderer *renderer)
{
	this->tileset = NULL;
	this->renderer = renderer;
	this->slimeTexture = IMG_LoadTexture(renderer, "assets/characters/Slime/Slime.png");
	if (this->slimeTexture == NULL)
		throw std::runtime_error("Game constructor: failed to load texture: assets/characters/Slime/Slime.png");
}

Level::~Level()
{
	if (this->tileset)
		SDL_DestroyTexture(this->tileset);
	if (this->slimeTexture)
		SDL_DestroyTexture(this->slimeTexture);
	for (size_t i = 0; i < this->actors.size(); i++)
	{
		delete (this->actors[i]);
	}
}

void	Level::removeEnemy(Enemy *enemy)
{
	enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
	actors.erase(std::remove(actors.begin(), actors.end(), enemy), actors.end());
	delete enemy;
}


void	Level::handleEvent(SDL_Event& event)
{
	if (event.type == ENEMYDEAD)
	{
		removeEnemy(static_cast<Enemy *>(event.user.data1));
		std::cout << "enemy size: " << enemies.size() << std::endl;
	}
}


void	Level::update(float deltaTime, t_ctx &ctx)
{
	for (size_t i = 0; i < this->actors.size(); i++)
	{
		this->actors[i]->update(deltaTime, ctx);
	}
}
void	Level::render(SDL_Renderer *renderer, SDL_Point camera)
{
	for (size_t i = 0; i < this->actors.size(); i++)
	{
		this->actors[i]->render(renderer, camera);
	}
}

std::vector<Enemy *>	&Level::getEnemies()
{
	return (this->enemies);
}
std::vector<Sprite *>	&Level::getTiles()
{
	return (this->tiles);
}

int	Level::getMapWidth() const
{
	return (this->mapWidth);
}
int	Level::getMapHeight() const
{
	return (this->mapHeight);
}
int	Level::getTileGridWidth() const
{
	return (this->tiled_map.width);
}
int	Level::getTileSize() const
{
	return (this->tileSize);
}


std::vector<t_player_start>	Level::getPlayerStart() const
{
	return (this->playerStarts);
}

SDL_Point	Level::getPlayerStart(const std::string &name) const
{
	for (size_t i = 0; i < playerStarts.size(); i++)
	{
		std::cout << "look for name: " << name << " playerStarts[i].name: " << playerStarts[i].name << std::endl;
		if (playerStarts[i].name == name)
			return ((SDL_Point){playerStarts[i].x, playerStarts[i].y});
	}
	return ((SDL_Point){0, 0});
}


