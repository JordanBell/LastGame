#ifndef environment_h
#define environment_h

#include "EntityContainer.h"
#include "GridTiles.h"
#include "Config.h"
#include "Tools.h"
#include "Player.h"
#include "EnvironmentLayer.h"

class Environment :
	public EntityContainer
{
<<<<<<< HEAD
	EnvironmentLayer topLayer;
	EnvironmentLayer bottomLayer;

public:
	Environment(float x, float y);

	void RenderTop(void) { topLayer.e_render(); }
	void RenderBottom(void) { bottomLayer.e_render(); }
	list<GridTile*>& GetTilesAt(const XY& position, const bool top = false);
	void AddTileToTop(GridTile* tile) { topLayer.addChild(tile); }
	void AddTileToBottom(GridTile* tile) { bottomLayer.addChild(tile); }
=======
public:
	Environment(float x, float y);
	~Environment(void);
	
	void BuildMap(void);
	void centerOn(Player* player);
	void BuildRoom(int x, int y, int w, int h, bool randomDoorway = false);

	GridTile* getTileAt(XY* gridPosition);
	Directions<bool> GetEdgeBools();
	Directions<bool> GetEdgeBools(float _x, float _y);

private:
	int width, height; //The total size of the world
	GridTile* tiles[WORLD_WIDTH][WORLD_HEIGHT]; // Note: Make 2D array of lists of tiles; Tile Layer? Used if a position has several tiles on top, and we don't want to override any tiles in that position.

	template <class T_Fill, class T_Border>
		void BuildBorderedRectangle(int x, int y, int w, int h);
	template <class T>
		void BuildRectangle(int x, int y, int w, int h, bool filled = true);
	template <class T>
		void AddTileTo(int _x, int _y);
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
};

extern Environment* g_environment;

#endif