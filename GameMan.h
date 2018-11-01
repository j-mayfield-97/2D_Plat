#pragma once
#include "Character.h"
#include <vector>
#include <SDL.h>
//I no longer believe I have a need for this class
class GameMan
{
public:
	GameMan();
	~GameMan();
	Character* player;
	
	std::vector<Uint8> gInputs;
	std::vector<Uint8> gPrevInputs;

	void Start(SDL_Renderer* r)
	{
		player = new Character(r);

		//initalize these vectors
		gInputs;
		gPrevInputs;
	}
};

