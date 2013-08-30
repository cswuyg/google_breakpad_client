/**************************************************************************/
/** 
* @brief  线程锁封装
* @author cswuyg
* @version 0.0 
* @date 2013/06
*****************************************************************************/ 
#pragma once

#include <windows.h>
namespace gnet
{
	/**
	@brief 线程锁
	@remark 使用CRITICAL_SECTION
	*/
	class CCritical
	{
	public:
		CRITICAL_SECTION m_section;

		CCritical()
		{
			InitializeCriticalSection(&m_section);
		};

		~CCritical()
		{
			DeleteCriticalSection(&m_section);
		};

		void lock()
		{
			EnterCriticalSection(&m_section);
		}

		void unlock()
		{
			LeaveCriticalSection(&m_section);
		}
	};

	/**
	@brief 进程锁
	@remark 使用Mutex
	*/
	class CMutex
	{
	public:
		HANDLE m_event;

		CMutex(const wchar_t* name = NULL)
		{
			m_event = ::CreateMutex(NULL, FALSE, name);
		}

		~CMutex()
		{
			::CloseHandle(m_event);
		}

		void lock()
		{
			::WaitForSingleObject(m_event, INFINITE);
		}

		void unlock()
		{
			::ReleaseMutex(m_event);
		}
	};

	/**
	@brief 锁帮助类

	// 线程锁
	// class data member
	Critical _cs;
	// in class member method
	Lock<> lock(_cs);

	// 进程锁
	// class data member
	Mutex _mutex;
	// in class member method
	Lock<Mutex> lock(_mutex);
	*/
	template < typename T = CCritical >
	class Lock
	{
	public:
		Lock(T& ref) : m_lock(ref)
		{
			m_lock.lock();
		}

		~Lock()
		{
			m_lock.unlock();
		}
	private:
		Lock& operator=(const Lock& obj);
	private:
		T& m_lock;
	};
}

