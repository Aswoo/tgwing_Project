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
	DoublySortedLinkedList(); /// DoublySortedLinkedList ������
	~DoublySortedLinkedList() {}; /// DoublySortedLinkedList  �Ҹ���

	bool IsFull(); /// ����Ʈ�� ���� �� �ִ��� Ȯ���ϴ� �Լ�
	void MakeEmpty();/// ����Ʈ�� �ʱ�ȭ �ϴ� �Լ�
	int GetLength() const { return m_nLength; };/// ����Ʈ�� ���̸� �����ϴ� �Լ�
	void Add(T item); /// ����Ʈ �߰� �Լ�
	int justadd(T item); //����Ʈ �߰� �Լ� ����������� ���Ѵ�.
	void Delete(T item); /// ����Ʈ ���� �Լ�
	void Replace(T item); /// ������ �ִ� ������ ��ü�ϴ� �Լ�
	int Get(T &item); /// ����Ʈ�� �ִ� ������ ã���Լ�

private:
	DoublyNodeType<T>* m_pFirst;
	DoublyNodeType<T>* m_pLast;
	int m_nLength;

};
/**
*	@brief DoublySortedLinkedList ������ �� ������ �����͸� �ʱ�ȭ�����ش�.
*/
template <typename T>
DoublySortedLinkedList<T>::DoublySortedLinkedList()
{
	m_pFirst = NULL;
	m_pLast = NULL;
	m_nLength = 0;
}
/**
*	@brief	����Ʈ ���� ���� ������ Ȯ�����ִ� ����.
*	@pre	����
*	@post	�� ������ true ���� �ƴҽ� false�� �����Ѵ�
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
*	@brief	����Ʈ ���� ���e �Լ�.
*	@pre	����
*	@post	����Ʈ �ʱ�ȭ .
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
*	@brief	����Ʈ�� ���ο� �����͸� �߰��Ѵ�.ID�� �������� �����ؼ� �߰��Ѵ�.
*	@pre	����Ʈ�� �ʱ�ȭ �Ǿ�� �Ѵ�.
*	@post	����Ʈ�� ���ο� ������ �߰��Ǿ� �ִ�.
*	@param [in]	item ���ο� T �� item
*	@return ����
*/
template <typename T>
int DoublySortedLinkedList<T>::justadd(T item) // ���� ������� unsorted�� ���Ѵ�.
{
	DoublyIterator<T> ite(*this);
	DoublyNodeType<T> *node = new DoublyNodeType<T>;

	node->data = item;
	node->next = NULL;
	node->prev = NULL;

	if (!IsFull())
	{
		if (!m_nLength) /// �ϳ��� ������ ������.
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
		if (!m_nLength)/// ������ �ϳ��� ������
		{
			m_pLast = m_pFirst = m_pitems;
		}
		else
		{
			while (1)
			{
				if (ito.m_pCurrentPos->data > m_pitems->data)/// ���� �����Ͱ� ���ٸ�
				{
					if (ito.m_pCurrentPos->prev == NULL) /// �ϳ��� ������ ��������
					{
						ito.m_pCurrentPos->prev = m_pitems;
						m_pitems->next = ito.m_pCurrentPos;
						m_pitems->prev = NULL;
						m_pFirst = m_pitems;

					}
					else /// �ϳ��� ������ ���մ°� �ƴҶ�
					{
						temp = ito.m_pCurrentPos->prev;
						ito.m_pCurrentPos->prev = m_pitems;
						temp->next = m_pitems;
						m_pitems->prev = temp;
						m_pitems->next = ito.m_pCurrentPos;
					}
					break;
				}

				if (ito.m_pCurrentPos->next == NULL) // ���� ����Ʈ�� ������ ������ �ʿ䰡 ������
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
*	@brief	�̸��� ���� �˻��� �̸��� ����Ʈ���� �����Ѵ�.
*	@pre	�˻��� �̸����� �Է¹޾ƾߵȴ�.
*	@post	�Է��� �̸� ����Ʈ�� ������ �����ǰ� �ȴ�.
*	@param  [in] item ���� ����Ʈ�� �ִ� ���̵�� ���ϱ� ���� ����(���ؼ� ������ ����Ʈ�� �ִ� �� ����)
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
*	@brief	�̸��� ���� ���� �˻��� ID�� ���� �����͸� ����Ʈ���� �ٸ� ������ ��ü�ϴ� ���̴�.
*	@pre	�˻��� �̸����� �Է¹޾ƾߵȴ�.
*	@post	�Է��� �̸��� �迭�� ������ �ٸ� �����ͷ� ��ü�ǰ� �ȴ�
*	@param  item ���� ����Ʈ�� �ִ� ���̵�� ���ϱ� ���� ����(���ؼ� ������ ����Ʈ�� �ִ� �� ��ü) - ���� �ִ� ���� ��� �ؼ� ���ο� ���� �߰� �ϴ� ���̹Ƿ� ������ ���� �ʴ´�.
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
*	@brief	ID(Primary Key)�� ���� ���� �˻��� ID�� ���� �����Ͱ� ����Ʈ�� �ִ��� �˻��ϴ� �Լ��̴�
*	@pre	�˻��� ID���� �Է¹޾ƾߵȴ�.
*	@post	�Է��� ID�� �迭�� ������ �˻��ϰ� �ȴ�.
*	@param [in,out]  item ���� ����Ʈ�� �ִ� ���̵�� ���ϱ� ���� ����
*	@return	�Է��� ���� ID�� list�� ������ 1�� ���� �׷��� ������ 0�� �����Ѵ�.
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






































