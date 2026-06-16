/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimatedSpriteComp.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 13:41:41 by injah             #+#    #+#             */
/*   Updated: 2026/04/06 10:04:05 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AnimatedSpriteComp.hpp"
#include "Actor.hpp"


AnimatedSpriteComp::AnimatedSpriteComp(Actor &owner, SDL_Texture *texture, int renderOffsetX, int renderOffsetY, int renderWidth, int renderHeight, int spriteWidth, int spriteHeight)
{
	this->owner = &owner;
	this->texture = texture;
	this->renderOffsetX = renderOffsetX;
	this->renderOffsetY = renderOffsetY;
	this->renderWidth = renderWidth;
	this->renderHeight = renderHeight;
	this->srcRect.y = 0;
	this->srcRect.x = 0;
	this->srcRect.w = spriteWidth;
	this->srcRect.h = spriteHeight;
	this->animIndex = -1;
	this->currentAnim = (t_animation){};
	this->flip = false;
}

AnimatedSpriteComp::~AnimatedSpriteComp()
{
}

void		AnimatedSpriteComp::update(float deltaTime, t_ctx &ctx)
{
	(void)deltaTime;
	(void)ctx;
	const Uint32	currentTime = SDL_GetTicks();
	if (currentTime - currentAnim.lastUpdate > currentAnim.playRate)
	{
		currentAnim.lastUpdate = currentTime;
		currentAnim.col++;
		if (currentAnim.col >= currentAnim.maxCol)
			currentAnim.col = 0;
		srcRect.x = this->srcRect.w * currentAnim.col;
		// std::cout << "currentTime:" << currentTime << " currentAnim.lastUpdate:" << currentAnim.lastUpdate << " currentAnim.playRate:" <<  currentAnim.playRate << "animCol: " << currentAnim.col << std::endl;
	}
	
}
void		AnimatedSpriteComp::render(SDL_Renderer *renderer, SDL_Point camera)
{
	const SDL_Rect	ownerRect = owner->getRect();
	SDL_Rect	renderRect;
	renderRect.x = ownerRect.x + this->renderOffsetX - camera.x;
	renderRect.y = ownerRect.y + this->renderOffsetY - camera.y;
	renderRect.w = this->renderWidth;
	renderRect.h = this->renderHeight;

	if (this->flip == true)
		SDL_RenderCopyEx(renderer, this->texture, &srcRect, &renderRect, 0, NULL, SDL_FLIP_HORIZONTAL);
	else
		SDL_RenderCopy(renderer, this->texture, &srcRect, &renderRect);
}

void	AnimatedSpriteComp::changeAnim(unsigned int newAnimIndex)
{
	if (newAnimIndex == this->animIndex)
		return ;
	if (animations.find(newAnimIndex) != animations.end())
		currentAnim = animations[newAnimIndex];
	this->animIndex = newAnimIndex;
	currentAnim.col = 0;
	currentAnim.lastUpdate = SDL_GetTicks();
	srcRect.y = srcRect.h * currentAnim.row;
	srcRect.x = 0;
}
void	AnimatedSpriteComp::addAnim(int animIndex, int row, int maxCol, int playRate)
{
	t_animation	anim;
	
	anim.col = 0;
	anim.lastUpdate = SDL_GetTicks();
	anim.maxCol = maxCol;
	anim.playRate = playRate;
	anim.row = row;
	this->animations[animIndex] = anim;
}

void	AnimatedSpriteComp::setFlip(bool newFlip)
{
	this->flip = newFlip;
}
