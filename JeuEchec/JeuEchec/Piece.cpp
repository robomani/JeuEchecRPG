#include "Piece.h"

#include <SDL_image.h>

Piece::Piece(const std::string a_PieceTexturePath, int i_HP, int i_Attack, int i_Armor)
{
	m_HP = i_HP;
	m_Attack = i_Attack;
	m_Armor = i_Armor;

	m_PieceTexture = IMG_Load((a_PieceTexturePath + ".png").c_str());

	m_AvailableMoves = std::vector<std::vector<std::tuple<int, int>>>();

	for (int i = 0; i < Enums::EDirection::Direction_Count; i++)
	{
		m_AvailableMoves.push_back(std::vector<std::tuple<int, int>>());
	}

	Init();
}

Piece::~Piece()
{
	if (m_PieceTexture != nullptr) 
	{
		SDL_FreeSurface(m_PieceTexture);
		m_PieceTexture = nullptr;
	}
}

void Piece::Init()
{

}

void Piece::Draw(SDL_Surface* a_Parent, SDL_Rect* a_TargetedRect)
{
	SDL_BlitSurface(m_PieceTexture, NULL, a_Parent, a_TargetedRect);
}

void Piece::Update()
{

}
