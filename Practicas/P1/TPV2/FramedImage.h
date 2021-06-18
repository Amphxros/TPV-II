#pragma once
#include "ecs/Component.h"
#include "Transform.h"

class FramedImage :
    public Component
{
	public:
	FramedImage(double thrust);
		virtual ~FramedImage();

		virtual void init() override;
		virtual void update() override;
		virtual void render() override;
		

	private:
		Transform* tr_;
		int srows, scols, row,col;
};

