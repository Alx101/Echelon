// Header files of frequent usage
//GLOBAL ENUMS
#ifndef _GLOBAL_ENUMS_INIT_
#define _GLOBAL_ENUMS_INIT_
#include "E_LogMgr.h"
#include <new>
#include <iostream>
#include <vld.h>

/*#define _MEMORY_TO_ALLOCATE_ 5000
#define _MAX_USABLE_MEMORY_BUFFER_ 100

void* operator new(size_t size);
void operator delete(void* p);
*/
namespace EEngine
{
	/*class memory
	{
		public:
			memory();
			~memory();
			void release(void* p);
			void assignLastBlock();
		//	void* allocate(size_t size);
			void* allocate(size_t size);
		private:
			int lastAvailableMemoryBlock;
			int scan_currentMemoryBlock;
			bool memoryDeleted;
			void* usableMemoryBuffer[_MAX_USABLE_MEMORY_BUFFER_];
			void* memoryHeap[_MEMORY_TO_ALLOCATE_];
	};*/

	enum shaderTypes
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,
		GEOMETRY_SHADER
	};

	enum FXdataTypes
	{
		POSITION,
		TEXTURE1,
		TEXTURE2,
		TEXTURE3,
		MATRIX4,
		MATRIX3,
		MATRIX2,
		MATRIX4X2,
		MATRIX4X3,
		MATRIX3X2,
		MATRIX3X4,
		MATRIX2X3,
		MATRIX2X4,
		VECTOR2,
		VECTOR3,
		VECTOR4,
		CUBEMAP,
		SHADOW
	};

	class vectors
	{
		public:
			int x;
			int y;
			int z;
	};

	namespace inputCode
	{
	enum InputEvtTarget
	{
		NODE,
		CORE,
		CUSTOM //This one calls the attached function in the InputEvent
	};
	enum InputEvtType
	{
		ONCE,
		TIME,
		TOGGLE
	};
	namespace node
	{
	enum nodeActions
	{
		MOVE,
		SCALE,
		ROTATE,
		ERASE,
		FOLLOW,
		DO_ACTION
	};
	}
	namespace core
	{
	enum coreActions
	{
		SHUTDOWN,
		WIREFRAME,
		TOGGLEFPS
	};
	}
	}

	//Redefines of New and Delete

	//Enum for keyHandling functions
	namespace keyCode
	{
	enum keyEnum 
	{
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		Num0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Escape,
		LControl,
		LShift,
		LAlt,
		LSystem,
		RControl,
		RShift,
		RAlt,
		RSystem,
		Menu,
		LBracket,
		RBracket,
		SemiColon,
		Comma,
		Period,
		Quote,
		Slash,
		BackSlash,
		Tilde,
		Equal,
		Dash,
		Space,
		Return,
		Back,
		Tab,
		PageUp,
		PageDown,
		End,
		Home,
		Insert,
		Delete,
		Add,
		Subtract,
		Multiply,
		Divide,
		Left,
		Right,
		Up,
		Down,
		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		Pause,
		KeyCount
	};
	}
	namespace Filehandling
	{
	enum fileType
	{
		READ,
		WRITE,
		READ_WRITE,
		WRITE_CONT
	};
	}
}
#endif

#include <ctime>
#include <fstream>
#include <windows.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <string>
#include <sstream>
using namespace std;

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML\Window.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\System.hpp>

#ifndef _ANOTHER_STRUCT_DEFINE_
#define _ANOTHER_STRUCT_DEFINE_
namespace EEngine
{
struct EvtMsg
{
	vector<int> iParam; //Put all messages for the input here (enums)
	vector<string> sParam;
	glm::vec3 vect;
};
struct InputEvent
{
	int iEvtType; //How the input should be handled
	int iEvtTarget;
	string nodeName;
	EvtMsg msg;
	int iKey;
	bool bPrevPressed;
	void (*customFunc)(EvtMsg mesg); //Custom function to be called, should take an EvtMsg as attribute
};

struct FX_DataStruct
{
	string activationID;
	list<string> dataID;
	map<string, int> idName;
	list<char*> dataForm;
	list<int> dataType;
	list<bool> uniforms;
	list<bool> vectors;
	list<string>::iterator idIt;
	list<int>::iterator iIt;
	list<bool>::iterator bIt;
	list<char*>::iterator cpIt;
	map<string, GLuint> attributes;
	map<string, GLuint>::iterator attribIt;
};

}

string intToString(int i);
#endif

// Some useful defines
#define FOR(q,n) for(int q=0;q<n;q++)
#define SFOR(q,s,e) for(int q=s;q<=e;q++)
#define RFOR(q,n) for(int q=n;q>=0;q--)
#define RSFOR(q,s,e) for(int q=s;q>=e;q--)
#define PI_OVER_360 3.14159265/360
#define ESZ(elem) (int)elem.size()
#define lEnd "\n"
#define ts "[ts]"
#ifndef _gcdFUNC_
#define _gcdFUNC_
static int gcd(int a, int b)
{
	return(b==0) ? a : gcd(b, a%b);
}
#endif