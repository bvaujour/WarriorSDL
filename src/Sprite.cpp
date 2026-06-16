/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sprite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 01:13:05 by injah             #+#    #+#             */
/*   Updated: 2026/04/02 13:06:49 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sprite.hpp"

Sprite::Sprite() : texture(NULL)
{
	// std::cout << "Sprite default constructor" << std::endl;
	this->flip = false;
}
Sprite::~Sprite()
{
	// std::cout << "Sprite destructor" << std::endl;
}


Sprite::Sprite(const Sprite &toCpy) : Actor(toCpy)
{
	*this = toCpy;
	// std::cout << "Sprite copy constructor" << std::endl;
}

Sprite 	&Sprite::operator=(const Sprite &toCpy)
{
	// std::cout << "Sprite op=" << std::endl;
	if (this != &toCpy)
	{
		this->srcRect = toCpy.srcRect;
		this->texture = toCpy.texture;
		this->flip = toCpy.flip;
	}
	return (*this);
}
Sprite::Sprite(SDL_Texture *Spriteset, SDL_Rect srcRect, SDL_Rect dstRect)
{
	this->rect = dstRect;
	this->texture = Spriteset;
	this->srcRect = srcRect;
	this->flip = false;
	// std::cout << "Sprite constructor" << std::endl;
}

void	Sprite::update(float deltaTime, t_ctx &ctx)
{
	(void)deltaTime;
	(void)ctx;

}

void	Sprite::render(SDL_Renderer *renderer, SDL_Point camera)
{
	SDL_Rect	renderRect = this->rect;
	renderRect.x = this->rect.x - camera.x;
	renderRect.y = this->rect.y - camera.y;

	if (this->flip)
		SDL_RenderCopyEx(renderer, this->texture, &srcRect, &renderRect, 0, NULL, SDL_FLIP_HORIZONTAL);
	else
		SDL_RenderCopy(renderer, this->texture, &srcRect, &renderRect);
}

void	Sprite::setTexture(SDL_Texture *texture)
{
	this->texture = texture;
}
