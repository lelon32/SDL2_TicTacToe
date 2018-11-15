/*********************************************************************
** Program name: Tic Tac Toe
** Author: Long Le
** Date: 7/20/2017
** Description: The MouseButtons class represents buttons that can be
*  interacted with the mouse pointer by clicking or hovering over.
*********************************************************************/
#include "mouseButtons.hpp"


/*********************************************************************
 ** Description: Constructor. 
 *********************************************************************/
MouseButtons::MouseButtons() 
{
    xLocation = 0;
    yLocation = 0;
    width = 0;
    height = 0;

    mouseOver = false;
    mouseClick = false;
    pick = No_Player; //Button that a player has picked in Tic Tac Toe.

    xMouseLocation = 0;
    yMouseLocation = 0;
}

/*********************************************************************
 ** Description: Sets the specifications of the mouse button. 
 *
 *  Parameters:
 *  1. int xLocation - x location of the button relative to the screen.
 *  2. int yLocation - y location of the button relative to the screen.
 *  3. int width - mouse button width. 
 *  4. int height - mouse button height. 
 *********************************************************************/
void MouseButtons::setButtonSpecs( int xLocation, int yLocation, int width, int height )
{
    this->xLocation = xLocation;
    this->yLocation = yLocation;
    this->width = width;
    this->height = height;
}

/*********************************************************************
 ** Description: Handles the status of the mouse events.  
 *
 *  Parameters: SDL_Event* - Event polling variable. 
 *********************************************************************/
void MouseButtons::handleEvent( SDL_Event* e )
{
    //Checks if a mouse event is occurring.
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN ) 
    {
        SDL_GetMouseState( &xMouseLocation, &yMouseLocation );
        mouseOver = true;
        
        //Mouse is left of the button.
        if( xMouseLocation < xLocation )
            mouseOver = false;

        //Mouse is right of the button
        else if( xMouseLocation > xLocation + width )
            mouseOver = false;

        //Mouse above the button
        else if( yMouseLocation < yLocation )
            mouseOver = false;

        //Mouse below the button
        else if( yMouseLocation > yLocation + height )
            mouseOver = false;

        else if( e->type == SDL_MOUSEBUTTONDOWN )
            mouseClick = true;
    }

    else
    {
        xMouseLocation = 0;
        yMouseLocation = 0;
        mouseOver = false;
    }
}

/*********************************************************************
 ** Description: Resets mouse button variables. 
 *********************************************************************/
void MouseButtons::reset()
{
    mouseOver = false;
    mouseClick = false;
    pick = No_Player;
}
