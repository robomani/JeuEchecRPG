#ifndef __BOARD__
#define __BOARD__

#include <string>
#include <SDL.h>
#include <vector>

class Case;

class Board
{
public:
	static const int CASE_NUMBER;  // The number of cases on the board
	static const int CASE_WIDTH;   // The case's width
	static const int CASE_HEIGHT;  // The case's height
	static const int X_OFFSET;
	static const int Y_OFFSET;

	int tempx;
	int tempy;


	
	/// <summary>
	/// Initializes a new instance of the <see cref="Board"/> class.
	/// </summary>
	Board();
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Board"/> class.
	/// </summary>
	~Board();
	
	/// <summary>
	/// Get The Current Selected Case.
	/// </summary>
	/// <returns>The current case selected.</returns>
	Case* GetCurrentCase() { return m_CurrentCase; }  // The current case clicked

	/// <summary>
	/// Get if the player is trying to switch pieces.
	/// </summary>
	/// <returns>
	///   <c>true</c> if the player is trying to switch pieces; otherwise, <c>false</c>.
	/// </returns>
	bool IsSwitchingPieces() { return m_IsSwitchingPieces; }

	/// <summary>
	/// Set the bool value of IsSwitchingPieces.
	/// </summary>
	/// <param name="a_Value">The bool value to set IsSwitchingPieces</param>
	void SetIsSwitchingPieces(bool a_Value) { m_IsSwitchingPieces = a_Value; }

	/// <summary>
	/// Get if the player has successfully done the switch of two pieces.
	/// </summary>
	/// <returns>
	///   <c>true</c> if the player has successfully done the switch of two pieces; otherwise, <c>false</c>.
	/// </returns>
	bool IsSwitchSuccessfull() { return m_IsSwitchSuccessfull; }

	/// <summary>
	/// Set the bool value of IsSwitchSuccessfull.
	/// </summary>
	/// <param name="a_Value">The bool value to set IsSwitchSuccessfull</param>
	void SetIsSwitchSuccessfull(bool a_Value) { m_IsSwitchSuccessfull = a_Value; }

	/// <summary>
	/// Draws all the cases on the board.
	/// </summary>
	/// <param name="a_Parent">The SDL Surface where to draw</param>
	void Draw(SDL_Surface* a_Parent);
	
	/// <summary>
	/// Call Change Turn On Tiles.
	/// </summary>
	void ChangeTurn();

	/// <summary>
	/// Updates this instance.
	/// </summary>
	void Update();

	/// <summary>
	/// Kill all ennemies pieces.
	/// </summary>
	void DestroAllEnnemies();
	
	/// <summary>
	/// When the left button is pressed on the mouse.
	/// </summary>
	/// <param name="a_X">The X coordinate</param>
	/// <param name="a_Y">The Y coordinate</param>
	void MouseButtonDown(const int a_X, const int a_Y);
	
	/// <summary>
	/// When the mouse move.
	/// </summary>
	/// <param name="a_X">The X coordinate</param>
	/// <param name="a_Y">The Y coordinate</param>
	void MouseMotion(const int a_X, const int a_Y);
	
	/// <summary>
	/// When the left button is release on the mouse.
	/// </summary>
	/// <param name="a_X">The X coordinate</param>
	/// <param name="a_Y">The Y coordinate</param>
	void MouseButtonUp(const int a_X, const int a_Y);

	/// <summary>
	/// Get The Current Selected Case.
	/// </summary>
	/// <returns>The current case selected.</returns>
	Case* GetTransportingCase() { return m_TransportingCase; }  // The current case clicked

	//Toggle if a piece is using it's power
	void ToogleUsingPower();

	void ResetUsingPower();

private:

	const std::string BOARD_TEXTURE_PATH = "images/Board.png";  // The path of the board's texture.
	
	/// <summary>
	/// Initializes this instance.
	/// </summary>
	void Init();

	//Bool remembering if selected piece is using its power
	bool m_UsingPower;

	//True if the player is trying to switch two of his pieces.
	bool m_IsSwitchingPieces = false;
	//True if the player has successfully done the switch of two pieces.
	bool m_IsSwitchSuccessfull = false;
	

	SDL_Surface* m_BoardTexture;   // The SDL Surface that contain the texture loaded.
	std::vector<std::vector<Case*>> m_Cases;  // All the cases of the board.
	Case* m_CurrentCase;  // The current case clicked
	Case* m_TransportingCase;  // The current case clicked

	std::vector<std::tuple<int, int>> m_AvailableMoveForCurrentPiece;  // Available moves for the piece clicked.
	std::vector<std::tuple<int, int>> m_AffectedPowerForCurrentPiece;  // Cases affected by the power for the piece clicked.
};

#endif // __BOARD__