#pragma once
#include <vector>
#include "EColor.h"
#include "Core/EntityPtr.h"
#include "Core/Public/Entity.h"

class Card : public Entity
{
    EColor Color;

    static std::string GetDisplayTypename(const Card& card);
    static std::string GetConsoleColorCode(const EColor& color);
    static void DrawCardsFromTo(const std::vector<EntityPtr<Card>>& cards, const bool& drawOption, const int& from, const int& to);
    static void AddToLineIndex(std::vector<std::string>& lines, const std::string& text, const int& i);

public:
    Card(const std::string& name, const EColor& color);
    [[nodiscard]] const EColor& GetColor() const;

    [[nodiscard]] virtual std::string GetCardTypeName() const = 0;
    [[nodiscard]] virtual bool CanTossCardOnMe(const EntityPtr<Card>& other) const;

    static std::vector<std::string> GetDisplayCard(const Card& card);
    static void DrawCards(const std::vector<EntityPtr<Card>>& cards, const bool& drawOption = false);

    void Draw() const;
};
