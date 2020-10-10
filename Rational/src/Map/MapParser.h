#pragma once
#include <tinyxml.h>
#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"

class MapParser
{
public:
	//Singleton getter
	inline static MapParser* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }

	//Load the map into the map dictionary
	bool Load();

	//Clean up the map dictionary
	void Clean();

	//Get the specified map by id
	inline GameMap* GetMap(std::string id) { return m_MapDict[id]; }

private:
	//Parses the map and adds to the map dictionary (m_MapDict)
	bool Parse(std::string id, std::string source);

	//Parses a tileset
	Tileset ParseTileset(TiXmlElement* xmlTileset);

	//Parses a tile layer
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int colCount);

private:
	MapParser() {};

	//Static singleton instance
	static MapParser* s_Instance;

	//Map dictionary for storing all maps
	std::map<std::string, GameMap*> m_MapDict;
};

