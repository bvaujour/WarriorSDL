/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 03:49:57 by injah             #+#    #+#             */
/*   Updated: 2026/04/06 09:54:03 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Enemy.hpp"


Enemy::Enemy()
{
	this->speed = 50;
	this->rect.h = 50;
	this->rect.w = 50;
	this->velocity.y = 0;
	this->velocity.x = 0;
	this->direction = -1;
	this->jumpPower = -1000;
	isFalling = true;
	movementMode = WALKING;
}


Enemy::~Enemy()
{

}

void	Enemy::sendMessageEnemyDead()
{
	SDL_Event event;
	SDL_zero(event);

	event.type = ENEMYDEAD;
	event.user.data1 = this;
	SDL_PushEvent(&event);
}