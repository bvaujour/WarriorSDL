/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Slime.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 12:35:34 by injah             #+#    #+#             */
/*   Updated: 2026/04/06 09:59:08 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Slime.hpp"
#include "Player.hpp"


Slime::Slime(int posX, int posY, SDL_Texture *texture) : body(*this, texture, -15, -50, 70, 100, 14, 15)
{
	this->rect.x = posX;
	this->rect.y = posY;
	this->speed = 200;
	this->rect.w = 35;
	this->rect.h = 50;
	this->spriteRect.w = 70;
	this->spriteRect.h = 90;
	this->spriteRect.x = -(this->spriteRect.w - rect.w) / 2;
	this->spriteRect.y = -(this->spriteRect.h - rect.h);
	this->velocity.y = 0;
	this->velocity.x = 0;
	this->direction = 0;
	this->jumpPower = -1500;
	isFalling = false;
	body.addAnim(SLIMEIDLE, 0, 4, 200);
	body.addAnim(SLIMERUN, 0, 4, 90);
	body.addAnim(SLIMEATTACK, 1, 4, 120);
	body.addAnim(SLIMEDEATH, 2, 4, 120);
	body.changeAnim(SLIMEIDLE);
}


Slime::~Slime()
{

}

void	Slime::update(float deltaTime, t_ctx &ctx)
{
	body.update(deltaTime, ctx);
	move(deltaTime, ctx);
	if (SDL_HasIntersection(&ctx.player->getRect(), &this->rect))
		body.changeAnim(SLIMEATTACK);
	else
		body.changeAnim(SLIMEIDLE);
	// std::cout << isFalling << std::endl;
}

void	Slime::render(SDL_Renderer *renderer, SDL_Point camera)
{
	body.render(renderer, camera);
	SDL_Rect	physicRect = this->rect;
	physicRect.x = this->rect.x - camera.x;
	physicRect.y = this->rect.y - camera.y;
	
	SDL_SetRenderDrawColor(renderer, 100, 255, 100, 150);
	SDL_RenderFillRect(renderer, &physicRect);
}