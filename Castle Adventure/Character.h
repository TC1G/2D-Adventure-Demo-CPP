#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    virtual void Tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    // weapon collision
    Rectangle GetWeaponCollisionRec()
    {
        return weaponCollisionRec;
    }
    int GetHealth() const {return health;}
    void TakeDamage(float damage);

private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    // make health
    float health{100.f};
};

#endif