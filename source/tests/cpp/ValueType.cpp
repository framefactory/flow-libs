/**
* CPP Test - Language tests
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "ValueType.h"
#include <iostream>

using namespace flow;
using std::cout;
using std::endl;


ValueType::ValueType()
{
	cout << "ValueType::DefaultConstructor - " << _value << endl;
}

ValueType::ValueType(const std::string& value) :
	_value(value)
{
	cout << "ValueType::ConstructorWithValue - " << _value << endl;
}

ValueType::ValueType(std::string&& value) :
	_value(std::move(value))
{
	cout << "ValueType::MoveConstructor - " << _value << endl;
}

ValueType::ValueType(const ValueType& other) :
	_value(other._value)
{
	cout << "ValueType::CopyConstructor - " << _value << endl;
}

ValueType::~ValueType()
{
	cout << "ValueType::Destructor - " << _value << endl;
}

ValueType& ValueType::operator=(const ValueType& other)
{
	_value = other._value;

	cout << "ValueType::AssignmentOperator - " << _value << endl;

	return *this;
}

void ValueType::set(const std::string& value)
{
	_value = value;
}