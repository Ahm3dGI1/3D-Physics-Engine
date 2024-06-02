#include "physicsObjects/cloth.h"

Cloth::Cloth(int w, int h, float s, float f, float m, Vec3 pos) {
    width = w;
    height = h;
    spacing = s;
    flexibility = f;
    mass = m;
    position = pos;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            particles.push_back(PhysicsObject(std::make_unique<Sphere>(1.0, 3), Vec3(position.x + (j * spacing), position.y - (i * spacing), position.z), mass / (width * height), 0.7f));
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j < width - 1) {
                springs.push_back(Spring(&particles[i * width + j], &particles[i * width + j + 1], spacing, flexibility));
            }
            if (i < height - 1) {
                springs.push_back(Spring(&particles[i * width + j], &particles[(i + 1) * width + j], spacing, flexibility));
            }
        }
    }

    particles[0].rigidBody.SetFixed(true);
    particles[width - 1].rigidBody.SetFixed(true);

}

void Cloth::Update(float deltaTime) {
    for (int i = 0; i < springs.size(); i++) {
        springs[i].ApplySpringForce();
    }

    for (int i = 0; i < particles.size(); i++) {
        particles[i].Update(deltaTime);
    }
}