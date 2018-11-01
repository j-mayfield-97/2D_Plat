#include "Map.h"
#include "SDL_image.h"

//dont think I need these functions up top
void _get_map_tile_point(Vector2 point)
{
	return;
}
int Map::GetMapTileYAtPoint(float y)
{
	return (int)((y - mPosition.y_pos) / (float)(tile_size));
}

int Map::GetMapTileXAtPoint(float x)
{
	return (int)((x - mPosition.x_pos) / (float)(tile_size));
}

Map::Map(){}

Map::Map(SDL_Renderer* r)
{
	//how many tiles can fit on screen depending on window size
	height = 35;
	width = 30;
	//vector for mapping
	mPosition.x_pos = 0;
	mPosition.y_pos = 0;
	
	//drawing rect
	draw_rect.x = 0;
	draw_rect.y = 0;
	draw_rect.w = tile_size;
	draw_rect.h = tile_size;


	//add textures
	emp_tx = IMG_LoadTexture(r, "assets/wall32.png");
	blk_tx = IMG_LoadTexture(r, "assets/grass32.png");

	//temporary map init
	mTiles = { 
	{ Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty },
	{ Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty },
	{ Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty },
	{ Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Block,Empty,Empty },
	{ Empty,Empty,Block,Empty,Empty,Empty,Empty,Block,Empty,Block,Empty },
	{ Empty,Block,Empty,Block,Block,Block,Block,Empty,Empty,Empty,Block },
	{ Block,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty }
	};
}
void Map::map_render(SDL_Renderer* r)
{
	int x = 0;
	int y = 0;
	//loop through the 2d vector tiles
	for (std::size_t i = 0; i < mTiles.size(); ++i)
	{
		for (std::size_t j = 0; j < mTiles[i].size(); j++)
		{
			
			TileType b = mTiles[i][j];

			//multiply the tile size by the indices to spread the tiles consequtively
			draw_rect.x = tile_size * j;
			draw_rect.y = tile_size * i;

			//switch on the tiles, draw what it is
			switch (b)
			{
			case Empty:
				SDL_RenderCopy(r, emp_tx, NULL, &draw_rect); 
				break;
			case Block:
				SDL_RenderCopy(r, blk_tx, NULL, &draw_rect);
				break;
			}
		}
	}
}

TileType Map::GetTile(int x, int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return Block;
 
    return mTiles[x][y];
}
bool Map::IsObstacle(int x, int y)//we check if the tile is out of bounds, and if it is then we return true, so any tile out of bounds is treated as an obstacle
{
	if (x < 0 || x >= width
		|| y < 0 || y >= height)
		return true;

	return  (mTiles[x][y] == Block);
}
bool Map::IsGround(int x, int y)//We can stand on both a block and a one-way platform, so we need to return true if the tile is any of these two
{
	if (x < 0 || x >= width
		|| y < 0 || y >= height)
		return false;

	return (mTiles[x][y] == OneWay || mTiles[x][y] == Block);
}
bool Map::IsOneWayPlatform(int x, int y)
{
	if (x < 0 || x >= width
		|| y < 0 || y >= height)
		return false;

	return (mTiles[x][ y] == OneWay);
}
bool Map::IsEmpty(int x, int y)
{
	if (x < 0 || x >= width
		|| y < 0 || y >= height)
		return false;

	return (mTiles[x][ y] == Empty);
}
Map::~Map()
{
}