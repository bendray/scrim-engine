#include "Launcher.hpp"
#if defined(MSVC) 
int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
#else
int main()
#endif
{
	CLauncher app;
	return app.Execute();
}
