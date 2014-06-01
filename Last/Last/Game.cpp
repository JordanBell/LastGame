#pragma once

#include "Game.h"
#include "Camera.h" // Initialising g_camera
#include "Player.h" // Initialising g_player
#include "HUD_Layer.h" // UI HUD
#include "GameStateManager.h"

Game* g_game = nullptr;

void Game::OnStart()
{
	// Initialise the UI
	UI_HUD = new HUD_Layer();
		UI_Fatigue = new UI_Status(g_fatigue, Coordinates(0, 0));
		UI_Loneliness = new UI_Status(g_loneliness, Coordinates(1, 0));
		UI_Insanity = new UI_Status(g_insanity, Coordinates(0, 1));
		UI_Fear = new UI_Status(g_fear, Coordinates(1, 1));
	UI_HUD->InitChildren(); // Add all of the above to the HUD Layer

	// Initiailise the Environment
	g_environment = new Environment();
	g_environment->Initialise();

	// Initialise the Player
	Coordinates worldCenter((WORLD_WIDTH/2), (WORLD_HEIGHT/2));
	g_player = new Player(worldCenter);
	g_environment->AddToMiddle(g_player); // Stick the player in the world.

	// Add everything to the Camera
	g_camera = new Camera();
	g_camera->InitChildren();
}

void Game::OnEnd()
{
	delete g_camera; 
	delete UI_HUD;
}

void Game::Render()
{
	if (!isPaused)
	{
		// Render camera (Environment, player, environment UI, etc.)
		g_camera->Render();

		// Render UI HUD
		//UI_HUD->Render();
	}
	else m_pauseScreen.Render();
}

void Game::OnUpdate(const int delta)
{
	// Update the entities
	if (!isPaused)
	{
		g_camera->Update(delta);
		UI_HUD->Update(delta);
	}
}

void Game::Pause(void)
{
	isPaused = true;
	m_pauseScreen.Open();
}

void Game::Unpause(void)
{
	isPaused = false;
	m_pauseScreen.Close();
}


void Game::OnKeys(const Uint8* keystates)
{
	//WASD moves the player
	if (keystates[SDL_SCANCODE_W])	g_player->Walk(UP);
	if (keystates[SDL_SCANCODE_S])	g_player->Walk(DOWN);
	if (keystates[SDL_SCANCODE_A])	g_player->Walk(LEFT);
	if (keystates[SDL_SCANCODE_D])	g_player->Walk(RIGHT);

	// Other
	if (keystates[SDL_SCANCODE_F]) g_player->Interact();
	if (keystates[SDL_SCANCODE_RETURN]) ToggleFullscreen();
	if (keystates[SDL_SCANCODE_ESCAPE]) g_manager->Quit();
	//if (keystates[SDL_SCANCODE_ESCAPE]) Pause();

	// Testing
	if (MANUAL_ZOOM)
	{
		if (keystates[SDL_SCANCODE_LCTRL])
		{
			// Up and Down to zoom in and out
			if (keystates[SDL_SCANCODE_UP]) if (!g_camera->ZoomToWidth(++widthCounter)) widthCounter--;
			if (keystates[SDL_SCANCODE_DOWN]) if (!g_camera->ZoomToWidth(--widthCounter)) widthCounter++;
		}
		else
		{
			// Up, Down, Left, Right move the player, as does WASD
			if (keystates[SDL_SCANCODE_UP]) g_player->Walk(UP);
			if (keystates[SDL_SCANCODE_DOWN]) g_player->Walk(DOWN);
			if (keystates[SDL_SCANCODE_LEFT]) g_player->Walk(LEFT);
			if (keystates[SDL_SCANCODE_RIGHT]) g_player->Walk(RIGHT);
		}
	}
	else
	{
		
	}
}