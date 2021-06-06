#pragma once
#include <SDL.h>

#include "ecs/Component.h"
#include "sdlutils/SDLUtils.h"

class Texture;

class Image : public Component {

	/*

	 - tex: una texturea que corresponde a una imagen con 'rows'
	 filas y 'col' columas, i.e., tiene rows*cols frames de
	 igual tama�o

	 - x, y, w, h: la posici�n/tama�o relativo de la imagen dentro
	 de cada frame (para evitar los espacios que normalmente
	 tenemos entre los frames).

	 > x,y: es la posici�n de la esquina sup-izq, relativo a la
	 esquina sup-izq del frame
	 > w,h: anchura y altura

	 - srow, scol, nrows, ncols: definen los frames que queremos
	 mostrar. Es un cuadro con (srow,scol) como equina sup-izq,
	 con 'nrows' filas y 'ncols' columnas.

	 - dur: la duraci�n en millisegundos de cada frame

	 */
	Image(Texture* tex, //
		int cols, int rows, //
		int x, int y, int w, int h, //
		int srow, int scol, int nrows = 1, int ncols = 1, //
		Uint32 dur = 300) {
		reset(tex, cols, rows, x, y, w, h, srow, scol, nrows, ncols, dur);
	}

	virtual ~Image() {
	}

	void reset(Texture* tex, //
		int cols, int rows, //
		int x, int y, int w, int h, //
		int srow, int scol, int nrows = 1, int ncols = 1, //
		Uint32 dur = 300) {

		tex_ = tex;
		x_ = x;
		y_ = y;
		w_ = w;
		h_ = h;
		srow_ = srow;
		scol_ = scol;
		nrows_ = nrows;
		ncols_ = ncols;
		frameDuration_ = dur;

		frameWidth_ = tex_->width() / cols;
		frameHeight_ = tex->height() / rows;
		currFrameR_ = 0;
		currFrameC_ = 0;
		lastFrameChange_ = 0;
		srcRect_ = { };
	}

	const SDL_Rect& nextFrame() {

		int r = (currFrameR_ + srow_);
		int c = (currFrameC_ + scol_);
		srcRect_ = { c * frameWidth_ + x_, r * frameHeight_ + y_, w_, h_ };

		if (sdlutils().currRealTime() > lastFrameChange_ + frameDuration_) {
			lastFrameChange_ = sdlutils().currRealTime();
			currFrameC_ = (currFrameC_ + 1) % ncols_;
			if (currFrameC_ == 0)
				currFrameR_ = (currFrameR_ + 1) % nrows_;
		}

		return srcRect_;
	}

	Texture* tex_;

	int x_;
	int y_;
	int w_;
	int h_;
	int srow_;
	int scol_;
	int nrows_;
	int ncols_;

	int frameWidth_;
	int frameHeight_;
	int currFrameR_;
	int currFrameC_;

	Uint32 frameDuration_;
	Uint32 lastFrameChange_;
	SDL_Rect srcRect_;
};

