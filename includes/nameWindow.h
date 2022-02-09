#ifndef NAMEWINDOW
#define NAMEWINDOW
#include <types.h>

class stNameWindow { 
	public:
		bool isNgWord(const char* word);
		bool setName(const char* name);
		void reset();
		void setWindowAnm(int anim);
		int exec();
		void draw();
		bool isWindowAnmEnd();
		int getHelpStrID();
		void term();
		int getResult();
		char* getResultString();
		void enableCollisionTest(bool a1);
};
#endif