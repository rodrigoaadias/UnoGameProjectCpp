#include "Public/JumpRound.h"
#include "Public/Player.h"
#include "Core/Core.h"

JumpRound::JumpRound(const int index)
    :Round{index}
{}

void JumpRound::RunRound(const EntityPtr<Player>& currentPlayer, const EntityPtr<DeckController>& deckController, ETurnFlow turnFlow)
{
    DrawTurn(currentPlayer, deckController, turnFlow);
    Core::LogMessage(currentPlayer->GetName() + " your turn will be skipped because the last card tossed is a Jump Card!");
}