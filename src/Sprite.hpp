/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sprite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 01:12:34 by injah             #+#    #+#             */
/*   Updated: 2026/04/04 11:08:37 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "Header.hpp"
# include "Actor.hpp"

class	Sprite : public Actor
{
	protected:
		SDL_Rect	srcRect;
		SDL_Texture	*texture;
		bool		flip;
		
		public:
					Sprite();
					virtual		~Sprite();
					Sprite(const Sprite &toCpy);
					Sprite		&operator=(const Sprite &toCpy);
					Sprite(SDL_Texture *Spriteset, SDL_Rect srcRect, SDL_Rect dstRect);
		void		update(float deltaTime, t_ctx &ctx);
		void		render(SDL_Renderer *renderer, SDL_Point camera);
		void		setTexture(SDL_Texture *texture);

};

