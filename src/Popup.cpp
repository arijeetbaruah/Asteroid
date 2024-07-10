#include "../include/Popup.hpp"
#include "../include/Text.hpp"
#include "../include/Button.hpp"
#include "../include/Game.hpp"

Popup::Popup(Game* aGame, std::string fontFile, std::string aText, std::function<void()> aOnApply, std::function<void()> aOnCancel)
	: game(aGame), onApply(aOnApply), onCancel(aOnCancel), isEnable(false)
{
	text = std::make_shared<Text>(game, fontFile, aText);
	applyBtn = std::make_shared<Button>(game, fontFile, "OK", std::bind(&Popup::onApplyEvent, this));
	cancelBtn = std::make_shared<Button>(game, fontFile, "Cancel", std::bind(&Popup::onCancelEvent, this));

	sf::Vector2u scale = game->window.getSize();
	backgound = sf::RectangleShape(sf::Vector2f(scale.x / 2, scale.y / 2));
	sf::FloatRect bounds = backgound.getLocalBounds();
	backgound.setOrigin(sf::Vector2f(bounds.getSize().x / 2, bounds.getSize().y / 2));

	backgound.setPosition(sf::Vector2f(scale.x / 2, scale.y / 2));
	text->setPosition(sf::Vector2f(scale.x / 2, scale.y / 2));
	text->setFillColor(sf::Color::Black);

	applyBtn->setPosition(sf::Vector2f(scale.x / 2 + 200, (scale.y / 2) + 200));
	applyBtn->setScale(sf::Vector2f(scale.x / 500, 5));

	cancelBtn->setPosition(sf::Vector2f(scale.x / 2 - 200, (scale.y / 2) + 200));
	cancelBtn->setScale(sf::Vector2f(scale.x / 500, 5));
}

void Popup::hidePop()
{
	isEnable = false;
}

void Popup::showPop()
{
	isEnable = true;
	
	applyBtn->reset();
	cancelBtn->reset();
}

bool Popup::getEnable() const
{
	return isEnable;
}

void Popup::handleInput(sf::Event event)
{
	if (!isEnable)
	{
		return;
	}

	applyBtn->handleInput(event);
	cancelBtn->handleInput(event);
}

void Popup::update(sf::Time& elapsed)
{
	if (!isEnable)
	{
		return;
	}

	applyBtn->update(elapsed);
	cancelBtn->update(elapsed);
}

void Popup::render()
{
	if (!isEnable)
	{
		return;
	}

	game->window.draw(backgound);

	text->render();
	applyBtn->render();
	cancelBtn->render();
}
