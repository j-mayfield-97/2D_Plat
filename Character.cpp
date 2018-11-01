#include "Character.h"
#include <chrono>
#include <SDL_image.h>

//constants for the character
const float cWalkSpeed = 3.0f;
const float cJumpSpeed = 410.0f;
const float cMinJumpSpeed = 200.0f;
const float cHalfSizeY = 20.0f;
const float cHalfSizeX = 6.0f;

//size of the characters sprite
const int character_height = 100;
const int character_width = 100;

//this could be for the recangles and stuff
void Character::char_init(std::vector<Uint8> i, std::vector<Uint8> p, SDL_Renderer* r)
{
	//init rect postion here
	mAABB.halfSize = Vector2(cHalfSizeX,cHalfSizeY);
	mAABB_offset.y_pos = mAABB.halfSize.y_pos;

	//init other members
	inputs = i;
	prev_inputs = p;

	jump_speed = cJumpSpeed;
	walk_speed = cWalkSpeed;

	scale.one(); //might need a pointer for this

	init_rect_tx(r, "assets/main_sprites.png", character_width, character_height);

	//the exit condition is with the player, as th econtrols are in the player class
	running = true;

	//start standing
	current_state = Stand;
}

Character::Character()
{
}

Character::Character(SDL_Renderer* r)
{
	char_init(inputs,prev_inputs, r);
}

Character::~Character()
{
}

//function to update the pervious keystate array
//they use a signed byte here
void Character::update_prev_inputs()
{
	////not useful currently
}

Uint8 Character::released(Keys k)
{
	return (!inputs[(int)k] && prev_inputs[(int)k]); //this could probably just be a xor
}

Uint8 Character::keystate(Keys k)
{
	return inputs[(int)k];
}

Uint8 Character::pressed(Keys k)
{
	return (inputs[(int)k] && !prev_inputs[(int)k]);
}


void Character::control_updater(SDL_Renderer* r)
{
	//input type for concurrent key presses
	const Uint8* currentKeyStates;
	currentKeyStates = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || currentKeyStates[SDL_SCANCODE_ESCAPE])
		{
			running = false;
		}
	}

	switch (current_state)
	{
		case Stand:
			current_speed.zero();
			//make sure the standing animation happens here
			//if the character is in the air play jump animation
			//animate_help(50, 37, 4, 0, 150);
			//the controls have to repeat Uint8* pattern for sdl
			const Uint8* currentKeyStates_stand;
			currentKeyStates_stand = SDL_GetKeyboardState(NULL);

			if (!mOnGround)
			{
				current_state = Jump;
				break;
			}
			if (currentKeyStates_stand[SDL_SCANCODE_A] != currentKeyStates_stand[SDL_SCANCODE_D])
			{
				current_state = Walk;
				break;
			}
			if (currentKeyStates_stand[SDL_SCANCODE_SPACE])
			{
				current_speed.y_pos = jump_speed;
				current_state = Jump;
				break;
			}
			break;
		case Walk:
			const Uint8* currentKeyStates_walk;
			currentKeyStates_walk = SDL_GetKeyboardState(NULL);
			//walking animation here
			animate_help(50, 37, 6, 1, 1, 6, 200);

			if (currentKeyStates_walk[SDL_SCANCODE_A] == currentKeyStates_walk[SDL_SCANCODE_D])
			{
				current_state = Stand;
				current_speed.zero();
				break;
			}
			else if (currentKeyStates_walk[SDL_SCANCODE_D])
			{
				if (mPushesRightWall) //this is how wall collisons are handled
					current_speed.x_pos = 0.0f;
				else
					current_speed.x_pos = walk_speed;

				scale.x_pos = std::abs(scale.x_pos);
				flipper = SDL_FLIP_NONE;
			}
			else if (currentKeyStates_walk[SDL_SCANCODE_A])
			{
				if (mPushesLeftWall)
					current_speed.x_pos = 0.0f;
				else
					current_speed.x_pos = -walk_speed;
				//does just negating the scale flip the horz ?
				scale.x_pos = -std::abs(scale.x_pos);
				flipper = SDL_FLIP_HORIZONTAL;
			}
			if (currentKeyStates_walk[SDL_SCANCODE_SPACE])
			{
				current_speed.y_pos = jump_speed;
				//they play audio here
				current_state = Jump;
				break;
			}
			else if (!mOnGround)
			{
				current_state = Jump;
				break;
			}
			break;
		case Jump:
			//jump anim
			animate_help(50, 37, 6, 1, 1, 6, 200);
		{
			const Uint8* currentKeyStates_jump;
			currentKeyStates_jump = SDL_GetKeyboardState(NULL);
			//temp fall gravity
			current_speed.y_pos = walk_speed*0.1;

			//put some limiter here max fall speed
			if (currentKeyStates[SDL_SCANCODE_A] == currentKeyStates[SDL_SCANCODE_D])
			{
				//current_state = Stand;
				current_speed.x_pos = 0;
				break;
			}
			if (currentKeyStates_jump[SDL_SCANCODE_D])
			{
				if (mPushesRightWall) //this is how wall collisons are handled
					current_speed.x_pos = 0.0f;
				else
					current_speed.x_pos = walk_speed;

				scale.x_pos = std::abs(scale.x_pos);
				flipper = SDL_FLIP_NONE;
			}
			//min jump height needed
			if (!currentKeyStates_jump[SDL_SCANCODE_SPACE] && current_speed.y_pos > 0.0f) 
			{

			}
			if (currentKeyStates_jump[SDL_SCANCODE_A])
			{
				if (mPushesLeftWall)
					current_speed.x_pos = 0.0f;
				else
					current_speed.x_pos = -walk_speed;
				//does just negating the scale flip the horz ?
				flipper = SDL_FLIP_HORIZONTAL;
				scale.x_pos = -std::abs(scale.x_pos);
			}
		}
			break;
			// to be updated
		case GrabLedge:
			break;
		case Duck:
			break;
		case Run:
			break;
		default:
			throw "non-valid state";
			std::cout << "default" << std::endl;
			break;

	}
	//main logical update
	updater(r);
	update_prev_inputs();
}