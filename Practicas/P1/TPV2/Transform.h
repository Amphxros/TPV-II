#include "ecs/Component.h"
#include "utils/Vector2D.h"

class Transform : public Component
{
public:
    Transform();
    Transform(Vector2D pos, Vector2D dir, double width, double height, double rotation);
    virtual ~Transform();

    virtual void init() override;
    virtual void update() override;

    Vector2D getPos() { return pos; }
    Vector2D getDir() { return dir; }

    inline void setPos(Vector2D pos) { pos = pos; }
    inline void setDir(Vector2D dir) { dir = dir; }

    inline void setPos(double x, double y) { pos.set(x, y); }
    inline void setDir(double x, double y) { dir.set(x, y); }

    inline double getW() { return w; }
    inline double getH() { return h; }
    inline double getRotation() { return rot_; }

    inline void setW(double w) { w = w; }
    inline void setH(double h) { h = h; }
    inline void setRotation(double r) { rot_ = r; }

private:
    Vector2D pos, dir;
    double w, h, rot_;
};