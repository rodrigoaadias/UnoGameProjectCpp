﻿#pragma once
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
    [[nodiscard]] bool CanYell() const;
    void Yell();
    void TossValidCard(const std::weak_ptr<DeckController>& deckController, uint32_t choice);
    void BuyCardAndTryToss(const std::weak_ptr<DeckController>& deckController, const EntityPtr<Card>& tossedCard);
    void SelectCardToToss(const std::weak_ptr<DeckController>& deckController, const EntityPtr<Card>& tossedCard);

protected:
    void AddCardToHand(EntityPtr<Card> card);

public:
    Player(const std::string& name, int index);

    [[nodiscard]] std::string GetDisplayName() const;
    [[nodiscard]] bool CanTossCard(const EntityPtr<Card>& lastTossedCard) const;
    void BuyDeckCard(const std::weak_ptr<DeckController>& deckController);
    void PlayTurn(const std::weak_ptr<DeckController>& deckController);
    void SwitchHandsWith(EntityPtr<Player>& other);
    [[nodiscard]] std::string ToString() const;
    [[nodiscard]] const std::vector<EntityPtr<Card>>& GetCards() const;
    std::vector<EntityPtr<Card>>& GetCardsWrite();
};
