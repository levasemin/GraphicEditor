#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>

int main()
{
    sf::ContextSettings glsettings;
    glsettings.antialiasingLevel = 2;
    sf::RenderWindow window{sf::VideoMode{300, 80}, "loadFromMemory Example", sf::Style::Titlebar | sf::Style::Close, glsettings};

    const auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition({static_cast<int>(desktop.width / 2 - window.getSize().x / 2),
                       static_cast<int>(desktop.height / 4 - window.getSize().y / 4)});

    window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    std::ifstream texture_file{"example-texture.png", std::ifstream::binary};
    std::vector<char> buffer;
    if (texture_file) {
        // get length of file:
        texture_file.seekg(0, texture_file.end);
        const auto length = texture_file.tellg();
        if (!length) {
            std::cerr << "Cannot load zero byte texture file" << std::endl;
            return EXIT_FAILURE;
        }
        buffer.resize(length); // reserve space

        texture_file.seekg(0, texture_file.beg);

        auto start = &*buffer.begin();
        texture_file.read(start, length);
        texture_file.close();
    } else {
        std::cerr << "Could not open texture file" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Texture texture;
    if (!texture.loadFromMemory(&buffer[0], buffer.size())) {
        std::cerr << "Texture load failed" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    return EXIT_SUCCESS;
}