#include "CApp.h"

void CApp::OnPaused()
{
	//When game is paused show high score screens and listen for return to be clicked to restart game 
	//or for game to exit
	score.showHighScores();
}