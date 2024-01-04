#include "Public/SwitchHandCard.h"
#include "Core/Core.h"
#include "Public/Player.h"

SwitchHandCard::SwitchHandCard()
: Card{"Switch Hand Card", EColor::None }
{}

std::string SwitchHandCard::GetCardTypeName() const
{
    return "Hand";
}

void SwitchHandCard::Execute(IMatchContext* currentMatch)
{
    Core::LogMessage(currentMatch->GetCurrentPlayer()->GetName()+" will SWITCH HANDS!");
    Core::LogMessage(currentMatch->GetCurrentPlayer()->GetName()+ " - Select the player that you want to switch hands: ");

    int optionNumber = -1;
    for (const EntityPtr<Player>& player : currentMatch->GetPlayers())
    {
        optionNumber++;
        if(player != currentMatch->GetCurrentPlayer())
        {
            Core::LogMessage(std::to_string(optionNumber) + " - " + player->GetName() + ": has " + std::to_string(player->GetCards().size()) + " cards");
        }
    }

    int choice = Core::GetInput<int>({});
    while (choice < 0 || choice >= currentMatch->GetPlayersAmount() || currentMatch->GetPlayers().at(choice) == currentMatch->GetCurrentPlayer())
    {
        Core::LogError("Select an option between 0 and " + std::to_string(optionNumber) + " and do not select you!");
        choice = Core::GetInput<int>({});
    }

    EntityPtr<Player> selectedPlayer = currentMatch->GetPlayers().at(choice);
    currentMatch->GetCurrentPlayer()->SwitchHandsWith(selectedPlayer);

    Core::LogMessage(currentMatch->GetCurrentPlayer()->GetDisplayName() + " HAS SWITCHED HANDS WITH " + selectedPlayer->GetDisplayName());
}