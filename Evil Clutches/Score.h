#ifndef _EC_SCORE_H_
#define _EC_SCORE_H_

#include "OGE\OFontEntity.h"
#include "Define.h"
#include <algorithm>

class Score
{
public:

	static int sCurrentScore;

	Score();

	void onLoad();
	void onLoop();
	void onCleanup();
	void onReset();

	void showHighScores();

private:
	static const int maxHighScores = 10;

	OFontEntity scoreText;

	OFontEntity highScoreText;

	Sint32 highscores[maxHighScores+1]; //Add one buffer for session score

	bool static sortDecending(Sint32 i, Sint32 j);
	
	void addScoreToHighScore();

	int highScoreMessageMaxWidth = 200;

	SDL_Color fontColor = { 255,255,255 };

	bool scoreRecorded;
		
};
#endif // !_EC_SCORE_H_
