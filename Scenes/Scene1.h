#include "Scene.h"

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