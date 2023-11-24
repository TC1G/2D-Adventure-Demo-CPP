#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

/////////////// MAIN //////////
int main()
{

	const int windowWidth = 1024;							  // width
	const int windowHeight = 768;							  // height
	InitWindow(windowWidth, windowHeight, "2DAdventureDemo"); // load window
	InitAudioDevice();
	Vector2 mapPos = {0.0f, 0.0f};
	const float mapScale{4.0f};

	SetTargetFPS(60); // fps

	// KNIGHT
	Character knight{windowWidth, windowHeight};

	// PROP
	Prop props[4]{
		Prop{Vector2{800.0f, 700.0f}, LoadTexture("nature_tileset/Rock.png")},
		Prop{Vector2{600.0f, 900.0f}, LoadTexture("nature_tileset/Log.png")},
		Prop{Vector2{800.0f, 1000.0f}, LoadTexture("nature_tileset/Sign.png")},
		Prop{Vector2{900.0f, 1000.0f}, LoadTexture("nature_tileset/Bush.png")}};

	// ENEMY
	Enemy Goblin{
		Vector2{800.f, 600.f},
		LoadTexture("characters/goblin_idle_spritesheet.png"),
		LoadTexture("characters/goblin_run_spritesheet.png")};

	Enemy Slime{
		Vector2{700.f, 500.f},
		LoadTexture("characters/slime_idle_spritesheet.png"),
		LoadTexture("characters/slime_run_spritesheet.png")

	};

	Enemy *enemies[]{
		&Goblin,
		&Slime};

	for (auto Enemy : enemies)
	{
		Enemy->SetTarget(&knight);
	}

	Texture2D Map = LoadTexture("nature_tileset/OpenWorldMap24x24.png"); // load texture

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);
		mapPos = Vector2Scale(knight.GetWorldPos(), -1.0f);
		// DRAW MAP
		DrawTextureEx(Map, mapPos, 0.0, mapScale, WHITE);
		for (auto Prop : props)
		{
			Prop.Render(knight.GetWorldPos());
		}

		if (!knight.GetAlive())
		{
			DrawText("Game OVER!", 55.f, 55.f, 40.f, RED);
			EndDrawing();

			continue;
		}
		else
		{
			std::string KnightsHealth = "HP: ";
			KnightsHealth.append(std::to_string(knight.GetHealth()), 0, 5);
			DrawText(KnightsHealth.c_str(), 55.f, 45.f, 40, RED);
		}

		knight.Tick(GetFrameTime());
		// Map bounds
		if (knight.GetWorldPos().x < 0.f || knight.GetWorldPos().y < 0.f || knight.GetWorldPos().x + windowWidth > Map.width * mapScale || knight.GetWorldPos().y + windowHeight > Map.height * mapScale)
		{
			knight.UndoMovement();
		}

		for (auto prop : props)
		{
			if (CheckCollisionRecs(prop.GetCollisionRec(knight.GetWorldPos()), knight.GetCollisionRec()))
			{
				knight.UndoMovement(); // check prop collisions
			}
		}
		for (auto Enemy : enemies)
		{
			Enemy->Tick(GetFrameTime());
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			for (auto Enemy : enemies)
			{
				if (CheckCollisionRecs(Enemy->GetCollisionRec(), knight.GetWeaponCollisionRec()))
				{
					Enemy->SetAlive(false);
				}
			}
		}

		EndDrawing();
	}
	CloseWindow();
}
