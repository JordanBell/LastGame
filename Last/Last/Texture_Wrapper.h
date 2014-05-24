#pragma once
#include "Tools.h"

class TextureStreamer;

class Texture_Wrapper
{
public:
	// Create a texture from a sprite sheet file
	Texture_Wrapper(const SSID ssid, const bool staticClip, SDL_Rect* clip = NULL);

	virtual ~Texture_Wrapper(void);

	// Add a Texture Streamer for this to stream its texture toward
	void SetStreamer(TextureStreamer* streamer) { m_targetStreamer = streamer; }

	// Change the image's clip
	void SetClip(SDL_Rect* newClip) { m_clip = newClip; }

	// Render texture onto renderer-pointer's target
	void RenderToTarget(Coordinates pos) const;

	// Return the raw SDL Texture
	SDL_Texture* GetTexture(void) const { return m_texture; }

	// Get the width and height of this image
	virtual Dimensions Size(void) const;

	bool ShouldRender(void) const { return (m_texture != NULL); }

protected:
	// The SDL_Texture that this class wraps around
	SDL_Texture* m_texture;
	// Pointer to any TextureStreamers
	const TextureStreamer* m_targetStreamer;
	// The clip from which this object renders
	SDL_Rect* m_clip;

private:
	SDL_Surface* m_source;

	// Load the source surface that this Texture comes from
	void LoadSource(SSID ssid);

	// Load the texture from the Source, using the renderer
	void CreateTextureFromSource(bool staticClip);

	// Load the texture from the Source, using the renderer
	void CreateTextureForStreaming(void);

	void RenderToStreamer(Coordinates pos) const;
	void RenderToWindow(Coordinates pos) const;
};

typedef Texture_Wrapper Image;
typedef Texture_Wrapper Texture;

class TextureStreamer : public Texture_Wrapper
{
public:
	// Create a texture with NULL source
	TextureStreamer(SDL_Rect* clip = NULL) : Texture_Wrapper(SSID_NULL, false, clip) {}
};

typedef TextureStreamer ImageStreamer;
