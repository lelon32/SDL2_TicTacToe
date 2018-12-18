/*********************************************************************
** Program name: Tic Tac Toe
** Author: Long Le
** Date: 7/20/2017
** Description: The GraphicsHandler class initializes SDL and handles
*  the graphic related components of the Tic Tac Toe game.  
*********************************************************************/
#include "graphicsHandler.hpp"

/*********************************************************************
** Description: Constructor.
*
* Parameters: 
* 1. int screenWidth - the window screen width in pixels.
* 2. int screenHeight - the window screen height in pixels.
*********************************************************************/
GraphicsHandler::GraphicsHandler( int screenWidth, int screenHeight ) :
SCREEN_WIDTH ( screenWidth ), SCREEN_HEIGHT ( screenHeight )
{
	mainWindow = NULL;
	mainRenderer = NULL;
    highlightOpacity = 0;

    

    //The grey Tic Tac Toe board.
    fillRectangle = { 0, 0, SCREEN_WIDTH - 160, SCREEN_HEIGHT };
    highlight = { 0, 0, 0, 0 };

    //Length, size and location of the grey lines.
    lines[0] = { 150, 40, 15, 0 };
    lines[1] = { 315, 40, 15, 0};
    lines[2] = { 40, 150, 0, 15 };
    lines[3] = { 40, 315, 0, 15 };
    
    //viewport for the HUD.
    viewportHud = { 480, 0, 160, SCREEN_HEIGHT };
    viewportSpecs = { 0, 0, 160, SCREEN_HEIGHT };

    //Specifications for the different texts
    //and texture graphics.
    text = { 10, 15, 140, 20 };
    Xpoints = { 10, 400, 120, 20 };
    Opoints = { 10, 425, 120, 20 };
    playAgainBox = { 20, 100, 120, 120 };
    playAgainText = { 27, 150, 105, 20 };
    XPLoc = { 125, 400, 15, 20 };
    OPLoc = { 125, 425, 15, 20 };

    //Used for controlling point increments.
    incremented = false;
    
    fontOpacity = 0;
}

/*********************************************************************
** Description: Destructor. 
*********************************************************************/
GraphicsHandler::~GraphicsHandler()
{
    //empty.
}

/*********************************************************************
** Description: This function initializes SDL and graphics setup for
* the program.
*
* Return: bool - indicates whether the operations were successful.
*********************************************************************/
bool GraphicsHandler::initiateSDL()
{
    bool initSuccess = true;

    //Initiates SDL.
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "SDL did not successfully initialize! SDL ERROR: %s\n", SDL_GetError() );
        initSuccess = false;
    }

    else
    {
        //Set texture filtering to linear.
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "WARNING: Linear texture filtering was not enabled!" );
        }
        
        mainWindow = SDL_CreateWindow( "Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, 
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

        if( mainWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			initSuccess = false;
		}

		else
		{
			//Create renderer for window and uses software rendering as a fallback.
			mainRenderer = SDL_CreateRenderer( mainWindow, -1, SDL_RENDERER_PRESENTVSYNC 
                           | SDL_RENDERER_ACCELERATED );

			if( mainRenderer == NULL )
			{
				printf( "Accelerated Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				printf( "Attempting to use Software Renderer...\n" );

			    mainRenderer = SDL_CreateRenderer( mainWindow, -1, 
                               SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_SOFTWARE );

                if( mainRenderer == NULL )
                {

                    printf( "Software Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                    initSuccess = false;
                }
			}

			else
			{
				//Initialize renderer color set to white.
				SDL_SetRenderDrawColor( mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading.
				int imgFlags = IMG_INIT_PNG;

				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					initSuccess = false;
				}
                
                //Initialize SDL_ttf true type font.
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    initSuccess = false;
                }
			}
		}
	}

	return initSuccess;
}

/*********************************************************************
** Description: This function allows SDL to initiate outside of the
*  class. It also loads media.
*
*  Return: bool - indicates if the initiation process was successful.
*********************************************************************/
bool GraphicsHandler::startUp()
{
    bool success = true;

    //Initiates SDL and all related functions.
    if( !initiateSDL() )
    {
        printf( "Program failed to initialize!\n" );
        success = false;
    }

    //Loads media.
    else if( !ticTacToeTextures.loadMedia( mainRenderer ) )
    {
        printf( "Failed to load media!\n" );
        success = false;
    }

    else
    {
        //Retrieve the X and O sprite clippings.
        X = ticTacToeTextures.getRectX();
        O = ticTacToeTextures.getRectO();

        //Allows alpha blending.
        SDL_SetRenderDrawBlendMode( mainRenderer, SDL_BLENDMODE_BLEND ); 
    }

    return success;
}

/*********************************************************************
** Description: This function clears the color on the screen to white.
*********************************************************************/
void GraphicsHandler::clearScreen()
{
    SDL_SetRenderDrawColor ( mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF ); 
    SDL_RenderClear( mainRenderer );
}

/*********************************************************************
** Description: This function draws the Tic Tac Toe board. 
*
*  Parameters:
*  1. MouseButtons* mouseHoverButton - current mouse button that the
*     mouse pointer is hovering over.
*  2. bool click - represents a valid mouse click.
*********************************************************************/
void GraphicsHandler::drawGame( MouseButtons* mouseHoverButton, Player player, Outcome win )
{
    clearScreen();

    //Render the viewport for the board.
    SDL_RenderSetViewport( mainRenderer, &fillRectangle);

    //Draw the dark grey portion.
    SDL_SetRenderDrawColor( mainRenderer, 0x1A, 0x1A, 0x1A, 0xFF );
    SDL_RenderFillRect( mainRenderer, &fillRectangle );

    //Set the color of the grey lines.
    SDL_SetRenderDrawColor( mainRenderer, 0xCC, 0xCC, 0xCC, 0xFF );

    //Draw the grey lines.
    SDL_RenderFillRect( mainRenderer, &lines[0] );
    SDL_RenderFillRect( mainRenderer, &lines[1] );
    SDL_RenderFillRect( mainRenderer, &lines[2] );
    SDL_RenderFillRect( mainRenderer, &lines[3] );

    //Line animations.
    if( lines[0].h < 396 )
        lines[0].h += 5; 

    if( lines[1].h < 396 )
        lines[1].h += 5; 

    if( lines[2].w < 396 )
        lines[2].w += 5; 

    if( lines[3].w < 396 )
        lines[3].w += 5; 

    //Highlights mouse buttons that are hovered over by the mouse.
    if( mouseHoverButton == nullptr )
        highlightOpacity = 0;

    else if( win == UNFINISHED ) 
    {
        highlightOpacity = 35;

        highlight = { mouseHoverButton->getXLocation(), mouseHoverButton->getYLocation(), 
                      mouseHoverButton->getWidth(), mouseHoverButton->getHeight() };

        SDL_SetRenderDrawColor( mainRenderer, 0x42, 0xE2, 0xF4, highlightOpacity );
        SDL_RenderFillRect( mainRenderer, &highlight );

        if( mouseHoverButton->getMouseClick() && mouseHoverButton->getPick() == No_Player )
        {
            buttonClicked.emplace_back( highlight, player );
            mouseHoverButton->setPick( player );

            if(win == UNFINISHED)
            {
                turn = 1 - turn;
            }
        }
    }
    
    //Draw the Xs and Os. 
    for( unsigned i = 0; i < buttonClicked.size(); i++ )
    {
        if( buttonClicked.at(i).cPlayer == X_Player )
        {
            renderTexture( ticTacToeTextures.getXO(), &X, &buttonClicked.at(i).button );
        }

        else if( buttonClicked.at(i).cPlayer == O_Player )
        {
            renderTexture( ticTacToeTextures.getXO(), &O, &buttonClicked.at(i).button );
        }
    }

    //Create the viewport HUD that displays game information.
    SDL_RenderSetViewport( mainRenderer, &viewportHud );
    SDL_SetRenderDrawColor( mainRenderer, 0xCC, 0xCC, 0xCC, 0xFF );
    SDL_RenderFillRect( mainRenderer, &viewportSpecs );

    //Fade in font animation variable
    if(fontOpacity < 249 )
    {
        fontOpacity += 2;
    }

    //Draw the win and draw message.
    if( win == DRAW )
    {
        renderTexture( ticTacToeTextures.getDraw(), NULL, &text );

        SDL_SetRenderDrawColor( mainRenderer, 0xAF, 0xAF, 0xA8, 0xFF );
        SDL_RenderFillRect( mainRenderer, &playAgainBox);
        renderTexture( ticTacToeTextures.getPlayAgain(), NULL, &playAgainText );

        if( mouseHoverButton == nullptr )
            highlightOpacity = 0;

        else 
        {
            highlightOpacity = 50;

            highlight = { 20, mouseHoverButton->getYLocation(), 
                          mouseHoverButton->getWidth(), mouseHoverButton->getHeight() };

            SDL_SetRenderDrawColor( mainRenderer, 0x42, 0xE2, 0xF4, highlightOpacity );
            SDL_RenderFillRect( mainRenderer, &playAgainBox );

            if( mouseHoverButton->getMouseClick() && mouseHoverButton->getPick() == No_Player )
            {
                buttonClicked.emplace_back( highlight, player );
                mouseHoverButton->setPick( player );
            }
        }
    }

    else if( win == X_WON )
    {
        renderTexture( ticTacToeTextures.getXWin(), NULL, &text );
        SDL_SetRenderDrawColor( mainRenderer, 0xAF, 0xAF, 0xA8, 0xFF );
        SDL_RenderFillRect( mainRenderer, &playAgainBox);
        renderTexture( ticTacToeTextures.getPlayAgain(), NULL, &playAgainText );

        if(!incremented)
        {
            ticTacToeTextures.incrementX( mainRenderer );
            incremented = true;
        }

        if( mouseHoverButton == nullptr )
            highlightOpacity = 0;

        else 
        {
            highlightOpacity = 50;

            highlight = { 20, mouseHoverButton->getYLocation(), 
                          mouseHoverButton->getWidth(), mouseHoverButton->getHeight() };

            SDL_SetRenderDrawColor( mainRenderer, 0x42, 0xE2, 0xF4, highlightOpacity );
            SDL_RenderFillRect( mainRenderer, &playAgainBox );

            if( mouseHoverButton->getMouseClick() && mouseHoverButton->getPick() == No_Player )
            {
                buttonClicked.emplace_back( highlight, player );
                mouseHoverButton->setPick( player );
            }
        }

    }

    else if( win == O_WON )
    {
        renderTexture( ticTacToeTextures.getOWin(), NULL, &text );

        SDL_SetRenderDrawColor( mainRenderer, 0xAF, 0xAF, 0xA8, 0xFF );
        SDL_RenderFillRect( mainRenderer, &playAgainBox);
        renderTexture( ticTacToeTextures.getPlayAgain(), NULL, &playAgainText );

        if(!incremented)
        {
            ticTacToeTextures.incrementO( mainRenderer );
            incremented = true;
        }

        if( mouseHoverButton == nullptr )
            highlightOpacity = 0;

        else 
        {
            highlightOpacity = 50;

            highlight = { 20, mouseHoverButton->getYLocation(), 
                          mouseHoverButton->getWidth(), mouseHoverButton->getHeight() };

            SDL_SetRenderDrawColor( mainRenderer, 0x42, 0xE2, 0xF4, highlightOpacity );
            SDL_RenderFillRect( mainRenderer, &playAgainBox );

            if( mouseHoverButton->getMouseClick() && mouseHoverButton->getPick() == No_Player )
            {
                buttonClicked.emplace_back( highlight, player );
                mouseHoverButton->setPick( player );
            }
        }
    }

    else if( turn == 0 )
    {
        SDL_SetTextureAlphaMod( ticTacToeTextures.getXTurn(), fontOpacity ); 
        renderTexture( ticTacToeTextures.getXTurn(), NULL, &text );
    }

    else if( turn == 1 )
    {
        SDL_SetTextureAlphaMod( ticTacToeTextures.getOTurn(), fontOpacity ); 
        renderTexture( ticTacToeTextures.getOTurn(), NULL, &text );
    }


    SDL_SetTextureAlphaMod( ticTacToeTextures.getXPoints(), fontOpacity ); 
    renderTexture( ticTacToeTextures.getXPoints(), NULL, &Xpoints ); 

    SDL_SetTextureAlphaMod( ticTacToeTextures.getXP(), fontOpacity ); 
    renderTexture( ticTacToeTextures.getXP(), NULL, &XPLoc); 

    SDL_SetTextureAlphaMod( ticTacToeTextures.getOPoints(), fontOpacity ); 
    renderTexture( ticTacToeTextures.getOPoints(), NULL, &Opoints ); 

    SDL_SetTextureAlphaMod( ticTacToeTextures.getOP(), fontOpacity ); 
    renderTexture( ticTacToeTextures.getOP(), NULL, &OPLoc); 

    SDL_RenderPresent( mainRenderer ); //Update the rendering screen.
}

/*********************************************************************
** Description: This function renders images to the screen according
* to the rectangle dimensions and location.
*
* Parameters:
* 1. SDL_Texture* - the image that will be rendered.
* 2. SDL_Rect* clip - the clip of the image, if it is part of a larger 
*    sheet.
* 3. SDL_Rect* renderQuad - the target rectangle rendering shape. 
* 4. double - the angle the image will rotate.
* 5. SDL_Point* - the point the target will rotate around. NULL for the
*    center.
* 6. SDL_RendererFlip - flip the orientation of the image horizontally,
*    vertically, or none.
*********************************************************************/
void GraphicsHandler::renderTexture( SDL_Texture* texture, SDL_Rect* clip, 
SDL_Rect* renderQuad, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    if( texture != NULL )
    {
        SDL_RenderCopyEx( mainRenderer, texture, clip, renderQuad, angle, center, flip );
    }
}

/*********************************************************************
** Description: Function to reset the button choices every turn. 
*********************************************************************/
void GraphicsHandler::reset()
{
    incremented = false;
    buttonClicked.clear();
    turn = 1;
}

/*********************************************************************
** Description: Cleans up SDL functions and frees memory. 
*********************************************************************/
void GraphicsHandler::cleanUp()
{
    //reset( 3 );
    reset();

    ticTacToeTextures.cleanUp();

    if( mainRenderer != NULL)
    {
	    SDL_DestroyRenderer( mainRenderer );
	    mainRenderer = NULL;
    }
    
    if( mainWindow != NULL )
    {
	    SDL_DestroyWindow( mainWindow );
	    mainWindow = NULL;
    }

	SDL_Quit();
}
