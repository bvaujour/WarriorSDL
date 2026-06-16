/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:18:14 by injah             #+#    #+#             */
/*   Updated: 2026/04/06 10:05:15 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"


Player::~Player()
{

}

Player::Player(SDL_Texture *texture) : body(*this, texture, -15, -50, 70, 100, 15, 20)
{
	this->rect.w = 40;
	this->rect.h = 50;
	body.addAnim(IDLE, 0, 4, 90);
	body.addAnim(RUN, 1, 8, 90);
	body.addAnim(SLIDE, 2, 8, 90);
	body.addAnim(HITREACT, 3, 4, 90);
	body.addAnim(DEATH, 4, 4, 90);
	this->body.changeAnim(IDLE);
	isFalling = true;
	this->speed = 500;
}


void	Player::update(float deltaTime, t_ctx &ctx)
{
	const Uint8	*keys = SDL_GetKeyboardState(NULL);

	this->direction = 0;
	if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_Q])
	{
		this->direction -= 1;
	}
	if (keys[SDL_SCANCODE_D])
	{
		this->direction += 1;
	}
	if (keys[SDL_SCANCODE_SPACE])
	{
		if (isFalling == false)
		{
			isFalling = true;
			this->velocity.y = -1500;
		}
	}
	if (direction == 0)
		body.changeAnim(IDLE);
	else
	{
		body.changeAnim(RUN);
		if (direction == -1)
			body.setFlip(true);
		else if (direction == 1)
			body.setFlip(false);
	}
	body.update(deltaTime, ctx);
	move(deltaTime, ctx);
}

void	Player::render(SDL_Renderer *renderer, SDL_Point camera)
{
	body.render(renderer, camera);
	SDL_Rect	physicRect = this->rect;
	physicRect.x = this->rect.x - camera.x;
	physicRect.y = this->rect.y - camera.y;
	
	SDL_SetRenderDrawColor(renderer, 100, 255, 100, 150);
	SDL_RenderFillRect(renderer, &physicRect);
}
