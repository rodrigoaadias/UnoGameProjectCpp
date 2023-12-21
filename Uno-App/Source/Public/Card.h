#pragma once
#include <vector>
#include "EColor.h"
#include "Core/EntityPtr.h"
#include "Core/Public/Entity.h"

class Card : public Entity
{
    static constexpr int COLOR_DISPLAY_SIZE = 7;
    static constexpr int CARDS_PER_LINE = 7;
    EColor Color;

    static std::string GetTypename(const Card& card);
    static std::string GetConsoleColorCode(EColor color);
    static void DrawCardsFromTo(const std::vector<EntityPtr<Card>>& cards, bool drawOption, int from, int to);
    static void AddToLineIndex(std::vector<std::string>& lines, const std::string& text, int i);

public:
    Card(const std::string& name, EColor color);
    EColor GetColor() const { return Color; }

    virtual std::string GetCardTypeName() const = 0;
    virtual bool CanBeTossed(EntityPtr<Card> other);

    static std::vector<std::string> GetDisplayCard(const Card& card);  
    static void DrawCards(const std::vector<EntityPtr<Card>>& cards, bool drawOption = false);

    void Draw() const;
};
