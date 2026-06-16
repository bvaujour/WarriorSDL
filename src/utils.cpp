/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:53:27 by injah             #+#    #+#             */
/*   Updated: 2026/04/03 20:41:03 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header.hpp"
#include "Sprite.hpp"
#include "nlohmann/json.hpp"

SDL_FPoint	normalize(SDL_FPoint vector)
{
	float length;
	
	length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	if (length > 0.0f)
	{
		vector.x /= length;
		vector.y /= length;
	}
	return (vector);
}

std::vector<std::vector<int>> loadCSV(const std::string& filename)
{
	std::ifstream					file(filename);
	std::vector<std::vector<int>>	map;
	std::string						line;

	while (std::getline(file, line))
	{
		std::vector<int>	row;
		std::stringstream	ss(line);
		std::string			value;

		while (std::getline(ss, value, ','))
		{
			if (!value.empty())
				row.push_back(std::stoi(value));
		}
		if (!row.empty())
			map.push_back(row);
	}

	return map;
}

t_tiled_json loadTiledJson(const std::string& filename)
{
	std::ifstream	file(filename);
	nlohmann::json	json;
	t_tiled_json	tiled = {};
	file >> json;
	
	tiled.compressionlevel = json["compressionlevel"];
	tiled.height = json["height"];
	tiled.infinite = json["infinite"];
	tiled.orientation = json["orientation"];
	tiled.renderorder = json["renderorder"];
	tiled.tiledversion = json["tiledversion"];
	tiled.tileheight = json["tileheight"];
	tiled.tilewidth = json["tilewidth"];
	tiled.type = json["type"];
	tiled.version = json["version"];
	tiled.width = json["width"];
	for (const auto &tileset : json["tilesets"])
	{
		t_tileset	tileset_info = {};

		tileset_info.columns = tileset["columns"];
		tileset_info.firstgid = tileset["firstgid"];
		tileset_info.image = tileset["image"];
		tileset_info.imageheight = tileset["imageheight"];
		tileset_info.imagewidth = tileset["imagewidth"];
		tileset_info.margin = tileset["margin"];
		tileset_info.name = tileset["name"];
		tileset_info.spacing = tileset["spacing"];
		tileset_info.tilecount = tileset["tilecount"];
		tileset_info.tileheight = tileset["tileheight"];
		tileset_info.tilewidth = tileset["tilewidth"];
		tiled.tilesets.push_back(tileset_info);
	}
	for (const auto &layer : json["layers"])
	{
		if (layer["type"] == "tilelayer")
		{
			t_tile_layer	tileLayer = {};
			
			tileLayer.classe = layer["class"];
			tileLayer.data = layer["data"].get<std::vector<int>>();
			tileLayer.height = layer["height"];
			tileLayer.id = layer["id"];
			tileLayer.name = layer["name"];
			tileLayer.opacity = layer["opacity"];
			tileLayer.type = layer["type"];
			tileLayer.visible = layer["visible"];
			tileLayer.width = layer["width"];
			tileLayer.x = layer["x"];
			tileLayer.y = layer["y"];
			tiled.tileLayers.push_back(tileLayer);
		}
		if (layer["type"] == "imagelayer")
		{
			t_image_layer	imageLayer = {};
			
			imageLayer.classe = layer["class"];
			imageLayer.id = layer["id"];
			imageLayer.image = layer["image"];
			imageLayer.imageheight = layer["imageheight"];
			imageLayer.imagewidth = layer["imagewidth"];
			imageLayer.name = layer["name"];
			imageLayer.opacity = layer["opacity"];
			imageLayer.type = layer["type"];
			imageLayer.visible = layer["visible"];
			imageLayer.x = layer["x"];
			imageLayer.y = layer["y"];
			tiled.imageLayers.push_back(imageLayer);
		}
		if (layer["type"] == "objectgroup")
		{
			t_objects_layer	objectsLayer = {};
			
			objectsLayer.classe = layer["class"];
			objectsLayer.draworder = layer["draworder"];
			objectsLayer.id = layer["id"];
			objectsLayer.name = layer["name"];
			objectsLayer.opacity = layer["opacity"];
			objectsLayer.type = layer["type"];
			objectsLayer.visible = layer["visible"];
			objectsLayer.x = layer["x"];
			objectsLayer.y = layer["y"];
			for (const auto &object : layer["objects"])
			{
				t_object	objectInfo = {};
				
				objectInfo.height = object["height"];
				objectInfo.id = object["id"];
				objectInfo.name = object["name"];
				objectInfo.opacity = object["opacity"];
				objectInfo.rotation = object["rotation"];
				objectInfo.type = object["type"];
				objectInfo.visible = object["visible"];
				objectInfo.width = object["width"];
				objectInfo.x = object["x"];
				objectInfo.y = object["y"];
				if (object.contains("polygon"))
				{
					for (const auto &vertex : object["polygon"])
					{
						t_vertex	vertexInfo = {};

						vertexInfo.x = vertex["x"];
						vertexInfo.y = vertex["y"];
						objectInfo.vertex.push_back(vertexInfo);
					}
					objectsLayer.polygones.push_back(objectInfo);	
				}
				else if (object.contains("gid"))
				{
					objectInfo.gid = object["gid"];
					objectsLayer.sprites.push_back(objectInfo);
				}
				else if (object.contains("point"))
					objectsLayer.points.push_back(objectInfo);
				else if (object.contains("elipse"))
					objectsLayer.ellipses.push_back(objectInfo);
				else if (object.contains("capsule"))
					objectsLayer.capsules.push_back(objectInfo);
				else
					objectsLayer.rectangles.push_back(objectInfo);
			}
		}
	}
	return (tiled);
}

t_tiled_short loadTiledShort(const std::string& filename)
{
	std::ifstream	file(filename);
	nlohmann::json	json;
	t_tiled_short	tiled = {};
	file >> json;
	
	tiled.height = json["height"];
	tiled.width = json["width"];
	for (const auto &tileset : json["tilesets"])
	{
		t_tileset_short	tileset_info = {};

		tileset_info.columns = tileset["columns"];
		tileset_info.image = tileset["image"];
		tileset_info.tileSize = tileset["tileheight"];
		tiled.tileset = tileset_info;
	}
	for (const auto &layer : json["layers"])
	{
		if (layer["type"] == "tilelayer")
		{
			t_tile_layer_short	tileLayer = {};

			tileLayer.data = layer["data"].get<std::vector<int>>();
			tileLayer.name = layer["name"];
			tileLayer.opacity = layer["opacity"];
			tileLayer.x = layer["x"];
			tileLayer.y = layer["y"];
			tiled.tileLayers.push_back(tileLayer);
		}
		if (layer["type"] == "objectgroup")
		{
			for (const auto &object : layer["objects"])
			{
				t_object_short	objectInfo = {};
				
				objectInfo.type = object["type"];
				objectInfo.height = object["height"];
				objectInfo.name = object["name"];
				objectInfo.opacity = object["opacity"];
				objectInfo.rotation = object["rotation"];
				objectInfo.width = object["width"];
				objectInfo.x = object["x"];
				objectInfo.y = object["y"];
				if (object.contains("properties"))
				{
					for (const auto &property : object["properties"])
					{
						if (property["type"] == "string")
							objectInfo.sproperties[property["name"]] = property["value"];
						else if (property["type"] == "int")
							objectInfo.iproperties[property["name"]] = property["value"];
					}
				}
				if (object.contains("gid"))
				{
					objectInfo.gid = object["gid"];
					tiled.sprites.push_back(objectInfo);
				}
				else if (object.contains("point"))
					tiled.points.push_back(objectInfo);
				else if (object.contains("elipse"))
					;
				else if (object.contains("capsule"))
					;
				else
					tiled.rectangles.push_back(objectInfo);
			}
		}
	}
	return (tiled);
}

Sprite	*getCollidingTile(SDL_Rect rect, std::vector<Sprite *> &tiles, int tileGridWidth, int tileSize)
{
	SDL_Rect							tileRect;
	SDL_Point							rectCell;
	SDL_Point							tilesToTest;
	int									tileIndex;

	rectCell.x = rect.x / tileSize;
	rectCell.y = rect.y / tileSize;
	tilesToTest.x = rect.w / tileSize + 1;
	tilesToTest.y = rect.h / tileSize + 1;
	for (int y = 0; y <= tilesToTest.y; y++)
	{
		for (int x = 0; x <= tilesToTest.x; x++)
		{
			tileIndex = (rectCell.y + y) * tileGridWidth + (rectCell.x + x);
			if (tileIndex < 0 || tileIndex >= static_cast<int>(tiles.size()) || tiles[tileIndex] == NULL)
				continue;
			tileRect = tiles[tileIndex]->getRect();
			if (SDL_HasIntersection(&tileRect, &rect))
				return (tiles[tileIndex]);
		}
	}
	return (NULL);
}

bool	isOutOfBounds(SDL_Rect rect, int mapWidth, int mapHeight)
{
	if (rect.x < 0 || rect.y < 0)
		return (true);
	if (rect.x + rect.w > mapWidth || rect.y + rect.h > mapHeight)
		return (true);
	return (false);
}
