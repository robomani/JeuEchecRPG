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
		m_Texts.push_back(new TextData("Pipi patate poil", { 255, 0, 255 }, {1000, 30*i, 100, 100}));
	}
}


void Text::Destroy()
{
	TTF_CloseFont(m_Font);
}

void Text::ChangeText(int a_HP, int a_Attack, int a_Armor, bool a_IsPowerReady)
{

}

void Text::ChangeText(std::string a_NewText)
{

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