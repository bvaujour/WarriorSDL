/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NextLevelZone.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 01:40:22 by injah             #+#    #+#             */
/*   Updated: 2026/04/02 19:09:58 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NextLevelZone.hpp"
#include "Player.hpp"



NextLevelZone::NextLevelZone(/* args */)
{
	
}

NextLevelZone::NextLevelZone(SDL_Rect rect, const std::string &nextLevel, const std::string &nextPlayerStart)
{
	this->nextLevel = nextLevel;
	this->rect = rect;
	this->nextPlayerStart = nextPlayerStart;
}

NextLevelZone::~NextLevelZone()
{
	
}

void	NextLevelZone::update(float deltaTime, t_ctx &ctx)
{
	(void)deltaTime;
	if (SDL_HasIntersection(&ctx.player->getRect(), &this->getRect()))
	{
		SDL_Event event;
		SDL_zero(event);

		event.type = CHANGELEVEL;
		event.user.data1 = new std::string(this->nextLevel);
		event.user.data2 = new std::string(this->nextPlayerStart);
		SDL_PushEvent(&event);
	}
}
void	NextLevelZone::render(SDL_Renderer *renderer, SDL_Point camera)
{
	if (DEBUG >= 1)
	{
		SDL_Rect	renderRect = this->rect;
		renderRect.x -= camera.x;
		renderRect.y -= camera.y;
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
		SDL_RenderFillRect(renderer, &renderRect);
	}
}