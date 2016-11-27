#pragma once
#define _CRT_NONSTDC_NO_WARNINGS
#pragma warning(disable : 4996)
#ifndef _MAIL_H
#define _MAIL_H

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <ctime>
#include <time.h>
#include <sys/timeb.h>
using namespace std;

enum RelationType2 { smaller, bigger, same };

/**
*	�� ���� Item ���̿� ���踦 LESS,GREATER,EQUAL �� ������
*/


/**item information class.
*/
class Mail
{
public:
	/**
	*	default ������
	*/
	Mail()
	{
		m_sSender = "";
		m_sSubject = "";
		m_sContent.resize(256, 0);
		m_sAddress = "";
		m_sTime.resize(16, 0);
		m_sReadmark = 0;
		m_sReceiver = "";
	}
	/*
	Mail(Mail &temp) {
		
		m_sSender = temp.m_sSender;
		m_sReceiver = temp.m_sReadmark;
		m_sSubject = temp.m_sSubject;
		m_sContent = temp.m_sContent;
		m_sAddress = temp.m_sAddress;
		m_sTime = temp.m_sTime;
		m_sReadmark = temp.m_sReadmark;
	}
	*/
	Mail operator=(const Mail &temp)
	{
		m_sReceiver = temp.m_sReceiver;
		m_sSender = temp.m_sSender;
		m_sSubject = temp.m_sSubject;
		m_sContent = temp.m_sContent;
		m_sAddress = temp.m_sAddress;
		m_slabel = temp.m_slabel;
		m_sTime = temp.m_sTime;
		m_sReadmark = temp.m_sReadmark;
		return *this;
	}

	~Mail() {}

	string GetAddress() // �ּ� ����
	{
		return m_sAddress;
	}

	string GetSubject() //���� ����
	{
		return m_sSubject;
	}

	string GetSender() // ������� �̸� ����
	{
		return m_sSender;
	}
	string GetTime() // �ð� ����
	{
		return m_sTime;
	}
	string GetLabel()
	{
		return m_slabel;
	}
	string GetReceiver()
	{
		return m_sReceiver;
	}
	string GetContent()
	{
		return m_sContent;
	}
	int GetReadmark()
	{
		return m_sReadmark;
	}
	void SetAddress(string inAddress)
	{
		m_sAddress = inAddress;
	}
	 
	void setSubject(string inSubject)
	{
		m_sSubject = inSubject;
	}
	void setSender(string inSender)
	{
		m_sSender = inSender;
	}
	void setContent(string inContent)
	{
		m_sContent.assign(inContent);
	}
	void SetTime(string inTime)
	{
		m_sTime.assign(inTime);
	}
	void SetLabel(string inLabel)
	{
		m_slabel = inLabel;
	}
	void SetReadMark(int inReadmark)
	{
		m_sReadmark = inReadmark;
	}
	void SetReceiver(string inReceiver)
	{
		m_sReceiver = inReceiver;
	}
	void SetRecord(string inLabel, string inSubject, string inSender, string inReceiver, string inAddress, string inContent, string inTime, int inReadmark) // �����»��,�޴»��,����,����,�ð� ����
	{
		SetLabel(inLabel);
		setSender(inSender);
		SetAddress(inAddress);
		setSubject(inSubject);
		setContent(inContent);
		SetTime(inTime);
		SetReceiver(inReceiver);
		SetReadMark(inReadmark);
	}

	/**
	*	@brief	Display student id on screen.
	*	@pre	student id is set.
	*	@post	student id is on screen.
	*/

	/**
	*	@brief	Display student name on screen.
	*	@pre	student name is set.
	*	@post	student name is on screen.
	*/

	void DisplaySenderOnScreen()
	{
		cout << "\tSender : " << m_sSender << endl;
	};
	void DisplaySubjectOnScreen()
	{
		cout << "\tSubject : " << m_sSubject << endl;
	};
	void DisplayContentOnScreen()
	{
		cout << "\tContent : " << m_sContent << endl;
	};
	void DisplayTimeOnScreen()
	{
		cout << "\tTime : " << m_sTime << endl;
	};
	/**
	*	@brief	Display student address on screen.
	*	@pre	student address is set.
	*	@post	student address is on screen.
	*/
	void DisplayAddressOnScreen() // ȭ�鿡 �ּ� ���
	{
		cout << "\tAddress : " << m_sAddress << endl;
	};

	void DisplayLabelOnScreen()
	{
		cout << "\tLabel : " << "<" << m_slabel << ">" << endl;
	}
	void DisplayReceiverOnScreen() {
		cout << "\tReceiver : " << m_sReceiver << endl;
	}
	void DisplayReadmarkOnScreen() {
		string temp = m_sReadmark ? string("Yes") : string("No");
		cout << "\tRead : " << temp << endl;
	}
	/**
	*	@brief	Display an student record on screen.
	*	@pre	student record is set.
	*	@post	student record is on screen.
	*/
	void DisplayRecordOnScreen() // id,name,address ���
	{
		DisplayLabelOnScreen();
		DisplaySubjectOnScreen();
		DisplaySenderOnScreen();
		DisplayReceiverOnScreen();
		DisplayAddressOnScreen();
		DisplayContentOnScreen();
		DisplayTimeOnScreen();
		DisplayReadmarkOnScreen();
	};
	void SetIdFromKB() {}; //Ű����� ���� id �Է�
	void SetNameFromKB() {}; // Ű����� ���� �̸� �Է�
	void SetAddressFromKB(); // Ű����κ��� �ּ� �Է�
	void SetRecordFromKB(); // Ű����κ��� �����»��,�ּ�,����,����,�ð� ����
	void SetsubjectFromKB(); // Ű����κ��� ���� ���� ����
	void SetcontentFromKB(); // Ű����κ��� ���� ���� ����
	void SetReceiverFromdKB(); // Ű���κ��� ������ ��� ����
	void SetSenderFromKB(); // Ű����κ��� �޴��� ����
	void SetTimeFromReal(); // Ű����κ��� �ð� ����
	void SetLabelFromKB(); //Ű����κ��� �� ����
	void SetTimeFromKB(); // Ű����κ��� �ð����� // �˻��û��

	int ReadDataFromFile(ifstream& fin); //���Ϸκ��� ���ڵ带 �д´�

										 /**
							
							*	@brief	Write a record into file.
										 *	@pre	the target file is opened. And the list should be initialized.
										 *	@post	the target file is included the new student record.
										 *	@param	fout	file descriptor.
										 *	@return	return 1 if this function works well, otherwise 0.
										 */
	int WriteDataToFile(ofstream& fout); //������ ���ڵ�� ����

										 /**
										 *	�ΰ��� itemType�� ���Ѵ�
										 *	@brief	Name�� �ΰ��� itemType �� ���Ѵ�.
										 *	@pre	�ΰ��� �������� �ʱ�ȭ �Ǿ� �־���Ѵ�.
										 *	@post	Ÿ�� ������ ���ѵ� �׿� �ٸ� ���ϰ��� ����ϰ� �ȴ�.
										 *	@param	data	Ÿ�� �������� ���ϱ� ���ؼ� ���ȴ�
										 *	@return	 ���� this.id < data.id LESS�� �����ϰ�
										 *			 ���� this.id > data.id GREATER�� �����Ѵ�
										 *			�׷��� ������ EQUAL�� �����Ѵ�.
										 */
	RelationType2 CompareByID(const Mail &data) {};
	RelationType2 CompareBytime(const Mail &data);
	void CopyRecord(Mail inData) {
		SetRecord(inData.m_slabel,inData.m_sSubject, inData.m_sSender,inData.m_sReceiver,
			inData.m_sAddress, inData.m_sContent, inData.m_sTime, inData.m_sReadmark);
	};

	bool operator >(Mail &item)const
	{
		if (m_sTime > item.m_sTime) return true;
		return false;
	}
	bool operator <(Mail& item)const
	{
		if (m_sTime < item.m_sTime) return true;
		return false;
	}
	bool operator ==(Mail& item)const
	{
		if (m_sSubject == item.m_sSubject && m_sSender == item.GetSender()) return true;
	
		return false;
	}	
	friend ostream& operator<<(ostream& os, const Mail& mail) //��¿����� �����ε�
	{
		os << "\t" << mail.m_sReceiver << "\t" << mail.m_sAddress << endl;
		return os;
	}
protected:
	string m_slabel;    /// <label �� �з�
	string m_sSubject;  ///< ���� ����
	string m_sSender;		///< �����»��.
	string m_sReceiver; // �޴� ���
	string m_sAddress;	///< ���� �ּ�
	string m_sContent;  ///< ���� ����
	string m_sTime; //���� ���� �ð�
	int m_sReadmark; // ����ǥ�� -> 0 ���� ����,1����
};

						
#endif	_MAIL_H
