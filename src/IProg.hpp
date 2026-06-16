/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IGame.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:49:00 by injah             #+#    #+#             */
/*   Updated: 2026/03/30 14:24:47 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>

class	IProg
{
	protected:
		SDL_Renderer	*renderer;
	public:
		virtual 		~IProg() = default;
		virtual void	handleEvent(SDL_Event& event) = 0;
		virtual void	update(float dt) = 0;
		virtual void	render(SDL_Renderer* renderer) = 0;
};