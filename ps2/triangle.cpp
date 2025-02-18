// Copyright 2025 Manasa Praveen
#include <cmath>
#include "triangle.hpp"

Triangle::Triangle(float x, float y, float size) : m_x(x), m_y(y), m_size(size, depth(depth) {
    // Create main triangle
    m_triangles.push_back(createTriangle(x, y, size));
    generateFractal(x, y, size, depth); // Increased depth to 3 to generate 1/8th sized triangles
}

void Triangle::setPosition(float x, float y) {
    m_x = x;
    m_y = y;
    // Clear and recreate triangles at new position
    m_triangles.clear();
    m_triangles.push_back(createTriangle(x, y, m_size));
    generateFractal(x, y, m_size, depth);
}

void Triangle::generateFractal(float x, float y, float size, int depth) {
    if (depth <= 0) return;
    float height = size * std::sqrt(3.0f) / 2.0f;
    float childSize = size / 2.0f;
    float childHeight = childSize * std::sqrt(3.0f) / 2.0f;
    // Calculate vertices of current triangle
    float bottomX = x;
    float bottomY = y;
    float topLeftX = x - size/2;
    float topLeftY = y - height;
    float topRightX = x + size/2;
    float topRightY = y - height;
    
    // Add three child triangles at the vertices
    
    // Top-left child
    m_triangles.push_back(createTriangle(topLeftX, topLeftY, childSize));
    generateFractal(topLeftX, topLeftY, childSize, depth - 1);
    
    // Top-right child (shifted right by half its width)
    m_triangles.push_back(createTriangle(topRightX + childSize/2, topRightY + childHeight, childSize));
    generateFractal(topRightX + childSize/2, topRightY + childHeight, childSize, depth - 1);
    
    // Bottom child
    m_triangles.push_back(createTriangle(bottomX - childSize/2, bottomY + childHeight, childSize));
    generateFractal(bottomX - childSize/2, bottomY + childHeight, childSize, depth - 1);
}

sf::ConvexShape Triangle::createTriangle(float x, float y, float size) const {
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    
    float height = size * std::sqrt(3.0f) / 2.0f;
    
    triangle.setPoint(0, sf::Vector2f(x, y)); // Bottom point
    triangle.setPoint(1, sf::Vector2f(x - size/2, y - height)); // Top left
    triangle.setPoint(2, sf::Vector2f(x + size/2, y - height)); // Top right
    
    triangle.setFillColor(sf::Color::White);
    triangle.setOutlineColor(sf::Color::Black);
    triangle.setOutlineThickness(2.0f);
    
    return triangle;
}

void Triangle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& triangle : m_triangles) {
        target.draw(triangle, states);
    }
}
