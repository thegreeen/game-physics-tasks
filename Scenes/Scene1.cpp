#include "Scene1.h"
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
}

void Scene1::init(){
    //setup vars
    points = {
        {{0.f, 0.f, 0.f}, {-1.f, 0.f, 0.f}, 10.f},
        {{0.f, 2.f, 0.f}, {1.f, 0.f, 0.f}, 10.f}
    };
    springs = {{40.f, 1.f, 0, 1}};

    //print default
    std::cout << "Initial Values:" << std::endl;
    std::cout << std::endl;

    std::cout << "Masspoint 0" << std::endl;
    printPoint(points[0]);
    std::cout << "Masspoint 1" << std::endl;
    printPoint(points[1]);
    std::cout << std::endl;

    auto backupPoints = points;


    const float dt = 0.1f;
    eulerStep(dt);

    //print euler
    std::cout << "After 0.1s using Euler Method:" << std::endl;
    std::cout << "Masspoint 0" << std::endl;
    printPoint(points[0]);
    std::cout << "Masspoint 1" << std::endl;
    printPoint(points[1]);

    points = backupPoints;
    midPointStep(dt);

    //print midpoint
    std::cout << "After 0.1s using Midpoint Method:" << std::endl;
    std::cout << "Masspoint 0" << std::endl;
    printPoint(points[0]);
    std::cout << "Masspoint 1" << std::endl;
    printPoint(points[1]);

}

void Scene1::eulerStep(float dt){
    auto accels = calcAccel(points);
    for(size_t i = 0; i < points.size(); i++){
        points[i].position += dt*points[i].velocity;
        points[i].velocity += dt*accels[i];
    }
}

void Scene1::midPointStep(float dt){
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

std::vector<glm::vec3> Scene1::calcAccel(std::vector<MassPoint> &state) const
{
    std::vector<glm::vec3> accels(state.size(), glm::vec3(0.f));
    for(auto& spring : springs){
        auto i = spring.p0; auto j = spring.p1; //poits of the spring
        const glm::vec3 d = state[i].position - state[j].position; //dir
        const float len = glm::length(d);

        const glm::vec3 f = hooke(len, spring.k, spring.L, d);
        accels[i] += f / state[i].mass;
        accels[j] -= f / state[j].mass;
    }
    return accels;
}

void Scene1::onDraw(Renderer &renderer){
}

void Scene1::simulateStep(){
}

void Scene1::onGUI(){
}