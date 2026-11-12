#include "Scene4.h"
#include <glm/gtx/quaternion.hpp>
#include <imgui.h>
#include "glm/gtx/string_cast.hpp"

namespace {
    void printPoint(const MassPoint &point){
        std::cout << "position: " << glm::to_string(point.position) << std::endl;
        std::cout << "velocity: " << glm::to_string(point.velocity) << std::endl;
    }


    glm::vec3 hooke(float len, float k, float L, const glm::vec3 &d){
        return (-1) * k * (len - L) * (d/len);
    }

    float dt = 0.005f;
    glm::vec3 gravityAccel = glm::vec3(0,0, -9.81f);
    float groundFriction = 0.7f;
    int methodIndex = 0;
    float groundHeight = -1.f;
}

void Scene4::init(){
    //setup vars
    
points = {
    // Level 0: Bottom cube base (z = 0)
    {{0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, 1.f}, // 0
    {{1.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, 1.f}, // 1
    {{1.f, 1.f, 0.f}, {0.f, 0.f, 0.f}, 1.f}, // 2
    {{0.f, 1.f, 0.f}, {0.f, 0.f, 0.f}, 1.f}, // 3

    // Level 1: Between cube 1 and 2 (z = 1)
    {{0.f, 0.f, 1.f}, {0.f, 0.f, 0.f}, 1.f}, // 4
    {{1.f, 0.f, 1.f}, {0.f, 0.f, 0.f}, 1.f}, // 5
    {{1.f, 1.f, 1.f}, {0.f, 0.f, 0.f}, 1.f}, // 6
    {{0.f, 1.f, 1.f}, {0.f, 0.f, 0.f}, 1.f}, // 7

    // Level 2: Between cube 2 and 3 (z = 2)
    {{0.f, 0.f, 2.f}, {0.f, 0.f, 0.f}, 1.f}, // 8
    {{1.f, 0.f, 2.f}, {0.f, 0.f, 0.f}, 1.f}, // 9
    {{1.f, 1.f, 2.f}, {0.f, 0.f, 0.f}, 1.f}, // 10
    {{0.f, 1.f, 2.f}, {0.f, 0.f, 0.f}, 1.f}, // 11

    // Level 3: Top of cube 3 (z = 3)
    {{0.f, 0.f, 3.f}, {0.f, 0.f, 0.f}, 1.f}, // 12
    {{1.f, 0.f, 3.f}, {0.f, 0.f, 0.f}, 1.f}, // 13
    {{1.f, 1.f, 3.f}, {0.f, 0.f, 0.f}, 1.f}, // 14
    {{0.f, 1.f, 3.f}, {0.f, 0.f, 0.f}, 1.f}  // 15
};

springs = {
    {400.f, 1.f, 0, 1},
    {400.f, 1.f, 1, 2},
    {400.f, 1.f, 2, 3},
    {400.f, 1.f, 3, 0},

    {400.f, 1.f, 4, 5},
    {400.f, 1.f, 5, 6},
    {400.f, 1.f, 6, 7},
    {400.f, 1.f, 7, 4},

    {400.f, 1.f, 8, 9},
    {400.f, 1.f, 9, 10},
    {400.f, 1.f, 10, 11},
    {400.f, 1.f, 11, 8},

    {400.f, 1.f, 12, 13},
    {400.f, 1.f, 13, 14},
    {400.f, 1.f, 14, 15},
    {400.f, 1.f, 15, 12},

    {400.f, 1.f, 0, 4},
    {400.f, 1.f, 1, 5},
    {400.f, 1.f, 2, 6},
    {400.f, 1.f, 3, 7},

    {400.f, 1.f, 4, 8},
    {400.f, 1.f, 5, 9},
    {400.f, 1.f, 6, 10},
    {400.f, 1.f, 7, 11},

    {400.f, 1.f, 8, 12},
    {400.f, 1.f, 9, 13},
    {400.f, 1.f, 10, 14},
    {400.f, 1.f, 11, 15},

    {400.f, 1.41421356f, 0, 2},
    {400.f, 1.41421356f, 1, 3},
    {400.f, 1.41421356f, 4, 6},
    {400.f, 1.41421356f, 5, 7},
    {400.f, 1.41421356f, 8, 10},
    {400.f, 1.41421356f, 9, 11},
    {400.f, 1.41421356f, 12, 14},
    {400.f, 1.41421356f, 13, 15},

    {400.f, 1.73205081f, 0, 6},
    {400.f, 1.73205081f, 1, 7},
    {400.f, 1.73205081f, 2, 4},
    {400.f, 1.73205081f, 3, 5},

    {400.f, 1.73205081f, 4, 10},
    {400.f, 1.73205081f, 5, 11},
    {400.f, 1.73205081f, 6, 8},
    {400.f, 1.73205081f, 7, 9},

    {400.f, 1.73205081f, 8, 14},
    {400.f, 1.73205081f, 9, 15},
    {400.f, 1.73205081f, 10, 12},
    {400.f, 1.73205081f, 11, 13}
};

}

void Scene4::eulerStep(float dt){
    auto accels = calcAccel(points);
    for(size_t i = 0; i < points.size(); i++){
        points[i].position += dt*points[i].velocity;
        points[i].velocity += dt*accels[i];
    }
}

void Scene4::midPointStep(float dt){
    auto initAccels = calcAccel(points);
    auto halfPoints = points;

    //halfPoints
    for(size_t i = 0; i < halfPoints.size(); i++){
        halfPoints[i].position += (dt/2) * points[i].velocity;
        halfPoints[i].velocity += (dt/2) * initAccels[i];
    }
    auto halfAcc = calcAccel(halfPoints);

    for(size_t i = 0; i < points.size(); i++){
        points[i].position += dt*halfPoints[i].velocity;
        points[i].velocity += dt*halfAcc[i];
    }
}

std::vector<glm::vec3> Scene4::calcAccel(std::vector<MassPoint> &state) const
{
    std::vector<glm::vec3> accels(state.size(), gravityAccel);
    for(auto& spring : springs){
        auto i = spring.p0; auto j = spring.p1; //poits of the spring
        const glm::vec3 d = state[i].position - state[j].position; //dir
        const float len = glm::length(d);

        //no 0 length spring
        if(len < 1e-6f)
            continue;

        const glm::vec3 f = hooke(len, spring.k, spring.L, d);
        accels[i] += (f / state[i].mass);
        accels[j] -= (f / state[j].mass);
    }
    return accels;
}

void Scene4::calcGroundCol(){
    for(auto& point : points){ //col
        if(point.position.z < groundHeight + 0.1f){
            point.position.z = groundHeight + 0.1f;
            if(point.velocity.z < 0.f){ //bounce
                point.velocity.z *= -0.3f;

                //friction
                point.velocity.x *= (1.f - groundFriction);
                point.velocity.y *= (1.f - groundFriction);
            }
        }
    }
}

void Scene4::onDraw(Renderer &renderer){
    for(auto& point : points){
        renderer.drawSphere(point.position, 0.1f);
    }

    for(auto& spring : springs){
        renderer.drawLine(points[spring.p0].position, points[spring.p1].position, glm::vec3(1));
    }
    //ground
    for (int i = -5; i <= 5; i++) {
        float x = static_cast<float>(i);

        renderer.drawLine(
            glm::vec3(x, -5.f, groundHeight),
            glm::vec3(x, 5.f, groundHeight),
            glm::vec3(0.4f)
        );

        renderer.drawLine(
            glm::vec3(-5.f, x, groundHeight),
            glm::vec3(5.f, x, groundHeight),
            glm::vec3(0.4f)
        );
    }
}

void Scene4::simulateStep(){
    if(methodIndex == 0) midPointStep(dt);
    else eulerStep(dt);
    calcGroundCol();
}

void Scene4::onGUI(){
    ImGui::SliderFloat("Delta t", &dt, 0.0001f, 0.02f);
    ImGui::SliderFloat("Ground Friction", &groundFriction, 0.f, 1.f);
    ImGui::SliderFloat("Ground Height", &groundHeight, -10.f, 10.f);

    ImGui::RadioButton("Midpoint", &methodIndex, 0);
    ImGui::SameLine();
    ImGui::RadioButton("Euler", &methodIndex, 1);
}