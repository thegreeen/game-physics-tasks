#include "Scene.h"


struct MassPoint{
    glm::vec3  position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float mass;
};

struct Spring{
    float k;
    float L;
    MassPoint p0;
    MassPoint p1;
};

class Scene1 : public Scene
{
    virtual void onDraw(Renderer &renderer) override;
    virtual void simulateStep() override;
    virtual void onGUI() override;
    virtual void init() override;

    std::vector<MassPoint> points;
    std::vector<Spring> springs;
};