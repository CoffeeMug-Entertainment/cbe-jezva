#ifndef CB_COLOUR
#define CB_COLOUR

#ifdef SDL_h_ //TODO fhomolka 08/08/2021 -> Check if SDL defines something else 
#ifdef _WIN32
#include "SDL_pixels.h"
#else 
#include "SDL2/SDL_pixels.h"
#endif
#endif

#include <algorithm>

namespace CB
{
	static const int RGB8_MAX = 255;
	struct RGBA
	{
		float red;
		float green;
		float blue;
		float alpha;

		//Prefix - negative of the image
		RGBA operator-()
		{
			return {1.0f - this->red, 1.0f - this->green, 1.0f - this->blue, this->alpha};
		}

		//Read in from HSV
		/*
		//fhomolka 08/08/2021 -> Yeah, ordering and all that, this needs to be rethinked
		RGBA& operator=(const HSV& rhs)
		{
			*this = rhs.toRGBA();
			return *this;
		}
		*/

		RGBA negative()
		{
			return -(*this);
		}

		void FromRGBA8(int r, int g, int b, int a)
		{
			this->red =  std::clamp((float)r / RGB8_MAX, 0.0f, 1.0f);
			this->green = std::clamp((float)g / RGB8_MAX, 0.0f, 1.0f);
			this->blue = std::clamp((float)b / RGB8_MAX, 0.0f, 1.0f);
			this->alpha = std::clamp((float)a / RGB8_MAX, 0.0f, 1.0f);
		}

		//Compatibility stuff
		#ifdef SDL_h_
		SDL_Color ToSDLColor()
		{
			return SDL_Color{static_cast<uint8_t>(this->red * RGB8_MAX), static_cast<uint8_t>(this->green * RGB8_MAX), static_cast<uint8_t>(this->blue * RGB8_MAX), static_cast<uint8_t>(this->alpha * RGB8_MAX)};
		}

		RGBA& operator=(const SDL_Color& rhs)
		{
			this->red = rhs.r / RGB8_MAX;
			this->green = rhs.g / RGB8_MAX;
			this->blue = rhs.b / RGB8_MAX;
			this->alpha = rhs.a / RGB8_MAX;
			return *this;
		}
		#endif

		#ifdef SFML_COLOR_HPP
		//TODO fhomolka 08/08/2021
		#endif

		static const RGBA BLACK;
		static const RGBA WHITE;
		static const RGBA CLEAR;
		static const RGBA RED;
		static const RGBA GREEN;
		static const RGBA BLUE;
		static const RGBA YELLOW;
		static const RGBA MAGENTA;
		static const RGBA CYAN;
	};

	inline constexpr RGBA RGBA::BLACK{0.0f, 0.0f, 0.0f, 1.0f};
	inline constexpr RGBA RGBA::WHITE{1.0f, 1.0f, 1.0f, 1.0f};
	inline constexpr RGBA RGBA::CLEAR{1.0f, 1.0f, 1.0f, 0.0f};
	inline constexpr RGBA RGBA::RED{1.0f, 0.0f, 0.0f, 1.0f};
	inline constexpr RGBA RGBA::GREEN{0.0f, 1.0f, 0.0f, 1.0f};
	inline constexpr RGBA RGBA::BLUE{0.0f, 0.0f, 1.0f, 1.0f};
	inline constexpr RGBA RGBA::YELLOW{1.0f, 1.0f, 0.0f, 1.0f};
	inline constexpr RGBA RGBA::MAGENTA{1.0f, 0.0f, 1.0f, 1.0f};
	inline constexpr RGBA RGBA::CYAN{0.0f, 1.0f, 1.0f, 1.0f};

	using Colour = RGBA;
	using Color = RGBA;

	struct HSV
	{
		float hue; // radian value
		float saturation;
		float value;

		float chroma()
		{
			return value * saturation;
		}

		RGBA toRGBA()
		{
			if (this->saturation == 0)
			{
				return RGBA{this->value, this->value, this->value, 255};
			}

			const float sxDeg = 60 / 360 / 10;

			int iH;
			float f, p, q, t;
			RGBA newRGBA;

			if (this->hue <= 1.0f)
			{
				this->hue = 0;
			}
			else
			{
				this->hue *= sxDeg;
			}

			iH = (int)this->hue;
			f = this->hue - iH;

			p = this->value * (1.0f - this->saturation);
			q = this->value * (1.0f - this->saturation * f);
			t = this->value * (1.0f - this->saturation * (1.0f - f));

			switch(iH)
			{
				case 0:
					newRGBA.red = this->value;
					newRGBA.green = t;
					newRGBA.blue = p;
					break;
				case 1:
					newRGBA.red = q;
					newRGBA.green = this->value;
					newRGBA.blue = p;
					break;
				case 2:
					newRGBA.red = p;
					newRGBA.green = this->value;
					newRGBA.blue = t;
					break;
				case 3:
					newRGBA.red = p;
					newRGBA.green = q;
					newRGBA.blue = this->value;
					break;
				case 4:
					newRGBA.red = t;
					newRGBA.green = p;
					newRGBA.blue = this->value;
					break;
				default:
					newRGBA.red = this->value;
					newRGBA.green = p;
					newRGBA.blue = q;
					break;
			}

			return newRGBA;
		}
	};

}

#endif