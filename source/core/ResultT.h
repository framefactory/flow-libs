/**
* Flow Libs - Core
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_RESULTT_H
#define _FLOWLIBS_RESULTT_H

#include "library.h"
#include <string>
#include <utility>

#ifdef ERROR
#undef ERROR
#endif

#ifdef OK
#undef OK
#endif

namespace flow
{
	struct ResultState
	{
		enum enum_type
		{
			OK,
			ERROR
		};

		F_DECLARE_ENUM(F_CORE_EXPORT, ResultState, ERROR);
	};

	inline const char* ResultState::name() const
	{
		switch (_state) {
			F_ENUM_NAME(OK);
			F_ENUM_NAME(ERROR);
			F_ENUM_ASSERT_DEFAULT;
		}
	}

	class Result;

	template<typename T>
	class ResultT
	{
	public:
		static ResultT<T> ok(const std::string& message = std::string{}) {
			return ResultT<T>(ResultState::OK, message);
		}
		static ResultT<T> error(const std::string& message = std::string{}) {
			return ResultT<T>(ResultState::ERROR, message);
		}

		ResultT(const Result& result);
		ResultT(ResultState state = ResultState::ERROR, const std::string& message = std::string{});
		ResultT(const T& value, ResultState state = ResultState::OK, const std::string& message = std::string{});
		ResultT(T&& value, ResultState state = ResultState::OK, const std::string& message = std::string{});

		bool isOK() const { return _state == ResultState::OK; }
		bool isError() const { return _state == ResultState::ERROR; }
		const ResultState state() const { return _state; }
		const std::string& message() const { return _message; }
		const T& value() const { return _value; }

	private:
		ResultState _state;
		std::string _message;
		T _value;
	};

	template<typename T>
	ResultT<T>::ResultT(ResultState state, const std::string& errorMessage) :
		_state(ResultState::ERROR),
		_message(errorMessage)
	{
	}

	template<typename T>
	ResultT<T>::ResultT(const T& value, ResultState state, const std::string& message) :
		_state(state),
		_message(message),
		_value(value)
	{
	}

	template<typename T>
	ResultT<T>::ResultT(T&& value, ResultState state, const std::string& message) :
		_state(state),
		_message(message),
		_value(std::move(value))
	{
	}

	////////////////////////////////////////////////////////////////////////////////

	class Result
	{
	public:
		static Result ok(const std::string& message = std::string{}) {
			return Result(ResultState::OK, message);
		}
		static Result error(const std::string& message = std::string{}) {
			return Result(ResultState::ERROR, message);
		}

		Result(ResultState state = ResultState::ERROR, const std::string& message = std::string{}) :
			_state(state),
			_message(message) { }

		template<typename T>
		Result(const ResultT<T>& result) :
			_state(result.state()),
			_message(result.message()) { }

		bool isOK() const { return _state == ResultState::OK; }
		bool isError() const { return _state == ResultState::ERROR; }
		const ResultState state() const { return _state; }
		const std::string& message() const { return _message; }

	private:
		ResultState _state;
		std::string _message;
	};

	////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	ResultT<T>::ResultT(const Result& result) :
		_state(result.state()),
		_message(result.message())
	{
	}
}

#endif // _FLOWLIBS_RESULTT_H