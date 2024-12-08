#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <ctime>

// Function to generate a random color
sf::Color getRandomColor() {
    return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}

int main() {
    // Seed random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Simple SFML Game");

    // Create a circle
    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Cyan);
    circle.setPosition(375.f, 275.f); // Start in the middle of the screen

    // Set the movement speed
    float speed = 5.0f;

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Movement logic
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            circle.move(0.f, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            circle.move(0.f, speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            circle.move(-speed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            circle.move(speed, 0.f);
        }

        // Boundary check and color change
        sf::Vector2f position = circle.getPosition();
        if (position.x <= 0 || position.x + 2 * circle.getRadius() >= 800 ||
            position.y <= 0 || position.y + 2 * circle.getRadius() >= 600) {
            circle.setFillColor(getRandomColor());
        }

        // Clear the screen
        window.clear();

        // Draw the circle
        window.draw(circle);

        // Display everything
        window.display();
    }

    return 0;
}
