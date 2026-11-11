#include "Scene.h"
#include <random>

struct Particle{
    glm::vec3  position;
    glm::vec3 velocity;
    glm::vec4 color;
    float lifeTime;
};

class Scene1 : public Scene
{
    float pitch = 0.f;
    float roll = 0.f;
    float yaw = 0.f;

    float pitch_inc = 0.005f;
    float roll_inc = 0.005f;
    float yaw_inc = 0.005f;

    float particleLifetime = 1.5f;

    int32_t launch_delay = 8;
    int32_t lastLaunch = 0;
    void launchSphere();

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> dis;

    std::vector<Particle> particles;

    virtual void onDraw(Renderer &renderer) override;
    virtual void simulateStep() override;
    virtual void onGUI() override;

    public:
        Scene1() : gen(rd()), dis(0.f, 1.f) {}
};