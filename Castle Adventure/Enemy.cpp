#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)

{
    WorldPos = pos;
    texture = idle_texture;
    Run = run_texture;
    width = texture.width / maxframes;
    height = texture.height;
    speed = 3.5f;
};

void Enemy::Tick(float deltaTime)
{
    // pseudo
     if (!GetAlive()) return;
    // get toTarget
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity)<radius) velocity = {};
   
    
    BaseCharacter::Tick(deltaTime);
    if (CheckCollisionRecs(target->GetCollisionRec(), GetCollisionRec()))
    {
        target -> TakeDamage (EnemyDamagePerSec * deltaTime);
    }
    
};

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(WorldPos, target->GetWorldPos());
}