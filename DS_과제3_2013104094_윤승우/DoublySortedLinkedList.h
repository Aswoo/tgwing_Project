#pragma once
#include "DoublyIteratorh.h"
#include <iostream>

using namespace std;

#define MAX 10


template <typename T>
class DoublyIterator;

template <typename T>
struct DoublyNodeType
{
	T data;
	DoublyNodeType *prev;
	DoublyNodeType *next;
};


template <typename T>
class DoublySortedLinkedList
{
	friend class DoublyIterator<T>;
public:
	DoublySortedLinkedList(); /// DoublySortedLinkedList 생성자
	~DoublySortedLinkedList() {}; /// DoublySortedLinkedList  소멸자

	bool IsFull(); /// 리스트가 가득 차 있는지 확인하는 함수
	void MakeEmpty();/// 리스트를 초기화 하는 함수
	int GetLength() const { return m_nLength; };/// 리스트의 길이를 리턴하는 함수
	void Add(T item); /// 리스트 추가 함수
	int justadd(T item); //리스트 추가 함수 순서상관없이 더한다.
	void Delete(T item); /// 리스트 삭제 함수
	void Replace(T item); /// 기존에 있는 정보를 교체하는 함수
	int Get(T &item); /// 리스트에 있는 정보를 찾는함수

private:
	DoublyNodeType<T>* m_pFirst;
	DoublyNodeType<T>* m_pLast;
	int m_nLength;

};
/**
*	@brief DoublySortedLinkedList 생성자 각 변수와 포인터를 초기화시켜준다.
*/
template <typename T>
DoublySortedLinkedList<T>::DoublySortedLinkedList()
{
	m_pFirst = NULL;
	m_pLast = NULL;
	m_nLength = 0;
}
/**
*	@brief	리스트 안이 가득 찻는지 확인해주는 여부.
*	@pre	없다
*	@post	다 찻을시 true 리턴 아닐시 false를 리턴한다
*/
template <typename T>
bool DoublySortedLinkedList<T>::IsFull()
{
	DoublyIterator<T> itor(*this);

	if (m_nLength > MAX - 1)
		return true;
	else
		return false;
}

/**
*	@brief	리스트 안을 비우늖 함수.
*	@pre	없다
*	@post	리스트 초기화 .
*/
template <typename T>
void DoublySortedLinkedList<T>::MakeEmpty()
{
	DoublyNodeType<T> *m_pItem;
	DoublyIterator<T> ito(*this);

	while (1)
	{
		m_pItem = ito.m_pCurrentPos;
		if (ito.NextNotNull())
			ito.Next();
		delete m_pItem;
		m_nLength--;
		if (m_nLength == 0)
		{
			m_pFirst = NULL;
			m_pLast = NULL;
			return;

		}
	}

}

/**
*	@brief	리스트에 새로운 데이터를 추가한다.ID를 기준으로 정렬해서 추가한다.
*	@pre	리스트는 초기화 되어야 한다.
*	@post	리스트에 새로운 정보가 추가되어 있다.
*	@param [in]	item 새로운 T 형 item
*	@return 없다
*/
template <typename T>
int DoublySortedLinkedList<T>::justadd(T item) // 순서 상관없이 unsorted로 더한다.
{
	DoublyIterator<T> ite(*this);
	DoublyNodeType<T> *node = new DoublyNodeType<T>;

	node->data = item;
	node->next = NULL;
	node->prev = NULL;

	if (!IsFull())
	{
		if (!m_nLength) /// 하나의 정보도 없을때.
		{
			m_pFirst = m_pLast = node;
		}
		else
		{
			m_pLast->next = node;
			node->prev = m_pLast;
			m_pLast = node;
		}
	}
	m_nLength++;
	return 0;
}
template <typename T>
void DoublySortedLinkedList<T>::Add(T item)
{
	DoublyNodeType<T> *m_pitems = new DoublyNodeType<T>;
	DoublyNodeType<T> *temp;
	DoublyIterator<T> ito(*this);

	m_pitems->data = item;
	m_pitems->prev = NULL;
	m_pitems->next = NULL;

	if (!IsFull())
	{
		if (!m_nLength)/// 정보가 하나도 없을때
		{
			m_pLast = m_pFirst = m_pitems;
		}
		else
		{
			while (1)
			{
				if (ito.m_pCurrentPos->data > m_pitems->data)/// 만약 데이터가 같다면
				{
					if (ito.m_pCurrentPos->prev == NULL) /// 하나의 정보만 차있을때
					{
						ito.m_pCurrentPos->prev = m_pitems;
						m_pitems->next = ito.m_pCurrentPos;
						m_pitems->prev = NULL;
						m_pFirst = m_pitems;

					}
					else /// 하나의 정보만 차잇는게 아닐때
					{
						temp = ito.m_pCurrentPos->prev;
						ito.m_pCurrentPos->prev = m_pitems;
						temp->next = m_pitems;
						m_pitems->prev = temp;
						m_pitems->next = ito.m_pCurrentPos;
					}
					break;
				}

				if (ito.m_pCurrentPos->next == NULL) // 만약 리스트의 끝까지 정렬할 필요가 없을때
				{
					ito.m_pCurrentPos->next = m_pitems;
					m_pitems->prev = ito.m_pCurrentPos;
					m_pLast = m_pitems;
					break;
				}
				ito.Next();
			}
		}
	}
	m_nLength++;

}
/**
*	@brief	이름를 통해 검색한 이름을 리스트에서 삭제한다.
*	@pre	검색할 이름값을 입력받아야된다.
*	@post	입력한 이름 리스트에 있으면 삭제되게 된다.
*	@param  [in] item 원래 리스트에 있는 아이디와 비교하기 위한 변수(비교해서 있으면 리스트에 있는 값 삭제)
*/
template <typename T>
void DoublySortedLinkedList<T>::Delete(T item)
{
	DoublyNodeType<T> *m_pitems = new DoublyNodeType<T>;

	DoublyIterator<T> ito(*this);
	DoublyNodeType<T> *temp;

	m_pitems->data = item;
	m_pitems->prev = NULL;
	m_pitems->next = NULL;

	bool bFound = false;

	while (1)
	{
		if (ito.m_pCurrentPos->data == m_pitems->data)
		{
			if (ito.m_pCurrentPos->prev == NULL)
			{
				temp = ito.m_pCurrentPos;
				ito.m_pCurrentPos = ito.m_pCurrentPos->next;
				if(ito.m_pCurrentPos != NULL) ito.m_pCurrentPos->prev = NULL;
				if(ito.m_pCurrentPos != NULL) m_pFirst = ito.m_pCurrentPos;
				delete temp;
			}
			else if (ito.m_pCurrentPos->next == NULL)
			{
				temp = ito.m_pCurrentPos;
				ito.prev();
				ito.m_pCurrentPos->next = NULL;
				m_pLast = ito.m_pCurrentPos;
				delete temp;
			}
			else
			{
				temp = ito.m_pCurrentPos;
				temp->prev->next = ito.m_pCurrentPos->next;
				temp->next->prev = ito.m_pCurrentPos->prev;
				delete temp;
			}
			bFound = true;
			break;
		}
		if (ito.m_pCurrentPos->next == NULL)
		{
			cout << "\tNo record in the list.." << endl;
			return;
		}
		ito.Next();

	}

	if (bFound == true) m_nLength--;
}
/**
*	@brief	이름을 통해 내가 검색한 ID를 가진 데이터를 리스트에서 다른 정보로 대체하는 것이다.
*	@pre	검색할 이름값을 입력받아야된다.
*	@post	입력한 이름가 배열에 있으면 다른 데이터로 대체되게 된다
*	@param  item 원래 리스트에 있는 아이디와 비교하기 위한 변수(비교해서 있으면 리스트에 있는 값 대체) - 원래 있던 곳을 대신 해서 새로운 값을 추가 하는 것이므로 정렬을 하지 않는다.
*/

template <typename T>
void DoublySortedLinkedList<T>::Replace(T item)
{
	DoublyNodeType<T> *m_pitems = new DoublyNodeType<T>;
	DoublyNodeType<T> *new_data = new DoublyNodeType<T>;
	DoublyIterator<T> ito(*this);
	DoublyNodeType<T> *temp;


	m_pitems->data = item;
	m_pitems->prev = NULL;
	m_pitems->next = NULL;

	new_data->prev = NULL;
	new_data->next = NULL;



	while (1)
	{
		if (ito.m_pCurrentPos->data == m_pitems->data)
		{
			cin >> new_data->data;
			if (ito.m_pCurrentPos->prev == NULL)
			{
				temp = ito.m_pCurrentPos;
				new_data->prev = NULL;
				new_data->next = ito.m_pCurrentPos->next;
				ito.m_pCurrentPos->next->prev = new_data;
				m_pFirst = new_data;
				delete temp;
			}

			else if (ito.m_pCurrentPos->next == NULL)
			{
				temp = ito.m_pCurrentPos;
				new_data->prev = ito.m_pCurrentPos->prev;
				new_data->next = NULL;
				ito.m_pCurrentPos->prev->next = new_data;
				m_pLast = new_data;
				delete temp;
			}

			else
			{
				temp = ito.m_pCurrentPos;
				new_data->next = ito.m_pCurrentPos->next;
				new_data->prev = ito.m_pCurrentPos->prev;
				ito.m_pCurrentPos->prev->next = new_data;
				ito.m_pCurrentPos->next->prev = new_data;
				delete temp;
			}
			break;
		}
		ito.Next();

	}
}
/**
*	@brief	ID(Primary Key)를 통해 내가 검색한 ID를 가진 데이터가 리스트에 있는지 검색하는 함수이다
*	@pre	검색할 ID값을 입력받아야된다.
*	@post	입력한 ID가 배열에 없는지 검색하게 된다.
*	@param [in,out]  item 원래 리스트에 있는 아이디와 비교하기 위한 변수
*	@return	입력한 값의 ID가 list에 있으면 1을 리턴 그렇지 않으면 0을 리턴한다.
*/

template <typename T>
int DoublySortedLinkedList<T>::Get(T &item)
{

	DoublyNodeType<T> *m_pitems = new DoublyNodeType<T>;
	DoublyIterator<T> ito(*this);

	m_pitems->data = item;
	m_pitems->prev = NULL;
	m_pitems->next = NULL;

	while (1)
	{
		if (ito.m_pCurrentPos->data == m_pitems->data)
		{

			return 1;
		}
		if (ito.NextNotNull() == 1)
		{
			ito.Next();
		}
		else if (ito.NextNotNull() == 0)
		{
			return 0;
		}
	}

}






































