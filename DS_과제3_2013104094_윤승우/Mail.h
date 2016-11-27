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
*	두 개의 Item 사이에 관계를 LESS,GREATER,EQUAL 로 정의함
*/


/**item information class.
*/
class Mail
{
public:
	/**
	*	default 생성자
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

	string GetAddress() // 주소 리턴
	{
		return m_sAddress;
	}

	string GetSubject() //제목 리턴
	{
		return m_sSubject;
	}

	string GetSender() // 보낸사람 이름 리턴
	{
		return m_sSender;
	}
	string GetTime() // 시간 리턴
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
	void SetRecord(string inLabel, string inSubject, string inSender, string inReceiver, string inAddress, string inContent, string inTime, int inReadmark) // 보내는사람,받는사람,제목,내용,시간 설정
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
	void DisplayAddressOnScreen() // 화면에 주소 출력
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
	void DisplayRecordOnScreen() // id,name,address 출력
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
	void SetIdFromKB() {}; //키보드로 부터 id 입력
	void SetNameFromKB() {}; // 키보드로 부터 이름 입력
	void SetAddressFromKB(); // 키보드로부터 주소 입력
	void SetRecordFromKB(); // 키보드로부터 보내는사람,주소,제목,내용,시간 설정
	void SetsubjectFromKB(); // 키보드로부터 메일 제목 설정
	void SetcontentFromKB(); // 키보드로부터 메일 내용 설정
	void SetReceiverFromdKB(); // 키보로부터 보내는 사람 설정
	void SetSenderFromKB(); // 키보드로부터 받는이 설정
	void SetTimeFromReal(); // 키보드로부터 시간 설정
	void SetLabelFromKB(); //키보드로부터 라벨 설정
	void SetTimeFromKB(); // 키보드로부터 시간설정 // 검색시사용

	int ReadDataFromFile(ifstream& fin); //파일로부터 레코드를 읽는다

										 /**
							
							*	@brief	Write a record into file.
										 *	@pre	the target file is opened. And the list should be initialized.
										 *	@post	the target file is included the new student record.
										 *	@param	fout	file descriptor.
										 *	@return	return 1 if this function works well, otherwise 0.
										 */
	int WriteDataToFile(ofstream& fout); //파일을 레코드로 저장

										 /**
										 *	두개의 itemType을 비교한다
										 *	@brief	Name로 두개의 itemType 을 비교한다.
										 *	@pre	두개의 아이템은 초기화 되어 있어야한다.
										 *	@post	타겟 파일의 비교한뒤 그에 다른 리턴값을 출력하게 된다.
										 *	@param	data	타겟 아이템을 비교하기 위해서 사용된다
										 *	@return	 만약 this.id < data.id LESS을 리턴하고
										 *			 만약 this.id > data.id GREATER을 리턴한다
										 *			그렇지 않으면 EQUAL을 리턴한다.
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
	friend ostream& operator<<(ostream& os, const Mail& mail) //출력연산자 오버로딩
	{
		os << "\t" << mail.m_sReceiver << "\t" << mail.m_sAddress << endl;
		return os;
	}
protected:
	string m_slabel;    /// <label 고객 분류
	string m_sSubject;  ///< 메일 제목
	string m_sSender;		///< 보내는사람.
	string m_sReceiver; // 받는 사람
	string m_sAddress;	///< 메일 주소
	string m_sContent;  ///< 메일 내용
	string m_sTime; //메일 보낸 시간
	int m_sReadmark; // 읽음표시 -> 0 읽지 않음,1읽음
};

						
#endif	_MAIL_H
