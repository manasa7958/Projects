// Universe.cpp - Fixed Version
#include "Universe.hpp"
#include <iostream>
#include <cmath>

namespace NB {

Universe::Universe() : universeSize_(0.0), bgTexture_(std::make_shared<sf::Texture>()),
bgSprite_(std::make_shared<sf::Sprite>()) {}

bool Universe::initBackground(const std::string& filename) {
    if (bgTexture_->loadFromFile(filename)) {
        bgSprite_->setTexture(*bgTexture_);
        return true;
    } else {
        std::cerr << "Could not load background image: " << filename << std::endl;
        return false;
    }
}

size_t Universe::size() const {
    return celestialObjects_.size();
}

double Universe::radius() const {
    return universeSize_;
}

const CelestialBody& Universe::operator[](size_t i) const {
    return celestialObjects_[i];
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    if (bgSprite_) {
        window.draw(*bgSprite_, states);
    }
    for (const auto& obj : celestialObjects_) {
        window.draw(obj, states);
    }
}

void Universe::step(double dt) {
    const double G_CONST = 6.67e-11;
    size_t count = celestialObjects_.size();
    if (count == 0) return;

    std::vector<double> forceX(count, 0.0);
    std::vector<double> forceY(count, 0.0);

    for (size_t i = 0; i < count; i++) {
        for (size_t j = i + 1; j < count; j++) {
            double dx = celestialObjects_[j].position().x - celestialObjects_[i].position().x;
            double dy = celestialObjects_[j].position().y - celestialObjects_[i].position().y;
            double dist = std::sqrt(dx * dx + dy * dy);
            if (dist < 1e-10) dist = 1e-10;
            double force = G_CONST * celestialObjects_[i].mass() * celestialObjects_[j].mass() / (dist * dist);
            double fx = force * dx / dist;
            double fy = force * dy / dist;
            forceX[i] += fx;
            forceY[i] += fy;
            forceX[j] -= fx;
            forceY[j] -= fy;
        }
    }

    for (size_t i = 0; i < count; i++) {
        double accelX = forceX[i] / celestialObjects_[i].mass();
        double accelY = forceY[i] / celestialObjects_[i].mass();
        double newVx = celestialObjects_[i].velocity().x + accelX * dt;
        double newVy = celestialObjects_[i].velocity().y + accelY * dt;
        double newX = celestialObjects_[i].position().x + newVx * dt;
        double newY = celestialObjects_[i].position().y + newVy * dt;
        celestialObjects_[i].setPosition(newX, newY);
        celestialObjects_[i].setVelocity(newVx, newVy);
    }
}

std::istream& operator>>(std::istream& is, Universe& universe) {
    int bodyCount;
    double size;
    is >> bodyCount >> size;
    universe.universeSize_ = size;
    universe.celestialObjects_.clear();

    for (int i = 0; i < bodyCount; ++i) {
        CelestialBody object;
        is >> object;
        universe.celestialObjects_.push_back(object);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Universe& universe) {
    os << universe.size() << " " << universe.radius() << "\n";
    for (const auto& obj : universe.celestialObjects_) {
        os << obj << "\n";
    }
    return os;
}
}  // namespace NB
