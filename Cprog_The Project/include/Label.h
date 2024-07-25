//Nicole Nechita, rone8293
#ifndef LABEL_H
#define LABEL_H
#include "Component.h"
#include <SDL2/SDL.h>
#include <string>
namespace cwing{
    class Label: public Component{
        public:
            static Label* getInstance(int x, int y, int w, int h, const std::string& txt);
            std::string getText() const;
            void setText(std::string& newText);
            static void setColor(const Uint8& red,const Uint8& green,const Uint8& blue);
            ~Label();
        protected:
            void draw() const;
            void tick();
            int getLives()const{return 0;}
            void performCollision(const ObjectType& object);
            Label(int x, int y, int w, int h, const std::string& txt);
        private:
            std::string text;
            SDL_Texture* texture;
            static Uint8 m_red;
            static Uint8 m_green;
            static Uint8 m_blue;
            Label(const Label&) = delete;
            const Label& operator=(const Label&) = delete;
    };
}
#endif