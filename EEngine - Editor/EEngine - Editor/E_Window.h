#ifndef _E_WINDOW_H_
#define _E_WINDOW_H_

#include "E_GL.h"

namespace EEngine
{
class E_Window
{
	public:
		E_Window();
		~E_Window();

		bool createMainWindow(int w = 800, int h = 600,int AA = 0, string title = "deafult text", bool stdEvtProc = true);
		bool createMainWindow(sf::VideoMode vMode, sf::ContextSettings settings, string title = "deafult text", bool stdEvtProc = true);
		bool updateWindow();
		bool drawWindow();
		bool pumpMessages();
		int printFPS();
		void resize(int w, int h);
		sf::Event getEvt();

		void toggleDrawFPS();
		void closeWindow();

		static vector<sf::VideoMode> getVideoModes();

		bool isFocused();
		void switchFocus(bool set);
		sf::Window window;
		bool bClosed;
		bool defaultEvtProc;
		int width;
		int height;

	private:
		bool doDrawFps;
		fstream fpsLog;
		int second;
		int fps;
		sf::Clock fpsClock;
		sf::Time time;
		sf::Event evt;
		bool hasFocus;
};
}

#endif