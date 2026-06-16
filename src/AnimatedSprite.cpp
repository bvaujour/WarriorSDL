/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimatedSprite.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:01:49 by injah             #+#    #+#             */
/*   Updated: 2026/04/04 12:54:02 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite()
{
	animIndex = 0;
}

AnimatedSprite::~AnimatedSprite()
{
	
}

AnimatedSprite::AnimatedSprite(const AnimatedSprite &toCpy) : Sprite(toCpy)
{
	*this =toCpy;
}

AnimatedSprite	&AnimatedSprite::operator=(const AnimatedSprite &toCpy)
{
	if (this != &toCpy)
	{
		this->anims = toCpy.anims;
		this->animIndex = toCpy.animIndex;
	}
	return (*this);
}

void	AnimatedSprite::changeAnim(unsigned int newAnimIndex)
{
	if (newAnimIndex == this->animIndex)
		return ;
	if (newAnimIndex >= this->anims.size())
	{
		std::cout << "anim Index too High" << std::endl;
		return ;
	}
	// std::cout << "change anim to " << newAnimIndex << std::endl;
	this->animIndex = newAnimIndex;
	this->anims[newAnimIndex].col = 0;
	this->anims[newAnimIndex].lastUpdate = SDL_GetTicks();
	srcRect.y = srcRect.h * newAnimIndex;
	srcRect.x = 0;
}
void	AnimatedSprite::addAnim(int maxCol, int playRate)
{
	t_anim	anim;
	
	anim.col = 0;
	anim.lastUpdate = SDL_GetTicks();
	anim.maxCol = maxCol;
	anim.playRate = playRate;
	this->anims.push_back(anim);
}


void	AnimatedSprite::updateAnimation(t_anim &anim)
{
	const Uint32	currentTime = SDL_GetTicks();
	if (currentTime - anim.lastUpdate > anim.playRate)
	{
		anim.lastUpdate = currentTime;
		anim.col++;
		if (anim.col >= anim.maxCol)
			anim.col = 0;
		srcRect.x = srcRect.w * anim.col;
		// std::cout << "currentTime:" << currentTime << " anim.lastUpdate:" << anim.lastUpdate << " anim.playRate:" <<  anim.playRate << "animCol: " << anim.col << std::endl;
	}
}


void	AnimatedSprite::update(float deltaTime, t_ctx &ctx)
{
	(void)ctx;
	(void)deltaTime;
	updateAnimation(this->anims[animIndex]);
}