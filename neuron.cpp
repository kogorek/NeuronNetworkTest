#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <GL/gl.h>
//#include <GL/glu.h>

#include <iostream>
#include <string>
#include <cmath>

#include "neuron.h"
#include "vars.h"

#define UNUSED(x) (void)(x)

void initGLandSDL();

SDL_Window *win = NULL;

int n_screenWidth = 480;
int n_screenHeight = 480;

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

int main(int argc, char *argv[])
{
    std::string inputPath;

    char letter[2];
    neuron *neuroWeb[26];
    bool b_running = true;
    SDL_Surface* surface;
    for(int i = 0; i < 26; i++)
    {
        neuroWeb[i] = new neuron('A'+i);
    }
    while(b_running)
    {
        inputPath = "./letters/";
        std::cout << "Enter letter name: ";
        std::cin >> letter;
        if(letter[0] == '.')
            b_running = false;
        if(b_running == true)
        {
            inputPath = inputPath + letter + ".bmp";
            surface = IMG_Load(inputPath.c_str());

            for(int i = 0; i < 26; i++)
            {
                for (int x = 0; x < 30; x++)
                {
                    for (int y = 0; y < 30; y++)
                    {
                        Uint8 r;
                        Uint8 g;
                        Uint8 b;
                        SDL_GetRGB(getpixel(surface, x, y), surface->format, &r, &g, &b);
                        neuroWeb[i]->input[x][y] = round((r+g+b)/3);
                    }
                }
            }

            SDL_FreeSurface(surface);

            for (int i = 0; i < 26; i++)
            {
                for (int x = 0; x < 30; x++) //x
                {
                    for (int y = 0; y < 30; y++) //y
                    {
                        int n = neuroWeb[i]->memory[x][y];
                        int m = neuroWeb[i]->input[x][y];
                        if (abs(m-n) < 120)
                            if (m < 250)
                                neuroWeb[i]->weight=neuroWeb[i]->weight+1;
                        if (m != 0)
                        {
                            if (m < 250)
                                n = round((n+(n+m)/2)/2);
                            //neuroWeb[i]->memory[x][y] = n;
                        }
                        else if(n != 0)
                            if (m<250)
                                n = round((n+(n+m)/2)/2);
                        //neuroWeb[i]->memory[x][y] = n;
                    }
                }
            }
            int maxWeight = 0;
            int maxN = 0;
            for (int i = 0; i < 26; i++)
            {
                if (neuroWeb[i]->weight > maxWeight)
                {
                    maxWeight = neuroWeb[i]->weight;
                    maxN = i;
                }
            }

            std::cout << "I think this is " << neuroWeb[maxN]->name << std::endl;
            std::cout << "Enter what it was ";
            std::cin >> letter;
            std::cout << "==================" << std::endl;
            for(int x = 0; x < 30; x++)
                for(int y = 0; y < 30; y++)
                {
                    int i = int(*letter) - 65;
                    int n = neuroWeb[i]->memory[x][y];
                    int m = neuroWeb[i]->input[x][y];
                    if (m != 0)
                    {
                        if (m < 250)
                            n = round((n+(n+m)/2)/2);
                        neuroWeb[i]->memory[x][y] = n;
                    }
                    else if(n != 0)
                        if (m<250)
                            n = round((n+(n+m)/2)/2);
                    neuroWeb[i]->memory[x][y] = n;
                }
        }
    }
    for (int i = 0; i < 26; i++)
        delete neuroWeb[i];

    return 0;
}
