#include "interface.h"

#include <string.h>

bool handle_authentication_interface_events(char* name, int& index);

const int NAME_MAX_LENGTH = 20;

char* authentication_interface(Mario& mario_info, SDL_Surfaces& surfaces, SDL_Elements& SDL_elements, const Colors& colors)
{
    SDL_Event event;
    bool quit = false;
    char name[NAME_MAX_LENGTH + 1]; // + 1 for null character
    int index = 0;
    name[index] = '\0';
    char text[100];

    while (!quit)
    {
        DrawRectangle(*(surfaces.screen), 4, 4, SCREEN_WIDTH - 8, 54, colors.szary, colors.szary);
        sprintf_s(text, 100, "Please enter you name, maximum length is 25 characters: ");
        DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 10, text, *(surfaces.charset));
        sprintf_s(text, 100, "Your name: %s", name);
        DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 26, text, *(surfaces.charset));

        SDL_UpdateTexture(SDL_elements.scrtex, NULL, (*(surfaces.screen))->pixels, (*(surfaces.screen))->pitch);
        //		SDL_RenderClear(renderer);
        SDL_RenderCopy(SDL_elements.renderer, SDL_elements.scrtex, NULL, NULL);
        SDL_RenderPresent(SDL_elements.renderer);

        // Fill the entire screen with given color
        SDL_FillRect((*(surfaces.screen)), NULL, colors.czarny);
        quit = handle_authentication_interface_events(name, index);
    }
    name[index] = '\0';
    return name;
}

bool handle_authentication_interface_events(char* name, int& index)
{

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
            return true;
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_RETURN && index > 0)
                return true;
            else if (event.key.keysym.sym == SDLK_BACKSPACE && index > 0)
            {
                index--;
                name[index] = '\0';
            }
        }
        else if (event.type == SDL_TEXTINPUT && index < NAME_MAX_LENGTH)
        {
            name[index] = *(event.text.text);
            index++;
            name[index] = '\0';
            return false;
        }
    }
    return false;
}