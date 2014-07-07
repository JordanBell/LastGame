#pragma once
#include "entitycontainer.h"

class Text;

class LoadingScreen :
	public EntityContainer
{
public:
	LoadingScreen(void);
	~LoadingScreen(void);
	
	void SetMessage(string message);
	void Add(int val) { 
		m_percentage += val; 
		UpdateLoaderSize(); 
	}
	
	void E_Update(const int delta) override final;
	void E_Render(void) override final;

private:
	static const int m_outlineThickness; // Thickness of the outline on the bar
	static const Dimensions m_barProportion; // The proportion of the screen size that the bar's size takes up

	ImageTarget* m_barGraphic; // The static image behind the growing bar
	ImageTarget* m_barLoader;  // The growing bar
	Dimensions m_loaderSize;
	Dimensions m_barSize;
	Dimensions m_barPos;
	int m_percentage;
	Text* m_text;
	
	void InitBar(void);
	void InitText(void);

	// Visibly updates the size of the loader bar based on the percentage
	void UpdateLoaderSize(void);
};
