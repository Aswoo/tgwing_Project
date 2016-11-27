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

	Application(); // ������


	~Application(); // �Ҹ���


	void Run(); // ���α׷��� ���۰� ��


	int GetCommand(); // Ŀ�ǵ� �Է�

	void DisplayM_List();// ��� ����Ʈ ���

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

	int AddMail(); // ������ �߰��Ѵ�.
	int FindMail(); // ������ �˻��Ѵ�.(����˻�)
	int DeleteMail(); // ���� ���� �˻��� ����
	int FindNDisplayMailByTime();
	void DisplayRecentAddress(); // Queue�� �ִ� �ּҸ� ȭ�鿡 ���(DisplayAllItems() ���

	void AddressMenu(); // �ּҷ� �޴�
	int AddMailAddress(Contact temp); // �ּҷϿ� �����ּ� �߰�
	int DeleteMailAddress(); // �ּҷϿ��� �����ּ� ����
	int SearchMailAddress(); // �ּҷϿ��� �����ּ� �˻�
	void PrintMailAddress(); // �ּҷϿ��� �����ּ� ���
	void TrashFolderMenu(); // ���� ������ �޴�
	void PrintTrashFolder(); // ���� ������ ���
	void RecoveryTrashFolder(); // ���� ���� ����
	int LoginPage(); // �α��� ������
	void SignUp(); // ȸ������
	bool Login(); // �α��ο���
	int savetempListBySender(); // ������� �̸����� �˻��� ����
	int savetempListBySubject(); // �������� �˻� �� ����
	int savetempListByContent(); // �������� �˻��� ����
	int savetempListReadMail(); // ���� ���� �˻� �� ����
	void PrinttempList(); // ��������̸� ����Ʈ ���
	void SimplePrinttempList();
	void MailMenu(); // ���� �޴�
	void SearchMailMenu(); //���� �˻� �޴�
	void savetempListByReadMark(); // ���������� ����
	void makeMailListEmpty();
	bool IsTherePattern(const std::string source,const std::string pattern);


private:
	char* filename;
	User* current_user; // ���� �α����� �����
	DoublySortedLinkedList<User> user_List;	 // ����� ����Ʈ
	ifstream m_InFile;		///< input file descriptor.
	ofstream m_OutFile;		///< output file descriptor.
	DoublySortedLinkedList<Mail> tempList; 
	int m_Command;			///< current command number.
};

#endif	// _APPLICATION_H#pragma once
