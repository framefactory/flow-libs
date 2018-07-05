/**
* CPP Test - Language tests
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "core/setup.h"
#include <string>


namespace flow
{
	class ValueType
	{
	public:
		ValueType();
		ValueType(const std::string& value);
		ValueType(std::string&& value);
		ValueType(const ValueType& other);

		virtual ~ValueType();

		ValueType& operator=(const ValueType& other);

		void set(const std::string& value);
		const std::string& get() const { return _value; }

	private:
		std::string _value;
	};
}