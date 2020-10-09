#pragma once
#include "Layer.h"
#include <string>
#include <vector>
#include <iostream>

struct Tileset {
	int FirstID=0, LastID=0;
	int RowCount=0, ColCount=0;
	int TileCount=0, TileSize=0;
	std::string Name="", Source="";
};



using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer: public Layer
{
public:
	TileLayer(int tileSize, int rowCount, int colCount, TileMap tilemap, TilesetList tilesets);
	virtual void Render(float scale=1);
	virtual void Update();
	inline TileMap GetTileMap() { return m_TileMap; }

private:
	int m_TileSize;
	unsigned int m_RowCount, m_ColCount;
	TileMap m_TileMap;
	TilesetList m_Tilesets;

};

