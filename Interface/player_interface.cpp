#include "../functions_definitions.h"
#include "../Mario/mario.h"
#include <string.h>
#include <iostream>

void interface(Mario& mario_info, SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex,
	SDL_Renderer* renderer, char* text, Colors& colors)
{
	DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, colors.czerwony, colors.niebieski);
	sprintf(text, "Mario lifes = %d		Mario points = %d ", mario_info.lifes, mario_info.points);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
	sprintf(text, "Esc - start the game, \030 - choose higher level, \031 - choose lower level");
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}