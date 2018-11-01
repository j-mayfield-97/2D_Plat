#include "player.h"
#include "smallEnum.h"

Player::Player()
{

}

void Player::set_up(SDL_Renderer* r, const char* path)
{ 
	player_rect.h = screenHeight / 20;
	player_rect.w = screenHeight / 20;
	player_rect.x = screenHeight / 20;
	player_rect.y = screenHeight / 20;

	sprite_rect.h = player_rect.h;
	sprite_rect.w = player_rect.w* 1.1;

	skintx = IMG_LoadTexture(r, path);

	on_floor = false;
	jump_limiter = false;
	health = 5;
	mass = 10;
	walk_speed = 3;
	run_speed = 7;

}
//also make it a template
//void Player::gravity(SDL_Rect* rect) //this has gottta go in a physics class somewhere

void Player::draw_player(SDL_Renderer* r, SDL_Rect floor_tile)//floor collision in here to for right now
{
	//gravity(&player_rect);
	if (player_rect.y + player_rect.h >= floor_tile.y &
		player_rect.x>0)//figure out horizantal platforming
	{
		player_rect.y = floor_tile.y - player_rect.h;
		on_floor = true;
		jump_limiter = false;
	}
	sprite_rect.x = player_rect.x - (sprite_rect.w - player_rect.w);
	sprite_rect.y = player_rect.y;
	SDL_RenderCopy(r, skintx,NULL,&sprite_rect);
}
void Player::horz_move(int velo)
{
	player_rect.x += velo;
}

void Player::jump(int height)
{

	if (on_floor & !jump_limiter)
	{
		jump_limiter = true;//good job?
		player_rect.y -= height;
	}
}

Player::~Player()
{
	SDL_DestroyTexture(skintx);
}
