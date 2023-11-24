#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}


void BaseCharacter::UndoMovement()
{

    WorldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{

    return Rectangle 
    {
        
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale


    };

}
void BaseCharacter::Tick(float deltaTime)
{
    worldPosLastFrame = WorldPos;
     //update anim frame
     RunningTime += deltaTime;

    if (RunningTime >= updateTime)
    {
        frame++;
        RunningTime = 0.f;
        if (frame > maxframes)
        {
            frame = 0.f;
        }
    }
    if (Vector2Length(velocity) != 0)
    {

        WorldPos = Vector2Add(WorldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? RightLeft = -1.0f : RightLeft = 1.0f;
        texture = Run;
    }

    else
    {
        texture = Idle;
    }
    velocity= {};
    //draw
    Rectangle source{frame * width, 0.0f, RightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);

}