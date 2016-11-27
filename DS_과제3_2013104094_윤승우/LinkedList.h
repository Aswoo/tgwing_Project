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
	NodeType<T>* m_pList;	///< Pointer for pointing a first node // ����Ʈ ������.
	NodeType<T>* m_pCurPointer;	//Current pointer.
	int m_nLength;	///����Ʈ�� ����� ����� ����
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
LinkedList<T>::~LinkedList() //����Ʈ���� ��� node ����
{
	MakeEmpty();
}

// Initialize list to empty state.
template <typename T>
void LinkedList<T>::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
	// ����Ʈ���� ��� ��� ���� �ϰ� ����Ʈ�� length�� �ʱ�ȭ
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
	// ����Ʈ �ʱ�ȭ
	ResetList();

	// ����Ʈ�� �߰��� ���ο� node ��ü�� ���� ��带 ����ų ������ ����
	NodeType<T> *node = new NodeType<T>;
	NodeType<T> *pre;
	bool bFound = false;

	// node ��ü�� �Է¹��� ������ ���� �� �ʱ�ȭ
	node->data = item;
	node->next = NULL;

	// list �� node �� �������� �ʴ� ���
	if (!m_nLength)
	{
		m_pList = node;
	}
	// list �� node �� �ϳ� �̻� �����ϴ� ���
	else
	{
		// ���� ������ node �� �̵� �� ����
		while (1)
		{
			// ���� ��带 ����Ű�� ������ ����
			pre = m_pCurPointer;

			// iteration �� �̿��� node ������ ����.
			GetNext();

			// node �����Ͱ� ������ node �� ����Ű�� �� �ڿ� ���ο� node ����.
			if (m_pCurPointer->next == NULL)
			{
				// ������ node �� ���ο� node ����
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
	// current pointer �ʱ�ȭ
	m_pCurPointer = NULL;
}



template<typename T>
int LinkedList<T>::GetNext()
{	//current position �� ���� ���� �̵�
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
	//item �� current position �� info �� ����
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
			if (pre == NULL)//������ ������ �ϳ� �϶� //�� ó���϶�
			{
				m_pList = m_pCurPointer->next;
				//tempPtr = m_pCurPointer;
				//m_pCurPointer = m_pCurPointer->next;
				//delete tempPtr;
				delete m_pCurPointer;
				bFound = true;
				break;
			}
			if (pre != NULL) //������ ������ �ϳ��̻��϶�
			{

				tempPtr = m_pCurPointer;
				pre->next = m_pCurPointer->next;
				delete tempPtr;
				bFound = true;
				break;
			}

		}
		if (m_pCurPointer->next == NULL)//������ �ϳ��� ������
		{
			cout << "\tNo record in the list.." << endl;
		}
	}
	if (bFound == true) m_nLength--;
	
}

#endif	// LINKED_LIST