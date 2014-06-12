#pragma once
#include "MenuScreen.h"

class TitleMenuScreen : public MenuScreen
{
public:
	TitleMenuScreen(void);

protected:
	ImageTarget m_background;
	void E_Render(void);
};

