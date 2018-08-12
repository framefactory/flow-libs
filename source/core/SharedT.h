/**
* Flow Libs - Core
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_CORE_SHAREDT_H
#define _FLOWLIBS_CORE_SHAREDT_H

#include "library.h"

namespace flow
{
	struct SharedImpl;

	template <typename T>
	class SharedT
	{
	public:
		SharedT() :
			_pImpl(nullptr)
		{
		}

		SharedT(const T& other) :
			_pImpl(static_cast<const SharedT<T>*>(&other)->_pImpl)
		{
			_pImpl->addRef();
		}

		virtual ~SharedT()
		{
			if (!_pImpl->releaseRef()) {
				F_SAFE_DELETE(_pImpl);
			}
		}

		T& operator=(const T& other)
		{
			if (&other == this) {
				return *static_cast<T*>(this);
			}

			if (!_pImpl->releaseRef()) {
				F_SAFE_DELETE(_pImpl);
			}
			_pImpl = static_cast<const SharedT<T>*>(&other)->_pImpl;
			_pImpl->addRef();
			return *((T*)this);
		}

	protected:
		SharedImpl* _pImpl;
	};

	struct SharedImpl
	{
		SharedImpl() :
			_ref(1)
		{
		}

		virtual ~SharedImpl() {}

		void addRef() const {
			_ref++;
		}
		
		bool releaseRef() const {
			_ref--;
			return _ref != 0;
		}

	private:
		mutable uint32_t _ref;
	};
}

#endif // _FLOWLIBS_CORE_SHAREDT_H