// Universe.cpp - Fixed version
#include "Universe.hpp"
#include <iostream>
#include <cmath>

namespace NB {

Universe::Universe() : universeRadius(0.0), backgroundTexture(std::make_shared<sf::Texture>()),
backgroundSprite(std::make_shared<sf::Sprite>()) {}

bool Universe::initBackground(const std::string& filename) {
    if (backgroundTexture->loadFromFile(filename)) {
        backgroundSprite->setTexture(*backgroundTexture);
        return true;
    } else {
        std::cerr << "Could not load background image: " << filename << std::endl;
        return false;
    }
}

size_t Universe::size() const {
    return bodies.size();
}

double Universe::radius() const {
    return universeRadius;
}

const CelestialBody& Universe::operator[](size_t i) const {
    return *bodies[i];
}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (backgroundSprite) {
        target.draw(*backgroundSprite, states);
    }

    for (const auto& body : bodies) {
        float screenX = (body->position().x / universeRadius) * 400 + 400;
        float screenY = (body->position().y / universeRadius) * 400 + 400;
        
        if (body->sprite) {
            body->sprite->setPosition(screenX, screenY);
            target.draw(*body->sprite, states);
        }
    }
}

std::istream& operator>>(std::istream& in, Universe& universe) {
    size_t n;
    double r;
    is >> n >> r;
    universe.universeRadius = r;
    universe.bodies.clear();

    for (size_t i = 0; i < n; ++i) {
        auto body = std::make_shared<CelestialBody>();
        is >> *body;
        universe.bodies.push_back(body);
    }
    return is;
}

std::ostream& operator<<(std::ostream& out, const Universe& universe) {
    os << universe.bodies.size() << " " << universe.universeRadius << "\n";
    for (const auto& body : universe.bodies) {
        os << *body << "\n";
    }
    return os;
}

void Universe::step(double dt) {
    const double G = 6.67e-11;
    size_t n = bodies.size();
    if (n == 0) return;

    std::vector<double> forceX(n, 0.0);
    std::vector<double> forceY(n, 0.0);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            double dx = bodies[j]->position().x - bodies[i]->position().x;
            double dy = bodies[j]->position().y - bodies[i]->position().y;
            double r = std::sqrt(dx * dx + dy * dy);

            if (r < 1e-10) r = 1e-10;

            double force = G * bodies[i]->mass() * bodies[j]->mass() / (r * r);

            double fx = force * dx / r;
            double fy = force * dy / r;

            forceX[i] += fx;
            forceY[i] += fy;
            forceX[j] -= fx;
            forceY[j] -= fy;
        }
    }

    for (size_t i = 0; i < n; i++) {
        double ax = forceX[i] / bodies[i]->mass();
        double ay = forceY[i] / bodies[i]->mass();

        double vx = bodies[i]->velocity().x;
        double vy = bodies[i]->velocity().y;

        const double MAX_ACCEL = 1.0e20;
        if (std::abs(ax) > MAX_ACCEL) ax = ax > 0 ? MAX_ACCEL : -MAX_ACCEL;
        if (std::abs(ay) > MAX_ACCEL) ay = ay > 0 ? MAX_ACCEL : -MAX_ACCEL;

        double new_vx = vx + ax * dt;
        double new_vy = vy + ay * dt;

        double px = bodies[i]->position().x;
        double py = bodies[i]->position().y;

        double new_px = px + new_vx * dt;
        double new_py = py + new_vy * dt;

        bodies[i]->setPosition(new_px, new_py);
        bodies[i]->setVelocity(new_vx, new_vy);
    }
}

}  // namespace NB
