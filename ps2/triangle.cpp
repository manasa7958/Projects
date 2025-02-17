// Copyright 2025 Manasa Praveen
#include <cmath>
#include "triangle.hpp"

Triangle::Triangle(double length, int depth, float rotation)
    : length(length), depth(depth), angle(rotation) {
    generate();
}

void Triangle::generate() {
    sf::Vector2f center(400.0f, 300.0f);
    sf::Vector2f v1 = rotatePoint(sf::Vector2f(400.0f, 100.0f), center, angle);
    sf::Vector2f v2 = rotatePoint(sf::Vector2f(400.0f - static_cast<float>(length) / 2.0f, 
                                               100.0f + static_cast<float>(length) * static_cast<float>(sqrt(3)) / 2.0f), 
                                  center, angle);
    sf::Vector2f v3 = rotatePoint(sf::Vector2f(400.0f + static_cast<float>(length) / 2.0f, 
                                               100.0f + static_cast<float>(length) * static_cast<float>(sqrt(3)) / 2.0f), 
                                  center, angle);
    fractal(std::array<sf::Vector2f, 3>{v1, v2, v3}, depth);
}


sf::Vector2f Triangle::rotatePoint(sf::Vector2f point, sf::Vector2f center, float angle) {
    float radians = angle * M_PI / 180.0f;
    float cosA = cos(radians); //degrees to radians
    float sinA = sin(radians);
    
    sf::Vector2f rotated;
    rotated.x = cosA * (point.x - center.x) - sinA * (point.y - center.y) + center.x;
    rotated.y = sinA * (point.x - center.x) + cosA * (point.y - center.y) + center.y;
    return rotated;
}

//recursive fractal function
void Triangle::fractal(std::array<sf::Vector2f, 3> vertices, int level) {
    sf::Color color = sf::Color(50 + level * 20, 100 + level * 15, 255 - level * 10); 
    if (level == 0) {
        sf::VertexArray triangle(sf::Triangles, 3);
        for (int i = 0; i < 3; i++) {
            triangle[i].position = vertices[i];
            triangle[i].color = color;
        }
        triangles.push_back(triangle);
        return;
    }
    
    sf::Vector2f mid1 = (vertices[0] + vertices[1]) / 2.0f;
    sf::Vector2f mid2 = (vertices[1] + vertices[2]) / 2.0f;
    sf::Vector2f mid3 = (vertices[2] + vertices[0]) / 2.0f;
    fractal(std::array<sf::Vector2f, 3>{vertices[0], mid1, mid3}, level - 1);
    fractal(std::array<sf::Vector2f, 3>{mid1, vertices[1], mid2}, level - 1);
    fractal(std::array<sf::Vector2f, 3>{mid3, mid2, vertices[2]}, level - 1);
}

void Triangle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& triangle : triangles) {
        target.draw(triangle, states);
    }
}
