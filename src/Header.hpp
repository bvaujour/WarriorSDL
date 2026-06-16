/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:57:08 by injah             #+#    #+#             */
/*   Updated: 2026/04/05 13:35:18 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
 #define HEADER_HPP

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <iostream>
# include <vector>
# include <fstream>
# include <sstream>
# include <stdexcept>
# include <algorithm>
# include <map>
# include <unordered_map>

# define GRAVITY		5000
# define DEBUG			1
# define LEVELSPATH		"assets/levels/"

typedef enum	e_custom_events
{
	CHANGELEVEL,
	ENEMYDEAD,
	NUMCUSTOMEVENT,
}				e_custom_events;

typedef struct	s_tile_layer
{
	std::string			classe;
	std::vector<int>	data;
	int					id;
	std::string			name;
	float				opacity;
	std::string			type;
	bool				visible;
	int					x;
	int					y;
	int					width;
	int					height;
}				t_tile_layer;

typedef struct	s_vertex
{
	float	x;
	float	y;
}				t_vertex;

typedef struct	s_object
{
	int			gid;
	int			id;
	std::string	name;
	float		opacity;
	float		rotation;
	std::string	type;
	bool		visible;
	int			x;
	int			y;
	int			width;
	int			height;
	std::vector<t_vertex>	vertex;

}				t_object;

typedef struct	s_objects_layer
{
	std::string				classe;
	std::string				draworder;
	int						id;
	std::string				name;
	float					opacity;
	std::string				type;
	bool					visible;
	int						x;
	int						y;
	std::vector<t_object>	rectangles;
	std::vector<t_object>	polygones;
	std::vector<t_object>	ellipses;
	std::vector<t_object>	capsules;
	std::vector<t_object>	points;
	std::vector<t_object>	sprites;

}				t_objects_layer;

typedef struct	s_image_layer
{
	std::string			classe;
	int					id;
	std::string			image;
	int					imageheight;
	int					imagewidth;
	std::string			name;
	float				opacity;
	std::string			type;
	bool				visible;
	int					x;
	int					y;
}				t_image_layer;

typedef struct	s_tileset
{
	int			columns;
	int			firstgid;
	std::string	image;
	int			imageheight;
	int			imagewidth;
	int			margin;
	std::string	name;
	int			spacing;
	int			tilecount;
	int			tileheight;
	int			tilewidth;
}				t_tileset;

typedef	struct s_tiled_json
{
	int								compressionlevel;
	size_t							height;
	bool							infinite;
	std::string						orientation;
	std::string						renderorder;
	std::string						tiledversion;
	int								tileheight;
	int								tilewidth;
	std::string						type;
	std::string						version;
	size_t							width;
	std::vector<t_tile_layer>		tileLayers;
	std::vector<t_image_layer>		imageLayers;
	std::vector<t_objects_layer>	objectsLayers;
	std::vector<t_tileset>			tilesets;
}		t_tiled_json;


typedef struct	s_object_short
{
	int									gid;
	std::string							name;
	std::string							type;
	std::map<std::string, std::string>	sproperties;
	std::map<std::string, int>			iproperties;
	float								rotation;
	float								opacity;
	int									x;
	int									y;
	int									width;
	int									height;
}				t_object_short;

typedef struct	s_tileset_short
{
	int			columns;
	std::string	image;
	int			tileSize;
}				t_tileset_short;

typedef struct	s_tile_layer_short
{
	std::vector<int>	data;
	std::string			name;
	float				opacity;
	int					x;
	int					y;
}				t_tile_layer_short;

typedef	struct s_tiled_short
{
	size_t							width;
	size_t							height;
	std::vector<t_tile_layer_short>	tileLayers;
	std::vector<t_object_short>		points;
	std::vector<t_object_short>		rectangles;
	std::vector<t_object_short>		sprites;
	t_tileset_short					tileset;
}		t_tiled_short;


typedef	struct	s_image
{
	SDL_Rect	srcRect;
	SDL_Rect	dstRect;
	SDL_Texture	*texture;
}				t_image;

typedef struct	s_player_start
{
	int	x;
	int	y;
	std::string	name;
}				t_player_start;

class Player;
class Sprite;
class Enemy;

typedef	struct	s_ctx
{
	Player							*player;
	std::vector<Sprite *>			*tiles;
	std::vector<Enemy *>			*enemies;
	int								tileGridWidth;
	int								tileSize;
	int								mapWidth;
	int								mapHeight;
	Uint32							startEvent;
}				t_ctx;


SDL_FPoint						normalize(SDL_FPoint vector);
std::vector<std::vector<int>>	loadCSV(const std::string& filename);
t_tiled_json 					loadTiledJson(const std::string& filename);
t_tiled_short 					loadTiledShort(const std::string& filename);
Sprite							*getCollidingTile(SDL_Rect rect, std::vector<Sprite *> &tiles, int tileGridWidth, int tileSize);
bool							isOutOfBounds(SDL_Rect rect, int mapWidth, int mapHeight);

#endif