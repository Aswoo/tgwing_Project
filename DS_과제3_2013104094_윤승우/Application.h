#pragma once

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

#include "User.h"
#include "SortedLinkedList.h"
#include "hQueueType.h"
#include "LinkedList.h"
#include "Contact.h"
#include "Mail.h"
#include "DoublySortedLinkedList.h"
#include "DoublyIteratorh.h"
#include "Folder.h"

#define FILENAMESIZE 1024

/**
*	application class for item management simply.
*/
class Application
{
public:

	Application(); // 생성자


	~Application(); // 소멸자


	void Run(); // 프로그램의 시작과 끝


	int GetCommand(); // 커맨드 입력

	void DisplayM_List();// 모든 리스트 출력

						   /**
						   *	@brief	Open a file by file descriptor as an input file.
						   *	@pre	a file for reading is exist.
						   *	@post	open the file for reading.
						   *	@param	fileName	a filename to open for reading.
						   *	@return	return 1 if this function works well, otherwise 0.
						   */
	void ReadUserFile();

	/**
	*	@brief	Open a file by file descriptor as an output file.
	*	@pre	list should be initialized.
	*	@post	open the file for writing.
	*	@param	fileName	a filename to open for writing.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	void WriteUserFile();

	/**
	*	@brief	Open a file as a read mode, read all data on the file, and set list by the data.
	*	@pre	The file is not opened.
	*	@post	list holds all records from the file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/

	
	int WriteUserFromList();
	int ReadUserFromFile();
	void CreateDir(string tempPath);
	
	/**
	*	@brief	Open a file as a write mode, and write all data into the file,
	*	@pre	The file is not opened.
	*	@post	the list is stored in the output file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	//int WriteDataToFile();

	void findUserByAddress(string address, User*& tempUser);

	int AddMail(); // 메일을 추가한다.
	int FindMail(); // 메일을 검색한다.(제목검색)
	int DeleteMail(); // 메일 제목 검색후 삭제
	int FindNDisplayMailByTime();
	void DisplayRecentAddress(); // Queue에 있는 주소를 화면에 출력(DisplayAllItems() 사용

	void AddressMenu(); // 주소록 메뉴
	int AddMailAddress(Contact temp); // 주소록에 메일주소 추가
	int DeleteMailAddress(); // 주소록에서 메일주소 삭제
	int SearchMailAddress(); // 주소록에서 메일주소 검색
	void PrintMailAddress(); // 주소록에서 메일주소 출력
	void TrashFolderMenu(); // 지운 메일함 메뉴
	void PrintTrashFolder(); // 지운 메일함 출력
	void RecoveryTrashFolder(); // 지운 메일 복구
	int LoginPage(); // 로그인 페이지
	void SignUp(); // 회원가입
	bool Login(); // 로그인여부
	int savetempListBySender(); // 보낸사람 이름으로 검색후 저장
	int savetempListBySubject(); // 제목으로 검색 후 저장
	int savetempListByContent(); // 내용으로 검색후 저장
	int savetempListReadMail(); // 읽은 메일 검색 후 저장
	void PrinttempList(); // 보낸사람이름 리스트 출력
	void SimplePrinttempList();
	void MailMenu(); // 메일 메뉴
	void SearchMailMenu(); //메일 검색 메뉴
	void savetempListByReadMark(); // 안읽은메일 저장
	void makeMailListEmpty();
	bool IsTherePattern(const std::string source,const std::string pattern);


private:
	char* filename;
	User* current_user; // 현재 로그인한 사용자
	DoublySortedLinkedList<User> user_List;	 // 사용자 리스트
	ifstream m_InFile;		///< input file descriptor.
	ofstream m_OutFile;		///< output file descriptor.
	DoublySortedLinkedList<Mail> tempList; 
	int m_Command;			///< current command number.
};

#endif	// _APPLICATION_H#pragma once
