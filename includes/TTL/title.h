#ifndef TITLE
#define TITLE
#include <spritestudio.h>

namespace TTL
{
	typedef struct mpMap
	{ 
		
	} mpMap;

	static mpMap* mpMapTemp;

	void thDataLoad();
	void title_loop4();
	void mpTOPLOOP();
	void mpLOOP3();
	void Start(int a1, void* a2);
	void Ready(int a1, void* a2);
	void Mchg(int a1, void* a2);
	void Loop2(int a1, void* a2);
	void Loop(int a1, void* a2)
	
	class CSetCallback : public WATAM_UTILITY::CSetCallback
	{
		public:
			virtual int CallbackFunction(int a1, int a2, int a3, int a4, int a5, int a6);
			virtual ~CSetCallback() { } 
	}

}

#endif