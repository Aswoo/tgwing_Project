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
	};///DoublyIterator �� ������
	bool NotNull(); /// �����Ͱ� ����ִ��� Ȯ���ϴ��Լ�
	bool NextNotNull(); /// ����Ʈ�� ������ Ȯ���ϴ� �Լ�
	T First(); /// ��� ó������ ���ư��� ��
	T Next(); /// ���ĳ��� ���ư��� �Լ�
	T prev(); /// �������� ���ư����Լ�
	DoublyNodeType<T> GetCurrentNode(); /// DoublyNodeType��  m_pCurrentPos�� �����ϴ� �Լ�
	void GetCurrentItemPtr(T*& item);
private:
	const DoublySortedLinkedList<T>* m_List; ///< DoublySortedLinkedList Ŭ������ ��ü
	DoublyNodeType<T> *m_pCurrentPos; /// DoublyNodeType�� ������ ����
};

// ������� �Ⱥ������ Ȯ�� 
template <typename T>
bool DoublyIterator<T>::NotNull()
{
	if (m_pCurrentPos->data == NULL)
		return false;
	else
		return true;
}
// ���� ��尡 ������� Ȯ��
template <typename T>
bool DoublyIterator<T>::NextNotNull()
{
	if (m_pCurrentPos->next == NULL)
		return false;
	else
		return true;
}


// list�� ó�� node�� item�� ��ȯ�ϴ� �Լ�.
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
// ���� node�� �̵��ϰ� �ش� node�� item�� ��ȯ�ϴ� �Լ�.
template <typename T>
T DoublyIterator<T>::Next()
{
	if (m_pCurrentPos != NULL)
	{
		m_pCurrentPos = m_pCurrentPos->next;
		return m_pCurrentPos->data;
	}
}
// ���� iterator ������ ��ȯ
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
