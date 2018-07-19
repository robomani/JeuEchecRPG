#include "EPieceType.h"
#include "Player.h"
#include "Text.h"
#include "Case.h"
#include "Game.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::ChangeManaBy(int a_Value)
{
	m_Mana += a_Value;
}

void Player::ChangePowerTexts()
{
	SDL_Color red = {255, 0, 0};
	SDL_Color green = {0, 255, 0 };

	m_Mana >= 1 ? Text::SetColor(ETextContent::PlayerPower01, green) : Text::SetColor(ETextContent::PlayerPower01, red);
	m_Mana >= 2 ? Text::SetColor(ETextContent::PlayerPower02, green) : Text::SetColor(ETextContent::PlayerPower02, red);
	m_Mana >= 3 ? Text::SetColor(ETextContent::PlayerPower03, green) : Text::SetColor(ETextContent::PlayerPower03, red);
	m_Mana >= 5 ? Text::SetColor(ETextContent::PlayerPower04, green) : Text::SetColor(ETextContent::PlayerPower04, red);
	m_Mana >= 25 ? Text::SetColor(ETextContent::PlayerPower05, green) : Text::SetColor(ETextContent::PlayerPower05, red);
}

void Player::Power01(Board& a_Board)
{
	if (a_Board.GetCurrentCase() != nullptr)
	{
		return;
	}

	ChangeManaBy(-1);
	Game::ChangeColorTurn();
}

void Player::Power02(Board& a_Board)
{
	Case* currentCase = a_Board.GetCurrentCase();

	if (currentCase 
	&& currentCase->IsNotEmpty() 
	&& !currentCase->IsPowerReady())
	{
		ChangeManaBy(-2);
		currentCase->ResetCurrentPower();
		Text::SetText(ETextContent::PiecesPowerAvable, "Power Ready");
		ChangePowerTexts();
	}
}

void Player::Power03(Board& a_Board)
{
	Case* currentCase = a_Board.GetCurrentCase();

	if (currentCase
	&& currentCase->IsNotEmpty())
	{
		ChangeManaBy(-3);
		currentCase->BoostCurrentPiece(2);
		Text::SetText(ETextContent::PiecesStats, currentCase->GetHP(), currentCase->GetAttack(), currentCase->GetArmor());
		if (currentCase->GetPieceType() == Enums::EPieceType::Pion)
		{
			currentCase->UpdatePiecePowerDescr();
		}
		Text::SetText(ETextContent::PiecesPower, currentCase->GetPowerDescr());

		ChangePowerTexts();
	}
}

void Player::Power04(Board& a_Board)
{
	Case* currentCase = a_Board.GetCurrentCase();

	if (currentCase
	&& currentCase->IsNotEmpty())
	{
		a_Board.SetIsSwitchingPieces(true);
	}
}

void Player::Power05(Board& a_Board)
{
	ChangeManaBy(-25);
	ChangePowerTexts();
	a_Board.DestroAllEnnemies();
}