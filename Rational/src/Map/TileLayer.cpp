#include "TileLayer.h"
#include "../Graphics/TextureManager.h"
#include <iostream>


TileLayer::TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TilesetList tilesets):
	m_TileSize(tileSize), m_ColCount(colCount), m_RowCount(rowCount), m_TileMap(tileMap), m_Tilesets(tilesets)
{

	for (unsigned int i = 0; i < m_Tilesets.size(); i++)
	{
		TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "assets/levels/" + m_Tilesets[i].Source);
	}
}

void TileLayer::Render(float scale)
{
	static int cnt = 0;
	for (unsigned int i = 0; i < m_RowCount; i++)
	{
		for (unsigned int j = 0; j < m_ColCount; j++)
		{
			int tileID = m_TileMap[i][j];
			if (tileID == 0)
				continue;
			else
			{
				int index = 0;;
				if (m_Tilesets.size() > 1)
				{
					for (unsigned int k = 1; k < m_Tilesets.size(); k++)
					{
						if (tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID)
						{
							tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
							index = k;
							
							break;
						}
					}
				}

				Tileset ts = m_Tilesets[index];
				int tileRow = tileID / ts.ColCount;
				int tileCol = tileID - tileRow * ts.ColCount - 1;

				if (tileID % ts.ColCount == 0)
				{
					tileRow--;
					tileCol = ts.ColCount - 1;
				}

				TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, ts.TileSize *  (float)j, ts.TileSize * (float)i, scale, tileRow, tileCol);
			}
		}
	}
	cnt++;
}

void TileLayer::Update()
{
}
