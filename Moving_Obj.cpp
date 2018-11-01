#include "Moving_Obj.h"
#include "Map.h"
#include <iostream>
#include <chrono>
#include <SDL_image.h>
//#include <time.h>

void Moving_Obj::init_rect_tx(SDL_Renderer* r, const char* path, int w, int h)
{
	//init rect and texture
	sprite_tx = IMG_LoadTexture(r, path);
	src_sprite_rect.x = 0;
	src_sprite_rect.y = 0;
	src_sprite_rect.w = 0;
	src_sprite_rect.h = 0;

	//flip the texture on rectangle
	flipper = SDL_FLIP_NONE;

	//SDL_QueryTexture() method gets the width and height of the texture
	SDL_QueryTexture(sprite_tx, NULL, NULL, &sprite_sheet_w, &sprite_sheet_h);

	//visible sprite rect
	sprite_rect.x = mAABB.center.x_pos;
	sprite_rect.y = mAABB.center.y_pos;
	sprite_rect.w = w;
	sprite_rect.h = h;

	practice_map = new Map(r);
}

void Moving_Obj::animate_help(int w, int h, int frames, int row, int column, int sprites_in_row, int delay)
{
	//w and h are size of sprites
	//frames is how many frames will be in animation
	//row column are where the animation starts i.e. 0th row, 5th column
	src_sprite_rect.y = row * h;
	src_sprite_rect.w = w;
	src_sprite_rect.h = h;

	//SDL_GetTicks() method gives us the time in milliseconds
	//'frame' will give us the index of frame we want to render
	//For example, if 'frame' is 2, it will give us the third frame
	int frame = (SDL_GetTicks() / delay) % frames;

	//must wrap around when it get to the end on sheet
	if (frame + column > sprites_in_row)
	{
		src_sprite_rect.x = 0;
		src_sprite_rect.y += h;
	}
	else
		src_sprite_rect.x = (frame + column) * src_sprite_rect.w;	
}

Moving_Obj::Moving_Obj()
{
}

Moving_Obj::Moving_Obj(SDL_Renderer* r, const char* path, int w, int h)
{
	init_rect_tx(r, path, w, h);
}

// time diff will provide the time diffrenece between frames.
double Moving_Obj::time_diff()
{
	auto start = std::chrono::system_clock::now();
	// the for loop is only to add a little time 
	for (int i = 0; i < 2; i++) 
		{ 20.6f / 3.9f; }

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;

	//we're using system time to get the movents based on clock, but it returns a value too low for sdl , but multiplying the sixth power helps
	double dt = diff.count() * pow(10, 6);

	//we want a low number to be returned in case anything goes wrong with lag between frames
	if (dt > 1){ return 1; }

return dt;
}

bool Moving_Obj::HasGround(Vector2 oldPosition, Vector2 position, Vector2 speed, float groundY)
{
	//Get the bottom left and bottom right corners of the rect
	Vector2 bottom_left(current_pos.x_pos, current_pos.y_pos + sprite_rect.h);
	Vector2 bottom_right(current_pos.x_pos + sprite_rect.w, current_pos.y_pos + sprite_rect.h);

	int tileIndexX, tileIndexY;

	//go through the tile from left to right of character_rect
	for (Vector2 checkedTile = bottom_left; ; checkedTile.x_pos += practice_map->tile_size)
	{
		//check the closest tile between rectangles the next tile and the chracteer's right
		checkedTile.x_pos = std::fmin(checkedTile.x_pos, bottom_right.x_pos);

		tileIndexX = practice_map->GetMapTileXAtPoint(checkedTile.x_pos);
		tileIndexY = practice_map->GetMapTileYAtPoint(checkedTile.y_pos);

		// check through the logical map to see if on ground
		groundY = (float)tileIndexY * practice_map->tile_size + practice_map->mPosition.y_pos;

		if (practice_map->IsObstacle(tileIndexX, tileIndexY))
			return true;

		if (checkedTile.x_pos >= bottom_right.x_pos)
			break;
	}

	return false;
}

Moving_Obj::~Moving_Obj()
{
	SDL_DestroyTexture(sprite_tx);
}

void Moving_Obj::UpdatePhysics()
{
	//update the current states to the previous frame
	prev_pos = current_pos;
	prev_speed = current_speed;

	//update obstacle states
	mWasOnGround = mOnGround;
	mPushedRightWall = mPushesRightWall;
	mPushedLeftWall = mPushesLeftWall;
	mWasAtCeiling = mAtCeiling;

	//ground collision check
	float groundY = 0;
	if (current_speed.y_pos <= 0.0f
		&& HasGround(prev_pos, current_pos, current_speed, groundY))
	{
		current_pos.y_pos = groundY + mAABB.halfSize.y_pos - mAABB_offset.y_pos;
		current_speed.y_pos = 0.0f;
		mOnGround = true;
	}
	else
		mOnGround = false;
	//update logical position
	current_pos.x_pos += current_speed.x_pos * time_diff();
	current_pos.y_pos += current_speed.y_pos * time_diff();


	mAABB.center = current_pos + mAABB_offset;
	//the tutorial uses transform for the renderer here

	//update the visual position
	sprite_rect.x = current_pos.x_pos;
	sprite_rect.y = current_pos.y_pos;
}

void Moving_Obj::render_ex(SDL_Renderer* r, SDL_Texture* tx, SDL_Rect* src, SDL_Rect* dest, SDL_RendererFlip flip, double angle, SDL_Point* center)
{ //Function just to add easy defaults to rendercopyEx 
	
	//Render to screen 
	SDL_RenderCopyEx(r, tx, src, dest, angle, center, flip ); 
}

void Moving_Obj::updater(SDL_Renderer* r)
{
	UpdatePhysics();
	render_ex(r, sprite_tx, &src_sprite_rect, &sprite_rect, flipper);
}
