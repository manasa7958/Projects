// Copyright 2025 Manasa Praveen
/*#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Triangle : public sf::Drawable {
public:
    Triangle(double length, int depth, float rotation = 0.0f);
    void generate();

private:
    double length;
    int depth;
    float angle;
    std::vector<sf::VertexArray> triangles;
    void fractal(std::array<sf::Vector2f, 3> vertices, int level);
    sf::Vector2f rotatePoint(sf::Vector2f point, sf::Vector2f center, float angle);
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
    // Constructor with position and size
    Triangle(float x, float y, float size);
    
    // Set the position of the triangle
    void setPosition(float x, float y);
    
    // Generate level 2 triangles
    void generateLevel2();

private:
    // Helper to create a single triangle
    sf::ConvexShape createTriangle(float x, float y, float size) const;
    
    // Override draw method from sf::Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    // Member variables
    std::vector<sf::ConvexShape> m_triangles;
    float m_x, m_y;
    float m_size;
};

#endif // TRIANGLE_HPP
