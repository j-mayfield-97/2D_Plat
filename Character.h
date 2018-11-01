#pragma once
#include "Moving_Obj.h"
#include <vector>

//whats the diff between enum class and enum?
enum class Keys 
{
	Left = 0,
	Right,
	Down,
	Jump,
	Count
};

enum Character_States
{
	Stand,
	Walk,
	Jump,
	GrabLedge,
	Duck,
	Run
};

class Character :
	public Moving_Obj
{
	std::vector<Uint8> inputs;
	std::vector<Uint8> prev_inputs;
	//key checks 
	Uint8 released(Keys k);
	Uint8 keystate(Keys k);
	Uint8 pressed(Keys k);

	SDL_Event e;
	//hold player's state
	Character_States current_state;
	float jump_speed;
	float walk_speed;
	float run_speed;

	//void update(SDL_Renderer* r);
	void update_prev_inputs();
public:
	
	//void update(SDL_Renderer* r);
	void control_updater(SDL_Renderer* r);
	Character();
	Character(SDL_Renderer* r);
	~Character();
	void char_init(std::vector<Uint8> i, std::vector<Uint8> p, SDL_Renderer* r);
	bool running;
};

