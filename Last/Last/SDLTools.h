#pragma once

namespace SDLTools 
{
	// Print and throw the most recent SDL error
	void ErrorResponse(void);

	// Invoke Error Response if argument is null
	void* EnsureSuccess(void* ptr);
	
	// Invoke Error Response if argument is non-zero
	void EnsureSuccess(int indicator);
}