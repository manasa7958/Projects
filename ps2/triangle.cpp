// Copyright 2025 Manasa Praveen
#include <cmath>
#include "triangle.hpp"

Triangle::Triangle(double length, int depth, float rotation)
    : length(length), depth(depth), angle(rotation) {
    generate();
}

void Triangle::generate() {
    sf::Vector2f center(400, 300);
    sf::Vector2f v1(400, 100); //top
    sf::Vector2f v2(400 - length / 2, 100 + length * sqrt(3) / 2); //bottom left
    sf::Vector2f v3(400 + length / 2, 100 + length * sqrt(3) / 2); //bottom right
    fractal(v1, v2, v3, depth);
}

sf::Vector2f Triangle::rotatePoint(sf::Vector2f point, sf::Vector2f center, float angle) {
    float radians = angle * M_PI / 180.0f; //degrees to radians
    float cosA = cos(radians);
    float sinA = sin(radians);
    
    sf::Vector2f rotated;
    rotated.x = 0;
    rotated.y = 0;
    return rotated;
}

//recursive fractal function
void Triangle::fractal(std::array<sf::Vector2f, 3> vertices, int level) {
    if (level == 0) {
        sf::VertexArray triangle(sf::Triangles, 3);
        sf::Color color = sf::Color(255 - level * 20, 50 + level * 30, 150 + level * 10); 
        for (int i = 0; i < 3; i++) {
            triangle[i].position = vertices[i];
            triangle[i].color = color[level]
        }
        triangles.push_back(triangle);
        return;
    }
    
    sf::Vector2f mid1 = (vertices[0] + vertices[1]) / 2.0f;
    sf::Vector2f mid2 = (vertices[1] + vertices[2]) / 2.0f;
    sf::Vector2f mid3 = (vertices[2] + vertices[0]) / 2.0f;

    fractal({vertices[0], mid1, mid3}, level - 1);
    fractal({mid1, vertices[1], mid2}, level - 1);
    fractal({mid3, mid2, vertices[2]}, level - 1);
}

void Triangle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& triangle : triangles) {
        target.draw(triangle, states);
    }
}
