#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform : public Component
{
public:

    Transform(): pos_(Vector2D()), dir_(Vector2D()), w_(0),h_(0), rot_(0) {};
    Transform(Vector2D pos, Vector2D dir, double width, double height, double rotation);
    virtual ~Transform();

    virtual void init() override;
    virtual void update() override;

    Vector2D getPos() { return pos_; }
    Vector2D getDir() { return dir_; }

    inline void setPos(Vector2D pos) { pos_ = pos; }
    inline void setDir(Vector2D dir) { dir_ = dir; }

    inline void setPos(double x, double y) { pos_.set(x, y); }
    inline void setDir(double x, double y) { dir_.set(x, y); }

    inline double getW() { return w_; }
    inline double getH() { return h_; }
    inline double getRotation() { return rot_; }

    inline void setW(double w) { w = w; }
    inline void setH(double h) { h = h; }
    inline void setRotation(double r) { rot_ = r; }

private:

    Vector2D pos_, dir_;
    double w_, h_, rot_;

};