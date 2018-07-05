/**
* Flow Libs - Core
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "DebugStream.h"

#include <iostream>
#include <Windows.h>


using namespace flow;
using std::string;
using std::cout;
using std::endl;


DebugStream::Guard DebugStream::s_guard;

DebugStream::DebugStream()
{
	cout.rdbuf(this);
}

DebugStream::~DebugStream()
{
	sync();
}

void DebugStream::start()
{
	if (!s_guard.pInstance) {
		s_guard.pInstance = new DebugStream();
	}
}

int DebugStream::sync()
{
	::OutputDebugStringA(str().c_str());
	str(string{});

	return 0;
}