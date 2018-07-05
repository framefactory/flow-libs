/**
* Flow Libs - Core
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_SINGLETONT_H
#define _FLOWLIBS_SINGLETONT_H

#include "library.h"

namespace flow
{
	// -----------------------------------------------------------------------------
	//  Class SingletonAutoT
	// -----------------------------------------------------------------------------

	/// Template class which can be used as base for automatic singleton classes.
	/// Singletons that derive from FSingletonAutoT are automatically created the
	/// first time their instance() function is called and are destroyed automatically
	/// when the program is terminated. The template type is the type of the derived
	/// class. The derived class must declare the template base class as a friend.
	template <typename T>
	class SingletonAutoT
	{
		//  Static methods -----------------------------------------------

	public:
		/// Returns a pointer to the only instance of this class.
		/// The instance is created the first time this function is called.
		inline static T* instance()
		{
			if (!s_pInstance)
				s_pInstance = new T();

			return s_pInstance;
		}

		/// Returns true if no instance is present.
		static bool isNull() { return (s_pInstance == nullptr); }

		//  Constructors and destructor ----------------------------------

	protected:
		/// Protected default constructor. Use the static member Instance()
		/// to get access to the single instance of this class.
		SingletonAutoT() {}
		/// Virtual destructor.
		virtual ~SingletonAutoT() {}

		//  Internal data members ----------------------------------------

	private:
		template <typename S>
		struct SingletonGuardT
		{
			SingletonGuardT(S** ppInstance)
				: m_ppInstance(ppInstance)
			{
			}

			~SingletonGuardT()
			{
				if (*m_ppInstance) {
					delete *m_ppInstance;
					*m_ppInstance = nullptr;
				}
			}

			S** m_ppInstance;
		};

		static T* s_pInstance;
		static SingletonGuardT<T> s_guard;
	};

	template <typename T>
	T* SingletonAutoT<T>::s_pInstance = nullptr;

	template <typename T>
	typename SingletonAutoT<T>:: template SingletonGuardT<T> SingletonAutoT<T>::s_guard(&s_pInstance);

	// -----------------------------------------------------------------------------
	//  Class FSingletonT
	// -----------------------------------------------------------------------------

	/// Derive a class from this template to ensure that only one object can be
	/// created from the class. The derived class must provide a private or protected
	/// default constructor. createInstance() needs to be called explicitly to create
	/// the singleton instance; destroyInstance() deletes the singleton instance.
	/// The template parameter is the type of the derived class. The derived class
	/// must declare the template base class as a friend.
	template <typename T>
	class SingletonT
	{
		//  Static methods -----------------------------------------------

	public:
		/// Creates the only instance of the class. If the instance
		/// was already created, the function throws an assertion.
		static void createInstance()
		{
			if (!s_pInstance)
				s_pInstance = new T();
			else
				F_ASSERT(false);
		}

		/// Returns a pointer to the only instance of this class.
		inline static T* instance()
		{
			F_ASSERT(s_pInstance);
			return s_pInstance;
		}

		/// Destroys the only instance of this class.
		static void destroyInstance()
		{
			if (s_pInstance) {
				delete s_pInstance;
				s_pInstance = nullptr;
			}
		}

		/// Returns true if no instance is present.
		static bool isNull() { return (s_pInstance == nullptr); }

		//  Constructors and destructor ----------------------------------

	protected:
		/// Protected default constructor. Use the static member Instance()
		/// to get access to the single instance of this class.
		SingletonT() {}
		/// Virtual destructor.
		virtual ~SingletonT() {}

		//  Internal data members ----------------------------------------

	private:
		template <typename S>
		class SingletonGuardT
		{
		public:
			~SingletonGuardT() { S::destroyInstance(); }
		};

		static T* s_pInstance;
		static SingletonGuardT<T> s_guard;
	};

	template <typename T>
	T* SingletonT<T>::s_pInstance = nullptr;

	template <typename T>
	typename SingletonT<T>::template SingletonGuardT<T> SingletonT<T>::s_guard;

	// -----------------------------------------------------------------------------
	//  Class FSingletonAutoBaseT
	// -----------------------------------------------------------------------------

	/// Derive a class from this template to ensure that only one object can be created
	/// from the class. The derived class must provide a private or protected default
	/// constructor. In addition to FSingletonAutoT this class provides an additional
	/// template parameter to specify a base class.
	template <typename T, typename BASE>
	class SingletonAutoBaseT : public BASE
	{
		//  Static methods -----------------------------------------------

	public:
		/// Returns a pointer to the only instance of this class.
		/// The instance is created the first time this function is called.
		inline static T* instance()
		{
			if (!s_pInstance)
				s_pInstance = new T();

			return s_pInstance;
		}

		/// Returns true if no instance is present.
		static bool isNull() { return (s_pInstance == nullptr); }

		//  Constructors and destructor ----------------------------------

	protected:
		/// Protected default constructor. Use the static member Instance()
		/// to get access to the single instance of this class.
		SingletonAutoBaseT() {}
		/// Virtual destructor.
		virtual ~SingletonAutoBaseT() {}

		//  Internal data members ----------------------------------------

	private:
		template <typename S>
		struct SingletonGuardT
		{
			SingletonGuardT(S** ppInstance)
				: m_ppInstance(ppInstance)
			{
			}

			~SingletonGuardT()
			{
				if (*m_ppInstance) {
					delete *m_ppInstance;
					*m_ppInstance = nullptr;
				}
			}

			S** m_ppInstance;
		};

		static T* s_pInstance;
		static SingletonGuardT<T> s_guard;

	};

	template <typename T, typename BASE>
	T* SingletonAutoBaseT<T, BASE>::s_pInstance = nullptr;

	template <typename T, typename BASE>
	typename SingletonAutoBaseT<T, BASE>::template SingletonGuardT<T>
		SingletonAutoBaseT<T, BASE>::s_guard(&s_pInstance);

	// -----------------------------------------------------------------------------
	//  Class FSingletonBaseT
	// -----------------------------------------------------------------------------

	/// Derive a class from this template to ensure that only one object can be created
	/// from the class. The derived class must provide a private or protected default
	/// constructor. In addition to FSingletonT this class provides an additional
	/// template parameter to specify a base class.
	template <typename T, typename BASE>
	class SingletonBaseT : public BASE
	{
		//  Static methods -----------------------------------------------

	public:
		/// Creates the only instance of the class. If the instance
		/// was already created, the function throws an assertion.
		static void createInstance()
		{
			if (!s_pInstance)
				s_pInstance = new T();
			else
				F_ASSERT(false);
		}

		/// Returns a pointer to the only instance of this class.
		inline static T* instance()
		{
			F_ASSERT(s_pInstance);
			return s_pInstance;
		}

		/// Destroys the only instance of this class.
		static void destroyInstance()
		{
			if (s_pInstance) {
				delete s_pInstance;
				s_pInstance = nullptr;
			}
		}

		/// Returns true if no instance is present.
		static bool isNull() { return (s_pInstance == nullptr); }

		//  Constructors and destructor ----------------------------------

	protected:
		/// Protected default constructor. Use the static member Instance()
		/// to get access to the single instance of this class.
		SingletonBaseT() {}
		/// Virtual destructor.
		virtual ~SingletonBaseT() {}

	private:

		//  Internal data members ----------------------------------------

	private:
		template <typename S>
		class SingletonGuardT
		{
		public:
			~SingletonGuardT() { S::destroyInstance(); }
		};

		static T* s_pInstance;
		static SingletonGuardT<T> s_guard;
	};

	template <typename T, typename BASE>
	T* SingletonBaseT<T, BASE>::s_pInstance = nullptr;

	template <typename T, typename BASE>
	typename SingletonBaseT<T, BASE>:: template SingletonGuardT<T> SingletonBaseT<T, BASE>::s_guard;
}

#endif // _FLOWLIBS_SINGLETONT_H
