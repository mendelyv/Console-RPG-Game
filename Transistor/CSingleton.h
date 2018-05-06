/*
File Name : CSingleton.h
Function : Singleton
Updata time : 2017 11 10
*/
/*
单例模式，保证一个类只产生一个对象
*/

#ifndef CSINGLETON_H
#define CSINGLETON_H

template <typename T>
class CSingleton
{
public:
	static T* getInstance()
	{
		if (nullptr != m_pSingleton)
		{
			return m_pSingleton;
		}

		m_pSingleton = new T;

		if (0 != m_pSingleton)
		{
			return m_pSingleton;
		}
		return 0;
	}
protected:
	static T* m_pSingleton;
};

template <typename T> 
T* CSingleton<T>::m_pSingleton = nullptr;//声明静态成员

#endif