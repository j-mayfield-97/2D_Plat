#pragma once
#include <SDL.h>
#include <vector>
#include "Vector2.h"

enum TileType //All the possible tiles should be listed here
{
	Empty,
	Block,
	OneWay
};

class Map
{
	//all the types of tiles	
	//I cant have a vec of sdl textures for some reason?
	std::vector<const char*> mTilesSprites;
	SDL_Rect draw_rect;
	SDL_Texture* emp_tx;
	SDL_Texture* blk_tx;
	
public:
	Map();
	Map(SDL_Renderer* r);
	~Map();

	//2d array of tiles
	std::vector<std::vector<TileType>> mTiles;

	int height, width;
	Vector2 mPosition;

	//pixel size of square tiles
	const int tile_size = 50;

	void map_render(SDL_Renderer* r);
	TileType GetTile(int x, int y);
	bool IsObstacle(int x, int y);
	bool IsGround(int x, int y);
	bool IsOneWayPlatform(int x, int y);
	bool IsEmpty(int x, int y);
	int GetMapTileXAtPoint(float x);
	int GetMapTileYAtPoint(float y);
	
};

