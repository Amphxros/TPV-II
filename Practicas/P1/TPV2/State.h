#pragma once
#include "ecs/Component.h"

enum GameState { NEW, RUNNING, PAUSE, GAMEOVER };
class State :
    public Component
{
public:
    State();
    virtual ~State();
    virtual void init() override;
    GameState getGameState() { return gameState; }
    void changeState(GameState gs) { gameState = gs; }

private:
    GameState gameState;
};

