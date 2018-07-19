#pragma once
#include "Board.h"

class Player
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="Player"/> class.
	/// </summary>
	Player();

	/// <summary>
	/// Finalizes an instance of the <see cref="Player"/> class.
	/// </summary>
	~Player();

	/// <summary>
	/// Gets the actual Player Mana.
	/// </summary>
	/// <returns>The int value of the actual player Mana.</returns>
	int GetMana() { return m_Mana; }

	/// <summary>
	/// Change the Players Mana value by an addition of a int value. 
	/// </summary>
	/// <param name="a_Value">The value to add to the Mana</param>
	void ChangeManaBy(int a_Value);

	/// <summary>
	/// Change the Players Powers Texts color. red = unavailable, green = available.
	/// </summary>
	void ChangePowerTexts();

	/// <summary>
	/// End The Player Turn.
	/// </summary>
	/// <param name="a_Board">The instance of the game board</param>
	void Power01(Board& a_Board);

	/// <summary>
	/// The Next Ally Selected Piece Will Have his Power Reseted.
	/// </summary>
	/// <param name="a_Board">The instance of the game board</param>
	void Power02(Board& a_Board);

	/// <summary>
	/// The Next Ally Selected Piece Will Gain 2 HP And 2 Attack.
	/// </summary>
	/// <param name="a_Board">The instance of the game board</param>
	void Power03(Board& a_Board);

	/// <summary>
	/// Drag And Drop An Ally Piece on a second ally piece to switch their positions. 
	/// </summary>
	/// <param name="a_Board">The instance of the game board</param>
	void Power04(Board& a_Board);

	/// <summary>
	/// Called By the Board When The Power04 is Accomplished. 
	/// </summary>
	/// <param name="a_Board">The instance of the game board</param>
	void OnSwitchDone(Board& a_Board);

	/// <summary>
	/// Win The Game.
	/// </summary>
	/// <param name="a_Board">The instance of the game board</param>
	void Power05(Board& a_Board);
private:

	int m_Mana = 0; //Define the base player Mana at the beggining of the game;
};