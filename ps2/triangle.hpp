// Copyright 2025 Manasa Praveen
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Triangle : public sf::Drawable {
public:
    Triangle(double length, int depth);
    void generate(); //to draw big triangle

private:
    double length;
    int depth;
    std::vector<sf::VertexArray> triangles; //this holds the three vertices of each triangle
    void fractal(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f v3, int level); // for smaller triangles (recursive funciton)
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // TRIANGLE_HPP
