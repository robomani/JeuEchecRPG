#include <SDL_image.h>
#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "Text.h"
#include <iostream>

Enums::EPieceColor Game::m_ColorTurn = Enums::EPieceColor::Blanche;
Enums::EPieceColor Game::m_ChangeTurnToColor = Enums::EPieceColor::Blanche;
const int Game::SCREEN_WIDTH = 1500;
const int Game::SCREEN_HEIGHT = 1000;

Game::Game()
{
	Init();
}

Game::~Game()
{
	if (m_WindowSurface != nullptr)
	{
		SDL_FreeSurface(m_WindowSurface);
		m_WindowSurface = nullptr;
	}

	if (m_BackgroundSurface != nullptr)
	{
		SDL_FreeSurface(m_BackgroundSurface);
		m_BackgroundSurface = nullptr;
	}

	if (m_Window != nullptr)
	{
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	}

	Text::Destroy();

	TTF_Quit(); //Close the TTF.
}

void Game::Init()
{
	TTF_Init(); //Init the TTF for the game to Draw texts.

	//Init the Text
	Text::Init();

	// Init the SDL Window
	m_Window = SDL_CreateWindow("Once upon a chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	m_WindowSurface = SDL_GetWindowSurface(m_Window);
	m_BackgroundSurface = IMG_Load("./images/Background.jpg");

	m_Board = new Board();

	m_Player01 = new Player();
	m_Player02 = new Player();
}

void Game::ChangeColorTurn()
{
	m_ChangeTurnToColor = static_cast<Enums::EPieceColor>(!static_cast<bool>(m_ColorTurn));
}


void Game::Run()
{
	bool quit = false;
	while (!quit) {
		quit = Inputs();
		Draw();
		Update();
	}
}

bool Game::Inputs()
{
	SDL_Event e;
	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
		{
			return true;
		}
		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_SPACE:
			{
				m_Board->ToogleUsingPower();
				break;
			}
			case SDLK_1:
			{
				if (GetColorTurn() == Enums::Blanche && m_Player01->GetMana() >= 1)
				{
					m_Player01->Power01(*m_Board);

				}
				else if (GetColorTurn() == Enums::Noire && m_Player02->GetMana() >= 1)
				{
					m_Player02->Power01(*m_Board);
				}
				break;
			}
			case SDLK_2:
			{
				if (GetColorTurn() == Enums::Blanche && m_Player01->GetMana() >= 2)
				{
					m_Player01->Power02(*m_Board);
					UpdateMana(1);
				}
				else if (GetColorTurn() == Enums::Noire && m_Player02->GetMana() >= 2)
				{
					m_Player02->Power02(*m_Board);
					UpdateMana(2);
				}
				break;
			}
			case SDLK_3:
			{
				if (GetColorTurn() == Enums::Blanche && m_Player01->GetMana() >= 3)
				{
					m_Player01->Power03(*m_Board);
					UpdateMana(1);
				}
				else if (GetColorTurn() == Enums::Noire && m_Player02->GetMana() >= 3)
				{
					m_Player02->Power03(*m_Board);
					UpdateMana(2);
				}
				break;
			}
			case SDLK_4:
			{
				if (GetColorTurn() == Enums::Blanche && m_Player01->GetMana() >= 5)
				{
					m_Player01->Power04(*m_Board);
					UpdateMana(1);
				}
				else if (GetColorTurn() == Enums::Noire && m_Player02->GetMana() >= 5)
				{
					m_Player02->Power04(*m_Board);
					UpdateMana(2);
				}
				break;
			}
			case SDLK_5:
			{
				if (GetColorTurn() == Enums::Blanche && m_Player01->GetMana() >= 25)
				{
					m_Player01->Power05(*m_Board);
					UpdateMana(1);
				}
				else if (GetColorTurn() == Enums::Noire && m_Player02->GetMana() >= 25)
				{
					m_Player02->Power05(*m_Board);
					UpdateMana(2);
				}
				break;
			}
			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			int x = 0;
			int y = 0;
			SDL_GetMouseState(&x, &y);
			m_Board->MouseButtonDown(x, y);
			break;
		}
		case SDL_MOUSEMOTION:
		{
			int x = 0;
			int y = 0;
			SDL_GetMouseState(&x, &y);
			m_Board->MouseMotion(x, y);
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			int x = 0;
			int y = 0;
			SDL_GetMouseState(&x, &y);
			m_Board->MouseButtonUp(x, y);
			break;
		}
		default:
			break;
		}
	}

	return false;
}

void Game::Draw()
{
	SDL_UpdateWindowSurface(m_Window);
	SDL_BlitSurface(m_BackgroundSurface, NULL, m_WindowSurface, NULL);

	m_Board->Draw(m_WindowSurface);

	Text::Draw(m_WindowSurface);
}

void Game::Update()
{
	if (m_Board->IsSwitchingPieces())
	{
		Text::SetText(ETextContent::SwitchMode, "Drop The Piece On An Ally Piece To Swap Their Positions.");
	}


	if (m_ChangeTurnToColor != m_ColorTurn)
	{
		if (m_Board->IsSwitchingPieces())
		{
			m_Board->SetIsSwitchingPieces(false);
			Text::SetText(ETextContent::SwitchMode, "");
		}

		m_Board->ResetUsingPower();
		m_ColorTurn = m_ChangeTurnToColor;

		if (m_ColorTurn == Enums::EPieceColor::Blanche)
		{
			if (m_Board->IsSwitchSuccessfull())
			{
				m_Player02->ChangeManaBy(-5);
				m_Board->SetIsSwitchSuccessfull(false);
			}
			m_Player01->ChangeManaBy(1);
			m_Player01->ChangePowerTexts();
		}
		else
		{
			if (m_Board->IsSwitchSuccessfull())
			{
				m_Player01->ChangeManaBy(-5);
				m_Board->SetIsSwitchSuccessfull(false);
			}
			m_Player02->ChangeManaBy(1);
			m_Player02->ChangePowerTexts();
		}

		UpdateMana(1);
		UpdateMana(2);
	}

	m_Board->Update();
}

void Game::UpdateMana(int a_Player)
{
	if (a_Player == 1)
	{
		Text::SetText(ETextContent::Player01Mana, "Mana: " + std::to_string(m_Player01->GetMana()));
	}
	else
	{
		Text::SetText(ETextContent::Player02Mana, "Mana: " + std::to_string(m_Player02->GetMana()));
	}
}