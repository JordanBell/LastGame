#pragma once

#include "Tools.h"
#include "EntityFormat.h"
#include "AnimationModule.h"
#include "ModuleMisuseException.h"
#include "Texture_Wrapper.h"

class EntityContainer;

/*
An entity is an object which:
	* Is rendered
	* Has a position
	* Has an image related to it
	* Adheres to any number of EntityFormat declarations
The exact implementation of the entity is dictated by the EntityFormat
*/
class Entity
{
public:

	Coordinates pos; // Relative to the parent's position. If the parent is nullptr, then these coordinates are direct.
	virtual ~Entity(void);

	
	/**** Short Functions ****/
	// Set an EntityContainer as this object's parent.
	void SetParent(EntityContainer* p);

	// Get the blitting position of this object, to be blitted onto its parent's texture
	Coordinates GetBlittingPos(void) const { return /*GetAbsolutePos()*/pos + m_blitOffset; }
	
	// Get the absolute position of this object.
	Coordinates GetAbsolutePos(void) const;

	void Center(bool centerX = true, bool centerY = true);

	// Virtual image retrieval, as the image implementation for EntityContainer can be overridden as an ImageTarget
	virtual Image& GetImage(void) { return m_image; }

	// Whether or not E_Render should be called from Render. Overridden by EntityContainers.
	virtual bool ShouldRender(void) { return ShouldRenderImage(); }

	// Return whether or not a visible part of this object is on the screen. 
	virtual bool IsOnScreen(void); // Overridden for EntityContainers

	// Apply this object's sprite sheet onto the screen at this object's blitting position
	void BlitToParent(void);

	bool operator[](int formatIndex) { return m_format[formatIndex]; }


	/**** CHECKED DELEGATION FUNCTIONS ****/

	void Render(void);
	void Update(const int delta);
	void OnInteract(void);
	bool CanMoveThrough(void);

protected:
	// Raw info Constructor
	Entity(const Coordinates& _pos,		  // Entity Position
		   const Coordinates& blitOffset, // Blit offset, the distance from this Entity's position that its image is rendered
		   SSID spriteSheetID,	  // Accepts IDs from the SSID enum in tools.h
		   EntityFormat format,	  // Accepts prewritten formats from config.h
		   SDL_Rect* clip = nullptr, // If nullptr, image will be blitted as entire SpriteSheet surface
		   AnimationModule* personalisedAnimationModule = nullptr // An animation module that has already been initialised with this Entity's animation data
		   );

	// Passing an Image as argument
	Entity(const Coordinates& _pos,		  // Entity Position
		   const Coordinates& blitOffset, // Blit offset, the distance from this Entity's position that its image is rendered
		   Image image,	  // The image object used by this entity
		   EntityFormat format,	  // Accepts prewritten formats from config.h
		   AnimationModule* personalisedAnimationModule = nullptr // An animation module that has already been initialised with this Entity's animation data
		   );

	// Entity with blank image (used in subclasses with differing image implementations)
	Entity(const Coordinates& _pos,		  // Entity Position
		   const Coordinates& blitOffset, // Blit offset, the distance from this Entity's position that its image is rendered
		   EntityFormat format,	  // Accepts prewritten formats from config.h
		   AnimationModule* personalisedAnimationModule = nullptr // An animation module that has already been initialised with this Entity's animation data
		   );
	
	Image m_image;				// The image which this entity displays.
	EntityFormat m_format;		// The format of this entity, dictating its behavior.
	Coordinates m_blitOffset;	// The number of pixels that this object is blitted from the origin.
	EntityContainer* parent;	// The parent of this Entity
	AnimationModule* a_module;	// Encapsulated Animation handler. nullptr if this entity is not animated.

	// Set the position based on the format
	void SetPosition(const Coordinates& _pos);

	// Create the format outside of the 
	void SetFormat(EntityFormat& format);

	void SetImage(Image& image);

	// Return whether or not this entity's image should be rendered
	bool ShouldRenderImage(void);

	// Get this object's position on the grid (pos/TILE_SIZE)
	Coordinates GetGridPosition(void) const { return GetGridPosition(pos); }

	// Get a set of coordinates' position on the grid (pos/TILE_SIZE)
	static Coordinates GetGridPosition(const Coordinates& _pos);

	// Update the clip via the assigned animation module
	virtual void UpdateClipFromAnimation(void) { GetImage().SetClip( a_module->GetClip() ); }

	/**** CHECKED VIRTUAL FUNCTIONS ****/
	/*
	The following functions are called publicly before being delegated to their true functions. 
	Therefore, these functions can be overridden, while retaining the public checks prior to their call.
	*/
	virtual void E_Render(void) { BlitToParent(); }
	virtual void E_Update(const int delta) { throw ModuleMisuseException("An updateable Entity must override Entity::E_Update()"); };
	virtual void E_OnInteract(void) { throw ModuleMisuseException("An interactable Entity must override Entity::E_OnInteract()"); };
	virtual bool E_CanMoveThrough(void) { return false; }

private:
	void Animate(void);

	// Initialise the Entity's sprite sheet
	void InitSpriteSheet(const int ssid);

	// Initialise the Entity's texture
	void InitImageTexture(void);

	// Set the member image's target
	inline void SetImageTarget(void);
};