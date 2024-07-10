#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>

class Text;
class Game;

class Button
{
private:
    Game* game;
    std::shared_ptr<Text> text;

    sf::Texture backgroundTexture;
    sf::Texture hoverTexture;
    sf::Sprite background;

    bool isHovered;
    bool isClicked;

    std::function<void()> onClickEvent;

public:
    Button(Game* game, std::string fontFile, std::string aText, std::function<void()> onClick);

    void reset();
    void setCharacterSize(unsigned int aSize);
    void setFillColor(sf::Color aColor);
    void setStyle(sf::Text::Style aStyle);
    void setText(std::string aText);
    void setPosition(sf::Vector2f aPosition);
    void setPosition(float x, float y);
    void setScale(float x, float y);
    void setScale(sf::Vector2f aSize);
    void handleInput(sf::Event handleInput);
    void update(sf::Time& elapsed);
    void render();
    void onHoverEnter();
    void onHoverLeave();
    void onClick();
    bool IsHovered() const;
    bool IsClicked() const;
};
