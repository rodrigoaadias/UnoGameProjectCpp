#pragma once
#include <memory>
#include <vector>
#include "Card.h"
#include "Core/Public/Entity.h"

class DeckController;

class Player : public Entity
{
    int Index;
    bool HasYelled;
    std::vector<EntityPtr<Card>> CardsOnHand;
    void AddCardToHand(EntityPtr<Card> card);
    bool CanTossCard(const EntityPtr<Card>& lastTossedCard);
    EntityPtr<Card> PopCardFrom(uint32_t index);

    bool CanYell() const;
    void Yell();
public:
    Player(const std::string& name, const int& index);
    std::string GetDisplayName();

    void BuyDeckCard(std::weak_ptr<DeckController> deckController);
    void TossValidCard(std::weak_ptr<DeckController> deckController, uint32_t choice);
    void PlayTurn(std::weak_ptr<DeckController> deckController);
    std::string ToString();
    std::vector<EntityPtr<Card>>& GetCards();
};
