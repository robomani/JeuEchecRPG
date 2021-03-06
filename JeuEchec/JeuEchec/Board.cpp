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

	if (m_TransportingCase != nullptr)
	{
		m_TransportingCase = nullptr;
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
	Text::SetText(ETextContent::UsingPowerMode, "Not Using Power");

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

void Board::DestroAllEnnemies()
{
	for (int i = 0; i < m_Cases.size(); i++)
	{
		for (int x = 0; x < m_Cases[i].size(); x++)
		{
			if (m_Cases[i][x]->IsNotEmpty()
			&& m_Cases[i][x]->IsPieceIsNotThisColor(Game::GetColorTurn()))
			{
				m_Cases[i][x]->RemovePiece();
			}
		}
	}
}

void Board::MouseButtonDown(const int a_X, const int a_Y)
{
	int i = (a_Y - Y_OFFSET) / Board::CASE_WIDTH;
	int j = (a_X - X_OFFSET) / Board::CASE_HEIGHT;

	if (i > -1 && i < Board::CASE_NUMBER && j > -1 && j < Board::CASE_NUMBER)
	{
		Case* caseTargeted = m_Cases[i][j];

		if (caseTargeted->IsNotEmpty())
		{
			tempx = i;
			tempy = j;
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



			for (int i = 0; i < m_Cases.size(); i++)
			{
				for (int x = 0; x < m_Cases[i].size(); x++)
				{
					if (std::find(m_AvailableMoveForCurrentPiece.begin(), m_AvailableMoveForCurrentPiece.end(), std::tuple<int, int>(i, x)) != m_AvailableMoveForCurrentPiece.end())
					{
						m_Cases[i][x]->ColorGreen();
					}
					if (std::find(m_AffectedPowerForCurrentPiece.begin(), m_AffectedPowerForCurrentPiece.end(), std::tuple<int, int>(i, x)) != m_AffectedPowerForCurrentPiece.end())
					{
						m_Cases[i][x]->ColorBlue();
					}
				}
			}
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
	if (m_TransportingCase != nullptr)
	{
		m_TransportingCase->ClearColor();
		m_TransportingCase = nullptr;
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

void Board::ResetUsingPower()
{
	 m_UsingPower = false; 
	 if (m_TransportingCase != nullptr)
	 {
		 m_TransportingCase->ClearColor();
		 m_TransportingCase = nullptr;
	 }
	Text::SetText(ETextContent::UsingPowerMode, "Not Using Power");	 
}

void Board::MouseButtonUp(const int a_X, const int a_Y)
{
	if (m_CurrentCase != nullptr)
	{
		for (int i = 0; i < m_Cases.size(); i++)
		{
			for (int x = 0; x < m_Cases[i].size(); x++)
			{
				m_Cases[x][i]->ClearColor();
			}
		}

		int i = (a_Y - Y_OFFSET) / Board::CASE_WIDTH;
		int j = (a_X - X_OFFSET) / Board::CASE_HEIGHT;
		if (i > -1 && i < Board::CASE_NUMBER && j > -1 && j < Board::CASE_NUMBER)
		{
			Case* caseTargeted = m_Cases[i][j];
			if (!m_UsingPower)
			{
				if (m_IsSwitchingPieces
				&& caseTargeted->IsNotEmpty()
				&& caseTargeted->IsPieceIsThisColor(Game::GetColorTurn())
				&& m_CurrentCase != caseTargeted)
				{
					m_IsSwitchingPieces = false;
					m_IsSwitchSuccessfull = true;
					caseTargeted->SwapPieceWith(m_CurrentCase);
					Game::ChangeColorTurn();
				}

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
						m_CurrentCase->UsePower();
						if (m_Cases[tempx][tempy]->DamageCurrentPiece(m_CurrentCase->CurrentPieceAttack()))
						{
							m_CurrentCase->RemovePiece();
						}
						
					}
					Game::ChangeColorTurn();
					break;
				case Enums::EPieceType::Chevalier:
					if (m_TransportingCase == nullptr)
					{
						if (std::find(m_AffectedPowerForCurrentPiece.begin(), m_AffectedPowerForCurrentPiece.end(), std::tuple<int, int>(i, j)) != m_AffectedPowerForCurrentPiece.end())
						{
							// The targeted case is empty
							if (caseTargeted->IsEmpty())
							{

							}
							else if (caseTargeted->IsNotEmpty())
							{
								m_TransportingCase = caseTargeted;
								m_TransportingCase->ColorBlue();
							}
						}
					}
					else
					{
						if (std::find(m_AvailableMoveForCurrentPiece.begin(), m_AvailableMoveForCurrentPiece.end(), std::tuple<int, int>(i, j)) != m_AvailableMoveForCurrentPiece.end())
						{
							// The targeted case is empty
							if (caseTargeted->IsEmpty())
							{
								m_CurrentCase->UsePower();
								m_TransportingCase->ClearColor();
								caseTargeted->SwapPieceWith(m_TransportingCase);
								m_TransportingCase = nullptr;
								Game::ChangeColorTurn();
							}

						}
					}
					break;
				case Enums::EPieceType::Tour:
					if (std::find(m_AffectedPowerForCurrentPiece.begin(), m_AffectedPowerForCurrentPiece.end(), std::tuple<int, int>(i, j)) != m_AffectedPowerForCurrentPiece.end())
					{
						// The targeted case is empty
						if (caseTargeted->IsEmpty())
						{
							caseTargeted->SwapPieceWith(m_CurrentCase);
						}
						else if (caseTargeted->IsPieceIsNotThisColor(Game::GetColorTurn()))
						{
							m_CurrentCase->UsePower();
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
							ResetUsingPower();
						}
					}
					break;
				case Enums::EPieceType::Fou:
					if (std::find(m_AffectedPowerForCurrentPiece.begin(), m_AffectedPowerForCurrentPiece.end(), std::tuple<int, int>(i, j)) != m_AffectedPowerForCurrentPiece.end())
					{
						// The targeted case is empty
						if (caseTargeted->IsEmpty())
						{

						}
						else if (caseTargeted->IsPieceIsNotThisColor(Game::GetColorTurn()))
						{
							m_CurrentCase->UsePower();
							Enums::EPieceType temp = caseTargeted->GetPieceType();
							caseTargeted->RemovePiece();
							caseTargeted->CreatePiece(temp, m_CurrentCase->GetPieceColor());
							Game::ChangeColorTurn();
						}
					}


					break;
				case Enums::EPieceType::Reine:
					if (m_CurrentCase->GetPieceColor() == Enums::EPieceColor::Blanche)
					{
						if (IsBetween(tempx - 1, 0, 7) && IsBetween(tempy - 1, 0, 7) && m_Cases[tempx - 1][tempy - 1]->IsEmpty())
						{
							m_Cases[tempx - 1][tempy - 1]->CreatePiece(Enums::EPieceType::Pion, m_CurrentCase->GetPieceColor());
							m_CurrentCase->UsePower();
						}
						if (IsBetween(tempx - 1, 0, 7) && m_Cases[tempx - 1][tempy]->IsEmpty())
						{
							m_Cases[tempx - 1][tempy]->CreatePiece(Enums::EPieceType::Pion, m_CurrentCase->GetPieceColor());
							m_CurrentCase->UsePower();
						}
						if (IsBetween(tempx - 1, 0, 7) && IsBetween(tempy + 1, 0, 7) && m_Cases[tempx - 1][tempy + 1]->IsEmpty())
						{
							m_Cases[tempx - 1][tempy + 1]->CreatePiece(Enums::EPieceType::Pion, m_CurrentCase->GetPieceColor());
							m_CurrentCase->UsePower();
						}
						Game::ChangeColorTurn();
					}
					else
					{
						if (IsBetween(tempx + 1, 0, 7) && IsBetween(tempy + 1, 0, 7) && m_Cases[tempx + 1][tempy - 1]->IsEmpty())
						{
							m_Cases[tempx + 1][tempy - 1]->CreatePiece(Enums::EPieceType::Pion, m_CurrentCase->GetPieceColor());
							m_CurrentCase->UsePower();
						}
						if (IsBetween(tempx + 1, 0, 7) && m_Cases[tempx + 1][tempy]->IsEmpty())
						{
							m_Cases[tempx + 1][tempy]->CreatePiece(Enums::EPieceType::Pion, m_CurrentCase->GetPieceColor());
							m_CurrentCase->UsePower();
						}
						if (IsBetween(tempx + 1, 0, 7) && IsBetween(tempy + 1, 0, 7) && m_Cases[tempx + 1][tempy + 1]->IsEmpty())
						{
							m_Cases[tempx + 1][tempy + 1]->CreatePiece(Enums::EPieceType::Pion, m_CurrentCase->GetPieceColor());
							m_CurrentCase->UsePower();
						}
						Game::ChangeColorTurn();
					}
					
					break;
				case Enums::EPieceType::Roi:
					if (std::find(m_AffectedPowerForCurrentPiece.begin(), m_AffectedPowerForCurrentPiece.end(), std::tuple<int, int>(i, j)) != m_AffectedPowerForCurrentPiece.end())
					{
						// The targeted case is empty
						if (caseTargeted->IsEmpty())
						{

						}
						else if (caseTargeted->IsPieceIsThisColor(Game::GetColorTurn()))
						{
							m_CurrentCase->UsePower();
							m_CurrentCase->EatPiece(caseTargeted->GetHP(), caseTargeted->GetAttack(), caseTargeted->GetArmor(), caseTargeted->IsPowerReady());
							caseTargeted->SwapPieceWith(m_CurrentCase);
							m_CurrentCase->RemovePiece();
							Game::ChangeColorTurn();
						}
					}
					else
					{
						
					}
					break;
				default:
					break;
				
				}
				//Game::ChangeColorTurn();
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