/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:16:20 by injah             #+#    #+#             */
/*   Updated: 2026/04/06 09:51:59 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "Game.hpp"

Character::Character() : speed(0), direction(0), velocity({0, 0}), isFalling(false), movementMode(WALKING), floor(NULL)
{
	std::cout << "character construct" << std::endl;
}

Character::~Character()
{
	
}

Character::Character(const Character &toCpy) : Actor(toCpy)
{
	*this = toCpy;
}

Character		&Character::operator=(const Character &toCpy)
{
	if (this != &toCpy)
	{
		this->speed = toCpy.speed;
		this->direction = toCpy.direction;
		this->velocity = toCpy.velocity;
		this->isFalling = toCpy.isFalling;
		this->jumpPower = toCpy.jumpPower;
		this->movementMode = toCpy.movementMode;
		this->floor = toCpy.floor;
	}
	return (*this);
}

void	Character::move(float deltaTime, t_ctx &ctx)
{
	floor = getCollidingTile((SDL_Rect){rect.x, rect.y + 1, rect.w, rect.h}, *ctx.tiles, ctx.tileGridWidth, ctx.tileSize);
	if (floor == NULL)
		this->isFalling = true;
	if (isFalling && movementMode != FLYING)
	{
		velocity.y += GRAVITY * deltaTime;
	}
	velocity.x = direction * speed;
	if (velocity.x)
		moveX(deltaTime, ctx);
	if (velocity.y)
		moveY(deltaTime, ctx);
}

void	Character::moveX(float deltaTime, t_ctx &ctx)
{
	SDL_Rect	nextRectX;
	Sprite		*tile;

	nextRectX = rect;
	nextRectX.x += velocity.x * deltaTime;
	tile = getCollidingTile(nextRectX, *ctx.tiles, ctx.tileGridWidth, ctx.tileSize);
	if (tile)
	{
		if (velocity.x < 0)
		{
			rect.x = tile->getRect().x + tile->getRect().w;
			std::cout << "colliding Left" << std::endl;
		}
		else if (velocity.x > 0)
		{
			rect.x = tile->getRect().x - rect.w;
			std::cout << "colliding Right" << std::endl;
		}
	}
	else
		rect.x = nextRectX.x;
}

void	Character::moveY(float deltaTime, t_ctx &ctx)
{
	SDL_Rect	nextRectY;
	Sprite		*tile;

	nextRectY = rect;
	nextRectY.y += velocity.y * deltaTime;
	tile = getCollidingTile(nextRectY, *ctx.tiles, ctx.tileGridWidth, ctx.tileSize);
	if (tile)
	{
		if (velocity.y > 0)
		{
			isFalling = false;
			std::cout << "land" << std::endl;
			rect.y = tile->getRect().y - rect.h;
		}
		else if (velocity.y < 0)
		{
			std::cout << "knock head" << std::endl;
		}
		velocity.y = 0;
	}
	else
	{
		std::cout << "fall" << std::endl;
		rect.y = nextRectY.y;
		isFalling = true;
	}
}

const SDL_FPoint	&Character::getVelocity() const
{
	return(this->velocity);
}

void	Character::setVelocityX(float x)
{
	this->velocity.x = x;
}
void	Character::setVelocityY(float y)
{
	this->velocity.y = y;
}
void	Character::setVelocity(SDL_FPoint velocity)
{
	this->velocity = velocity;
}

void	Character::setIsFalling(bool isFalling)
{
	this->isFalling = isFalling;
}
