#include "interface.h"
#include <iostream>

bool handle_authentication_interface_events(char* name, int& index);

char* authentication_interface(Mario& mario_info, SDL_Surfaces& surfaces, SDL_Elements& SDL_elements)
{
    SDL_Event event;
    bool quit = false;
    char name[40];
    int index = 0;
    name[index] = '\0';
    char text[100];
    
    Colors colors;
    initialize_colors(*(surfaces.screen), colors);

    while (!quit)
    {
        DrawRectangle(*(surfaces.screen), 4, 4, SCREEN_WIDTH - 8, 54, colors.szary, colors.szary);
        sprintf(text, "Please enter you name: ");
        DrawString(*(surfaces.screen), (*(surfaces.screen))->w / 2 - strlen(text) * 8 / 2, 10, text, *(surfaces.charset));
        sprintf(text, "Your name: %s", name);
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
            if (event.key.keysym.sym == SDLK_RETURN)
                return true;
            else if (event.key.keysym.sym == SDLK_BACKSPACE && index > 0)
            {
                index--;
                name[index] = '\0';
            }
        }
        else if (event.type == SDL_TEXTINPUT && index < 60)
        {
            name[index] = *(event.text.text);
            index++;
            name[index] = '\0';
            return false;
        }
    }
    return false;
}