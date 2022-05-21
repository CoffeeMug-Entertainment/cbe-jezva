#ifndef C_SPRITE
#define C_SPRITE

#include "CB_SDL.h"
#include "../TextureManager.hpp"
#include "../AssetManager.hpp"
#include "C_Transform.hpp"

class C_Sprite: public Component {
	private:
		C_Transform* transform;
		SDL_Texture* texture;
		SDL_Rect sourceRectangle;
		SDL_Rect destinationRectangle;
		bool isFixed;

	public:
		SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

		C_Sprite(std::string assetTextureId, bool isFixed = false) {
			this->isFixed = isFixed;
			SetTexture(assetTextureId);
		}

		void SetTexture(std::string assetTextureId) {
			texture = Game::assetManager->GetTexture(assetTextureId);
		}

		void Initialize() override {
			transform = owner->GetComponent<C_Transform>();
			int width, height;
			SDL_QueryTexture(texture, NULL, NULL, &width, &height);
			sourceRectangle.x = 0;
			sourceRectangle.y = 0;
			sourceRectangle.w = width;
			sourceRectangle.h = height;
		}

		void Update([[maybe_unused]] float deltaTime) override {

			destinationRectangle.x = static_cast<int>(transform->position.x) - (isFixed ? 0 : Game::camera.x);
			destinationRectangle.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Game::camera.y);
			destinationRectangle.w = transform->width * transform->scale;
			destinationRectangle.h = transform->height * transform->scale;
		}

		void Render() override {
			TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
		}
};

#endif
