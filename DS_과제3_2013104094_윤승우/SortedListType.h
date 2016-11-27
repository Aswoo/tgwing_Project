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
	/** @brief SortedArrayList의 생성자 */
	SortedListType()
	{
		m_Length = 0;
		ResetList();
		m_maxSize = 20;
		m_Array = new ItemType[m_maxSize]; // 동적할당생성
	}
	/** @brief SortedArrayList의 소멸자 */
	~SortedListType();
	/**
	*	@brief	리스트에 새로운 데이터를 추가한다.ID를 기준으로 정렬해서 추가한다.
	*	@pre	리스트는 초기화 되어야 한다.
	*	@post	리스트에 새로운 정보가 추가되어 있다.
	*	@param [in]	data 새로운 ItemType 형 Data
	*	@return 함수가 오 작동시 0 을 리턴한다.
	*/

	int Add(ItemType data);
	/**
	*	@brief	ID(Primary Key)를 통해 내가 검색한 ID를 가진 데이터가 리스트에 있는지 검색하는 함수이다 Binary 서치를 이용한다.
	*	@pre	검색할 ID값을 입력받아야된다.
	*	@post	입력한 ID가 배열에 없는지 검색하게 된다.
	*	@param [in,out] target 원래 리스트에 있는 아이디와 비교하기 위한 변수
	*	@return	입력한 값의 ID가 list에 있으면 mid을 리턴 그렇지 않으면 0을 리턴한다.
	*/
	int Get(ItemType &target);
	/**
	*	@brief	ID(Primary Key)를 통해 내가 검색한 ID를 가진 데이터를 리스트에서 삭제하고 뒤에서부터 배열을 이동해 빈칸을 채우는 함수이다.
	*	@pre	검색할 ID값을 입력받아야된다.
	*	@post	입력한 ID가 배열에 있으면 삭제되게 된다.
	*	@param  [in] data 원래 리스트에 있는 아이디와 비교하기 위한 변수(비교해서 있으면 리스트에 있는 값 삭제)
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
	*	@brief	primary key를 기준으로 정렬이 되도록 알맞은 자리에 항목을 추가한다.
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
	*	@brief	일부만 채워져있는 data에 알맞은 정보를 저장한다.
	*	@pre	data의 ID 변수는 채워져있어야 한다.
	*	@post	data 안의 멤버 변수가 모두 채워진다.
	*	@param	data : 일부만 채워져있는 ItemType.
	*	@return	찾으면 1, 찾지 못하면 0을 리턴한다.
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