/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimatedSpriteComp.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 13:00:06 by injah             #+#    #+#             */
/*   Updated: 2026/04/06 10:02:31 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Header.hpp"
typedef struct	s_animation
{
	unsigned int	maxCol;
	unsigned int	col;
	unsigned int	row;
	unsigned int	playRate;
	unsigned int	lastUpdate;
}				t_animation;

class Actor;
class AnimatedSpriteComp
{
	private:
		Actor											*owner;
		SDL_Texture										*texture;
		t_animation										currentAnim;
		std::unordered_map<unsigned int, t_animation>	animations;
		int												renderOffsetX;
		int												renderOffsetY;
		int												renderWidth;
		int												renderHeight;
		SDL_Rect										srcRect;
		unsigned int									animIndex;
		bool											flip;
		
	public:
					AnimatedSpriteComp(Actor &owner, SDL_Texture *texture, int renderOffsetX, int renderOffsetY, int renderWidth, int renderHeight, int spriteWidth, int spriteHeight);
					~AnimatedSpriteComp();
		void		update(float deltaTime, t_ctx &ctx);
		void		render(SDL_Renderer *renderer, SDL_Point camera);
		void		addAnim(int animIndex, int row, int maxCol, int playRate);
		void		changeAnim(unsigned int newAnimIndex);
		void		setFlip(bool newFlip);
};


