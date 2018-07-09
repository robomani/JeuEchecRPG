#pragma once
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
	/// Upade the piece Text shown in the game.
	/// </summary>
	/// <param name="a_HP">The HP of the piece</param>
	/// <param name="a_Attack">The Attack of the piece</param>
	/// <param name="a_Armor">The Armor of the piece</param>
	/// <param name="a_IsPowerReady">True if the piece can use its Power ability, else false.</param>
	static void ChangeText(int a_HP, int a_Attack, int a_Armor, bool a_IsPowerReady);
	static void Text::ChangeText(std::string a_NewText);

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

