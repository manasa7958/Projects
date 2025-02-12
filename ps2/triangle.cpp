// triangle.cpp
#include "triangle.hpp"
#include <cmath>

Triangle::Triangle(double length, int depth) : length(length), depth(depth) {
    generate();
}

void Triangle::generate() {
    sf::Vector2f p1(400, 100);
    sf::Vector2f p2(400 - length / 2, 100 + length * sqrt(3) / 2);
    sf::Vector2f p3(400 + length / 2, 100 + length * sqrt(3) / 2);
    fractal(p1, p2, p3, depth);
}

void Triangle::fractal(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, int level) {
    if (level == 0) {
        sf::VertexArray triangle(sf::Triangles, 3);
        triangle[0].position = p1;
        triangle[1].position = p2;
        triangle[2].position = p3;
        triangles.push_back(triangle);
        return;
    }
    
    sf::Vector2f mid1((p1 + p2) / 2.0f);
    sf::Vector2f mid2((p2 + p3) / 2.0f);
    sf::Vector2f mid3((p3 + p1) / 2.0f);
    
    fractal(p1, mid1, mid3, level - 1);
    fractal(mid1, p2, mid2, level - 1);
    fractal(mid3, mid2, p3, level - 1);
}

void Triangle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& triangle : triangles) {
        target.draw(triangle, states);
    }
}
