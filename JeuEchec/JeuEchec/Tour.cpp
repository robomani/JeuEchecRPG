#include "Tour.h"

Tour::Tour(const Enums::EPieceColor a_PieceColor, int i_HP, int i_Attack, int i_Armor)
	: Piece(a_PieceColor == Enums::EPieceColor::Blanche ? "images/WTower" : "images/BTower", i_HP, i_Attack, i_Armor)
{
	m_PieceType = Enums::EPieceType::Tour;
	m_PieceColor = a_PieceColor;

	for (int i = 1, j = 1; i < 8; i++, j++)
	{
		m_AvailableMoves[Enums::EDirection::North].push_back(std::tuple<int, int>(i, 0));
		m_AvailableMoves[Enums::EDirection::East].push_back(std::tuple<int, int>(0, j));
		m_AvailableMoves[Enums::EDirection::South].push_back(std::tuple<int, int>(-i, 0));
		m_AvailableMoves[Enums::EDirection::West].push_back(std::tuple<int, int>(0, -j));
	}
	
	m_AffectedPower[Enums::EDirection::East].push_back(std::tuple<int, int>(0, 1));
	m_AffectedPower[Enums::EDirection::North].push_back(std::tuple<int, int>(1, 0));
	m_AffectedPower[Enums::EDirection::West].push_back(std::tuple<int, int>(0, -1));
	m_AffectedPower[Enums::EDirection::South].push_back(std::tuple<int, int>(-1, 0));
	
}

Tour::~Tour()
{
}