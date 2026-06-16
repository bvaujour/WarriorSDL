/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:47:19 by injah             #+#    #+#             */
/*   Updated: 2026/03/28 12:09:26 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "Header.hpp"
# include "IProg.hpp"

class Engine
{
	private:
		SDL_Renderer	*renderer;
		SDL_Window		*window;
		bool			isRunning;
		int				fps;
		float			targetFrameDuration;
		int				screenHeight;
		int				screenWidth;

	public:
						Engine();
						~Engine();
						Engine(Engine &toCpy);
		
		Engine			&operator=(const Engine &toCpy);
		
		void			run(IProg &game, int targetFps);
		void			setFps(int fps);
		SDL_Renderer	*getRenderer() const;
		int				getScreenWidth() const;
		int				getScreenHeight() const;
};