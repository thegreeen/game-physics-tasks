#include "Scene1.h"
#include <glm/gtx/quaternion.hpp>
#include <imgui.h>

void Scene1::onDraw(Renderer &renderer){
    //Colormap
    auto cmap = Colormap("viridis");

    renderer.drawWireCube(glm::vec3(0), glm::vec3(5), glm::vec3(1));
    renderer.drawCube(
        glm::vec3(0, 0,0), //center pos
        glm::quat(glm::vec3(pitch, roll, yaw)), //rotation
        glm::vec3(0.5,0.5,0.5), //scale
        glm::vec4(1,0,0,1)); //color

    glm::mat4 rotation = glm::toMat4(glm::quat(glm::vec3(pitch, roll, yaw)));
    glm::vec3 forward = glm::vec3(rotation * glm::vec4(0, 0, 1, 0));
    glm::vec3 right = glm::vec3(rotation * glm::vec4(1, 0, 0, 0));
    glm::vec3 up = glm::vec3(rotation * glm::vec4(0, 1, 0, 0));

    renderer.drawLine(glm::vec3(0), forward, glm::vec4(1, 0, 0, 1));
    renderer.drawLine(glm::vec3(0), right, glm::vec4(0, 1, 0, 1));
    renderer.drawLine(glm::vec3(0), up, glm::vec4(0, 0, 1, 1));

    //draw particles
    for(auto& particle : particles){
        renderer.drawSphere(particle.position, 0.1f, glm::vec4(cmap(particle.lifeTime / particleLifetime), 1));
    }
}

void Scene1::simulateStep(){
    lastLaunch++;

    //gravity
    glm::vec3 gravityAccel = glm::vec3(0,0, -9.81f);

    float realtimeDT = ImGui::GetIO().DeltaTime;


    //pitch += pitch_inc;
    //roll += roll_inc;
    //yaw += yaw_inc;

    for(auto& particle : particles){
        particle.position += realtimeDT * particle.velocity;
        particle.lifeTime += realtimeDT;
        particle.velocity += gravityAccel * realtimeDT;
    }

    particles.erase(std::remove_if(particles.begin(), particles.end(), [this](const Particle& particle){
        return particle.lifeTime > particleLifetime;
    }), particles.end());

    if(ImGui::IsKeyDown(ImGuiKey_Space))
        launchSphere();
    if(ImGui::IsKeyDown(ImGuiKey_W))
        pitch += pitch_inc;
    if(ImGui::IsKeyDown(ImGuiKey_S))
        pitch -= pitch_inc;
    if(ImGui::IsKeyDown(ImGuiKey_A))
        roll += roll_inc;
    if(ImGui::IsKeyDown(ImGuiKey_D))
        roll -= roll_inc;
    if(ImGui::IsKeyDown(ImGuiKey_Q))
        yaw += yaw_inc;
    if(ImGui::IsKeyDown(ImGuiKey_E))
        yaw -= yaw_inc;

    //drag
    if(ImGui::IsMouseReleased(ImGuiMouseButton_Right)){   
        auto drag = ImGui::GetMouseDragDelta(1);
        if(!(drag.x == 0 && drag.y == 0)){
            auto dx = drag.x * right;
            auto dy = -drag.y * up;
            for (auto& particle : particles){
                particle.velocity += (dx + dy) * 0.01f;
            }
        }
    }
}

void Scene1::onGUI(){
    ImGui::SliderFloat("Pitch inc", &pitch_inc, -0.01f, 0.01f);
    ImGui::SliderFloat("Roll inc", &roll_inc, -0.01f, 0.01f);
    ImGui::SliderFloat("Yaw inc", &yaw_inc, -0.01f, 0.01f);
    ImGui::SliderInt("Launch Delay", &launch_delay, 0, 100);
    ImGui::SliderFloat("ParticleLifetime", &particleLifetime, 0.1f, 20.f);

    auto launch = ImGui::Button("Launch");

    if(launch){
        launchSphere();
    }
}

void Scene1::launchSphere(){
    if( lastLaunch < launch_delay)
        return;
    lastLaunch = 0;
    glm::mat4 rotation = glm::toMat4(glm::quat(glm::vec3(pitch, roll, yaw)));
    glm::vec3 forward = glm::vec3(rotation * glm::vec4(0, 0, 1, 0));
    glm::vec3 right = glm::vec3(rotation * glm::vec4(1, 0, 0, 0));
    glm::vec3 up = glm::vec3(rotation * glm::vec4(0, 1, 0, 0));

    glm::vec4 color = glm::vec4(dis(gen), dis(gen), dis(gen), 1);
    float velocityMagnitude = 4.5f + dis(gen);
    glm::vec3 velocity = forward * velocityMagnitude;

    velocity += right * (dis(gen) - 0.5f) * 2.f;
    velocity += up * (dis(gen) - 0.5f) * 2.f;

    particles.push_back(Particle{glm::vec3(0), velocity, color, .0});
}