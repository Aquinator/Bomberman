#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "raylib.h"

typedef enum 
{
    ONESHOT = 0,
    CONTINUOUS = 1
} Type;

typedef struct
{
    int first;
    int last;
    int curr;
    float frameTimer; 
    Type type;
    //Texture animeText;
} Animation;

Rectangle SpriteAnimationFrame(Animation *self, int numFramesPerLine, float objHeight, float objWidth);

void SpriteAnimationUpdate(Animation *self, float *accumulatedTime);

void SpriteAnimationShouldRepeat(Animation *self);


#endif