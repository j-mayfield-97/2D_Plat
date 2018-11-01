#pragma once
#include "Bounding.h"
#include "Map.h"
#include <SDL.h>


class Moving_Obj
{
	SDL_Texture* sprite_tx;
	SDL_Rect sprite_rect;
	SDL_Rect src_sprite_rect;
	void UpdatePhysics();
	bool HasGround(Vector2 oldPosition, Vector2 position, Vector2 speed, float groundY);
	
public:
	Moving_Obj();
	Moving_Obj(SDL_Renderer* r, const char* path, int w, int h);
	~Moving_Obj();
	void init_rect_tx(SDL_Renderer* r, const char* path, int w, int h);

	void animate_help(int w, int h, int frames, int row, int column, int sprites_in_row, int delay);
	void render_ex(SDL_Renderer* r, SDL_Texture* tx, SDL_Rect* src , SDL_Rect* dest, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0, SDL_Point* center = NULL);
	void updater(SDL_Renderer* r);
	double time_diff();

	SDL_RendererFlip flipper;
	Map* practice_map;

	Vector2 prev_pos;
	Vector2 current_pos;
	Vector2 prev_speed;
	Vector2 current_speed;
	Vector2 scale;

	Bounding mAABB;
	Vector2 mAABB_offset;

	 bool mPushedRightWall;
	 bool mPushesRightWall;

	 bool mPushedLeftWall;
	 bool mPushesLeftWall;

	 bool mWasOnGround;
	 bool mOnGround;

	 bool mWasAtCeiling;
	 bool mAtCeiling;

	 int sprite_sheet_w;
	 int sprite_sheet_h;
};

