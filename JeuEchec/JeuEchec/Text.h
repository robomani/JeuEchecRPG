#pragma once
#include "ETextContent.h"
#include <SDL_ttf.h>
#include <string>
#include <vector>

static class Text
{
public:

	/// <summary>
	/// Initialise the Text.
	/// </summary>
	static void Init();

	/// <summary>
	/// Clear the Text Pointer from the pile.
	/// </summary>
	static void Destroy();

	/// <summary>
	/// Change the Text shown in the game.
	/// </summary>
	/// <param name="a_TextData">The TextData To Modify.</param>
	/// <param name="a_HP">The HP of the piece</param>
	/// <param name="a_Attack">The Attack of the piece</param>
	/// <param name="a_Armor">The Armor of the piece</param>
	static void SetText(ETextContent a_TextData, int a_HP, int a_Attack, int a_Armor);

	/// <summary>
	/// Change the Text shown in the game.
	/// </summary>
	/// <param name="a_TextData">The TextData To Modify.</param>
	/// <param name="a_NewText">The new text that will be shown in the screen</param>
	static void SetText(ETextContent a_TextData, std::string a_NewText);

	/// <summary>
	/// Change the Text Rect.
	/// </summary>
	/// <param name="a_TextData">The TextData To Modify.</param>
	/// <param name="a_PosX">The Position in X axis of the Text Rect in Pixels</param>
	/// <param name="a_PosY">The Position in Y axis of the Text Rect in Pixels</param>
	/// <param name="a_Width">The Width (X axis) of the Text Rect in Pixels</param>
	/// <param name="a_Height">The Height (Y axis) of the Text Rect in Pixels</param>
	static void SetRect(ETextContent a_TextData, int a_PosX, int a_PosY, int a_Width, int a_Height);

	/// <summary>
	/// Change the Text Color.
	/// </summary>
	/// <param name="a_TextData">The TextData To Modify</param>
	/// <param name="a_R">The Amount of Red in The Text Color</param>
	/// <param name="a_G">The Amount of Green in The Text Color</param>
	/// <param name="a_B">The Amount of Blue in The Text Color</param>
	static void SetColor(ETextContent a_TextData, int a_R, int a_G, int a_B);

	/// <summary>
	/// Change the Text Color.
	/// </summary>
	/// <param name="a_TextData">The TextData To Modify</param>
	/// <param name="a_SDLColor">The SDL_Color The Text will be set</param>
	static void SetColor(ETextContent a_TextData, SDL_Color& a_SDLColor);

	/// <summary>
	/// Draws the text's texture
	/// </summary>	
	/// <param name="a_Parent">The parent to draw in</param>
	static void Draw(SDL_Surface* a_Parent);

private:

	static struct TextData
	{
		TextData(std::string a_Text, SDL_Color a_Color, SDL_Rect a_Rect)
		{
			text = a_Text;
			color = a_Color;
			rect = a_Rect;
		}

		std::string text; //The text text.
		SDL_Color color; //The text color.
		SDL_Rect rect; //The text rect, where the text will be.
	};

	static std::vector<TextData*> m_Texts; //The texts.

	static TTF_Font* m_Font; //The text font style.
};

