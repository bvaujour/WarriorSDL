/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Actor.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 18:27:57 by injah             #+#    #+#             */
/*   Updated: 2026/04/06 10:03:25 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Actor.hpp"
#include "Game.hpp"

Actor::Actor()
{
	this->rect.x = 0;
	this->rect.y = 0;
	this->rect.w = 100;
	this->rect.h = 100;
}

Actor::Actor(int x, int y, int width, int height)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = width;
	this->rect.h = height;
}



Actor::~Actor()
{
	// std::cout << "Actor Destructor" << std::endl;
}

Actor::Actor(const Actor &toCpy)
{
	*this = toCpy;
}
Actor	&Actor::operator=(const Actor &toCpy)
{
	if (this != &toCpy)
	{
		this->rect = toCpy.rect;
	}
	return (*this);
}

const SDL_Rect	&Actor::getRect() const
{
	return (this->rect);
}

void	Actor::setPosition(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
}

void	Actor::setPosX(int x)
{
	this->rect.x = x;
}
void	Actor::setPosY(int y)
{
	this->rect.y = y;
}

SDL_Point	Actor::getPosition() const
{
	SDL_Point	position;

	position.x = rect.x;
	position.y = rect.y;
	return (position);
}