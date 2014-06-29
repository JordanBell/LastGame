#pragma once

#include "Game.h"
#include "Camera.h" // Initialising g_camera
#include "Player.h" // Initialising g_player
#include "HUD_Layer.h" // UI HUD
#include "KeyTools.h"
#include "GameStateManager.h"
#include "LoadingOutput.h"

Game* g_game = nullptr;

void Game::OnStart()
{
	// Initialise loading screen
	LoadingOutput::Initialise();

	// Initialise the UI
	LoadingOutput::Notify(10, "Initialising HUD");

	UI_HUD = new HUD_Layer();
		UI_Fatigue = new UI_Status(g_fatigue, Coordinates(0, 0));
		UI_Loneliness = new UI_Status(g_loneliness, Coordinates(1, 0));
		UI_Insanity = new UI_Status(g_insanity, Coordinates(0, 1));
		UI_Fear = new UI_Status(g_fear, Coordinates(1, 1));
	UI_HUD->InitChildren(); // Add all of the above to the HUD Layer

	// Initiailise the Environment
	LoadingOutput::Notify(5, "Initialising Environment");

	g_environment = new Environment();
	g_environment->Initialise();

	// Initialise the Player
	LoadingOutput::Notify(5, "Dropping in the player.");

	Coordinates worldCenter((WORLD_WIDTH/2), (WORLD_HEIGHT/2));
	g_player = new Player(worldCenter);
	g_environment->AddToMiddle(g_player); // Stick the player in the world.

	// Add everything to the Camera
	LoadingOutput::Notify(5, "Wrapping everything up");

	g_camera = new Camera();
	g_camera->InitChildren();

	m_pauseScreen = new PauseScreen(this);

	// Delete the loading screen
	LoadingOutput::Uninitialise();
}

void Game::OnEnd()
{
	//delete g_camera; 
	delete UI_HUD;
}

void Game::Render()
{
	// Render camera (Environment, player, environment UI, etc.)
	g_camera->Render();

	// Render UI HUD
	//UI_HUD->Render();

	if (isPaused) m_pauseScreen->Render();
}

void Game::OnUpdate(const int delta)
{
	// Update the entities
	if (!isPaused)
	{
		g_camera->Update(delta);
		UI_HUD->Update(delta);
	}
	else m_pauseScreen->Update(delta);
}

void Game::TogglePause(void)
{
	if (isPaused) Unpause();
	else		  Pause();
}

void Game::Pause(void)
{
	isPaused = true;
	m_pauseScreen->Open();
}

void Game::Unpause(void)
{
	isPaused = false;
	m_pauseScreen->Close();
}


void Game::OnKeys(const Uint8* keystates)
{
	if (!isPaused)
	{
		if ( KeyTools::CheckKeyWithCooldown(SDL_SCANCODE_ESCAPE) ) Pause();

		//WASD moves the player
		if (keystates[SDL_SCANCODE_W])	g_player->Walk(UP);
		if (keystates[SDL_SCANCODE_S])	g_player->Walk(DOWN);
		if (keystates[SDL_SCANCODE_A])	g_player->Walk(LEFT);
		if (keystates[SDL_SCANCODE_D])	g_player->Walk(RIGHT);

		// Other
		if (keystates[SDL_SCANCODE_F]) g_player->Interact();

		// Testing
		if (MANUAL_ZOOM)
		{
			if (keystates[SDL_SCANCODE_LCTRL])
			{
				// Up and Down to zoom in and out
				if (KeyTools::CheckKeyWithCooldown(SDL_SCANCODE_UP), 2) if (!g_camera->ZoomToWidth(--widthCounter)) widthCounter++;
				if (KeyTools::CheckKeyWithCooldown(SDL_SCANCODE_DOWN), 2) if (!g_camera->ZoomToWidth(++widthCounter)) widthCounter--;
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
	}
	else
	{
		// ESCAPE
		if ( KeyTools::CheckKeyWithCooldown(SDL_SCANCODE_ESCAPE) ) 
		{
			// Unpause or go back through the menu
			if (m_pauseScreen->IsAtRootMenu())
				Unpause();
			else
				m_pauseScreen->GoBack(); 
		}
	}

}