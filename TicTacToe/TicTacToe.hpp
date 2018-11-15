/*********************************************************************
** Program name: Tic Tac Toe
** Author: Long Le
** Date: 7/20/2017
** Description: Tic Tac Toe game created using SDL libraries. There is
*  a 50% chance player X or player O will start first. Both players 
*  will try to get three in a row in order to win.
*********************************************************************/
#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "mouseButtons.hpp"
#include "graphicsHandler.hpp"
#include <SDL.h>
#include <cstdlib>
#include <ctime>

class TicTacToe
{
    private:
        Player currentPlayer,
               previousPlayer;

        MouseButtons ticTacToeButtons[3][3];
        MouseButtons playAgainButton;

        GraphicsHandler ticTacToeGraphics;

        int drawGameCountdown;

    public:
        TicTacToe( int, int );
        Outcome checkGame();
        void runGame();
        void cleanUp();
};

#endif
