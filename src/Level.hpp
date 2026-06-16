/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Level.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 03:42:26 by injah             #+#    #+#             */
/*   Updated: 2026/04/06 09:40:27 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "Header.hpp"
# include "Player.hpp"
# include "NextLevelZone.hpp"
# include "Slime.hpp"
# include "Sprite.hpp"
# include "Enemy.hpp"


class Level
{
	private:
		t_tiled_short								tiled_map;
		float										mapRatio;
		SDL_Texture									*tileset;
		int											tileSize;
		int											mapWidth;
		int											mapHeight;
		std::vector<Sprite *>						tiles;
		std::vector<Enemy *>						enemies;
		std::vector<Actor *>						actors;
		std::vector<t_player_start>					playerStarts;
		void										loadTiles(const std::vector<int> &tileIdTab, const std::string &layerName);
		void										removeEnemy(Enemy *enemy);
		SDL_Texture									*slimeTexture;
		SDL_Renderer								*renderer;




	public:
													Level(SDL_Renderer *renderer);
													~Level();
		void										handleEvent(SDL_Event& event);
		void										update(float deltaTime, t_ctx &ctx);
		void										render(SDL_Renderer *renderer, SDL_Point camera);
		void										loadMap(SDL_Renderer *renderer, std::string levelPath);
		std::vector<Enemy *>						&getEnemies();
		std::vector<Sprite *>						&getTiles();
		int											getMapWidth() const;
		int											getMapHeight() const;
		int											getTileGridWidth() const;
		int											getTileSize() const;
		std::vector<t_player_start>					getPlayerStart() const;
		SDL_Point									getPlayerStart(const std::string &name) const;

};