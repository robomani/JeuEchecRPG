#include "Board.h"
#include "Case.h"
#include "Game.h"
#include "Text.h"
#include "EPieceType.h"
#include <SDL_image.h>


const int Board::CASE_NUMBER = 8;
const int Board::CASE_WIDTH = 100;
const int Board::CASE_HEIGHT = 100;
const int Board::X_OFFSET = 100;
const int Board::Y_OFFSET = 100;

int tempx;
int tempy;

bool IsBetween(const int& i_Value, const int& i_Min, const int& i_Max);

Board::Board()
	: m_CurrentCase(nullptr)
{
	Init();
}

Board::~Board()
{
	if (m_CurrentCase != nullptr)
	{
		m_CurrentCase = nullptr;
	}

	for (std::vector<std::vector<Case*>>::iterator iter = m_Cases.begin(); iter != m_Cases.end(); iter++)
	{
		for (std::vector<Case*>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			delete (*iter2);
			(*iter2) = nullptr;
		}
		(*iter).clear();
	}
	m_Cases.clear();

	if (m_BoardTexture != nullptr)
	{
		SDL_FreeSurface(m_BoardTexture);
		m_BoardTexture = nullptr;
	}
}

void Board::Init()
{
	m_BoardTexture = IMG_Load(BOARD_TEXTURE_PATH.c_str());

	// Create all cases
	m_Cases = std::vector<std::vector<Case*>>();
	for (int i = 0; i < CASE_NUMBER; i++)
	{
		m_Cases.push_back(std::vector<Case*>());

		for (int j = 0; j < CASE_NUMBER; j++)
		{
			if (i < 2 || i > 5)
			{
				Enums::EPieceColor pieceColor = i < 2 ? Enums::EPieceColor::Noire : Enums::EPieceColor::Blanche;
				if (i == 1 || i == 6)
				{
					m_Cases[i].push_back(new Case(j * Board::CASE_WIDTH, i * Board::CASE_HEIGHT, Enums::EPieceType::Pion, pieceColor));
				}
				else if (i == 0 || i == 7)
				{
					switch (j) 
					{
					case 0:
					case 7:
						m_Cases[i].push_back(new Case(j * Board::CASE_WIDTH, i * Board::CASE_HEIGHT, Enums::EPieceType::Tour, pieceColor));
						break;
					case 1:
					case 6:
						m_Cases[i].push_back(new Case(j * Board::CASE_WIDTH, i * Board::CASE_HEIGHT, Enums::EPieceType::Chevalier, pieceColor));
						break;
					case 2:
					case 5:
						m_Cases[i].push_back(new Case(j * Board::CASE_WIDTH, i * Board::CASE_HEIGHT, Enums::EPieceType::Fou, pieceColor));
						break;
					case 3:
						m_Cases[i].push_back(new Case(j * Board::CASE_WIDTH, i * Board::CASE_HEIGHT, Enums::EPieceType::Roi, pieceColor));
						break;
					case 4:
						m_Cases[i].push_back(new Case(j * Board::CASE_WIDTH, i * Board::CASE_HEIGHT, Enums::EPieceType::Reine, pieceColor));
						break;
					}
				}
			}
			else 
			{
				m_Cases[i].push_back(new Case(j * Board::CASE_WIDTH, i * Board::CASE_HEIGHT));
			}
		}
	}
}

void Board::Draw(SDL_Surface* a_Parent)
{
	SDL_Rect r = { X_OFFSET, Y_OFFSET, CASE_WIDTH * CASE_NUMBER, CASE_HEIGHT * CASE_NUMBER };
	SDL_BlitSurface(m_BoardTexture, NULL, a_Parent, &r);

	for (std::vector<std::vector<Case*>>::const_iterator iter = m_Cases.begin(); iter != m_Cases.end(); iter++)
	{
		for (std::vector<Case*>::const_iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			if (m_CurrentCase == nullptr || (*iter2) != m_CurrentCase)
			{
				(*iter2)->Draw(a_Parent);
			}			
		}
	}

	if (m_CurrentCase != nullptr) 
	{
		m_CurrentCase->Draw(a_Parent);
	}
}

void Board::ChangeTurn()
{

}


void Board::Update()
{

}

void Board::MouseButtonDown(const int a_X, const int a_Y)
{
	int i = (a_Y - Y_OFFSET) / Board::CASE_WIDTH;
	int j = (a_X - X_OFFSET) / Board::CASE_HEIGHT;

	if (i > -1 && i < Board::CASE_NUMBER && j > -1 && j < Board::CASE_NUMBER)
	{
		Case* caseTargeted = m_Cases[i][j];
		tempx = i;
		tempy = j;
		if (caseTargeted->IsNotEmpty())
		{
			Case* caseToShowUI = m_Cases[i][j];
			std::string powerReadyText = caseToShowUI->IsPowerReady() ? "Power Ready" : "Power Not Ready";

			Text::SetText(ETextContent::PiecesStats, caseToShowUI->GetHP(), caseToShowUI->GetAttack(), caseToShowUI->GetArmor());
			Text::SetText(ETextContent::PiecesPower, caseToShowUI->GetPowerDescr());
			Text::SetText(ETextContent::PiecesPowerAvable, powerReadyText);
		}

		if (caseTargeted->IsNotEmpty() && caseTargeted->IsPieceIsThisColor(Game::GetColorTurn()))
		{
			m_CurrentCase = m_Cases[i][j];
			m_AvailableMoveForCurrentPiece = m_CurrentCase->GetAvailableMoves(m_Cases);
			m_AffectedPowerForCurrentPiece = m_CurrentCase->GetAffectedPowerCases(m_Cases);
			m_CurrentCase->Move(a_X, a_Y);
		}
	}
}

void Board::MouseMotion(const int a_X, const int a_Y)
{
	if (m_CurrentCase != nullptr) 
	{
		m_CurrentCase->Move(a_X, a_Y);
	}
}

void Board::ToogleUsingPower()
{
	if (m_UsingPower || (m_CurrentCase != nullptr && m_CurrentCase->IsPieceIsThisColor(Game::GetColorTurn()) && m_CurrentCase->IsPowerReady()))
	{
		m_UsingPower = !m_UsingPower;
	}
	if (m_CurrentCase != nullptr && m_CurrentCase->IsPieceIsThisColor(Game::GetColorTurn()) && m_CurrentCase->IsPowerReady())
	{
		m_UsingPower = !m_UsingPower;
	}

	if (m_UsingPower)
	{
		Text::SetText(ETextContent::UsingPowerMode, "Using Power");
	}
	else
	{
		Text::SetText(ETextContent::UsingPowerMode, "Not Using Power");
	}
}

void Board::MouseButtonUp(const int a_X, const int a_Y)
{
	if (m_CurrentCase != nullptr)
	{
		int i = (a_Y - Y_OFFSET) / Board::CASE_WIDTH;
		int j = (a_X - X_OFFSET) / Board::CASE_HEIGHT;
		if (i > -1 && i < Board::CASE_NUMBER && j > -1 && j < Board::CASE_NUMBER)
		{
			Case* caseTargeted = m_Cases[i][j];
			if (!m_UsingPower)
			{
				if (std::find(m_AvailableMoveForCurrentPiece.begin(), m_AvailableMoveForCurrentPiece.end(), std::tuple<int, int>(i, j)) != m_AvailableMoveForCurrentPiece.end())
				{
					// The targeted case is empty
					if (caseTargeted->IsEmpty())
					{
						caseTargeted->SwapPieceWith(m_CurrentCase);
						Game::ChangeColorTurn();
					}
					else if (caseTargeted->IsPieceIsNotThisColor(Game::GetColorTurn()))
					{
						int damage = m_CurrentCase->CurrentPieceAttack();
						caseTargeted->SwapPieceWith(m_CurrentCase);
						if (m_CurrentCase->DamageCurrentPiece(damage))
						{
							m_CurrentCase->RemovePiece();
						}
						else
						{
							caseTargeted->SwapPieceWith(m_CurrentCase);
						}
						Game::ChangeColorTurn();
					}
				}
			}
			else
			{
				switch (m_CurrentCase->GetPieceType())
				{
				case Enums::EPieceType::Pion:

					if (IsBetween(tempx + 1,0,7) && IsBetween(tempy - 1,0,7) && m_Cases[tempx + 1][tempy - 1]->IsNotEmpty())
					{
						if (m_Cases[tempx + 1][tempy - 1]->DamageCurrentPiece(m_CurrentCase->CurrentPieceAttack()))
						{
							m_Cases[tempx + 1][tempy - 1]->RemovePiece();
						}
					}
					if (IsBetween(tempx + 1, 0, 7) && m_Cases[tempx + 1][tempy]->IsNotEmpty())
					{
						if (m_Cases[tempx + 1][tempy]->DamageCurrentPiece(m_CurrentCase->CurrentPieceAttack()))
						{
							m_Cases[tempx + 1][tempy]->RemovePiece();
						}
					}
					if (IsBetween(tempx + 1, 0, 7) && IsBetween(tempy + 1, 0, 7) && m_Cases[tempx + 1][tempy + 1]->IsNotEmpty())
					{
						if (m_Cases[tempx + 1][tempy + 1]->DamageCurrentPiece(m_CurrentCase->CurrentPieceAttack()))
						{
							m_Cases[tempx + 1][tempy + 1]->RemovePiece();
						}
					}
					if (IsBetween(tempy - 1, 0, 7) && m_Cases[tempx][tempy - 1]->IsNotEmpty())
					{
						if (m_Cases[tempx][tempy - 1]->DamageCurrentPiece(m_CurrentCase->CurrentPieceAttack()))
						{
							m_Cases[tempx][tempy - 1]->RemovePiece();
						}
					}
					if (IsBetween(tempy + 1, 0, 7) && m_Cases[tempx][tempy + 1]->IsNotEmpty())
					{
						if (m_Cases[tempx][tempy + 1]->DamageCurrentPiece(m_CurrentCase->CurrentPieceAttack()))
						{
							m_Cases[tempx][tempy + 1]->RemovePiece();
						}
					}
					if (IsBetween(tempx - 1, 0, 7) && IsBetween(tempy - 1, 0, 7) && m_Cases[tempx - 1][tempy - 1]->IsNotEmpty())
					{
						if (m_Cases[tempx - 1][tempy - 1]->DamageCurrentPiece(m_CurrentCase->CurrentPieceAttack()))
						{
							m_Cases[tempx - 1][tempy - 1]->RemovePiece();
						}
					}
					if (IsBetween(tempx - 1, 0, 7) && m_Cases[tempx - 1][tempy]->IsNotEmpty())
					{
						if (m_Cases[tempx - 1][tempy]->DamageCurrentPiece(m_CurrentCase->CurrentPieceAttack()))
						{
							m_Cases[tempx - 1][tempy]->RemovePiece();
						}	
					}
					if (IsBetween(tempx - 1, 0, 7) && IsBetween(tempy + 1, 0, 7) && m_Cases[tempx - 1][tempy + 1]->IsNotEmpty())
					{
						if (m_Cases[tempx - 1][tempy + 1]->DamageCurrentPiece(m_CurrentCase->CurrentPieceAttack()))
						{
							m_Cases[tempx - 1][tempy + 1]->RemovePiece();
						}
						
					}
					if (m_Cases[tempx][tempy]->IsNotEmpty())
					{
						if (m_Cases[tempx][tempy]->DamageCurrentPiece(m_CurrentCase->CurrentPieceAttack()))
						{
							m_CurrentCase->RemovePiece();
						}
						
					}
					break;
				case Enums::EPieceType::Chevalier:
					break;
				case Enums::EPieceType::Tour:
					break;
				case Enums::EPieceType::Fou:
					break;
				case Enums::EPieceType::Reine:
					break;
				case Enums::EPieceType::Roi:
					break;
				default:
					break;
				
				}
				Game::ChangeColorTurn();
			}
		}

		m_CurrentCase->BackToOriginalPosition();
		m_CurrentCase = nullptr;
	}

	
}

bool IsBetween(const int& i_Value, const int& i_Min, const int& i_Max)
{
	if (i_Value >= i_Min && i_Value <= i_Max)
	{
		return true;
	}
	else
	{
		return false;
	}
}