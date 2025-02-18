// Copyright 2025 Manasa Praveen
/*#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Triangle : public sf::Drawable {
public:
    Triangle(double length, int depth);
    void generate();

private:
    double length;
    int depth;
    float angle;
    std::vector<sf::VertexArray> triangles;
    void fractal(std::array<sf::Vector2f, 3> vertices, int level);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif*/ // TRIANGLE_HPP

/*// triangle.hpp
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include <vector>
#include <SFML/Graphics.hpp>

class Triangle : public sf::Drawable {
public:
    Triangle(float x, float y, float size, int depth);
    void generateFractal(float x, float y, float size, int depth);

private:
    std::vector<sf::ConvexShape> triangles;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // TRIANGLE_HPP*/

//triangle.hpp
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Triangle : public sf::Drawable {
public:
    Triangle(float x, float y, float size, int depth);
    void setPosition(float x, float y);
    void generateLevel2();

private:
    float m_x, m_y;
    float m_size;
    int depth;
    std::vector<sf::ConvexShape> m_triangles;
    sf::ConvexShape createTriangle(float x, float y, float size) const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#endif // TRIANGLE_HPP
