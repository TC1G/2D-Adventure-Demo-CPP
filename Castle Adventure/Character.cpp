#include "Character.h"
#include "Prop.h"
#include "raymath.h"
#include <iostream>

Character::Character(int winWidth, int winHeight) :
windowWidth(winWidth),
windowHeight(winHeight)
{
    width = texture.width / maxframes;
    height = texture.height;

}
Vector2 Character::getScreenPos() 
{
    return Vector2
 {
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)
 };
}

// TICK
void Character::Tick(float deltaTime)
{

    if (!GetAlive()) return;
    
    if (IsKeyDown(KEY_A))
    {
        velocity.x -= 1.0;
    }
    if (IsKeyDown(KEY_D))
    {
        velocity.x += 1.0;
    }
    if (IsKeyDown(KEY_W))
    {
        velocity.y -= 1.0;
    }
    if (IsKeyDown(KEY_S))
    {
        velocity.y += 1.0;
    }
    BaseCharacter::Tick(deltaTime);
    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (RightLeft > 0.f)
    {   
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {getScreenPos().x + offset.x,getScreenPos().y + offset.y - weapon.height * scale, weapon.width * scale, weapon.height * scale};

        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ?  35.f : 0.f; // attack anim
        
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {getScreenPos().x + offset.x - weapon.width * scale, getScreenPos().y + offset.y - weapon.height * scale, weapon.width * scale, weapon.height * scale};
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ?  35.f : 0.f;
    }
    
    //draw sword
    Rectangle source {0.f,0.f,static_cast<float>(weapon.width) * RightLeft, static_cast<float>(weapon.height)};
    Rectangle dest {getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width*scale, weapon.height*scale};
    DrawTexturePro (weapon, source, dest, origin, rotation, WHITE);


    

}

void Character::TakeDamage(float damage)
{   
    health-=damage;
    if (health <= 0)
    {
        SetAlive(false);
    }
    

}