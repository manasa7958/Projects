// Copyright 2025 Ponita Ty
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
}  // namespace NB


/*
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

std::istream& operator>>(std::istream& is, Universe& universe) {
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

std::ostream& operator<<(std::ostream& os, const Universe& universe) {
    os << universe.bodies.size() << " " << universe.universeRadius << "\n";
    for (const auto& body : universe.bodies) {
        os << *body << "\n";
    }
    return os;
}

void Universe::step(double seconds) {
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

        double new_vx = vx + ax * seconds;
        double new_vy = vy + ay * seconds;

        double px = bodies[i]->position().x;
        double py = bodies[i]->position().y;

        double new_px = px + new_vx * seconds;
        double new_py = py + new_vy * seconds;

        bodies[i]->setPosition(new_px, new_py);
        bodies[i]->setVelocity(new_vx, new_vy);
    }
}

}  // namespace NB*/
