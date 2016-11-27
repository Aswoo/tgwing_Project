#pragma once

#define _CRT_NONSTDC_NO_WARNINGS
#pragma warning(disable : 4996)
#ifndef _CONTACT_H
#define _CONTACT_H

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <ctime>
#include <time.h>
#include <sys/timeb.h>
#include <iomanip>
using namespace std;

enum RelationType { LESS, GREATER, EQUAL };

/**Qitem information class.
*/
class Contact
{
public:
	/**
	*	default 생성자
	*/
	Contact()
	{	
		m_sReceiver = "";
		m_sAddress = "";
	}

	/**
	*	소멸자
	*/
	~Contact() {}

	/**
	*	@brief	Get 메일 address
	*	@pre	메일 address is set.
	*	@post	none.
	*	@return address.
	*/

	string GetAddress(){
		return m_sAddress;
	}
	string GetReceiver() // 받는이 리턴
	{
		return m_sReceiver;
	}
	void SetReceiver(string inReceiver)
	{
		m_sReceiver = inReceiver;
	}
	void SetAddress(string inAddress) //주소 설정
	{
		m_sAddress = inAddress;
	}
	void SetRecord( string inReceiver, string inAddress) // 상대방이름,주소,설정
	{
		SetReceiver(inReceiver);
		SetAddress(inAddress);
	}
	void DisplaySenderOnScreen()
	{
		cout << "\t" << m_sReceiver << "\t";
	};
	void DisplayAddressOnScreen() // 화면에 주소 출력
	{
		cout << "\t" << m_sAddress << endl;
		cout << "\t------------------------------------------------------";
		cout << endl;
	};

	/**
	*	@brief	Display an student record on screen.
	*	@pre	student record is set.
	*	@post	student record is on screen.
	*/
	void DisplayRecordOnScreen() // id,name,address 출력
	{
		cout << "\t" << m_sReceiver << "\t";
		cout << "\t" << m_sAddress << endl;
		cout << "\t------------------------------------------------------";
		cout << endl;
	};

	/**
	*	@brief	Set student id from keyboard.
	*	@pre	none.
	*	@post	student id is set.
	*/
	void SetAddressFromKB(); // 키보드로부터 주소 입력

							 /**
							 *	@brief	Set student record from keyboard.
							 *	@pre	none.
							 *	@post	student record is set.
							 */
	void SetRecordFromKB(); // 키보드로부터 보내는사람,주소,제목,내용,시간 설정

							/**
							*	@brief	Read a record from file.
							*	@pre	the target file is opened.
							*	@post	student record is set.
							*	@param	fin	file descriptor.
							*	@return	return 1 if this function works well, otherwise 0.
							*/
	void SetSenderFromKB(); // 키보드로부터 받는이 설정
	void SetReceiverFromKB();

	void CopyRecord(Contact inData) { SetRecord(inData.m_sReceiver,
		inData.m_sAddress);
	};

	bool operator >(Contact &item)const
	{
		if (m_sReceiver > item.GetReceiver()) return true;
		return false;
	}
	bool operator <(Contact& item)const
	{
		if (m_sReceiver < item.GetReceiver()) return true;
		return false;
	}
	bool operator ==(Contact& item)const // 주소록 검색시 이름비교하게 연산자 오버로딩
	{
		if (m_sReceiver == item.GetReceiver()) return true;
		return false;
	}
	friend ostream& operator<<(ostream& os, const Contact& contact) //출력연산자 오버로딩
	{
		os << "\t" << contact.m_sReceiver << "\t" << "\t" << contact.m_sAddress << endl;
		return os;
	}

	RelationType CompareBySender(const Contact &data);
protected:
	string m_sReceiver;	///< 보내는사람
	string m_sAddress;	///< 메일 주소
};

#endif	// _CONTACT_H
