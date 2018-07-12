#pragma once
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
private:

	int m_Mana = 0; //Define the base player Mana at the beggining of the game;
};