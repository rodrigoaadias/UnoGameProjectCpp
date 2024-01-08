#include "Public/CardPrinter.h"
#include "Statics.h"
#include "Core/Core.h"
#include "Public/Card.h"

std::string CardPrinter::GetDisplayTypename(const Card& card)
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

std::vector<std::string> CardPrinter::GetDisplayCard(const Card& card)
{
    std::vector<std::string> returnValue;
    returnValue.reserve(COLUMN_HEIGHT);

    std::string displayColor = GetColorName(card.GetColor());

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

    const std::string colorLine = GetConsoleColorCode(card.GetColor()) + "XX" + displayColor + "XX" + DEFAULT_COLOR;
    const std::string defaultLine = GetConsoleColorCode(card.GetColor()) + "X         X" + DEFAULT_COLOR;  
    const std::string centerLine = GetConsoleColorCode(card.GetColor()) + "X" + GetDisplayTypename(card) + "X" + DEFAULT_COLOR;

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

void CardPrinter::DrawUniqueCard(const Card& card)
{
    const std::vector<std::string> stringVector = GetDisplayCard(card);
    for (const auto& line : stringVector)
    {
        Core::LogMessage(line);
    }
}

void CardPrinter::AddToLineIndex(std::vector<std::string>& lines, const std::string& text, const int i)
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

void CardPrinter::DrawCardsFromTo(const std::vector<EntityPtr<Card>>& cards, const bool drawOption,
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
        std::vector<std::string> cardDisplay = CardPrinter::GetDisplayCard(card.GetRef());
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

void CardPrinter::DrawCards(const std::vector<EntityPtr<Card>>& cards, const bool drawOption)
{
    for (int i=0; i < static_cast<int>(cards.size()); i+=CARDS_PER_LINE)
    {
        DrawCardsFromTo(cards, drawOption, i, i + CARDS_PER_LINE);
        std::cout << std::endl;
    }
}