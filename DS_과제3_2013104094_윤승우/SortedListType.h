#pragma once
#ifndef _SORTEDLIST_H
#define _SORTEDLIST_H

#include <iostream>
#include <fstream>	
#include <string>
#include <string.h>
using namespace std;

#include "ItemType.h"

#define MAXSIZE 5
class SortedListType
{
public:
	/** @brief SortedArrayList�� ������ */
	SortedListType()
	{
		m_Length = 0;
		ResetList();
		m_maxSize = 20;
		m_Array = new ItemType[m_maxSize]; // �����Ҵ����
	}
	/** @brief SortedArrayList�� �Ҹ��� */
	~SortedListType();
	/**
	*	@brief	����Ʈ�� ���ο� �����͸� �߰��Ѵ�.ID�� �������� �����ؼ� �߰��Ѵ�.
	*	@pre	����Ʈ�� �ʱ�ȭ �Ǿ�� �Ѵ�.
	*	@post	����Ʈ�� ���ο� ������ �߰��Ǿ� �ִ�.
	*	@param [in]	data ���ο� ItemType �� Data
	*	@return �Լ��� �� �۵��� 0 �� �����Ѵ�.
	*/

	int Add(ItemType data);
	/**
	*	@brief	ID(Primary Key)�� ���� ���� �˻��� ID�� ���� �����Ͱ� ����Ʈ�� �ִ��� �˻��ϴ� �Լ��̴� Binary ��ġ�� �̿��Ѵ�.
	*	@pre	�˻��� ID���� �Է¹޾ƾߵȴ�.
	*	@post	�Է��� ID�� �迭�� ������ �˻��ϰ� �ȴ�.
	*	@param [in,out] target ���� ����Ʈ�� �ִ� ���̵�� ���ϱ� ���� ����
	*	@return	�Է��� ���� ID�� list�� ������ mid�� ���� �׷��� ������ 0�� �����Ѵ�.
	*/
	int Get(ItemType &target);
	/**
	*	@brief	ID(Primary Key)�� ���� ���� �˻��� ID�� ���� �����͸� ����Ʈ���� �����ϰ� �ڿ������� �迭�� �̵��� ��ĭ�� ä��� �Լ��̴�.
	*	@pre	�˻��� ID���� �Է¹޾ƾߵȴ�.
	*	@post	�Է��� ID�� �迭�� ������ �����ǰ� �ȴ�.
	*	@param  [in] data ���� ����Ʈ�� �ִ� ���̵�� ���ϱ� ���� ����(���ؼ� ������ ����Ʈ�� �ִ� �� ����)
	*/
	void MakeEmpty();

	/**
	*	@brief	Get a number of records in current list.
	*	@pre	none.
	*	@post	none.
	*	@return	number of records in current list.
	*/
	
	int GetLength();

	/**
	*	@brief	Check capacity of list is full.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list capacity reached to the upper bound, otherwise return false.
	*/
	bool IsFull();

	/**
	*	@brief	primary key�� �������� ������ �ǵ��� �˸��� �ڸ��� �׸��� �߰��Ѵ�.
	*	@pre	list should be initialized.
	*	@post	added the new record into the list.
	*	@param	data	new data.
	*	@return	return 1 if this function works well, otherwise 0.
	*/

	void ResetList();

	/**
	*	@brief	move list iterator to the next item in list and get that item.
	*	@pre	list and list iterator should not be initialized.
	*	@post	iterator is moved to next item.
	*	@param	data	get current iterator's item. it does not need to be initialized.
	*	@return	index of current iterator's item if is not end of list, oterwise return -1.
	*/
	int GetNextItem(ItemType& data);

	/**
	*	@brief	�Ϻθ� ä�����ִ� data�� �˸��� ������ �����Ѵ�.
	*	@pre	data�� ID ������ ä�����־�� �Ѵ�.
	*	@post	data ���� ��� ������ ��� ä������.
	*	@param	data : �Ϻθ� ä�����ִ� ItemType.
	*	@return	ã���� 1, ã�� ���ϸ� 0�� �����Ѵ�.
	*/

	void Delete(ItemType data);

	int GetbyBinarySearch(ItemType& data);
	int FindDisplayMail(ItemType& First_time, ItemType& Last_time, ItemType& data);
	int DeleteMails(ItemType& First_time, ItemType& Last_time, ItemType& data);

private:
	ItemType *m_Array;  ///< list array.
	int m_Length;		///< number of elements in list.
	int m_CurPointer;
	int m_maxSize;

};
#endif	// _SORTEDLIST_H