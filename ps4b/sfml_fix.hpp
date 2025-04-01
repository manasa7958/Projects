inline std::ostream& operator<<(std::ostream& os, const sf::Vector2u& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}
