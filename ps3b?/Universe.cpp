// Universe.cpp - Customized Version
#include "Universe.hpp"
#include <iostream>
#include <cmath>

namespace NB {

Universe::Universe() : universeSize_(0.0), bgTexture_(std::make_shared<sf::Texture>()),
bgSprite_(std::make_shared<sf::Sprite>()) {}

size_t Universe::size() const {
    return celestialObjects_.size();
}

double Universe::radius() const {
    return universeSize_;
}

const CelestialBody& Universe::operator[](size_t i) const {
    return celestialObjects_[i];
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

/*// Copyright 2025 Ponita Ty
#include "Universe.hpp"
#include <iostream>
#include <cmath>

namespace NB {

Universe::Universe() : radius_(0.0), backgroundTexture_(std::make_shared<sf::Texture>()),
backgroundSprite_(std::make_shared<sf::Sprite>()) {
}

bool Universe::initBackground(const std::string& filename) {
    try {
        if (backgroundTexture_->loadFromFile(filename)) {
            backgroundSprite_->setTexture(*backgroundTexture_);
            return true;
        } else {
            std::cerr << "Could not load background image: " << filename << std::endl;
            sf::Image img;
            img.create(100, 100, sf::Color(0, 0, 20));
            backgroundTexture_->loadFromImage(img);
            backgroundSprite_->setTexture(*backgroundTexture_);
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception loading background: " << e.what() << std::endl;
        return false;
    }
}

size_t Universe::size() const {
    return bodies_.size();
}

double Universe::radius() const {
    return radius_;
}

const CelestialBody& Universe::operator[](size_t i) const {
    return bodies_[i];
}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2u windowSize = target.getSize();

    if (backgroundSprite_ && backgroundTexture_ && backgroundTexture_->getSize().x > 0) {
        float scaleX = static_cast<float>(windowSize.x) / backgroundTexture_->getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / backgroundTexture_->getSize().y;
        backgroundSprite_->setScale(scaleX, scaleY);
        target.draw(*backgroundSprite_, states);
    }

    if (radius_ <= 0.0) return;

    float scale = std::min(windowSize.x, windowSize.y) / (2.0f * static_cast<float>(radius_));
    scale *= 0.5f;

    for (const auto& body : bodies_) {
        float screenX = (body.position().x * scale) + (windowSize.x / 2.0f);
        float screenY = (windowSize.y / 2.0f) - (body.position().y * scale);

        sf::Sprite* sprite = const_cast<sf::Sprite*>(body.sprite_.get());
        if (sprite && sprite->getTexture()) {
            sprite->setPosition(screenX, screenY);
            sprite->setScale(0.5f, 0.5f);
            target.draw(body, states);
        }
    }
}

std::istream& operator>>(std::istream& is, Universe& uni) {
    int n;
    double r;

    if (!(is >> n >> r)) {
        throw std::runtime_error("Invalid universe format");
    }

    if (n < 0) {
        throw std::runtime_error("Negative number of bodies");
    }

    uni.bodies_.clear();
    uni.radius_ = r;

    for (int i = 0; i < n; ++i) {
        CelestialBody body;
        if (is >> body) {
            uni.bodies_.push_back(body);
        } else {
            throw std::runtime_error("Failed to read body " + std::to_string(i));
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Universe& uni) {
    os << uni.size() << " " << uni.radius() << "\n";
    for (size_t i = 0; i < uni.size(); ++i) {
        os << uni[i] << "\n";
    }
    return os;
}

void Universe::step(double seconds) {
    const double G = 6.67e-11;

    size_t n = bodies_.size();
    if (n == 0) return;

    std::vector<double> forceX(n, 0.0);
    std::vector<double> forceY(n, 0.0);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            double dx = bodies_[j].position().x - bodies_[i].position().x;
            double dy = bodies_[j].position().y - bodies_[i].position().y;

            double r = std::sqrt(dx * dx + dy * dy);

            if (r < 1e-10) {
                r = 1e-10;
            }

            double force = G * bodies_[i].mass() * bodies_[j].mass() / (r * r);

            const double MAX_FORCE = 1.0e30;
            if (force > MAX_FORCE) force = MAX_FORCE;

            double fx = force * dx / r;
            double fy = force * dy / r;

            forceX[i] += fx;
            forceY[i] += fy;
            forceX[j] -= fx;
            forceY[j] -= fy;
        }
    }

    for (size_t i = 0; i < n; i++) {
        double ax = forceX[i] / bodies_[i].mass();
        double ay = forceY[i] / bodies_[i].mass();

        const double MAX_ACCEL = 1.0e20;
        if (std::abs(ax) > MAX_ACCEL) ax = ax > 0 ? MAX_ACCEL : -MAX_ACCEL;
        if (std::abs(ay) > MAX_ACCEL) ay = ay > 0 ? MAX_ACCEL : -MAX_ACCEL;

        double vx = bodies_[i].velocity().x;
        double vy = bodies_[i].velocity().y;

        // v = v0 + a*t
        double new_vx = vx + ax * seconds;
        double new_vy = vy + ay * seconds;

        double px = bodies_[i].position().x;
        double py = bodies_[i].position().y;

        // p = p0 + v*t
        double new_px = px + new_vx * seconds;
        double new_py = py + new_vy * seconds;

        bodies_[i].setPosition(new_px, new_py);
        bodies_[i].setVelocity(new_vx, new_vy);
    }
}
}  // namespace NB*/
