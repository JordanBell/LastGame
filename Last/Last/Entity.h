#ifndef Entity_h
#define Entity_h

#include "SDL.h"
#include "toolkit.h"
#include "Tools.h"
#include "Resources.h"
#include "EntityFormat.h"
#include "AnimationModule.h"
#include "ModuleMisuseException.h"


class EntityContainer;

/*
An entity is an object which:
	* Is rendered onto the window
	* Has a position
	* Has an image related to it
	* Adheres to any number of EntityFormat declarations
The exact implementation of the entity is dictated by the EntityFormat
*/
class Entity
{
public:
	// Sprite sheet ID numbers
	enum SSID {
		SSID_PLAYER,
		SSID_ENVIRONMENT,
		SSID_DOOR
	};

	XY pos;	// The x and y coordinates, relative to the parent's position. If the parent is NULL, then these coordinates are direct.

	virtual ~Entity(void);

	
	/**** Short Functions ****/
	// Set an EntityContainer as this object's parent.
	void SetParent(EntityContainer* p) { parent = p; }

	// Get the blitting position of this object.
	XY GetBlittingPos(void) const { return GetAbsolutePos() + m_blitOffset; }

	// Set a texture as this entity's spritesheet
	void SetSpriteSheet(SDL_Surface* spriteSheet) { m_spriteSheet = spriteSheet; }

	// Set a rect to define this Entity's clip
	void SetClip(SDL_Rect* clip) { m_clip = clip; }

	// Move this object's coordinates by a displacement amount.
	void Move(const XY& displacement) { throw ("Calling Move(XY)...\n"); /* I'm throwing a string here in order to highlight when this function is called. */ pos += displacement; }



	// Get the absolute position of this object
	XY GetAbsolutePos(void) const;

	// Return whether or not this entity's image should be rendered
	bool ShouldRenderImage(void) const;



	/**** CHECKED DELEGATION FUNCTIONS ****/

	void Render(void);
	void Update(const int delta);
	void OnInteract(void);
	bool CanMoveThrough(void);

protected:
	// Only Entity subclasses can construct a new entity
	Entity(const XY& _pos,		  // Entity Position
		   const XY& blitOffset,  // Blit offset, the distance from this Entity's position that its image is rendered
		   int spriteSheetID,	  // Accepts IDs from the SSID enum in tools.h
		   EntityFormat format,	  // Accepts prewritten formats from config.h
		   SDL_Rect* clip = NULL, // If NULL, image will be blitted as entire SpriteSheet surface
		   AnimationModule* personalisedAnimationModule = NULL // An animation module that has already been initialised with this Entity's animation data
		   );

	EntityContainer* parent;	// The parent of this Entity
	AnimationModule* a_module;	// Encapsulated Animation handler. NULL if this entity is not animated.
	EntityFormat m_format;		// The format of this entity, dictating its behavior.

	virtual void OverrideFormat(const EntityFormat& format) { m_format = format; }

	/**** CHECKED VIRTUAL FUNCTIONS ****/
	/*
	The following functions are called publicly before being delegated to their true functions. 
	Therefore, these functions can be overridden, while retaining the public checks prior to their call.
	*/
	virtual void E_Render(void) { Blit(); }
	virtual void E_Update(const int delta) { throw ModuleMisuseException("An updateable Entity must override Entity::E_Update()"); };
	virtual void E_OnInteract(void) { throw ModuleMisuseException("An interactable Entity must override Entity::E_OnInteract()"); };
	virtual bool E_CanMoveThrough(void) { return false; }

	// Get this object's position on the grid (pos/TILE_SIZE)
	XY GetGridPosition(void) const { return GetGridPosition(pos); }

	// Get a set of coordinates' position on the grid (pos/TILE_SIZE)
	static XY GetGridPosition(const XY& _pos);

private:
	SDL_Rect*	 m_clip;		// Section of the sprite_sheet to blit.
	SDL_Surface* m_spriteSheet;	// The sprite sheet (from file) from which the image is generated (using the m_clip to set the bounds).
	SDL_Texture* m_image;		// The image (from file) which this entity displays.
	XY m_blitOffset;			// The number of pixels that this object is blitted from the origin.
	bool isInSight;				// Whether or not this object is "within sight" of the player.

	// Initialise the Entity's sprite sheet
	void InitSpriteSheet(const int ssid);

	// Initialise the Entity's texture
	void InitImageTexture(void);


	// Apply this object's sprite sheet onto the screen at this object's blitting position
	void Blit(void);
	
	// Return whether or not this object is within viewing range of the player
	bool IsInSight(void) const;

	// Return whether or not a visible part of this object is on the screen. 
	bool IsOnScreen(void) const;
};

#endif