#ifndef __GAME__
#define __GAME__

#include "EPieceColor.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Board;
class Player;

class Game
{
public:
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Game"/> class.
	/// </summary>
	Game();
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Game"/> class.
	/// </summary>
	~Game();
	
	/// <summary>
	/// Runs this instance. This is the game loop.
	/// </summary>
	void Run();
	
	/// <summary>
	/// Changes the color turn and Call ChangeTurn on the board.
	/// </summary>
	static void ChangeColorTurn();
	
	/// <summary>
	/// Gets the color turn.
	/// </summary>
	/// <returns> the current turn color, enum (black or white)</returns>
	static Enums::EPieceColor GetColorTurn() { return m_ColorTurn; }

	/// <summary>
	/// Called when the king his dead. Set the Winner Color.
	/// </summary>
	/// <param name="a_Color">The Color of the died king</param>
	static void OnKingDead(Enums::EPieceColor a_Color);

private:
	
	static const int SCREEN_WIDTH;  // Define the width of the screen
	static const int SCREEN_HEIGHT; // Define the height of the screen

	static Enums::EPieceColor m_ColorTurn; // The color to play

	/// <summary>
	/// The color of the player who just winned the game.
	/// </summary>
	static Enums::EPieceColor m_WinnerColor;

	/// <summary>
	/// The color of the player who just winned the game.
	/// </summary>
	static std::string m_WinnerColorText;
	
	/// <summary>
	/// Initializes this instance.
	/// </summary>
	void Init();
	
	/// <summary>
	/// Handle all the inputs from the SDL pollEvent function.
	/// </summary>
	/// <returns>True if the user want to quit.</returns>
	bool Inputs();
	
	/// <summary>
	/// Call the draw on every cases and every texts.
	/// </summary>
	void Draw();
	
	/// <summary>
	/// Call the update on every cases.
	/// </summary>
	void Update();

	/// <summary>
	/// Update the player mana text.
	/// </summary>
	/// <param name="a_Player">The Player To Update The Mana 1 = player 01 Mana Text, Any other nbr Will update the Player 02 Mana text</param>
	void UpdateMana(int a_Player);


	SDL_Window* m_Window;	// The SDL window itself
	SDL_Surface* m_WindowSurface;  // The surface of the SDL window
	SDL_Surface* m_BackgroundSurface;  // The surface of the background

	Board* m_Board;  // The instance of the board.

	Player* m_Player01; //The instance of the player01.
	Player* m_Player02; //The instance of the player02.

	static Enums::EPieceColor m_ChangeTurnToColor;
};

#endif // __GAME__