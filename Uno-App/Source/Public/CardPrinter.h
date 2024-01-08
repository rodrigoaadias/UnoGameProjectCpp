#pragma once
#include <string>
#include <vector>
#include "Core/EntityPtr.h"

class Card;

class CardPrinter
{
    static std::string GetDisplayTypename(const Card& card);
    static void DrawCardsFromTo(const std::vector<EntityPtr<Card>>& cards, bool drawOption, int from, int to);
    static void AddToLineIndex(std::vector<std::string>& lines, const std::string& text, int i);
    
public:    
    static std::vector<std::string> GetDisplayCard(const Card& card);
    static void DrawCards(const std::vector<EntityPtr<Card>>& cards, bool drawOption = false);
    static void DrawUniqueCard(const Card& card);
};
