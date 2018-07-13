#include "Text.h"
#include "ETextContent.h"

std::vector<Text::TextData*> Text::m_Texts = std::vector<TextData*>(); //The texts.

TTF_Font* Text::m_Font = nullptr;

void Text::Init()
{
	//Init the TTF
	TTF_Init();
	m_Font = TTF_OpenFont("./times.ttf", 24); //Set the text font.

	for (int i = 0; i < ETextContent::Count; i++)
	{
		switch (i)
		{
			case ETextContent::PiecesStats:
			{
				m_Texts.push_back(new TextData("Les Stats de la piece selectionnee apparait ici", { 255, 0, 255 }, { 1000, 275, 100, 100 }));
				break;
			}
		case ETextContent::PiecesPower:
			{
				m_Texts.push_back(new TextData("Le powerup de la piece selectionnee apparait ici", { 255, 0, 255 }, { 1000, 300, 100, 100 }));
				break;
			}
		case ETextContent::PiecesPowerAvable:
			{
				m_Texts.push_back(new TextData("Powerup Ready / Already Used Appear Here", { 255, 0, 255 }, {1000, 325, 100, 100}));
				break;
			}
		case ETextContent::Player01Mana:
			{
				m_Texts.push_back(new TextData("Mana: 01", { 255, 0, 255 }, { 0, 350, 100, 100 }));
				break;
			}		
		case ETextContent::Player02Mana:
			{
				m_Texts.push_back(new TextData("Mana: 02", { 255, 0, 255 }, { 0, 650, 100, 100 }));
				break;
			}
		case ETextContent::PlayerPower01:
			{
				m_Texts.push_back(new TextData("Le powerup01 du joueur apparait ici", { 0, 255, 0 }, { 1000, 800, 100, 100 }));
				break;
			}		
		case ETextContent::PlayerPower02:
			{
				m_Texts.push_back(new TextData("Le powerup02 du joueur apparait ici", { 0, 255, 0 }, { 1000, 825, 100, 100 }));
				break;
			}
		case ETextContent::PlayerPower03:
			{
				m_Texts.push_back(new TextData("Le powerup03 du joueur apparait ici", { 0, 255, 0 }, { 1000, 850, 100, 100 }));
				break;
			}
		case ETextContent::PlayerPower04:
			{
				m_Texts.push_back(new TextData("Le powerup04 du joueur apparait ici", { 255, 0, 0 }, { 1000, 875, 100, 100 }));
				break;
			}
		case ETextContent::PlayerPower05:
			{
				m_Texts.push_back(new TextData("Le powerup05 du joueur apparait ici", { 255, 0, 0 }, { 1000, 900, 100, 100 }));
				break;
			}
		case ETextContent::UsingPowerMode:
		{
			m_Texts.push_back(new TextData("Saying if the player is Using Power for the piece he hold", { 255, 0, 0 }, { 1000, 350, 100, 100 }));
			break;
		}
		}
	}
}


void Text::Destroy()
{
	TTF_CloseFont(m_Font);
}

void Text::SetText(ETextContent a_TextData, int a_HP, int a_Attack, int a_Armor)
{
	m_Texts[a_TextData]->text = "HP: " + std::to_string(a_HP) + " Atk: " + std::to_string(a_Attack) + " Armor: " + std::to_string(a_Armor);
}

void Text::SetText(ETextContent a_TextData, std::string a_NewText)
{
	m_Texts[a_TextData]->text = a_NewText;
}

void Text::SetRect(ETextContent a_TextData, int a_PosX, int a_PosY, int a_Width, int a_Height)
{
	SDL_Rect newRect = { a_PosX, a_PosY, a_Width, a_Height };
	m_Texts[a_TextData]->rect = newRect;
}

void Text::SetColor(ETextContent a_TextData, int a_R, int a_G, int a_B)
{
	SDL_Color newColor = { a_R, a_G, a_B };
	m_Texts[a_TextData]->color = newColor;
}

void Text::Draw(SDL_Surface* a_Parent)
{
	for (int i = 0; i < m_Texts.size(); i++)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(m_Font, m_Texts[i]->text.c_str(), m_Texts[i]->color);
		SDL_BlitSurface(textSurface, NULL, a_Parent, &m_Texts[i]->rect);
		SDL_FreeSurface(textSurface);
	}
}