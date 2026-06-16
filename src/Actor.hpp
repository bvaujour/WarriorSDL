/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Actor.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 18:23:34 by injah             #+#    #+#             */
/*   Updated: 2026/04/06 10:03:13 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "Header.hpp"


class	Actor
{
	protected:
		SDL_Rect				rect;
	public:
								Actor();
								Actor(int x, int y, int width, int height);
		virtual					~Actor();
								Actor(const Actor &toCpy);
		Actor					&operator=(const Actor &toCpy);
		virtual void			update(float deltaTime, t_ctx &ctx) = 0;
		virtual void			render(SDL_Renderer *renderer, SDL_Point camera) = 0;
		const SDL_Rect			&getRect() const;
		void					setPosition(int x, int y);
		SDL_Point				getPosition() const;
		void					setPosX(int x);
		void					setPosY(int y);
};