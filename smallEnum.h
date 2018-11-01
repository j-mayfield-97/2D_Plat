#pragma once
//is it okay to just include this where its needed?

//any drawing method should take in a render and window as parameters, so just use get window height.
enum {
	screenWidth = 800,
	screenHeight = 640
};

/*void skin_rects_load_attach(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect rect, const char* path)
{
	tex = IMG_LoadTexture(ren, path);
	
}*/