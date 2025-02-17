// Copyright 2025 Manasa Praveen
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Triangle : public sf::Drawable {
public:
    Triangle(double length, int depth, float rotation = 0.0f);
    void generate(); //to draw big triangle

private:
    double length;
    int depth;
    float angle;
    std::vector<sf::VertexArray> triangles; //this holds the three vertices of each triangle
    void fractal(std::array<sf::Vector2f, 3> vertices, int level); // for smaller triangles (recursive funciton)
    sf::Vector2f rotatePoint(sf::Vector2f point, sf::Vector2f center, float angle);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // TRIANGLE_HPP
