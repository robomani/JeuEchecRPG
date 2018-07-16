#include "Player.h"
#include "Text.h"

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

}


void Player::Power02(Board& a_Board)
{

}


void Player::Power03(Board& a_Board)
{

}


void Player::Power04(Board& a_Board)
{

}


void Player::Power05(Board& a_Board)
{

}