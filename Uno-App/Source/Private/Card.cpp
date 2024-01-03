#include "Public/Card.h"
#include "Statics.h"
#include "Core/Core.h"

Card::Card(const std::string& name, const EColor color)
    : Entity{getColorName(color) + " " + name}, Color{color}
{}

std::string Card::GetTypename(const Card& card)
{
    std::string typeName = card.GetCardTypeName();
    bool bBefore = false;
    while (typeName.length() < LINE_WIDTH-2)
    {
        if(bBefore)
        {
            typeName.insert(typeName.begin(), ' ');
        }
        else
        {
            typeName.append(" ");            
        }

        bBefore = !bBefore;
    }
    if(typeName.length() > LINE_WIDTH - 2)
    {
        typeName.erase(typeName.begin() + LINE_WIDTH - 2, typeName.end());
    }

    return typeName;
}

std::string Card::GetConsoleColorCode(EColor color)
{
    switch (color)
    {
    case EColor::Blue:
        return "\033[34m";
    case EColor::Yellow:
        return "\033[33m";
    case EColor::Red:
        return "\033[31m";
    case EColor::Green:
        return "\033[32m";
    }

    return DEFAULT_COLOR;
}

bool Card::CanTossCardOnMe(EntityPtr<Card> other)
{
    return !other.IsValid() || Color == other->GetColor() || other->GetColor() == EColor::None || Color == EColor::None;
}

std::vector<std::string> Card::GetDisplayCard(const Card& card)
{
    std::vector<std::string> returnValue;
    returnValue.reserve(COLUMN_HEIGHT);
    std::string displayColor = getColorName(card.GetColor());
    bool bBefore = true;
    while (displayColor.length() < COLOR_DISPLAY_SIZE)
    {
        if(bBefore)
        {
            displayColor.insert(displayColor.begin(), ' ');
        }
        else
        {
            displayColor.append(" ");            
        }

        bBefore = !bBefore;
    }

    const std::string colorLine = GetConsoleColorCode(card.Color) + "XX" + displayColor + "XX" + DEFAULT_COLOR;
    const std::string defaultLine = GetConsoleColorCode(card.Color) + "X         X" + DEFAULT_COLOR;  
    const std::string centerLine = GetConsoleColorCode(card.Color) + "X" + GetTypename(card) + "X" + DEFAULT_COLOR;

    // build string vector
    for (int i=0; i < COLUMN_HEIGHT; i++)
    {
        if(i == 0 || i == COLUMN_HEIGHT - 1)
        {
            returnValue.emplace_back(colorLine);
        }
        else if(i == COLUMN_HEIGHT / 2)
        {
            returnValue.emplace_back(centerLine);
        }
        else
        {
            returnValue.emplace_back(defaultLine);
        }
    }

    return returnValue;
}

void Card::Draw() const
{
    const std::vector<std::string> stringVector = GetDisplayCard(*this);
    for (const auto& line : stringVector)
    {
        Core::LogMessage(line);
    }
}

void Card::AddToLineIndex(std::vector<std::string>& lines, const std::string& text, int i)
{
    if(static_cast<int>(lines.size()) <= i)
    {               
        lines.emplace_back(text);
    }
    else
    {
        lines[i].append(text);
    }
}

void Card::DrawCardsFromTo(const std::vector<EntityPtr<Card>>& cards, const bool drawOption,
    const int from, const int to)
{
    std::vector<std::string> lines;
    const int startAdding = drawOption ? 1 : 0;
    lines.reserve(COLUMN_HEIGHT + startAdding);

    int currentCard = -1;
    for (int k = from; k < to && k < static_cast<int>(cards.size()); k++)
    {
        EntityPtr<Card> card = cards.at(k);
        currentCard++;
        if(!card.IsValid())
        {
            continue;
        }

        std::string spaceBetweenCards = "      ";
        std::vector<std::string> cardDisplay = Card::GetDisplayCard(card.GetRef());
        if(drawOption)
        {
            std::string space = k < 10 ? "  " : " ";
            AddToLineIndex(lines, space + "Option: " + std::to_string(k) + spaceBetweenCards, 0);
        }

        for (int i=0; i < COLUMN_HEIGHT; i++)
        {
            AddToLineIndex(lines, cardDisplay[i] + spaceBetweenCards, i+startAdding);
        }
    }

    for (const std::string& line : lines)
    {
        Core::LogMessage(line + DEFAULT_COLOR);
    }
}

void Card::DrawCards(const std::vector<EntityPtr<Card>>& cards, bool drawOption)
{
    for (int i=0; i < static_cast<int>(cards.size()); i+=CARDS_PER_LINE)
    {
        DrawCardsFromTo(cards, drawOption, i, i + CARDS_PER_LINE);
        std::cout << std::endl;
    }
}