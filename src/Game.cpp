/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:12:53 by injah             #+#    #+#             */
/*   Updated: 2026/04/05 15:00:34 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"


Game::Game(SDL_Renderer *renderer, int screenWidth, int screenHeight) : level(renderer)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	this->renderer = renderer;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->fade = 255;
	this->fadeDirection = -1;
	this->fadeSpeed = 500;
	this->pause = false;
	std::cout << "Game Default constructor" << std::endl;
	cameraPos.x = 0;
	cameraPos.y = 0;
	cameraDeadZone = screenWidth / 6;
	this->playerTexture = IMG_LoadTexture(renderer, "assets/characters/player/knight_spriteSheet.png");
	if (this->playerTexture == NULL)
		throw std::runtime_error("Game constructor: failed to load texture: assets/characters/player/knight_spriteSheet.png");
	player = new Player(this->playerTexture);
	ctx.startEvent = SDL_RegisterEvents(NUMCUSTOMEVENT);
	this->openLevel("Start", "0");
	// SDL_Rect rect = (SDL_Rect){0, 0, 500, screenHeight};
	// SDL_RenderSetScale(renderer, 0.5, 0.5);
}


Game::~Game()
{
	std::cout << "Game Destructor" << std::endl;
	SDL_DestroyTexture(this->playerTexture);
	delete (player);
}

void	Game::handleEvent(SDL_Event &event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.scancode == SDL_SCANCODE_1)
		{
			// this->openLevel("assets/levels/level1");
			
		}
		if (event.key.keysym.scancode == SDL_SCANCODE_2)
		{
			// this->openLevel("assets/levels/level1");
			
		}
	}
	else if (event.type == CHANGELEVEL)
	{
		std::string *levelName = (std::string *)event.user.data1;
		std::string *playerStartName = (std::string *)event.user.data2;
		openLevel(*levelName, *playerStartName);
		delete (levelName);
		delete (playerStartName);
		// std::cout << "change level to"  << *levelName << " playerstart: " << *playerStartName << std::endl;
		
	}
	level.handleEvent(event);
}

void	Game::update(float deltaTime)
{
	if (this->pause == false)
	{
		player->update(deltaTime, ctx);
		level.update(deltaTime, ctx);
		if (cameraPos.x < player->getRect().x + player->getRect().w - screenWidth / 2 - cameraDeadZone)
			cameraPos.x = player->getRect().x + player->getRect().w - screenWidth / 2 - cameraDeadZone;
		else if (cameraPos.x > player->getRect().x - screenWidth / 2 + cameraDeadZone)
			cameraPos.x = player->getRect().x - screenWidth / 2 + cameraDeadZone;
		if (cameraPos.x < 0)
			cameraPos.x = 0;
		if (cameraPos.x + screenWidth > level.getMapWidth())
			cameraPos.x = level.getMapWidth() - screenWidth;
		cameraPos.y = player->getRect().y - screenHeight / 2;
		if (cameraPos.y < 0)
			cameraPos.y = 0;
		if (cameraPos.y + screenHeight > level.getMapHeight())
			cameraPos.y = level.getMapHeight() - screenHeight;
	}
	this->fade += this->fadeDirection * deltaTime * fadeSpeed;
	if (this->fade < 0)
	{
		this->fade = 0;
		this->fadeDirection = 0;
	}
	else if (this->fade > 255)
	{
		this->fade = 255;
		this->fadeDirection = 0;
	}
}


void	Game::render(SDL_Renderer *renderer)
{
	level.render(renderer, cameraPos);
	player->render(renderer, cameraPos);
	if (fade > 0)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, (Uint8)fade);
		SDL_RenderFillRect(renderer, NULL);
	}
}

void	Game::openLevel(const std::string &levelName, const std::string &playerStartName)
{
	SDL_Point	playerStart;

	this->fadeDirection = -1;
	this->fadeSpeed = 500;
	this->fade = 255;
	level.loadMap(renderer, levelName);
	playerStart = level.getPlayerStart(playerStartName);
	player->setPosition(playerStart.x, playerStart.y);
	ctx.player = this->player;
	ctx.tiles = &this->level.getTiles();
	ctx.enemies = &this->level.getEnemies();
	ctx.mapWidth = this->level.getMapWidth();
	ctx.mapHeight = this->level.getMapHeight();
	ctx.tileSize = this->level.getTileSize();
	ctx.tileGridWidth = this->level.getTileGridWidth();
}