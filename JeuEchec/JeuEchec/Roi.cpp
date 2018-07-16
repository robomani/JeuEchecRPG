#include "Roi.h"

Roi::Roi(const Enums::EPieceColor a_PieceColor, int i_HP, int i_Attack, int i_Armor)
	: Piece(a_PieceColor == Enums::EPieceColor::Blanche ? "images/WKing" : "images/BKing", i_HP, i_Attack, i_Armor)
{
	Piece::m_PowerupDescr = "Can Absorb All Stats From a Ally Around Him.";

	m_PieceType = Enums::EPieceType::Roi;
	m_PieceColor = a_PieceColor;

	m_AvailableMoves[Enums::EDirection::East].push_back(std::tuple<int, int>(0, 1));
	m_AvailableMoves[Enums::EDirection::North_East].push_back(std::tuple<int, int>(1, 1));
	m_AvailableMoves[Enums::EDirection::North].push_back(std::tuple<int, int>(1, 0));
	m_AvailableMoves[Enums::EDirection::North_West].push_back(std::tuple<int, int>(1, -1));
	m_AvailableMoves[Enums::EDirection::West].push_back(std::tuple<int, int>(0, -1));
	m_AvailableMoves[Enums::EDirection::South_West].push_back(std::tuple<int, int>(-1, -1));
	m_AvailableMoves[Enums::EDirection::South].push_back(std::tuple<int, int>(-1, 0));

	m_AffectedPower[Enums::EDirection::East].push_back(std::tuple<int, int>(0, 1));
	m_AffectedPower[Enums::EDirection::North_East].push_back(std::tuple<int, int>(1, 1));
	m_AffectedPower[Enums::EDirection::North].push_back(std::tuple<int, int>(1, 0));
	m_AffectedPower[Enums::EDirection::North_West].push_back(std::tuple<int, int>(1, -1));
	m_AffectedPower[Enums::EDirection::West].push_back(std::tuple<int, int>(0, -1));
	m_AffectedPower[Enums::EDirection::South_West].push_back(std::tuple<int, int>(-1, -1));
	m_AffectedPower[Enums::EDirection::South].push_back(std::tuple<int, int>(-1, 0));
	m_AffectedPower[Enums::EDirection::South_East].push_back(std::tuple<int, int>(-1, 1));
}

Roi::~Roi()
{
}