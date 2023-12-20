#include "JumpRound.h"

#include "Player.h"
#include "Core/Core.h"

JumpRound::JumpRound(int index)
    :Round{index}
{}

void JumpRound::RunRound(EntityPtr<Player> currentPlayer, EntityPtr<DeckController>& deckController)
{
    DrawTurn(currentPlayer, deckController);
    Core::LogMessage(currentPlayer->GetName() + " your turn will be skipped because the last card tossed is a Jump Card!");
}