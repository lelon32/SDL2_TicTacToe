/*********************************************************************
** Program name: Tic Tac Toe
** Author: Long Le
** Date: 7/20/2017
** Description: The GraphicsHandler class initializes SDL and handles
*  the graphic related components of the Tic Tac Toe game.  
*********************************************************************/
#ifndef GRAPHICS_HANDLER_HPP 
#define GRAPHICS_HANDLER_HPP 

#include "textureHandler.hpp"
#include "mouseButtons.hpp"

enum Outcome { X_WON, O_WON, DRAW, UNFINISHED };

/*********************************************************************
** Description: The ButtonClicked structure represents mouse buttons 
*  that were clicked on by the X and O players.
*********************************************************************/
struct ButtonClicked
{
    SDL_Rect button; //Specs of the mouse button.
    Player cPlayer; //Clicked by player X or O.

    ButtonClicked( SDL_Rect button, Player cPlayer ) 
    {
        this->button = button; 
        this->cPlayer = cPlayer; 
    }
};

class GraphicsHandler
{
    private:

    const int SCREEN_WIDTH,
              SCREEN_HEIGHT;

    //SDL windows and graphics setup pointer variables.
    SDL_Window* mainWindow;
    SDL_Renderer* mainRenderer;

    TextureHandler ticTacToeTextures;
    
    int highlightOpacity,
        turn; //Represents player turn.

    Uint8 fontOpacity; 

    //Basic geometric graphic properties.
    SDL_Rect fillRectangle;
    SDL_Rect highlight;
    SDL_Rect lines[4];
    SDL_Rect text;
    SDL_Rect viewportHud;
    SDL_Rect viewportSpecs;
    SDL_Rect X;
    SDL_Rect O;
    SDL_Rect Xpoints;
    SDL_Rect Opoints;
    SDL_Rect XPLoc;
    SDL_Rect OPLoc;
    SDL_Rect playAgainBox;
    SDL_Rect playAgainText;

    bool incremented; //Controls points incrementation.

    vector< ButtonClicked > buttonClicked;

    //Private Functions
    bool initiateSDL();
    void renderTexture( SDL_Texture* texture = NULL, SDL_Rect* clip = NULL, 
    SDL_Rect* renderQuad = NULL, double angle = 0.0, SDL_Point* center = NULL, 
    SDL_RendererFlip flip = SDL_FLIP_NONE );

    public:
    GraphicsHandler( int, int );
    ~GraphicsHandler();
    bool startUp();
    void reset(); 
    void clearScreen();
    void cleanUp();
    void setTurn( int turn ) { this->turn = turn; };
    void drawGame( MouseButtons* = NULL, Player = No_Player, Outcome = UNFINISHED );
};

#endif
