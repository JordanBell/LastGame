#include "Menu_TitleFront.h"

/*
DEPRECATED
*/


Menu_TitleFront::Menu_TitleFront(void) 
	: Menu("front"), 
	  m_newGame(Coordinates(50, 50)), 
	  m_exit(Coordinates(50, 150))
{
}


Menu_TitleFront::~Menu_TitleFront(void)
{
}
