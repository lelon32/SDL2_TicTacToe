/*********************************************************************
** Program name: Tic Tac Toe
** Author: Long Le
** Date: 7/20/2017
** Description: Tic Tac Toe game created using SDL libraries. There is
*  a 50% chance player X or player O will start first. Both players 
*  will try to get three in a row in order to win.
*********************************************************************/
#include "TicTacToe.hpp"

/*********************************************************************
** Description: Main function. Parameters set as required by SDL.
*********************************************************************/
int main( int argc, char** argv )
{
    const int SCREEN_WIDTH = 640,
              SCREEN_HEIGHT = 480;

    srand(time(NULL));

    TicTacToe ticTacToe( SCREEN_WIDTH, SCREEN_HEIGHT);

    ticTacToe.runGame();

    ticTacToe.cleanUp();

    return 0;
}

/*********************************************************************
** Description: Constructor.
*  Parameters:
*  1. int width - width of the game window.
*  2. int height - height of the game window.
*********************************************************************/
TicTacToe::TicTacToe( int width, int height ) :  ticTacToeGraphics( width, height )
{
    //Create the mouse buttons.
    ticTacToeButtons[0][0].setButtonSpecs(   0,   0, 150 , 150 ); 
    ticTacToeButtons[0][1].setButtonSpecs( 165,   0, 150 , 150 );
    ticTacToeButtons[0][2].setButtonSpecs( 330,   0, 150 , 150 );
    ticTacToeButtons[1][0].setButtonSpecs(   0, 165, 150 , 150 );
    ticTacToeButtons[1][1].setButtonSpecs( 165, 165, 150 , 150 );
    ticTacToeButtons[1][2].setButtonSpecs( 330, 165, 150 , 150 );
    ticTacToeButtons[2][0].setButtonSpecs(   0, 330, 150 , 150 );
    ticTacToeButtons[2][1].setButtonSpecs( 165, 330, 150 , 150 );
    ticTacToeButtons[2][2].setButtonSpecs( 330, 330, 150 , 150 );
    ticTacToeButtons[2][2].setButtonSpecs( 330, 330, 150 , 150 );

    //Play again button.
    playAgainButton.setButtonSpecs( 500, 100, 120, 120 );

    drawGameCountdown = 9;
}

/*********************************************************************
** Description: This function runs the game loop until the user clicks 
*  the close window button.
*********************************************************************/
void TicTacToe::runGame()
{
    //Randomly chooses player X or Player O to make the first move.
    int randomPlayerStarts = rand() % 2;
    ticTacToeGraphics.setTurn( randomPlayerStarts );
    currentPlayer = static_cast<Player>(randomPlayerStarts);
    previousPlayer = currentPlayer;

    //Initiate all the graphic components.
    if( !ticTacToeGraphics.startUp() )
    {
        printf( "Tic Tac Toe failed to start!\n" );
    }

    else
    {
        bool quit = false; //Quits the game.
        bool endLoop = false; //Exits button event loop.
        bool mousebButtonClicked = false;
        bool endRoundLoop = false; //Enters the post-round loop if true.

        Outcome gameState = UNFINISHED;
        MouseButtons* currentButton = nullptr; //Current mouse button clicked.
        SDL_Event event; //Polling event.

        //Running game loop.
        while( !quit )
        {
            endLoop = false;

            //Poll for input events.
            while( SDL_PollEvent( &event ) != 0 )
            {
                mousebButtonClicked = false;

                if( event.type == SDL_QUIT )
                {
                    quit = true;
                }

                else
                {
                    //Checks the buttons to see if any are clicked.
                    for( unsigned i = 0; i < 3 && !endLoop; i++ )
                    {
                        for( unsigned j = 0; j < 3 && !endLoop; j++ )
                        {
                            //Checks for hover over mouse and valid mouse click.
                            ticTacToeButtons[i][j].handleEvent( &event );

                            if( ticTacToeButtons[i][j].getMouseOver() == true )
                            {
                                endLoop = true;
                                currentButton = &ticTacToeButtons[i][j];
                                mousebButtonClicked = ticTacToeButtons[i][j].getMouseClick();
                            }
                        }
                    }
                }
            }

            //To get the game order right.
            previousPlayer = currentPlayer;

            if( mousebButtonClicked && currentButton->getPick() == No_Player )
            {
                drawGameCountdown--;
                currentPlayer = static_cast<Player> ( 1 - static_cast<int>( currentPlayer ) );
            }

            //Render the graphic to the screen.
            ticTacToeGraphics.drawGame( currentButton, previousPlayer, gameState );

            //Check the game status.
            gameState = checkGame();

            if( gameState != UNFINISHED )
                endRoundLoop = true;

            //Post-round loop. 
            while( endRoundLoop )
            {
                while( SDL_PollEvent( &event ) != 0 )
                {
                    currentButton = nullptr;
                    mousebButtonClicked = false;

                    if( event.type == SDL_QUIT )
                    {
                        endRoundLoop = false;
                    }

                    else
                    {
                        //Check to see if the user clicked the play again button.
                        playAgainButton.handleEvent( &event );

                        if( playAgainButton.getMouseOver() == true )
                        {
                            currentButton = &playAgainButton;
                            mousebButtonClicked = playAgainButton.getMouseClick();

                            //Clicking the play again button will reset
                            //the Tic Tac Toe buttons and variables.
                            if( mousebButtonClicked )
                            {
                                endRoundLoop = false;
                                quit = false;
                                gameState = UNFINISHED;
                                currentButton = nullptr;
                                drawGameCountdown = 9;
                                mousebButtonClicked = false;
                                ticTacToeGraphics.reset();
                                playAgainButton.reset();

                                for( unsigned i = 0; i < 3; i++ )
                                {
                                    for( unsigned j = 0; j < 3; j++ )
                                    {
                                        ticTacToeButtons[i][j].reset();
                                    }
                                }

                                randomPlayerStarts = rand() % 2;
                                ticTacToeGraphics.setTurn( randomPlayerStarts );
                                currentPlayer = static_cast<Player>(randomPlayerStarts);
                                previousPlayer = currentPlayer;
                            }
                        }
                    }
                }    

                ticTacToeGraphics.drawGame( currentButton, previousPlayer, gameState );
            }
        }
    }
}

/*********************************************************************
** Description: Checks for winning conditions of Tic Tac Toe.
*  
*  Return: Outcome - the Outcome enum type. Represents the outcome of
*  the game.
*********************************************************************/
Outcome TicTacToe::checkGame()
{
    Outcome gameOutcome = UNFINISHED; //Resets outcome.

    //All winning conditions.
  	if(    ( ticTacToeButtons[0][0].getPick() == previousPlayer
          && ticTacToeButtons[1][0].getPick() == previousPlayer 
          && ticTacToeButtons[2][0].getPick() == previousPlayer ) 

        || ( ticTacToeButtons[0][1].getPick() == previousPlayer 
          && ticTacToeButtons[1][1].getPick() == previousPlayer 
          && ticTacToeButtons[2][1].getPick() == previousPlayer )

        || ( ticTacToeButtons[0][2].getPick() == previousPlayer 
          && ticTacToeButtons[1][2].getPick() == previousPlayer 
          && ticTacToeButtons[2][2].getPick() == previousPlayer ) 

        || ( ticTacToeButtons[0][0].getPick() == previousPlayer 
          && ticTacToeButtons[0][1].getPick() == previousPlayer 
          && ticTacToeButtons[0][2].getPick() == previousPlayer )

        || ( ticTacToeButtons[1][0].getPick() == previousPlayer 
          && ticTacToeButtons[1][1].getPick() == previousPlayer 
          && ticTacToeButtons[1][2].getPick() == previousPlayer ) 

        || ( ticTacToeButtons[2][0].getPick() == previousPlayer  
          && ticTacToeButtons[2][1].getPick() == previousPlayer 
          && ticTacToeButtons[2][2].getPick() == previousPlayer ) 

        || ( ticTacToeButtons[0][0].getPick() == previousPlayer  
          && ticTacToeButtons[1][1].getPick() == previousPlayer 
          && ticTacToeButtons[2][2].getPick() == previousPlayer ) 

        || ( ticTacToeButtons[2][0].getPick() == previousPlayer  
          && ticTacToeButtons[1][1].getPick() == previousPlayer 
          && ticTacToeButtons[0][2].getPick() == previousPlayer ) )
    {    
        if( previousPlayer == X_Player )
        {
            gameOutcome = X_WON;
        }
        
        else if( previousPlayer == O_Player )
        {
            gameOutcome = O_WON;
        }
    }

    else if( drawGameCountdown < 1 )
    {
        gameOutcome = DRAW;
    }
	
	return gameOutcome;	
}

/*********************************************************************
** Description: Shuts down SDL and affiliated processes. 
*********************************************************************/
void TicTacToe::cleanUp()
{
    ticTacToeGraphics.cleanUp();
}
