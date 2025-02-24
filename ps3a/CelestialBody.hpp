#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

namespace NB {
class CelestialBody: public sf::Drawable {
public:
    explicit CelestialBody(); 

    sf::Vector2f position() const { return pos; }
    sf::Vector2f velocity() const { return vel; }
    float mass() const { return m; }

protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
private:
    sf::Vector2f pos;  // Position variable
    sf::Vector2f vel;  // Velocity variable
    float m;  // Mass variable
    std::string imageFile;  // Store the image filename
    sf::Texture texture;
    bool loadImage = true;

    friend std::istream& operator>>(std::istream& in, CelestialBody& body);
    friend std::ostream& operator<<(std::ostream& out, const CelestialBody& body);
    friend class TestAccess;
};

class TestAccess {
public:
    static void disableImageLoading(CelestialBody& body) {
        body.loadImage = false;  // ✅ Allow tests to disable image loading
    }
};

std::istream& operator>>(std::istream& in, CelestialBody& body);
std::ostream& operator<<(std::ostream& out, const CelestialBody& body);
}  // namespace NB
