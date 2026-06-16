/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 22:16:12 by injah             #+#    #+#             */
/*   Updated: 2026/04/06 09:49:27 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "Header.hpp"
# include "AnimatedSprite.hpp"

typedef		enum e_movementMode
{
	WALKING,
	FLYING,
}			e_movementMode;

class	Character : public Actor
{
	protected:
		int				speed;
		int				direction;
		SDL_FPoint		velocity;
		bool			isFalling;
		int				jumpPower;
		e_movementMode	movementMode;
		Sprite			*floor;
		SDL_Rect		spriteRect;
		void			move(float deltaTime, t_ctx &ctx);
		void			moveX(float deltaTime, t_ctx &ctx);
		void			moveY(float deltaTime, t_ctx &ctx);


	public:
							Character();
		virtual				~Character();
							Character(const Character &toCpy);
		Character			&operator=(const Character &toCpy);
		virtual void		render(SDL_Renderer *renderer, SDL_Point camera) = 0;
		const SDL_FPoint	&getVelocity() const;
		void				setVelocityX(float x);
		void				setVelocityY(float y);
		void				setVelocity(SDL_FPoint velocity);
		void				setIsFalling(bool isFalling);
};