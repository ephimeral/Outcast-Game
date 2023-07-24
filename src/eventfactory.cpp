#include "eventfactory.h"
#include "game.h"
#include "event.h"
#include <SFML/Graphics.hpp>
#include <memory>

EventFactory::EventFactory(Game* game): game(game)
{
}

EventFactory::EventFactory()
{
}

std::unique_ptr<Event> EventFactory::getDebugEvent(sf::Vector2f position, sf::Vector2f size)
{
    return std::make_unique<Event>(position, size, game, this, &EventFactory::functionDebugEvent);
}

void EventFactory::functionDebugEvent()
{
    std::unique_ptr<Stage> stage = std::make_unique<Stage>();
    game->stageBuilder.setSecondDebugRoom(*stage); 
    game->currentStage = std::move(stage);
}