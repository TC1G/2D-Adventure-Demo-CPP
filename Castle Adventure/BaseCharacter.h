
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
private:
    /* data */
public:
    BaseCharacter(/* args */);
    Vector2 GetWorldPos()
    {
        return WorldPos;
    }
    void UndoMovement();
    Rectangle GetCollisionRec();
    virtual void Tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool GetAlive()
    {
        return alive;
    };
    bool SetAlive(bool IsAlive) {alive = IsAlive;};

protected:
    // right left movement
    float RightLeft = 1.0f;
    // Anim variables
    float RunningTime{};
    int frame{};
    int maxframes{6};
    float updateTime{1.f / 12.f};
    float speed{4.0f};
    float width{};
    float height{};
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D Idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D Run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 ScreenPos{};
    Vector2 WorldPos{};
    Vector2 worldPosLastFrame{};
    float scale{4.0f};
    Vector2 velocity{};
    bool alive {true};
};

#endif