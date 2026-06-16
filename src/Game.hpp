/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:12:44 by injah             #+#    #+#             */
/*   Updated: 2026/04/05 14:57:44 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "Header.hpp"
# include "Player.hpp"
# include "Enemy.hpp"
# include "Actor.hpp"
# include "Level.hpp"
# include "IProg.hpp"
class	Game : public IProg
{
	private:
				bool 								pause;
				int									fade;
				int									fadeDirection;
				int									fadeSpeed;
				Player								*player;
				SDL_Texture							*playerTexture;
				int									cameraDeadZone;
				int									screenWidth;
				int									screenHeight;
				SDL_Point							cameraPos;
				Level								level;
				t_ctx								ctx;
				void								openLevel(const std::string &levelName, const std::string &playerStartName);
				

	public:
					Game(SDL_Renderer *renderer, int screenWidth, int screenHeight);
					~Game();

		void		handleEvent(SDL_Event& event);
		void 		update(float dt);
		void 		render(SDL_Renderer* renderer);
};