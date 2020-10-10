#include "MapParser.h"

MapParser* MapParser::s_Instance = nullptr;

//Loads the maps
bool MapParser::Load()
{
	return Parse("level", "assets/levels/level3.tmx");
}

//Empties the map dictionary
void MapParser::Clean()
{
	std::map<std::string, GameMap*>::iterator it;
	for (it = m_MapDict.begin(); it != m_MapDict.end(); it++)
		it->second = nullptr;

	m_MapDict.clear();
}

//Constructs a GameMap object for the given map file and adds to the map dictionary as ID specified
bool MapParser::Parse(std::string id, std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error())
	{
		std::cerr << "Failed to load: " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	int rowCount, colCount, tileSize = 0;

	root->Attribute("width", &colCount);
	root->Attribute("height", &rowCount);
	root->Attribute("tilewidth", &tileSize);

	//Add all tilesets to Tileset list
	TilesetList tilesets;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			tilesets.push_back(ParseTileset(e));
		}
	}
	
	//Parse each layer of the map
	GameMap* gamemap = new GameMap();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
		{
			TileLayer* tileLayer = ParseTileLayer(e, tilesets, tileSize, rowCount, colCount);
			gamemap->m_MapLayers.push_back(tileLayer);
		}
	}

	m_MapDict[id] = gamemap;
	return true;

}

//Parses an XML Tileset Element and returns a Tileset object
Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
	Tileset tileset;
	tileset.Name = xmlTileset->Attribute("name");

	xmlTileset->Attribute("firstgid", &tileset.FirstID);
	xmlTileset->Attribute("tilecount", &tileset.TileCount);
	xmlTileset->Attribute("tilewidth", &tileset.TileSize);
	xmlTileset->Attribute("columns", &tileset.ColCount);

	tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;
	tileset.RowCount = tileset.TileCount / tileset.ColCount;

	TiXmlElement* image = xmlTileset->FirstChildElement();
	tileset.Source = image->Attribute("source");
	
	return tileset;
}

//Parses an XML Layer element and returns a TileLayer object
TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int colCount)
{
	std::string id;
	TileLayer* tileLayer = nullptr;

	//For each data section in the XML Layer element
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			std::istringstream iss(e->GetText());

			TileMap tilemap(rowCount, std::vector<int>(colCount, 0));

			//For each tile in the map
			for (int row = 0; row < rowCount; row++)
			{
				for (int col = 0; col < colCount; col++)
				{
					//Store each comma seperated value in the stringstream and then add to the TileMap object
					std::getline(iss, id, ',');
					std::stringstream convertor(id);
					convertor >> tilemap[row][col];

					if (!iss.good())
						break;
				}
			}

			tileLayer = new TileLayer(tileSize, rowCount, colCount, tilemap, tilesets);
		}		
	}
	return tileLayer;
}

