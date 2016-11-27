#include <iostream>
#include <fstream>	
#include <string>
#include <string.h>
using namespace std;

#pragma once;

#include "LinkedList.h"


/*template <typename T>
struct NodeType
{
T data;	///< A data for each node.
NodeType* next;	///< A node pointer to point succeed node.
};*/

template<typename T>
class SortedLinkedList : public LinkedList<T>
{
public:
	SortedLinkedList(); // 생성자	
	~SortedLinkedList();// 소멸자 

	int Add(T data);
	int Get(T &target);
	void MakeEmpty();
	void DeleteItem(T& data);
	//void GetNext();
	//void GetCurrentItem(T& item);
	void ResetList();
	int GetLength() const;
	//int GetCurPointer(T& item);

	//NodeType<T> GetCurPointer();
	//NodeType<T> GetList();

};
template <typename T>
void SortedLinkedList<T>::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
	// 리스트내의 모든 노드 제거 하고 리스트의 length를 초기화
	NodeType<T>* tempPtr;

	while (m_pList != NULL)
	{
		tempPtr = m_pList;
		m_pList = m_pList->next;
		delete tempPtr;
	}

	m_nLength = 0;
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList()
{
	m_nLength = 0;
	ResetList();
}

template<typename T>
int SortedLinkedList<T>::Add(T item)
{
	NodeType<T> *node = new NodeType<T>;
	NodeType<T> *pre = NULL;
	//T dummy;
	bool bFound = false;
	ResetList();

	// node 객체에 입력받은 데이터 설정 및 초기화
	node->data = item;
	node->next = NULL;

	// list 에 node 가 존재하지 않는 경우
	if (!m_nLength)
	{
		m_pList = node;
	}
	// list 에 node 가 하나 이상 존재하는 경우
	else
	{
		// 가장 마지막 node 로 이동 후 삽입
		while (1)
		{
			// 이전 노드를 가리키는 포인터 갱신
			pre = m_pCurPointer;
			GetNext();
			// iteration 을 이용해 node 포인터 갱신.

			if (m_pCurPointer->data > node->data)
			{
				if (pre == NULL)//정보가 하나 들어가 있을때) 
				{
					node->next = m_pCurPointer;
					m_pList = node;
				}
				else//정보가 하나보다 더 들어가 있을때
				{
					pre->next = node;
					node->next = m_pCurPointer;
					break;
				}
			}

			if (m_pCurPointer->next == NULL)//리스트에 정보가 끝까지 들어갓을경우
			{
				m_pCurPointer->next = node;
				break;
			}

		}
	}
	m_nLength++;

	return 1;
}

template<typename T>
void SortedLinkedList<T>::DeleteItem(T& item)
{
	ResetList();
	NodeType<T> *pre;
	NodeType<T> *tempPtr;

	bool bFound = false;
	while (1)
	{
		pre = m_pCurPointer;
		GetNext();
		if (m_pCurPointer->data == item)
		{
			if (pre == NULL)//삭제할 정보가 하나 일때
			{
				m_pList = m_pCurPointer->next;
				tempPtr = m_pCurPointer;
				m_pCurPointer = m_pCurPointer->next;
				delete tempPtr;
				bFound = true;
				break;
			}
			if (pre != NULL) //삭제할 정보가 하나이상일때
			{

				tempPtr = m_pCurPointer;
				pre->next = m_pCurPointer->next;
				delete tempPtr;
				bFound = true;
				break;
			}

		}
		if (m_pCurPointer->next == NULL)//정보가 하나도 없을때
		{
			cout << "\tNo record in the list.." << endl;
		}
	}
	if (bFound == true) m_nLength--;
}


template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
	//리스트내의 모든 node 제거
	MakeEmpty();
}

template <typename T>
int SortedLinkedList<T>::GetLength() const
{
	return m_nLength;
}

template <typename T>
int SortedLinkedList<T>::Get(T& item)
{
	bool moreToSearch, found;
	NodeType<T>* location;

	location = m_pList;
	found = false;
	moreToSearch = (location != NULL);

	while (moreToSearch && !found)
	{
		if (item == location->data)
		{
			found = true;
			item = location->data;
		}
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}
	}

	if (found)
		return 1;
	else
		return 0;
}
template <typename T>
void SortedLinkedList<T>::ResetList()
{
	// current pointer 초기화
	m_pCurPointer = NULL;
}

/*template<typename T>
void SortedLinkedList<T>::GetCurrentItem(T& item)
{
//item 에 current position 의 info 를 삽입
item = m_pCurPointer->data;
}

template<typename T>
void SortedLinkedList<T>::GetNext()
{	//current position 을 다음 노드로 이동
if (m_pCurPointer == NULL)
{
m_pCurPointer = m_pList;
}
else {
m_pCurPointer = m_pCurPointer->next;
}
}*/

/* template<typename T>
NodeType<T> SortedLinkedList<T>::GetCurPointer()
{
return m_pCurPointer;
}

template<typename T>
NodeType<T> SortedLinkedList<T>::GetList()
{
return m_pList;
} */