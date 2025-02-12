// Copyright 2025 Manasa Praveen
#include "triangle.hpp"
#include <cmath>

//Constructor intialization
Triangle::Triangle(double length, int depth) : length(length), depth(depth) {
    generate();
}

//generate function defintion for the main triangle
void Triangle::generate() {
    sf::Vector2f v1(400, 100); //top
    sf::Vector2f v2(400 - length / 2, 100 + length * sqrt(3) / 2); //bottom left
    sf::Vector2f v3(400 + length / 2, 100 + length * sqrt(3) / 2); //bottom right
    fractal(v1, v2, v3, depth);
}

//recursive function
void Triangle::fractal(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f v3, int level) {
    if (level == 0) {
        sf::VertexArray triangle(sf::Triangles, 3);
        triangle[0].position = v1;
        triangle[1].position = v2;
        triangle[2].position = v3;
        triangles.push_back(triangle);
        return;
    }
    
    sf::Vector2f mid1((v1 + v2) / 2.0f);
    sf::Vector2f mid2((v2 + v3) / 2.0f);
    sf::Vector2f mid3((v3 + v1) / 2.0f);
    
    fractal(v1, mid1, mid3, level - 1);
    fractal(mid1, v2, mid2, level - 1);
    fractal(mid3, mid2, v3, level - 1);
}

//draw the triangles
void Triangle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& triangle : triangles) {
        target.draw(triangle, states);
    }
}
