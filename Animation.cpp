#include "Animation.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>

Animation::Animation(Type type, sf::Vector2f position, float duration, int points)
    : _type(type), _position(position), _duration(duration), _elapsedTime(0.f) {

    _font.loadFromFile("path/to/font.ttf");  // Replace with your font path

    if (_type == Type::ScoreIncrease) {
        SetupText(points);
    }
    else if (_type == Type::Combo) {
        SetupCombo();
    }
}

void Animation::Update(float dt) {
    _elapsedTime += dt;
    if (_type == Type::ScoreIncrease || _type == Type::Combo) {
        _position.y -= 50 * dt;  // Move the text upwards
        sf::Color color = _text.getFillColor();
        color.a = static_cast<sf::Uint8>(255 * (1.f - _elapsedTime / _duration));  // Fade out
        _text.setFillColor(color);
    }
}

void Animation::Draw(sf::RenderWindow& window) {
    if (_type == Type::ScoreIncrease || _type == Type::Combo) {
        window.draw(_text);
    }
}

bool Animation::IsComplete() const {
    return _elapsedTime >= _duration;
}

void Animation::SetupText(int points) {
    _text.setFont(_font);
    _text.setCharacterSize(30);
    _text.setString("+" + std::to_string(points));
    _text.setFillColor(sf::Color::Green);
    _text.setPosition(_position);
}

void Animation::SetupCombo() {
    _text.setFont(_font);
    _text.setCharacterSize(30);
    _text.setString("Combo!");
    _text.setFillColor(sf::Color::Yellow);
    _text.setPosition(_position);
}
