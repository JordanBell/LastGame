#include "Renderer_Wrapper.h"
#include "ToolKit.h"
#include "SDLTools.h"
#include "SDL_image.h"
using namespace SDLTools;

Renderer_Wrapper::Renderer_Wrapper(Window* window, Uint32 flags) : m_window(window)
{
	// Initialise the renderer with that window
	m_renderer = SDL_CreateRenderer(m_window->GetWindow(), -1, flags);
	EnsureSuccess(m_renderer);
}

Renderer_Wrapper::~Renderer_Wrapper(void)
{
	SDL_DestroyRenderer(m_renderer);
}

void Renderer_Wrapper::SetLogicalSize(Dimensions size)
{
	EnsureSuccess(
		SDL_RenderSetLogicalSize(m_renderer, size.x, size.y));
}

Dimensions Renderer_Wrapper::GetLogicalSize(void) const
{
	Dimensions r_size = Dimensions();
	SDL_RenderGetLogicalSize(m_renderer, (int*)(&r_size.x), (int*)(&r_size.y));

	return r_size;
}

Dimensions Renderer_Wrapper::GetWindowSize(void) const
{
	// Get the surface
	SDL_Surface* windowSurface = GetWindowSurface();

	// Save its size
	Dimensions r_size(windowSurface->w, windowSurface->h);

	return r_size;
}

void Renderer_Wrapper::SetScale(float scaleX, float scaleY)
{
	EnsureSuccess(
		SDL_RenderSetScale(m_renderer, scaleX, scaleY));
}

SDL_Texture* Renderer_Wrapper::CreateTexture(SDL_Surface* surface)
{
	SDL_Texture* result = SDL_CreateTextureFromSurface(m_renderer, surface);

	// Check for failure
	EnsureSuccess(result);

	return result;
}

SDL_Texture* Renderer_Wrapper::LoadImageTexture(std::string filename)
{
	SDL_Texture* r_texture = NULL;
	
	// Load
	r_texture = IMG_LoadTexture(m_renderer, filename.c_str());
	// Check
	EnsureSuccess(r_texture);

	return r_texture;
}

SDL_Texture* Renderer_Wrapper::CreateTexture(Dimensions size, int access, Uint32 format)
{
	SDL_Texture* result = SDL_CreateTexture(m_renderer, 
										    format,
										    access,
										    size.x, size.y);

	// Check for failure
	EnsureSuccess(result);

	return result;
}

void Renderer_Wrapper::RenderToWindow(SDL_Texture* source, SDL_Rect* srcrect, SDL_Rect* dstrect)
{
	EnsureSuccess(
		SDL_RenderCopy(m_renderer, source, srcrect, dstrect));
}

void Renderer_Wrapper::RenderToTexture(SDL_Texture* source, SDL_Texture* destination, SDL_Rect* srcrect, SDL_Rect* dstrect)
{
	//bool lockable = TextureHasAccess(destination, SDL_TEXTUREACCESS_STREAMING);

	//if (lockable)
	//{
	//	// Lock
	//	EnsureSuccess(
	//		SDL_LockTexture(destination, NULL, NULL, NULL));
	//	// Set the destination as the renderer target
	//}

	// Target the destination
	SetTarget(destination);
	// Render onto it
	EnsureSuccess(
		SDL_RenderCopy(m_renderer, source, srcrect, dstrect));
	// Reset target to NULL
	ResetTarget();

	//if (lockable)
	//	// Unlock Texture
	//	SDL_UnlockTexture(destination);
}

void Renderer_Wrapper::RenderRectToTexture(SDL_Texture* destination, SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	// Lock
	/*EnsureSuccess(
		SDL_LockTexture(destination, NULL, NULL, NULL));*/
	// Target the destination
	SetTarget(destination);

	//Draw the rectangle
	RenderRectToTarget(rect, r,g,b,a);

	// Reset target to NULL
	ResetTarget(); 
	// Unlock Texture
	//SDL_UnlockTexture(destination);
}


void Renderer_Wrapper::RenderRectToWindow(SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SetTarget(NULL);
	RenderRectToTarget(rect, r,g,b,a);
	ResetTarget();
}

void Renderer_Wrapper::RenderRectToTarget(SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	// Draw a rect of that size and color onto the texture
	EnsureSuccess(
		SDL_SetRenderDrawColor(m_renderer, r,g,b,a) |        
		SDL_RenderFillRect(m_renderer, rect));

	// Reset the draw color to the default.
	ResetDrawColor();
}

void Renderer_Wrapper::Clear(void)
{
	EnsureSuccess(
		SDL_RenderClear(m_renderer));

	for (TextureTarget* tt : m_textureTargets)
		tt->Clear();
}

void Renderer_Wrapper::Update(void)
{
	m_window->Update();
	SDL_RenderPresent(m_renderer);
}

void Renderer_Wrapper::ResetDrawColor(void)
{
	EnsureSuccess(
		SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF));
}

void Renderer_Wrapper::SetTarget(SDL_Texture* target)
{
	EnsureSuccess(
		SDL_SetRenderTarget(m_renderer, target));
}