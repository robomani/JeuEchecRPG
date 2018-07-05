#include "Game.h"
#include "Board.h"
#include <iostream>

Enums::EPieceColor Game::m_ColorTurn = Enums::EPieceColor::Blanche;
const int Game::SCREEN_WIDTH = 1000;
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

	if (m_Window != nullptr)
	{
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	}

	TTF_CloseFont(m_Font);
	TTF_Quit();
}

void Game::Init()
{
	// Init the SDL Window
	m_Window = SDL_CreateWindow("Once upon a chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	m_WindowSurface = SDL_GetWindowSurface(m_Window);

	//Init the TTF
	TTF_Init();
	m_Renderer = SDL_CreateRenderer(m_Window, 0, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	m_Font = TTF_OpenFont("./times.ttf", 24);
	m_TextColor = { 255, 0, 255 };
	m_TextRect = { 810, 0, 100, 100 };

	m_Board = new Board();
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

	m_Board->Draw(m_WindowSurface);

	SDL_Surface* textSurface = TTF_RenderText_Solid(m_Font, "Pipi Patate Poil", m_TextColor);
	SDL_BlitSurface(textSurface, NULL, m_WindowSurface, &m_TextRect);
	SDL_FreeSurface(textSurface);
}

void Game::Update()
{
	m_Board->Update();
}