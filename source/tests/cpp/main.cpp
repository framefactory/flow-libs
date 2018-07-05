/**
* CPP Test - Language tests
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/


#include "ValueType.h"

#include "core/DebugStream.h"
#include <iostream>


using namespace flow;

using std::cout;
using std::endl;

int main(int argc, char** ppArgv)
{
	DebugStream::start();

	ValueType a("a");
	ValueType b(std::string("b") + "b");
	ValueType c = a;
	ValueType d;
	d = b;

	return 0;
}