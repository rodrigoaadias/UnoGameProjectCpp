﻿#include "Public/Player.h"

#include "Core/Core.h"
#include "Public/DeckController.h"
#include "Public/CardPrinter.h"

Player::Player(const std::string& name, const int index)
    :Entity(name), Index{index}, HasYelled{false}
{
    CardsOnHand.reserve(10);
}

std::string Player::GetDisplayName() const
{
    return "Player " + std::to_string(Index)  + " - " + GetName();
}

void Player::AddCardToHand(const EntityPtr<Card> card)
{
    CardsOnHand.emplace_back(card);
}

bool Player::CanTossCard(const EntityPtr<Card>& lastTossedCard) const
{
    if(!lastTossedCard.IsValid())
    {
        return true;
    }

    for (const EntityPtr<Card>& card : CardsOnHand)
    {
        if(!card.IsValid())
        {
            continue;
        }

        if(lastTossedCard->CanTossCardOnMe(card))
        {
            return true;
        }
    }

    return false;
}

EntityPtr<Card> Player::PopCardFrom(const uint32_t index)
{
    EntityPtr<Card> returnCard = CardsOnHand.at(index);
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

void Player::BuyDeckCard(const std::weak_ptr<DeckController>& deckController)
{
    AddCardToHand(deckController.lock()->BuyCardFromDeck());
    HasYelled = false;
}

void Player::TossValidCard(const std::weak_ptr<DeckController>& deckController, const uint32_t choice)
{
    const EntityPtr<Card>& selectedCard = PopCardFrom(choice);
    deckController.lock()->AddCardToTable(selectedCard);

    Core::LogMessage(GetDisplayName() + " tossed the following card:");
    CardPrinter::DrawUniqueCard(selectedCard.GetRef());
}

void Player::BuyCardAndTryToss(const std::weak_ptr<DeckController>& deckController, const EntityPtr<Card>& tossedCard)
{
    Core::WaitAnyKey(GetDisplayName() + ": you must buy a card from deck! ");
    BuyDeckCard(deckController);
    Core::LogMessage(GetDisplayName() + " has bought the following card: ");
    const EntityPtr<Card>& boughtCard = CardsOnHand.at(static_cast<int>(CardsOnHand.size()) - 1);

    CardPrinter::DrawUniqueCard(boughtCard.GetRef());

    if(tossedCard->CanTossCardOnMe(boughtCard))
    {
        TryYell();
        Core::WaitAnyKey(GetDisplayName() + ": you can toss the card you bought!");
        TossValidCard(deckController, static_cast<int>(CardsOnHand.size()) - 1);
    }
    else
    {
        Core::LogMessage(GetDisplayName() + ": you can't toss the card you bought... :( your turn will be skipped");
    }
}

void Player::SelectCardToToss(const std::weak_ptr<DeckController>& deckController, const EntityPtr<Card>& tossedCard)
{
    const uint32_t choice = Core::GetInput<int>("Select the card you want to toss accordingly the Option Number showing over the card: ");
    while (choice < 0 || choice >= CardsOnHand.size())
    {
        Core::LogMessage("This option is not available. Select a valid option between 0 and " + std::to_string(CardsOnHand.size() - 1));
        SelectCardToToss(deckController, tossedCard);
        return;
    }

    if(tossedCard.IsValid() && !tossedCard->CanTossCardOnMe(CardsOnHand[choice]))
    {
        Core::LogMessage("You can't toss this card. The card must match the color or number of the " + tossedCard->GetName());
        SelectCardToToss(deckController, tossedCard);
        return;
    }

    TossValidCard(deckController, choice);
}

void Player::TryYell()
{
    if(CanYell())
    {
        const uint32_t yellChoice = Core::GetInput<int>("Would you like to yell?\n1 - Yes | [Any] - No: ");
        if(yellChoice == 1)
        {
            Yell();
        }
    }
}

void Player::PlayTurn(const std::weak_ptr<DeckController>& deckController)
{
    const EntityPtr<Card>& tossedCard = deckController.lock()->GetLastTossedCard();
    if(CanTossCard(tossedCard))
    {
        if(CardsOnHand.size() == 1 && !HasYelled)
        {
            Core::WaitAnyKey("You didn't yelled UNO!... Now you must buy 2 cards and skip your turn!");
            BuyDeckCard(deckController);
            BuyDeckCard(deckController);

            Core::LogMessage(GetName() + " bought the following cards: ");
            const std::vector cardsToDraw = {CardsOnHand.at(CardsOnHand.size() - 1),
                                CardsOnHand.at(CardsOnHand.size() - 2)};

            CardPrinter::DrawCards(cardsToDraw);
            return;
        }

        TryYell();

        SelectCardToToss(deckController, tossedCard);
    }
    else
    {
        BuyCardAndTryToss(deckController, tossedCard);
    }
}

void Player::SwitchHandsWith(EntityPtr<Player>& other)
{
    const std::vector<EntityPtr<Card>> cachedCards = CardsOnHand;
    CardsOnHand.clear();

    for (const EntityPtr<Card>& otherCard : other->GetCards())
    {
        CardsOnHand.emplace_back(otherCard);
    }

    other->GetCardsWrite().clear();

    for (const EntityPtr<Card>& cacheCard : cachedCards)
    {
        other->AddCardToHand(cacheCard);
    }
}

std::string Player::ToString() const
{
    std::string cardsToString =  std::to_string(CardsOnHand.size()) + " Cards on hand\n";
    for (const EntityPtr<Card>& card : CardsOnHand)
    {
        if(card.IsValid())
        {
            cardsToString += card->GetName() + "\n";
        }
    }

    return GetDisplayName() + ": " + cardsToString;
}

const std::vector<EntityPtr<Card>>& Player::GetCards() const
{
    return CardsOnHand;
}

std::vector<EntityPtr<Card>>& Player::GetCardsWrite()
{    
    return CardsOnHand;
}