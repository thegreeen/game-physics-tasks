#include "Scene1.h"
#include <glm/gtx/quaternion.hpp>
#include <imgui.h>
#include "glm/gtx/string_cast.hpp"

void printPoint(const MassPoint &point){
    std::cout << "position: " << glm::to_string(point.position) << std::endl;
    std::cout << "velocity: " << glm::to_string(point.velocity) << std::endl;
}

void Scene1::init(){
    //setup vars
    points = {
        {{0.f, 0.f, 0.f}, {-1.f, 0.f, 0.f}, 10.f},
        {{0.f, 2.f, 0.f}, {1.f, 0.f, 0.f}, 10.f}
    };
    springs = {{40.f, 1.f, points[0], points[1]}};

    //print default
    std::cout << "Masspoint 0" << std::endl;
    printPoint(points[0]);
    std::cout << "Masspoint 1" << std::endl;
    printPoint(points[1]);


    float dt = 0.1f;
    glm::vec3 d = points[1].position - points[0].position;
    float len = glm::length(d);



}

glm::vec3 hooke(float len, float k, float L, const glm::vec3 &d){
    return (-1) * k * (len - L) * (d/len);
}

void Scene1::onDraw(Renderer &renderer){
    /*for(auto& point : points){
        renderer.drawSphere(point.position, 0.1f);
    }

    for(auto& spring : springs){
        renderer.drawLine(spring.p0.position, spring.p1.position, glm::vec3(1));
    }*/
}

void Scene1::simulateStep(){
   
}

void Scene1::onGUI(){
    
}