#include "Public/Player.h"

#include "Core/Core.h"
#include "Public/DeckController.h"

Player::Player(const std::string& name, const int& index)
    :Entity(name), Index{index}
{
    CardsOnHand.reserve(10);
}

std::string Player::GetDisplayName()
{
    return "Player " + std::to_string(Index)  + ": " + GetName();
}

void Player::AddCardToHand(EntityPtr<Card> card)
{
    CardsOnHand.emplace_back(card);
}

bool Player::CanTossCard(const EntityPtr<Card>& lastTossedCard)
{
    if(!lastTossedCard.IsValid())
    {
        return true;
    }

    for (const auto& card : GetCards())
    {
        if(!card.IsValid())
        {
            continue;
        }

        if(card->CanBeTossed(lastTossedCard))
        {
            return true;
        }
    }

    return false;
}

EntityPtr<Card> Player::PopCardFrom(const uint32_t index)
{
    EntityPtr<Card> returnCard = CardsOnHand[index];
    CardsOnHand.erase(CardsOnHand.begin() + index);

    return returnCard;
}

bool Player::CanYell() const
{
    return CardsOnHand.size() == 2 && !HasYelled;
}

void Player::Yell()
{
    Core::LogMessage(GetDisplayName() + " has yelled UNO!");
    HasYelled = true;
}

void Player::BuyDeckCard(std::weak_ptr<DeckController> deckController)
{
    AddCardToHand(deckController.lock()->BuyCardFromDeck());
    HasYelled = false;
}

void Player::TossValidCard(std::weak_ptr<DeckController> deckController, const uint32_t choice)
{
    const EntityPtr<Card> selectedCard = PopCardFrom(choice);
    deckController.lock()->AddCardToTable(selectedCard);

    Core::LogMessage(GetDisplayName() + " tossed the following card:");
    selectedCard->Draw();
}

void Player::PlayTurn(std::weak_ptr<DeckController> deckController)
{
    EntityPtr<Card> tossedCard = deckController.lock()->GetLastTossedCard();
    if(CanTossCard(tossedCard))
    {
        if(CanYell())
        {
            const uint32_t yellChoice = Core::GetInput<int>("Would you like to yell? 1 - Yes | 2 - No: ");
            if(yellChoice == 1)
            {
                Yell();
            }
        }

        const uint32_t choice = Core::GetInput<int>("Select the card you want to toss accordingly the number showing over the card: ");
        while (choice < 0 || choice >= CardsOnHand.size())
        {
            Core::LogMessage("This option is not available. Select a valid option between 0 and " + std::to_string(CardsOnHand.size() - 1));
            PlayTurn(deckController);
            return;
        }

        if(!CardsOnHand[choice]->CanBeTossed(tossedCard))
        {
            Core::LogMessage("You can't toss this card. The card must match the color or number of the " + tossedCard->GetName());
            PlayTurn(deckController);
            return;
        }

        TossValidCard(deckController, choice);
    }
    else
    {
        BuyDeckCard(deckController);
        Core::LogMessage(GetDisplayName() + " has bought the following card: ");
        EntityPtr<Card> boughtCard = CardsOnHand.back();
        boughtCard->Draw();

        if(boughtCard->CanBeTossed(tossedCard))
        {
            TossValidCard(deckController, CardsOnHand.size() - 1);
        }
    }
}

std::string Player::ToString()
{
    std::string cardsToString =  std::to_string(CardsOnHand.size()) + " Cards on hand\n";
    for (auto card : CardsOnHand)
    {
        if(card.IsValid())
        {
            cardsToString += card->GetName() + "\n";
        }
    }

    return GetDisplayName() + ": " + cardsToString;
}

std::vector<EntityPtr<Card>>& Player::GetCards()
{
    return CardsOnHand;
}