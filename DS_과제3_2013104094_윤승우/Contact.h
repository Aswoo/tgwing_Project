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
	*	default ������
	*/
	Contact()
	{	
		m_sReceiver = "";
		m_sAddress = "";
	}

	/**
	*	�Ҹ���
	*/
	~Contact() {}

	/**
	*	@brief	Get ���� address
	*	@pre	���� address is set.
	*	@post	none.
	*	@return address.
	*/

	string GetAddress(){
		return m_sAddress;
	}
	string GetReceiver() // �޴��� ����
	{
		return m_sReceiver;
	}
	void SetReceiver(string inReceiver)
	{
		m_sReceiver = inReceiver;
	}
	void SetAddress(string inAddress) //�ּ� ����
	{
		m_sAddress = inAddress;
	}
	void SetRecord( string inReceiver, string inAddress) // �����̸�,�ּ�,����
	{
		SetReceiver(inReceiver);
		SetAddress(inAddress);
	}
	void DisplaySenderOnScreen()
	{
		cout << "\t" << m_sReceiver << "\t";
	};
	void DisplayAddressOnScreen() // ȭ�鿡 �ּ� ���
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
	void DisplayRecordOnScreen() // id,name,address ���
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
	void SetAddressFromKB(); // Ű����κ��� �ּ� �Է�

							 /**
							 *	@brief	Set student record from keyboard.
							 *	@pre	none.
							 *	@post	student record is set.
							 */
	void SetRecordFromKB(); // Ű����κ��� �����»��,�ּ�,����,����,�ð� ����

							/**
							*	@brief	Read a record from file.
							*	@pre	the target file is opened.
							*	@post	student record is set.
							*	@param	fin	file descriptor.
							*	@return	return 1 if this function works well, otherwise 0.
							*/
	void SetSenderFromKB(); // Ű����κ��� �޴��� ����
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
	bool operator ==(Contact& item)const // �ּҷ� �˻��� �̸����ϰ� ������ �����ε�
	{
		if (m_sReceiver == item.GetReceiver()) return true;
		return false;
	}
	friend ostream& operator<<(ostream& os, const Contact& contact) //��¿����� �����ε�
	{
		os << "\t" << contact.m_sReceiver << "\t" << "\t" << contact.m_sAddress << endl;
		return os;
	}

	RelationType CompareBySender(const Contact &data);
protected:
	string m_sReceiver;	///< �����»��
	string m_sAddress;	///< ���� �ּ�
};

#endif	// _CONTACT_H
