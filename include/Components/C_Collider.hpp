#ifndef CB_C_COLLIDER
#define CB_C_COLLIDER


#include "../Constants.h"
#include <SDL2/SDL.h>
#include <vector>
#include <functional>
#include "../Game.hpp"
#include "C_Transform.hpp"

#define FBind(...) std::bind(__VA_ARGS__, this, std::placeholders::_1)

class C_Collider: public Component {
    public:
        std::string colliderTag;
        SDL_Rect collider;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        C_Transform* transform;

        //std::vector<void (*)(Entity*)> onCollisionFuncs;
        std::vector<std::function<void(Entity*)>> onCollisionFuncs;

        C_Collider(std::string colliderTag, int x, int y, int width, int height);

        void Initialize() override;

        void Update(float deltaTime) override;

        virtual void OnCollisionReported(Entity* otherEntity);

        //void RegisterFunc(void (*newFunc)(Entity*));
        void RegisterFunc(std::function<void(Entity*)> func);


};

#endif
