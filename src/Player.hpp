/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:18:05 by injah             #+#    #+#             */
/*   Updated: 2026/04/06 09:42:21 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "Header.hpp"
# include "Character.hpp"
# include "AnimatedSpriteComp.hpp"

typedef	enum	e_playerAnim
{
	IDLE,
	RUN,
	SLIDE,
	HITREACT,
	DEATH,
}				e_playerAnim;

class	Player : public Character
{
	private:
		AnimatedSpriteComp	body;
	public:
					~Player();
					Player(SDL_Texture *texture);
		void		update(float deltaTime, t_ctx &ctx);
		void		render(SDL_Renderer *renderer, SDL_Point camera);
};