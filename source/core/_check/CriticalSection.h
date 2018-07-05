/**
* Flow Libs - Core
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_CORE_CRITICALSECTION_H
#define _FLOWLIBS_CORE_CRITICALSECTION_H

#include "library.h"

#if FLOW_PLATFORM & FLOW_PLATFORM_WINDOWS
#include <Windows.h>
#else
#  include <QMutex>
#endif


// -----------------------------------------------------------------------------
//  Class CriticalSection
// -----------------------------------------------------------------------------

class CriticalSection
{
	F_DISABLE_COPY(CriticalSection);

#if FLOW_PLATFORM & FLOW_PLATFORM_WINDOWS

public:
	CriticalSection() { InitializeCriticalSection(&m_critSect); }
	~CriticalSection() { DeleteCriticalSection(&m_critSect); }

	void lock() { EnterCriticalSection(&m_critSect); }
	bool tryLock() { return TryEnterCriticalSection(&m_critSect); }
	void unlock() { LeaveCriticalSection(&m_critSect); }

private:
	CRITICAL_SECTION m_critSect;

#else

public:
    CriticalSection() { }

	void lock() { m_mutex.lock(); }
	bool tryLock() { return m_mutex.tryLock(); }
	void unlock() { m_mutex.unlock(); }

private:
	QMutex m_mutex;

#endif
};

// -----------------------------------------------------------------------------
//  Class SectionLock
// -----------------------------------------------------------------------------

/// The section lock automatically protects a block of code. The constructor
/// locks the given CriticalSection. As soon as the object goes out of scope
/// the section is unlocked.
class SectionLock
{
	//  Constructors and destructor ----------------------------------

public:
	SectionLock(CriticalSection* pCriticalSection, bool initialLock = true)
		: m_pCriticalSection(pCriticalSection), m_isLocked(initialLock)
	{
		if (m_isLocked)
			m_pCriticalSection->lock();
	}

	~SectionLock()
	{
		if (m_isLocked)
			m_pCriticalSection->unlock();
	}

	//  Public commands ----------------------------------------------

public:
	/// Acquires a lock for the critical section.
	void lock()
	{
		if (!m_isLocked)
		{
			m_pCriticalSection->lock();
			m_isLocked = true;
		}
	}
	/// Tries to lock the critical section. Returns immediately if no lock can be obtained.
	bool tryLock()
	{
		if (!m_isLocked) {
			m_isLocked = m_pCriticalSection->tryLock();
		}

		return m_isLocked;
	}
	/// Unlocks the critical section.
	void unlock()
	{
		if (m_isLocked)	{
			m_pCriticalSection->unlock();
			m_isLocked = false;
		}
	}

	//  Internal data members ----------------------------------------

private:
	CriticalSection* m_pCriticalSection;
	bool m_isLocked;
};
	
// -----------------------------------------------------------------------------

#endif // _FLOWLIBS_CORE_CRITICALSECTION_H
