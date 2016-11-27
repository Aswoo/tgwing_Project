#pragma once
#pragma once
#pragma once
#include "DoublySortedLinkedList.h"
using namespace std;

template <typename T>
struct DoublyNodeType;

template <typename T>
class DoublySortedLinkedList;

template <typename T>
class DoublyIterator
{
	friend class DoublySortedLinkedList<T>;

public:
	DoublyIterator(const DoublySortedLinkedList<T> &list) {
		m_List = &list;
		m_pCurrentPos = m_List->m_pFirst;
	};///DoublyIterator 의 생성자
	bool NotNull(); /// 데이터가 비어있는지 확인하는함수
	bool NextNotNull(); /// 리스트의 끝인지 확인하는 함수
	T First(); /// 노드 처음으로 돌아가는 함
	T Next(); /// 이후노드로 돌아가는 함수
	T prev(); /// 이전노드로 돌아가는함수
	DoublyNodeType<T> GetCurrentNode(); /// DoublyNodeType의  m_pCurrentPos를 리턴하는 함수
	void GetCurrentItemPtr(T*& item);
private:
	const DoublySortedLinkedList<T>* m_List; ///< DoublySortedLinkedList 클래스의 객체
	DoublyNodeType<T> *m_pCurrentPos; /// DoublyNodeType의 포인터 변수
};

// 비었는지 안비었는지 확인 
template <typename T>
bool DoublyIterator<T>::NotNull()
{
	if (m_pCurrentPos->data == NULL)
		return false;
	else
		return true;
}
// 다음 노드가 비었는지 확인
template <typename T>
bool DoublyIterator<T>::NextNotNull()
{
	if (m_pCurrentPos->next == NULL)
		return false;
	else
		return true;
}


// list의 처음 node의 item을 반환하는 함수.
template <typename T>
T DoublyIterator<T>::First()
{
	return m_List->m_pFirst->data;
}
template <typename T>
T DoublyIterator<T>::prev()
{
	m_pCurrentPos = m_pCurrentPos->prev;
	return m_pCurrentPos->data;
}
// 다음 node로 이동하고 해당 node의 item을 반환하는 함수.
template <typename T>
T DoublyIterator<T>::Next()
{
	if (m_pCurrentPos != NULL)
	{
		m_pCurrentPos = m_pCurrentPos->next;
		return m_pCurrentPos->data;
	}
}
// 현재 iterator 포인터 반환
template <typename T>
DoublyNodeType<T> DoublyIterator<T>::GetCurrentNode()
{
	return *m_pCurrentPos;
}

template<typename T>
void DoublyIterator<T>::GetCurrentItemPtr(T*& item)
{
	item = &(m_pCurrentPos->data);
}
