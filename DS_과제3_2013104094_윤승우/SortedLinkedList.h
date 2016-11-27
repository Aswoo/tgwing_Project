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
	SortedLinkedList(); // ������	
	~SortedLinkedList();// �Ҹ��� 

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
			GetNext();
			// iteration �� �̿��� node ������ ����.

			if (m_pCurPointer->data > node->data)
			{
				if (pre == NULL)//������ �ϳ� �� ������) 
				{
					node->next = m_pCurPointer;
					m_pList = node;
				}
				else//������ �ϳ����� �� �� ������
				{
					pre->next = node;
					node->next = m_pCurPointer;
					break;
				}
			}

			if (m_pCurPointer->next == NULL)//����Ʈ�� ������ ������ �������
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
			if (pre == NULL)//������ ������ �ϳ� �϶�
			{
				m_pList = m_pCurPointer->next;
				tempPtr = m_pCurPointer;
				m_pCurPointer = m_pCurPointer->next;
				delete tempPtr;
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


template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
	//����Ʈ���� ��� node ����
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
	// current pointer �ʱ�ȭ
	m_pCurPointer = NULL;
}

/*template<typename T>
void SortedLinkedList<T>::GetCurrentItem(T& item)
{
//item �� current position �� info �� ����
item = m_pCurPointer->data;
}

template<typename T>
void SortedLinkedList<T>::GetNext()
{	//current position �� ���� ���� �̵�
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