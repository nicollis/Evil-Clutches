#include "Score.h"

int Score::sCurrentScore = 0;

Score::Score()
{
	scoreRecorded = false;
}

void Score::onLoad()
{
	//Initalize game sesson score
	highScoreText.onLoad("OGE/OpenSans-Bold.ttf", 18, fontColor, highScoreMessageMaxWidth);
	scoreText.onLoad("OGE/OpenSans-Bold.ttf");
	scoreText.setText("0");
	scoreText.getDemensions()->x = WINDOW_WIDTH - (scoreText.getDemensions()->w + 10);
	scoreText.getDemensions()->y = 0;

	//Load in scores file
	SDL_RWops* file = SDL_RWFromFile("scores.bin", "r+b");

	//File doesn't load
	if (file == NULL)
	{
		SDL_Log("Warning: Unable to open file! SDL Error: %s\n", SDL_GetError());
		//Create new file for writing
		file = SDL_RWFromFile("scores.bin", "w+b");
		if (file == NULL)
		{
			SDL_Log("Error: Unable to create file! SDL Error: %s\n", SDL_GetError());
		}
		else //Creat inital data!
		{
			for (int i = 0; i < maxHighScores; ++i)
			{
				highscores[i] = 0;
				SDL_RWwrite(file, &highscores[i], sizeof(Sint32), 1);
			}

			//Close file for now
			SDL_RWclose(file);
		}
	}
	else //Load scores from file
	{
		for (int i = 0; i < maxHighScores; ++i)
		{
			SDL_RWread(file, &highscores[i], sizeof(Sint32), 1);
		}

		//Close file
		SDL_RWclose(file);
	}
}

void Score::onLoop()
{
	scoreText.setText("Score: " + (std::to_string(sCurrentScore)));
	scoreText.getDemensions()->x = WINDOW_WIDTH - (scoreText.getDemensions()->w + 10);
}

void Score::onCleanup()
{
	addScoreToHighScore();

	SDL_RWops* file = SDL_RWFromFile("scores.bin", "w+b");
	if (file == NULL)
	{
		SDL_Log("Error: Unable to save file! SDL Error: %s\n", SDL_GetError());
	}
	else //Creat inital data!
	{
		for (int i = 0; i < maxHighScores; ++i)
		{
			SDL_RWwrite(file, &highscores[i], sizeof(Sint32), 1);
		}
		//Close file for now
		SDL_RWclose(file);
	}
}

void Score::onReset()
{
	onCleanup(); //Saves current high score list

	sCurrentScore = 0;

	scoreRecorded = false;

	highScoreText.setText("");
}

void Score::showHighScores()
{
	addScoreToHighScore();
	
	//Set onsreen text
	std::string text = "High Scores!\n";
	for (int i = 0; i < maxHighScores; ++i)
	{
		text += std::to_string(i) + ": " + std::to_string(highscores[i]);
		text += "\n";
	}
	text += "\nHit return to restart...";
	highScoreText.setText(text);
	highScoreText.getDemensions()->x = (WINDOW_WIDTH / 2) - (highScoreText.getDemensions()->w / 2);
	highScoreText.getDemensions()->y = (WINDOW_HEIGHT / 2) - (highScoreText.getDemensions()->h / 2);
	highScoreText.onLoop();
}

bool Score::sortDecending(Sint32 i, Sint32 j)
{
	return i > j;
}

void Score::addScoreToHighScore()
{
	if (scoreRecorded) return;
	//Load in score into array buffer
	highscores[maxHighScores] = sCurrentScore;
	//Orginize high scores and save to file
	std::sort(std::begin(highscores), std::end(highscores), Score::sortDecending);
	scoreRecorded = true;
}