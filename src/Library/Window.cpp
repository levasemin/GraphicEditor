#include "Window.h"

void Window::create(Vector2d shape, std::string name, int style)
{
    window_.create(sf::VideoMode(int(shape.x_), int(shape.y_)), name, style);
}

void Window::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
{
    window_.draw(drawable, states);
}	


void Window::draw(const sf::Vertex *vertices, std::size_t VertexCount, sf::PrimitiveType type, const sf::RenderStates &states)
{
    window_.draw(vertices, VertexCount, type);
}


void Window::draw(const sf::VertexBuffer &vertexBuffer, const sf::RenderStates &states)
{
    window_.draw(vertexBuffer, states);
}


bool Window::isOpen()
{
    return window_.isOpen();
}

bool Window::getVisible()
{
    return visible_;
}

void Window::setVisible(bool visible)
{
    visible_ = visible;
    window_.setVisible(visible);
}

bool Window::pollEvent(Event &event)
{
    sf::Event sfEvent;

    if (!window_.pollEvent(sfEvent))
    {
        return false;
    }

    event = Event(sfEvent);

    return true;
}


void Window::draw(Sprite sprite)
{
    window_.draw(sprite.sprite_);
}

void Window::close()
{
    window_.close();
}


void Window::display()
{
    window_.display();
}

void Window::clear()
{
    window_.clear();
}

void Window::clear(Color color)
{
    window_.clear(color.get_sf_color());
}