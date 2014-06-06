#include "LoadingOutput.h"

int LoadingOutput::s_total = 0;

void LoadingOutput::Notify(int percentage, char* message)
{
	// Add up the total
	s_total += percentage;

	// Print the data.
	printf("%d - %s\n", s_total, message);
}