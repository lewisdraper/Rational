#pragma once
#include "Layer.h"
#include <string>
#include <vector>

struct Tileset {
	int FirstID, LastID;
	int RowCount, ColCount;
	int TileCount, TileSize;
	std::string Name, Source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer: public Layer
{
public:
	TileLayer(int tileSize, int rowCount, int colCount, TileMap tilemap, TilesetList tilesets);
	virtual void Render();
	virtual void Update();
	inline TileMap GetTileMap() { return m_TileMap; }

private:
	int m_TileSize;
	unsigned int m_RowCount, m_ColCount;
	TileMap m_TileMap;
	TilesetList m_Tilesets;

};

