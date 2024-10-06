#pragma once


#define PIXEL_FONT_PATH "assets/PressStart2P-Regular.ttf"

#define FONT \
		([]() -> QFont { \
			int fontId = QFontDatabase::addApplicationFont(PIXEL_FONT_PATH); \
			if (fontId != -1) { \
				QString pixelFont = QFontDatabase::applicationFontFamilies(fontId).at(0); \
				return QFont(pixelFont, 10, QFont::Bold); \
			} else { \
				QFont("Arial", 15, QFont::Bold); \
			} \
		}())