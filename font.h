#ifndef _FONT_H_
#define _FONT_H_

#include "vector.h"

class Font {
private:
    Vec3 position;
    const char* text;
public:
    Font() : position(0,0,0){};
    Font(char* newText, Vec3 pos) : position(pos[0],pos[1],pos[2]){
        text = newText;
    };
    void Render();
    
    void setText(const char* newText) {
        text = newText;
    }
};
#endif