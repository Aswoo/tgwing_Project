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
	int IsItInQueue(T& key,T& data);  // Queue���� key�� ã�Ƽ� �����ϸ� TRUE�� ����
	int DeleteItem(T& key); // Queue���� key�� ã�Ƽ� ����  
	void DisplayAllItems(); // Queue�� �ִ� key���� �տ������� ���ʴ�� ȭ�鿡 ���
	void DisplayRecentAddress(); //�ֱ� �ּҷ� ���
	int UpdateRecentAddress(T key); // �ֱ� �ּҷ� ����
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
*	@brief hQueueType ������
*	@pre
*	@post ���������� �����Ҵ�
*/


template<class T>
hQueueType<T>::hQueueType()
{
	m_nMaxQueue = 5;
	m_iFront = m_iRear = m_nMaxQueue - 1;
	m_pitems = new T[m_nMaxQueue];
}

/**
*	@brief hQueueType ������
*	@pre max����ŭ m_nMaxQuene ���� �Ҵ�
*	@post ���������� �����Ҵ�
*/
template<class T>
hQueueType<T>::hQueueType(int max)
{
	m_nMaxQueue = max + 1;
	m_iFront = m_iRear = m_nMaxQueue - 1;
	m_pitems = new T[m_nMaxQueue];
}

/**
*	@brief	hQueneType �Ҹ���. �����Ҵ��� ��ü�Ѵ�.
*	@pre	ť �����Ͱ� �޸� ��ü�ȴ�.
*	@post
*/
template<class T>
hQueueType<T>::~hQueueType()
{
	delete[] m_pitems;
}

/**
*	@brief	hQueneType�� ��á���� Ȯ��
*	@pre
*	@post	��á���� true �ƴϸ� false
*/
template<class T>
bool hQueueType<T>::IsFull()
{
	return (m_iRear + 1) % m_nMaxQueue == m_iFront;
}

/**
*	@brief	hQueneType�� ������� Ȯ��
*	@pre
*	@post	������� true �ƴϸ� false
*/
template<class T>
bool hQueueType<T>::IsEmpty()
{
	return m_iRear == m_iFront;
}

/**
*	@brief	ť �ȿ� �����͸� ���� �Լ�
*	@pre
*	@post	m_iFront �� m_iRear �� m_nMaxQuene -1�� �ʱ�ȭ �Ǹ鼭 ť�� �ʱ�ȭ
*/
template<class T>
void hQueueType<T>::MakeEmpty()
{
	m_iFront = m_iReat = m_nMaxQueue - 1;
}
/**
*	@brief	ť�� ���ο� �������� �߰��Ѵ�
*	@pre	rear = rear���� 1�� ���ϰ� maxqueue�� ���� ������ ��
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
*	@brief	ť�� ������ �������� �����Ѵ�
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
*	@brief	ť�� ���ҵ��� ���
*	@pre
*	@post �� ������� ���
*/
template<class T>
void hQueueType<T>::DisplayAllItems()
{
	if (IsEmpty())
		cout << "����ִ�" << endl;
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
*	@brief	ť�� �����߿��� key�� �˻�
*	@pre data��ü�� �Է¹޾� ã������ data��ü�� �����Ѵ�
*	@post ������ true ������ false ��ȯ
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
*	@brief	ť�� �����߿��� key�� �˻� �� ����
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
		//cout << "������ ������ ������ �����մϴ�." << endl;
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
	m_CurPointer++;	// list pointer ����
	if (m_CurPointer == m_Length)	// end of list�̸� -1�� ����
		return -1;
	data = m_Array[m_CurPointer];	// ���� list pointer�� ���ڵ带 ����

	return m_CurPointer;
}