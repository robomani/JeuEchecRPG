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
			case SDL_SCANCODE_SPACE:
			{
				m_Board->ToogleUsingPower();
				break;
			}
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_SPACE:
					m_Board->ToogleUsingPower();
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
	if (m_ChangeTurnToColor != m_ColorTurn)
	{
		m_ColorTurn = m_ChangeTurnToColor;
		m_ColorTurn == Enums::EPieceColor::Blanche ? m_Player01->ChangeManaBy(1) : m_Player02->ChangeManaBy(1);
	}
	m_Board->Update();
}