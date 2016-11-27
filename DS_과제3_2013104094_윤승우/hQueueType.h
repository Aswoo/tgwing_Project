#include <iostream>
#include <fstream>	
#include <string>
#include <string.h>
#pragma once;

using namespace std;
template <class T>
class hQueueType
{
public : 
	hQueueType();
	hQueueType(int max);
	~hQueueType();


	bool IsFull();
	bool IsEmpty(); 
	void MakeEmpty();
	void EnQueue(T &item);
	void DeQueue(T &item);
	int IsItInQueue(T& key,T& data);  // Queue에서 key를 찾아서 존재하면 TRUE를 리턴
	int DeleteItem(T& key); // Queue에서 key를 찾아서 삭제  
	void DisplayAllItems(); // Queue에 있는 key들을 앞에서부터 차례대로 화면에 출력
	void DisplayRecentAddress(); //최근 주소록 출력
	int UpdateRecentAddress(T key); // 최근 주소록 갱신
	int GetNextItem(T& data);

private:
	int m_iFront;
	int m_iRear;
	int m_nMaxQueue;	
	int m_CurPointer;
	T *m_pitems;
};
/**
/**
*	@brief hQueueType 생성자
*	@pre
*	@post 각변수들을 동적할당
*/


template<class T>
hQueueType<T>::hQueueType()
{
	m_nMaxQueue = 5;
	m_iFront = m_iRear = m_nMaxQueue - 1;
	m_pitems = new T[m_nMaxQueue];
}

/**
*	@brief hQueueType 생성자
*	@pre max값만큼 m_nMaxQuene 공간 할당
*	@post 각변수들을 동적할당
*/
template<class T>
hQueueType<T>::hQueueType(int max)
{
	m_nMaxQueue = max + 1;
	m_iFront = m_iRear = m_nMaxQueue - 1;
	m_pitems = new T[m_nMaxQueue];
}

/**
*	@brief	hQueneType 소멸자. 동적할당을 해체한다.
*	@pre	큐 포인터가 메모리 해체된다.
*	@post
*/
template<class T>
hQueueType<T>::~hQueueType()
{
	delete[] m_pitems;
}

/**
*	@brief	hQueneType가 꽉찼는지 확인
*	@pre
*	@post	다찼으면 true 아니면 false
*/
template<class T>
bool hQueueType<T>::IsFull()
{
	return (m_iRear + 1) % m_nMaxQueue == m_iFront;
}

/**
*	@brief	hQueneType가 비었는지 확인
*	@pre
*	@post	비었으면 true 아니면 false
*/
template<class T>
bool hQueueType<T>::IsEmpty()
{
	return m_iRear == m_iFront;
}

/**
*	@brief	큐 안에 데이터를 비우는 함수
*	@pre
*	@post	m_iFront 와 m_iRear 와 m_nMaxQuene -1이 초기화 되면서 큐가 초기화
*/
template<class T>
void hQueueType<T>::MakeEmpty()
{
	m_iFront = m_iReat = m_nMaxQueue - 1;
}
/**
*	@brief	큐에 새로운 아이템을 추가한다
*	@pre	rear = rear값에 1을 더하고 maxqueue로 나눈 나머지 값
*	@post
*/
template<class T>
void hQueueType<T>::EnQueue(T& item)
{
	if (IsFull())
	{
		m_iRear = (m_iRear + 1) % m_nMaxQueue;
		m_pitems[m_iRear] = item;
		m_iFront = (m_iFront + 1) % m_nMaxQueue;
	}
	else
		m_iRear = (m_iRear + 1) % m_nMaxQueue;
		m_pitems[m_iRear] = item;
} 

/**
*	@brief	큐에 기존의 아이템을 삭제한다
*	@pre
*	@post
*/
template<class T>
void hQueueType<T>::DeQueue(T& item)
{
	m_iFront = (m_iFront + 1) % m_nMaxQueue;
	item = m_pitems[m_iFront];
}

/**
*	@brief	큐의 원소들을 출력
*	@pre
*	@post 들어간 순서대로 출력
*/
template<class T>
void hQueueType<T>::DisplayAllItems()
{
	if (IsEmpty())
		cout << "비어있다" << endl;
	else {
		T data;
		int index = (m_iFront + 1) % m_nMaxQueue;
		while (index != m_iRear)
		{
			data = m_pitems[index];

			cout << m_pitems[index];
			index = (index + 1) % m_nMaxQueue;
		}
		if (index == m_iRear)
		{
			data = m_pitems[index];
			cout << m_pitems[index];
		}
	}
}
/**
*	@brief	큐의 원소중에서 key를 검색
*	@pre data객체를 입력받아 찾은값을 data객체에 저장한다
*	@post 있으면 true 없으면 false 반환
*/
template<class T>
int hQueueType<T>::IsItInQueue(T& key, T& data)
{
	int index = (m_iFront + 1) % m_nMaxQueue;
	while(index != (m_iRear+1) % m_nMaxQueue)
	{
	if (key == m_pitems[index])
		{
		data = m_pitems[index];
		return true;
		}
		index = (index+1) % m_nMaxQueue;
	}
	return false;
}
/**
*	@brief	큐의 원소중에서 key를 검색 후 삭제
*	@pre
*	@post 
*/
template<class T>
int hQueueType<T>::DeleteItem(T& key)
{
	T data;
	{
		for (int i = (m_iFront + 1) % m_nMaxQueue; i - 1 != m_iRear; i++)
		{
			if (key == m_pitems[i])
			{
				if (i != m_iRear)
				{
					for (int j = i; j < m_iRear; j++)
					{
						m_pitems[j] = m_pitems[j + 1];
					}
					m_iRear = (m_iRear - 1) % m_nMaxQueue;
					break;
				}
				else
				{
					m_iRear = (m_iRear - 1+m_nMaxQueue) % m_nMaxQueue;
					break;
				}
			}

		}
	}
	return 0;
}

/*template<class T>
void hQueueType<T>::DisplayRecentAddress()
{
	if (m_iFront == m_iRear)
		cout << "\t Empty!!" << endl;
	else {
		T data;
		int index = (m_iFront + 1) % m_nMaxQueue;

		while (index != m_iRear)
		{
			data = m_pitems[index];
			data.DisplaySenderOnScreen();
			data.DisplayAddressOnScreen();
			index = (index + 1) % m_nMaxQueue;
		}
		if (index == m_iRear)
		{
			data = m_pitems[index];
			data.DisplaySenderOnScreen();
			data.DisplayAddressOnScreen();
		}
	}
}*/

template<class T>
int hQueueType<T>::UpdateRecentAddress(T key)
{
	T data;
	if (IsItInQueue(key, data))
	{
		//cout << "기존의 정보를 삭제후 대입합니다." << endl;
		DeleteItem(data);
		EnQueue(key);
	}
	else
	{
		EnQueue(key);
	}
	return 0;
}
template<class T>

int hQueueType<T>::GetNextItem(T& data)
{
	m_CurPointer++;	// list pointer 증가
	if (m_CurPointer == m_Length)	// end of list이면 -1을 리턴
		return -1;
	data = m_Array[m_CurPointer];	// 현재 list pointer의 레코드를 복사

	return m_CurPointer;
}