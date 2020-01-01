#include "App.h"

int main(int argc, char** argv)
{
	App* app = new App();

	app->run();
	delete app;
	cout << "Press ENTER to quit...\n";
	cin.get();
	return 0;
}