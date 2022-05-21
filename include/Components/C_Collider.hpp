#ifndef CB_C_COLLIDER
#define CB_C_COLLIDER


#include "../Constants.h"
#include "CB_SDL.h"
#include <vector>
#include <functional>
#include "../Game.hpp"
#include "C_Transform.hpp"

#define FBind(...) std::bind(__VA_ARGS__, this, std::placeholders::_1)

class C_Collider: public Component {
    public:
        //std::vector<void (*)(Entity*)> onCollisionFuncs;
        std::vector<std::function<void(Entity*)>> onCollisionEnterFuncs;
        std::vector<std::function<void(Entity*)>> onCollisionExitFuncs;

        C_Collider();
        ~C_Collider();

        void Initialize() override;

        virtual void OnCollisionEnter(Entity* otherEntity);
        virtual void OnCollisionExit(Entity* otherEntity);

        //void RegisterFunc(void (*newFunc)(Entity*));
        void RegisterOnEnterFunc(std::function<void(Entity*)> func);
        void RegisterOnExitFunc(std::function<void(Entity*)> func);


};

#endif
