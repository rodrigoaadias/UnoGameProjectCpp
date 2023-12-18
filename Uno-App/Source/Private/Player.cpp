#include "Public/Player.h"

Player::Player(const std::string& name, const int& index)
    :Entity(name), Index{index}
{
    CardsOnHand.reserve(10);
}

std::string Player::GetDisplayName()
{
    return "Player " + std::to_string(Index)  + ": " + GetName();
}

void Player::AddCardToHand(std::weak_ptr<Card> card)
{
    CardsOnHand.emplace_back(card);
}

std::string Player::ToString()
{
    std::string cardsToString =  std::to_string(CardsOnHand.size()) + " Cards on hand\n";
    for (const auto& card : CardsOnHand)
    {
        if(!card.expired())
        {
            cardsToString += card.lock()->GetName() + "\n";
        }
    }
    
    return GetDisplayName() + ": " + cardsToString;
}