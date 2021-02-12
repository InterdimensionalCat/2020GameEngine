#pragma once
#include "ActorUID.h"

class DrawableObject;
class Renderer;


namespace ic {

    class RenderComponent {

        void removeChild();
        void addBackChild();
        void addFrontChild();
        void addDrawableObject();
        void move();
        void update(Renderer& renderer);


        ActorUID id;
    };
}