#include "E_Window.h"
using namespace EEngine;

E_Window::E_Window()
{
	hasFocus = true;
	defaultEvtProc = true;
	bClosed = false;
	doDrawFps = false;
	time = sf::seconds(0);
	fpsClock.restart();
	fps = 0;
	second = 0;
	fpsLog.open("fpslog.txt", 'w');
}

E_Window::~E_Window()
{
	fpsLog.flush();
	fpsLog.close();
}

bool E_Window::createMainWindow(int w, int h, int AA, string title, bool stdEvtProc)
{
	width = w;
	height = h;
	sf::VideoMode mode;
	mode = sf::VideoMode::getDesktopMode();
	if(!mode.isValid())
	{
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << "[ts]Video mode is not valid!\n";
		return false;
	}
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = AA;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	defaultEvtProc = stdEvtProc;
	window.create(sf::VideoMode(width, height, mode.bitsPerPixel), title, sf::Style::Default, settings);
	settings = window.getSettings();
	string tmp = intToString(settings.majorVersion) + "." + intToString(settings.minorVersion);
	LogMgr::out << "[ts]Context settings:\n";
	LogMgr::addIndent(1);
	LogMgr::out << "[ts]Current OpenGL version is: " << tmp << lEnd;
	LogMgr::out << "[ts]Depth bits: " << intToString(settings.depthBits) << lEnd;
	LogMgr::out << "[ts]Stencil bits: " << intToString(settings.stencilBits) << lEnd;
	LogMgr::decrIndent(1);
	return true;
}

bool E_Window::createMainWindow(sf::VideoMode vMode, sf::ContextSettings settings, string title, bool stdEvtProc)
{
	defaultEvtProc = stdEvtProc;
	width = vMode.width;
	height = vMode.height;
	window.create(vMode, title, sf::Style::Default, settings);
	return true;
}

bool E_Window::drawWindow()
{
	window.display();
	if(doDrawFps)
		printFPS();
	return true;
}

bool E_Window::pumpMessages()
{
	if(defaultEvtProc)
	{
		window.pollEvent(evt);
		if(evt.type == sf::Event::Closed)
		{
			closeWindow();
			return true;
		}
		if(evt.type == sf::Event::GainedFocus)
		{
			hasFocus = true;
			return true;
		}
		if(evt.type == sf::Event::LostFocus)
		{
			hasFocus = false;
			return true;
		}
		if(evt.type == sf::Event::Resized)
		{
			resize(evt.size.width, evt.size.height);
			return true;
		}
		if(evt.type == sf::Event::KeyPressed)
		{
 			if(evt.key.code == sf::Keyboard::Escape)
				closeWindow();
		}
	}
	return true;
}

bool E_Window::isFocused()
{
	if(hasFocus)
		return true;
	else
		return false;
}

void E_Window::switchFocus(bool set)
{
	hasFocus = set;
}

int E_Window::printFPS()
{
	fps++;
	time = fpsClock.getElapsedTime();
	second = time.asSeconds();
	if(second == 1)
	{
		fpsClock.restart();
		second = 0;
		fpsLog << "|" << fps << "|";
		fps = 0;
	}
	return fps;
}

void E_Window::resize(int w, int h)
{
	width = w;
	height = h;
	E_GL::resize(w, h);
}

vector<sf::VideoMode> E_Window::getVideoModes()
{
	return sf::VideoMode::getFullscreenModes();
}

sf::Event E_Window::getEvt()
{
	return evt;
}

void E_Window::toggleDrawFPS()
{
	if(doDrawFps)
		doDrawFps = false;
	else if(!doDrawFps)
		doDrawFps = true;
}

void E_Window::closeWindow()
{
	window.close();
	bClosed = true;
}