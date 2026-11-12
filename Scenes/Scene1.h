#include "Scene.h"


struct MassPoint{
    glm::vec3  position;
    glm::vec3 velocity;
    float mass;
};

struct Spring{
    float k;
    float L;
    int p0;
    int p1;
};

class Scene1 : public Scene
{
    virtual void onDraw(Renderer &renderer) override;
    virtual void simulateStep() override;
    virtual void onGUI() override;
    virtual void init() override;

    void eulerStep(float dt);
    void midPointStep(float dt);
    std::vector<glm::vec3> calcAccel(std::vector<MassPoint>& state) const;

    std::vector<MassPoint> points;
    std::vector<Spring> springs;
};