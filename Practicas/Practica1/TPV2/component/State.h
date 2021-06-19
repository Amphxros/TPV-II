#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
enum GameState { NEW, RUNNING, PAUSE, GAMEOVER };
class State :
    public Component
{
public:
    State();
    virtual ~State();
    
	virtual void init() override;
    virtual void render() override;
    
	GameState getGameState() { return gameState; }
    void changeState(GameState gs, bool win=false) { gameState = gs; gameWin = win; }

private:

    bool gameWin;
	GameState gameState;
	
	Texture* initMsg;
	Texture* pauseMsg;
	Texture* gameOverMsg;
	Texture* gameWinMsg;

};

