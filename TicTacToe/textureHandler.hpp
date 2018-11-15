/*********************************************************************
** Program name: Tic Tac Toe
** Author: Long Le
** Date: 7/20/2017
** Description: The TextureHandler class generates textures used to
*  render onto the screen from PNG images or text using SDL_image and 
*  SDL_ttf respectively.
*********************************************************************/

#ifndef TEXTURE_HANDLER_HPP
#define TEXTURE_HANDLER_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstdio>

#include <string>
using std::string;

#include <sstream>
using std::stringstream;

#include <vector>
using std::vector;

class TextureHandler
{
    private:
    /*********************************************************************
     ** Description: This struct represents an image. It contains data
     * for the path to the image, the width and height, and the SDL_Texture
     * pointer that will be used to hold the optimized texture.
     *********************************************************************/
    struct ImageData 
    {
        string path;    

        SDL_Texture* texture;

        /*********************************************************************
         ** Description: Constructor. 
         * 
         * Parameters: string - the path to the image.
         *********************************************************************/
        ImageData( const string &path )
        {
            this->path = path;
            texture = NULL;
        }

        /*********************************************************************
         ** Description: This function frees the texture from memory. 
         *********************************************************************/
        void destroyTexture()
        {
            if( texture != NULL )
            {
                SDL_DestroyTexture( texture );
                texture = NULL;
            }
        }
    };

    //The X and O sprite clips.
    SDL_Rect X_Render;
    SDL_Rect O_Render;

    //The PNG sprite sheet.
    ImageData XandO;

    //Black color used for a game draw outcome.
    SDL_Color DrawColor;

    //Textures rendered to the screen.
    SDL_Texture* XTurn;
    SDL_Texture* OTurn;
    SDL_Texture* XWin;
    SDL_Texture* OWin;
    SDL_Texture* Draw;
    SDL_Texture* XPoints;
    SDL_Texture* OPoints;
    SDL_Texture* XP;
    SDL_Texture* OP;
    SDL_Texture* playAgain;

    TTF_Font* font; 
    string fontPath;

    stringstream XpointSS;
    stringstream OpointSS;

    int XPoint,
        OPoint;

    //Private functions.
    SDL_Texture* loadTexture( const string &, SDL_Renderer* );
    SDL_Texture* loadRenderedText( const string &, SDL_Color, SDL_Renderer* );

    public:
    TextureHandler();
    ~TextureHandler();
    bool loadMedia( SDL_Renderer* ); 
    void incrementX( SDL_Renderer* );
    void incrementO( SDL_Renderer* );
    void cleanUp();

    //Getter functions.
    SDL_Texture* getXO() { return XandO.texture; };
    SDL_Texture* getXTurn() { return XTurn; };
    SDL_Texture* getOTurn() { return OTurn; };
    SDL_Texture* getXWin() { return XWin; };
    SDL_Texture* getOWin() { return OWin; };
    SDL_Texture* getDraw() { return Draw; };
    SDL_Texture* getXPoints() { return XPoints; };
    SDL_Texture* getOPoints() { return OPoints; };
    SDL_Texture* getXP() { return XP; };
    SDL_Texture* getOP() { return OP; };
    SDL_Rect getRectX() { return X_Render; }; 
    SDL_Rect getRectO() { return O_Render; }; 
    SDL_Texture* getPlayAgain() { return playAgain; }; 
};

#endif
