#include "Application.hpp"
#if defined(MSVC) 
int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
#else
int main()
#endif
{
	Application app;
	if(app.Load())
	{
		return app.Run();
	}
	return -1;
}
