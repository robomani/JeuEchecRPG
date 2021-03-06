#include "Pion.h"
#include "Case.h"

Pion::Pion(const Enums::EPieceColor a_PieceColor, int i_HP, int i_Attack, int i_Armor)
	: Piece(a_PieceColor == Enums::EPieceColor::Blanche ? "images/WPawn" : "images/BPawn", i_HP, i_Attack, i_Armor)
{
	UpdatePiecePowerDescr();

	m_PieceType = Enums::EPieceType::Pion;
	m_PieceColor = a_PieceColor;

	for (int i = 0; i < Enums::EDirection::Direction_Count; i++)
	{
		m_PossibleAttacks.push_back(std::vector<std::tuple<int, int>>());
	}

	m_AvailableMoves[m_PieceColor == Enums::EPieceColor::Blanche ? Enums::EDirection::South : Enums::EDirection::North].push_back(std::tuple<int, int>(m_PieceColor == Enums::EPieceColor::Blanche ? -1 : 1, 0));

	if (m_PieceColor == Enums::EPieceColor::Blanche)
	{
		m_PossibleAttacks[Enums::EDirection::South_West].push_back(std::tuple<int, int>(-1, -1));
		m_PossibleAttacks[Enums::EDirection::South_East].push_back(std::tuple<int, int>(-1, 1));

	}
	else
	{
		m_PossibleAttacks[Enums::EDirection::North_West].push_back(std::tuple<int, int>(1, -1));
		m_PossibleAttacks[Enums::EDirection::North_East].push_back(std::tuple<int, int>(1, 1));
	}

	m_AffectedPower[Enums::EDirection::East].push_back(std::tuple<int, int>(0, 1));
	m_AffectedPower[Enums::EDirection::North_East].push_back(std::tuple<int, int>(1, 1));
	m_AffectedPower[Enums::EDirection::North].push_back(std::tuple<int, int>(1, 0));
	m_AffectedPower[Enums::EDirection::North_West].push_back(std::tuple<int, int>(1, -1));
	m_AffectedPower[Enums::EDirection::West].push_back(std::tuple<int, int>(0, -1));
	m_AffectedPower[Enums::EDirection::South_West].push_back(std::tuple<int, int>(-1, -1));
	m_AffectedPower[Enums::EDirection::South].push_back(std::tuple<int, int>(-1, 0));
	m_AffectedPower[Enums::EDirection::South_East].push_back(std::tuple<int, int>(-1, 1));
}

Pion::~Pion()
{
}

void Pion::UsePower()
{
	m_PowerReady = false;
}
