#pragma once
class Player;

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	static void Init();

private:
	static Player* m_Player01; //The instance of the player01.
	static Player* m_Player02; //The instance of the player02.

};

