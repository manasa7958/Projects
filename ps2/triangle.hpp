// triangle.hpp
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <SFML/Graphics.hpp>

class Triangle : public sf::Drawable {
public:
    Triangle(double length, int depth);
    void generate();

private:
    double length;
    int depth;
    std::vector<sf::VertexArray> triangles;
    void fractal(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, int level);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // TRIANGLE_HPP
