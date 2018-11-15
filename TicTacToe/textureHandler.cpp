/*********************************************************************
** Program name: Tic Tac Toe
** Author: Long Le
** Date: 7/20/2017
** Description: The TextureHandler class generates textures used to
*  render onto the screen from PNG images or text using SDL_image and 
*  SDL_ttf respectively.
*********************************************************************/
#include "textureHandler.hpp"

/*********************************************************************
** Description: Constructor. 
*********************************************************************/
TextureHandler::TextureHandler() : XandO( "image/xo.png" )
{
    fontPath = "font/theone.ttf";
    X_Render = { 0, 0, 0, 0 }; 
    O_Render = { 0, 0, 0, 0 }; 

    DrawColor = { 0, 0, 0, 0xFF };

    font = NULL;
    XTurn = NULL;
    OTurn = NULL;
    XWin = NULL;
    OWin = NULL;
    OP = NULL;
    XP = NULL;
    playAgain = NULL;

    XPoint = 0;
    OPoint = 0;

    //Used to render points. 
    XpointSS.str(string());  
    XpointSS << XPoint;
    OpointSS.str(string()); 
    OpointSS << OPoint;
}

/*********************************************************************
** Description: Destructor. 
*********************************************************************/
TextureHandler::~TextureHandler()
{
    //empty.
}

/*********************************************************************
** Description: This function loads the related media and calls
*  loadTexture() to optimize the images.
*
*  Return: bool - indicates whether the operation was successful.
*********************************************************************/
bool TextureHandler::loadMedia( SDL_Renderer* renderer )
{
	bool success = true;
    
    XandO.texture = loadTexture( XandO.path, renderer );

    if( XandO.texture == NULL) 
    {
        printf( "Failed to load images!\n" );
        success = false;
    }

    font = TTF_OpenFont( fontPath.c_str(), 28 );

    if( font == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }

    else
    {
        SDL_Color XColor = { 0x55, 0xa3, 0, 0xFF };
        SDL_Color OColor = { 0x9d, 0, 0, 0xFF };

        XTurn = loadRenderedText( "Player X Turn", XColor, renderer );
        OTurn = loadRenderedText( "Player O Turn", OColor, renderer );
        XWin = loadRenderedText( "X WON", XColor, renderer );
        OWin = loadRenderedText( "O WON", OColor, renderer );
        Draw = loadRenderedText( "DRAW", DrawColor, renderer );
        XPoints = loadRenderedText( "X Points: ", XColor, renderer );
        OPoints = loadRenderedText( "O Points: ", OColor, renderer );
        XP = loadRenderedText( XpointSS.str(), DrawColor, renderer );
        OP = loadRenderedText( OpointSS.str(), DrawColor, renderer );
        playAgain = loadRenderedText( "Play Again?", DrawColor, renderer );

        if( XTurn == NULL || OTurn == NULL || XWin == NULL || OWin == NULL ) 
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }

    //Clip the X and O sprites from the PNG image.
    if( success )
    {
        X_Render = { 0, 1181 / 2, 591, 1181 / 2 };
        O_Render = { 0, 0, 591, 1181 / 2 };
    }

	return success;
}

/*********************************************************************
** Description: This function creates textures from PNG images. 
*
*  Parameters: 
*  1. string - the path to the picture.
*  2. SDL_Renderer* - the screen renderer.
*
*  Return: SDL_Texture* - The optimized texture from an image. 
*********************************************************************/
SDL_Texture* TextureHandler::loadTexture( const string &path, SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); //Load the image onto a surface.

    if( loadedSurface == NULL )
    {
    	printf( "Unable to load image! SDL_image Error: %s\n", IMG_GetError() );
    }

    else
    {
        //Set transparent color to Cyan.
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        
		//Create texture from the loaded surface pixels.
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );

		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		SDL_FreeSurface( loadedSurface ); //Frees the previously loaded surface.
    }

    return newTexture;
}

/*********************************************************************
** Description: This function creates textures from ttf files. 
*
*  Parameters: 
*  1. string - the path to the font file.
*  2. SDL_Color - the color of the text.
*  3. SDL_Renderer* - the main renderer.
*
*  Return: SDL_Texture* - The optimized texture from the font file. 
*********************************************************************/
SDL_Texture* TextureHandler::loadRenderedText( const string &text, SDL_Color textColor, SDL_Renderer* renderer )
{
    SDL_Texture* newText = NULL;

    SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), textColor );

    if( textSurface == NULL )
    {
    	printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    else
    {
        newText = SDL_CreateTextureFromSurface( renderer, textSurface );

		if( newText == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", text.c_str(), SDL_GetError() );
		}

		SDL_FreeSurface( textSurface ); //Frees the previously loaded surface.
    }

    return newText;
}

/*********************************************************************
** Description: This function increments the X points and replaces the 
*  texture with the updated points. 
*
*  Parameters: SDL_Renderer* - the main renderer.
*********************************************************************/
void TextureHandler::incrementX( SDL_Renderer* renderer )
{   
    XPoint++;
    XpointSS.str(string());
    XpointSS << XPoint;
    SDL_DestroyTexture( XP );
    XP = loadRenderedText( XpointSS.str(), DrawColor, renderer );
}

/*********************************************************************
** Description: This function increments the O points and replaces the 
*  texture with the updated points. 
*
*  Parameters: SDL_Renderer* - the main renderer.
*********************************************************************/
void TextureHandler::incrementO( SDL_Renderer* renderer )
{   
    OPoint++;
    OpointSS.str(string());
    OpointSS << OPoint;
    SDL_DestroyTexture( OP );
    OP = loadRenderedText( OpointSS.str(), DrawColor, renderer );
}

/*********************************************************************
** Description: This function frees all memory from textures, fonts,
*  images and shuts down SDL processes.
*********************************************************************/
void TextureHandler::cleanUp()
{
    XandO.destroyTexture();

    if( font != NULL )
    {
        TTF_CloseFont( font );
        font = NULL;
    }

    if( XTurn != NULL)
    {
        SDL_DestroyTexture( XTurn );
        XTurn = NULL;
    }
    
    if( OTurn != NULL)
    {
        SDL_DestroyTexture( OTurn);
        OTurn = NULL;
    }

    if( XWin != NULL)
    {
        SDL_DestroyTexture( XWin );
        XWin = NULL;
    }

    if( OWin != NULL)
    {
        SDL_DestroyTexture( OWin );
        OWin = NULL;
    }

    if( Draw != NULL)
    {
        SDL_DestroyTexture( Draw );
        Draw = NULL;
    }

    if( XPoints != NULL)
    {
        SDL_DestroyTexture( XPoints );
        XPoints = NULL;
    }
    
    if( OPoints != NULL)
    {
        SDL_DestroyTexture( OPoints );
        OPoints = NULL;
    }

    if( XP != NULL)
    {
        SDL_DestroyTexture( XP );
        XP = NULL;
    }

    if( OP != NULL)
    {
        SDL_DestroyTexture( OP );
        OP = NULL;
    }

    if( playAgain != NULL)
    {
        SDL_DestroyTexture( playAgain );
        playAgain = NULL;
    }

	IMG_Quit();
    TTF_Quit();
}
