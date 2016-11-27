#pragma once
#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H
#include <iostream>
using namespace std;
/**
*	Structure for NodeType to use in Linked structure.
*/
template <typename T>
struct NodeType
{
	T data;	///< A data for each node.
	NodeType* next;	///< A node pointer to point succeed node.
};


/**
*	Simple unsorted list class for managing items.
*/
template <typename T>
class LinkedList
{
public:
	/**
	*	default constructor.
	*/
	LinkedList();
	/*
	LinkedList(LinkedList& a) {

		m_nLength = 0;
		m_pList = NULL;
		m_pCurPointer = NULL;

		a.ResetList();
		for (int i = 0; i < a.GetLength(); i++) {
			this->Add(a.GetNext());
		}
	}*/

	/**
	*	destructor.
	*/
	~LinkedList();

	/**
	*	@brief	Initialize list to empty state.
	*	@pre	None
	*	@post	List is empty.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get number of elements in the list.
	*	@pre	None.
	*	@post	Function value = number of elements in list.
	*	@return	Number of elements in this list.
	*/
	int GetLength() const;

	/**
	*	@brief	Add item into this list.
	*	@pre	List is not full. item is not in list.
	*	@post	Item is inserted in this list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Add(T item);

	/**
	*	@brief	Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	int Get(T& item);

	/**
	*	@brief	Initialize current pointer for an iteration through the list.
	*	@pre	None.
	*	@post	current pointer is prior to list. current pointer has been initialized.
	*/
	void ResetList();

	/**
	*	@brief	Get the next element in list.
	*	@pre	current pointer is defined. Element at current pointer is not last in list.
	*	@post	current pointer is updated to next position. item is a copy of element at current pointer.
	*/
	int GetNext();
	void DeleteItem(T& item);
	void GetCurrentItem(T& item);
	void GetCurrentItemPtr(T*& item);
protected:
	NodeType<T>* m_pList;	///< Pointer for pointing a first node // 리스트 포인터.
	NodeType<T>* m_pCurPointer;	//Current pointer.
	int m_nLength;	///리스트에 저장된 노드의 개수
};

// Class constructor
template <typename T>
LinkedList<T>::LinkedList()
{
	m_nLength = 0;
	m_pList = NULL;
	m_pCurPointer = NULL;
}
// Class destructor
template <typename T>
LinkedList<T>::~LinkedList() //리스트내의 모든 node 제거
{
	MakeEmpty();
}

// Initialize list to empty state.
template <typename T>
void LinkedList<T>::MakeEmpty()
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


// Get number of elements in the list.
template <typename T>
int LinkedList<T>::GetLength() const
{
	return m_nLength;
}


template <typename T>
int LinkedList<T>::Add(T item)
{
	// 리스트 초기화
	ResetList();

	// 리스트에 추가할 새로운 node 객체와 이전 노드를 가리킬 포인터 선언
	NodeType<T> *node = new NodeType<T>;
	NodeType<T> *pre;
	bool bFound = false;

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

			// iteration 을 이용해 node 포인터 갱신.
			GetNext();

			// node 포인터가 마지막 node 를 가리키면 그 뒤에 새로운 node 삽입.
			if (m_pCurPointer->next == NULL)
			{
				// 마지막 node 와 새로운 node 연결
				m_pCurPointer->next = node;
				break;
			}
		}
	}

	m_nLength++;

	return 1;
}




// Retrieve list element whose key matches item's key (if present).
template <typename T>
int LinkedList<T>::Get(T& item)
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


// Initializes current pointer for an iteration through the list.
template <typename T>
void LinkedList<T>::ResetList()
{
	// current pointer 초기화
	m_pCurPointer = NULL;
}



template<typename T>
int LinkedList<T>::GetNext()
{	//current position 을 다음 노드로 이동
	if (m_pCurPointer == NULL)
	{
		m_pCurPointer = m_pList;
		return true;
	}
	else
	{
		if (m_pCurPointer->next == NULL)
		{
	
			return false;
		}
		m_pCurPointer = m_pCurPointer->next;
		return true;
	}
}

template<typename T>
void LinkedList<T>::GetCurrentItem(T& item)
{
	//item 에 current position 의 info 를 삽입
	item = m_pCurPointer->data;
}
template<typename T>
void LinkedList<T>::GetCurrentItemPtr(T*& item)
{
	item = &(m_pCurPointer->data);
}

template<typename T>
void LinkedList<T>::DeleteItem(T& item)
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
			if (pre == NULL)//삭제할 정보가 하나 일때 //맨 처음일때
			{
				m_pList = m_pCurPointer->next;
				//tempPtr = m_pCurPointer;
				//m_pCurPointer = m_pCurPointer->next;
				//delete tempPtr;
				delete m_pCurPointer;
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

#endif	// LINKED_LIST