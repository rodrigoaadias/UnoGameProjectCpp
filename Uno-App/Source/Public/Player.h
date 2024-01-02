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
    EntityPtr<Card> PopCardFrom(uint32_t index);

    void TryYell();
    bool CanYell() const;
    void Yell();
    void TossValidCard(const std::weak_ptr<DeckController>& deckController, uint32_t choice);
    void BuyCardAndTryToss(const std::weak_ptr<DeckController>& deckController, const EntityPtr<Card>& tossedCard);
    void SelectCardToToss(const std::weak_ptr<DeckController>& deckController, EntityPtr<Card> tossedCard);
    
protected:
    void AddCardToHand(EntityPtr<Card> card);

public:
    Player(const std::string& name, const int& index);
    std::string GetDisplayName();

    bool CanTossCard(const EntityPtr<Card>& lastTossedCard);
    void BuyDeckCard(const std::weak_ptr<DeckController>& deckController);
    void PlayTurn(const std::weak_ptr<DeckController>& deckController);
    void SwitchHandsWith(EntityPtr<Player>& other);
    std::string ToString();
    std::vector<EntityPtr<Card>>& GetCards();
};
