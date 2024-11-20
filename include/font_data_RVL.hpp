/*!
	@file font_data_RVL.hpp
	@brief font data file. Project Name: ST7789_TFT_RPI
	@author Gavin Lyons.
	@details
		-#  pFontDefault  6 by 8
		-#  pFontPico 3 by 6
		-#  pFontSevenSeg 5 by 8 (NUMBERS ONLY + : . -)
		-#  pFontThick  8 by 8 (NO LOWERCASE letters)
		-#  pFontWide  9 by 8 (NO LOWERCASE letters)
		-#  pFontSinclairS 8 by 8
		-#  pFontOrla 8x12
		-#  pFontRetro 8x16
		-#  pFontMega  16 by 16
		-#  pFontArialBold 16 by 16
		-#  pFontHallfetica 16 by 16
		-#  pFontArialRound 16 by 24
		-#  pFontGroTesk 16 by 32
		-#  pFontMint 24 by 32
		-#  pFontSixteenSeg 32 by 48 (NUMBERS ONLY + : . -)
*/

#pragma once

#include <cstdint>
#include <cstdio>
#include "common_data_RVL.hpp" //error enum

// Font data is in the cpp file accessed thru extern pointers.
extern const uint8_t * pFontDefault;
extern const uint8_t * pFontPico;
extern const uint8_t * pFontSevenSeg;
extern const uint8_t * pFontThick;
extern const uint8_t * pFontWide;
extern const uint8_t * pFontSinclairS;
extern const uint8_t * pFontRetro;
extern const uint8_t * pFontMega;
extern const uint8_t * pFontArialBold;
extern const uint8_t * pFontHallfetica;
extern const uint8_t * pFontOrla;
extern const uint8_t * pFontArialRound;
extern const uint8_t * pFontGroTesk;
extern const uint8_t * pFontMint;
extern const uint8_t * pFontSixteenSeg;


/*! Enum to define current font type selected  */
enum display_Font_name_e : uint8_t
{
	font_default = 1,     /**< default 6by8  (FUll ASCII with mods) */
	font_pico = 2,        /**< Pico 3by6 */
	font_sevenSeg = 3,    /**< Seven Segment 6by8 (NUMBERS ONLY + : . -) */
	font_thick = 4,       /**< Thick 8by8 (NO LOWERCASE) */
	font_wide = 5,        /**< wide 9by8 (NO LOWERCASE) */
	font_sinclairS = 6,   /**< Sinclair 8by8 */
	font_retro = 7,       /**< Retro 8x16 */
	font_mega = 8,        /**< Mega 16by16 */
	font_arialBold = 9,   /**< Arial bold 16by16 */
	font_hallfetica = 10, /**< Hallfetica 16by16 */
	font_orla = 11,       /**< Orla 16by24 */
	font_arialRound = 12, /**< ArialRound 16by24 */
	font_groTesk = 13,    /**< GroTesk 16by32 */
	font_mint = 14,       /**< Mint 24by32 */
	font_sixteenSeg = 15  /**< Sixteen Segment 32by48 (NUMBERS ONLY + : . -) */
};

/*! @brief Font class to hold font data object  */
class display_Fonts
{
	public:
		display_Fonts();
		~display_Fonts(){};
		
		rvlDisplay_Return_Codes_e setFont(display_Font_name_e);
		void setInvertFont(bool invertStatus);
		bool getInvertFont(void);

	protected:
		const uint8_t *_FontSelect = pFontDefault; /**< Pointer to the active font,  Fonts Stored are Const */
		uint8_t _Font_X_Size = 0x06; /**< Width Size of a Font character */
		uint8_t _Font_Y_Size = 0x08; /**< Height Size of a Font character */
		uint8_t _FontOffset = 0x00; /**< Offset in the ASCII table 0x00 to 0xFF, where font begins */
		uint8_t _FontNumChars = 0xFE; /**< Number of characters in font 0x00 to 0xFE */
	private:
		bool _FontInverted = false; /**< Is the font inverted , False = normal , true = inverted*/
};


