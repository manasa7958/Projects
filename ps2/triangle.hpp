// Copyright 2025 Manasa Praveen and Ponita Ty
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include <vector>
#include <SFML/Graphics.hpp>

class Triangle : public sf::Drawable {
 public:
  // Constructor with position and size
  Triangle(float x, float y, float size, int depth);
  // Set the position of the triangle
  void setPosition(float x, float y);
  void setDepth(int depth);

 private:
  // Helper to create a single triangle
  sf::ConvexShape createTriangle(float x, float y, float size,
                                 sf::Color color) const;

  // Recursive function to generate fractal pattern
  void generateFractal(float x, float y, float size, int depth);

  // Override draw method from sf::Drawable
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

  // Member variables
  std::vector<sf::ConvexShape> m_triangles;
  float m_x, m_y;
  float m_size;
  int m_depth;
};
#endif  // TRIANGLE_HPP
