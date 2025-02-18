// Copyright 2025 Manasa Praveen
/*#include <cmath>
#include "triangle.hpp"

Triangle::Triangle(double length, int depth, float rotation)
    : length(length), depth(depth), angle(rotation) {
    generate();
}

void Triangle::generate() {
    sf::Vector2f center(400.0f, 300.0f);

    // Rotate only ONCE and store it
    static sf::Vector2f v1 = rotatePoint(sf::Vector2f(400.0f, 100.0f), center, angle);
    static sf::Vector2f v2 = rotatePoint(sf::Vector2f(400.0f - static_cast<float>(length) / 2.0f, 
                                               100.0f + static_cast<float>(length) * static_cast<float>(sqrt(3)) / 2.0f), 
                                  center, angle);
    static sf::Vector2f v3 = rotatePoint(sf::Vector2f(400.0f + static_cast<float>(length) / 2.0f, 
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
    if (level == 0) {
        sf::VertexArray triangle(sf::Triangles, 3);
        sf::Color color = sf::Color(50 + level * 20, 100 + level * 15, 255 - level * 10); 

        for (int i = 0; i < 3; i++) {
            triangle[i].position = vertices[i];
            triangle[i].color = color;
        }
        triangles.push_back(triangle);
        return;
    }

    // Compute midpoints
    sf::Vector2f mid1 = (vertices[0] + vertices[1]) / 2.0f;
    sf::Vector2f mid2 = (vertices[1] + vertices[2]) / 2.0f;
    sf::Vector2f mid3 = (vertices[2] + vertices[0]) / 2.0f;

    // Compute new smaller triangles at the three corners
    std::array<sf::Vector2f, 3> tri1 = {vertices[0], mid1, mid3};  // Top triangle
    std::array<sf::Vector2f, 3> tri2 = {mid1, vertices[1], mid2};  // Bottom left
    std::array<sf::Vector2f, 3> tri3 = {mid3, mid2, vertices[2]};  // Bottom right

    fractal(tri1, level - 1);
    fractal(tri2, level - 1);
    fractal(tri3, level - 1);
}

void Triangle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& triangle : triangles) {
        target.draw(triangle, states);
    }
}*/

// triangle.cpp
#include "triangle.hpp"
#include <cmath>

Triangle::Triangle(float x, float y, float size, int depth) {
    generateFractal(x, y, size, depth);
}

void Triangle::generateFractal(float x, float y, float size, int depth) {
    if (depth == 0) {
        sf::ConvexShape triangle(3);
        triangle.setPoint(0, sf::Vector2f(x, y));
        triangle.setPoint(1, sf::Vector2f(x + size / 2, y - size * sqrt(3) / 2));
        triangle.setPoint(2, sf::Vector2f(x + size, y));
        triangle.setFillColor(sf::Color::White);
        triangles.push_back(triangle);
    } else {
        float newSize = size / 2;
        float height = newSize * sqrt(3) / 2;  // Correct height calculation

        // Corrected positions to ensure triangles form at the vertices
        generateFractal(x - newSize / 2, y + height / 2, newSize, depth - 1); // Bottom-left vertex
        generateFractal(x + newSize / 2, y + height / 2, newSize, depth - 1); // Bottom-right vertex
        generateFractal(x, y - height, newSize, depth - 1);                   // Top vertex
    }
}

void Triangle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& triangle : triangles) {
        target.draw(triangle, states);
    }
}

