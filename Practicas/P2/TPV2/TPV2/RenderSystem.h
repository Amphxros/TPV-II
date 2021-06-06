#pragma once
#include <cstdint>

#include "ecs/System.h"

class Texture;

class RenderSystem : public System
{
public:
	RenderSystem();
	virtual ~RenderSystem();
	// - dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
	// - dibujar el marcador y las vidas (siempre).
	// - dibujar el mensaje correspondiente si el juego est� parado (como en la
	// pr�ctica 1)
	// - Otra posibilidad es definir un m�todo render en la clase System, y distribuir
	// este c�digo en los sistemas correspondientes en lugar de tener un s�lo
	// sistema para rendering
	void init() override;
	void update() override;
	void receive(const Message& m) override;

private:
	// Metodos para el sistema de mensajes
	void drawMsgs();
	void drawLives();
	void drawEntitiesWithImage();

	// Variables de control del estado del juego
	bool isRunning_;
	bool isGameOver_;
	bool isNewGame_;
	bool fighterWon_;
	unsigned short int remainingRounds_;

	// Texturas de las entidades
	Texture* fighter_;
	Texture* bullet_;
	Texture* asteroid_;
	Texture* asteroidGold_;
};