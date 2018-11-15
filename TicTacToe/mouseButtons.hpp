/*********************************************************************
** Program name: Tic Tac Toe
** Author: Long Le
** Date: 7/20/2017
** Description: The MouseButtons class represents buttons that can be
*  interacted with the mouse pointer by clicking or hovering over.
*********************************************************************/
#ifndef MOUSE_BUTTONS_HPP
#define MOUSE_BUTTONS_HPP

#include <SDL.h>

//Used to store information on which player has
//picked this button.
enum Player { X_Player, O_Player, No_Player };

class MouseButtons
{
	private:
        //Button specifications.
        int xLocation,
            yLocation,
            width,
            height;

        //Tracks location of the mouse.
	    int xMouseLocation, 
            yMouseLocation;

        //Stores mouse states.
        bool mouseOver,
             mouseClick;

        //Stores which player has picked this button.
        Player pick;

	public:
        MouseButtons();
		void handleEvent( SDL_Event* e );
        void setButtonSpecs( int, int, int, int );
        void reset();

        //Getter functions.
        bool getMouseOver()  { return mouseOver; };
        bool getMouseClick() { return mouseClick; };
        int  getXLocation()  { return xLocation; };
        int  getYLocation()  { return yLocation; };
        int  getWidth()      { return width; };
        int  getHeight()     { return height; };
        Player getPick()     { return pick; };

        //Sets the player that picks the button.
        void setPick( Player pick ) { this->pick = pick; };
};

#endif
