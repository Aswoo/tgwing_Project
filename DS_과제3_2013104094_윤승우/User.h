#pragma once;
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "DoublyIteratorh.h"
#include "DoublySortedLinkedList.h"
#include "SortedLinkedList.h"
#include "hQueueType.h"
#include "Contact.h"
#include "Mail.h"
#include "Folder.h"

enum FileDirNum {
	AD_LIST = 1, M_LIST, RECENT_LIST, TRASH_FOLDER, SENDER_LIST,TEMP_FOLDER
};

class User // Login 기능 class 
{
public:
	User();
	User(User& temp);
	~User();
	void set_email_add(string _email_add);
	void set_password(string _password);
	string get_email_add();	
	string get_password();
	void set_email_addFromKB();
	void set_passwordFromKB();
	void set_user(string _email_add, string _password);

	// 이메일과 비밀번호를 설정하는 get,set 함수들

	DoublySortedLinkedList<Contact>& getAd_List() { return Ad_List; };
	vector<Mail>* getM_List() { return &m_List; }
	hQueueType<Contact>& getRecent_List() { return Recent_List; }
	DoublySortedLinkedList<Mail>& getTrash_Folder() { return trash_folder; }
	vector<Mail>* getTemp_Folder() { return &temp_folder; }
	

	//Application class 에서 리스트 블러오기를 위한 함수

	LinkedList<Mail>& getMailFromM_ListByAddress(string address);
	Contact getContactFromAd_ListByAddress(string address);

	// 검색을 위해 함수 생성

	int deleteContactFromAd_ListByAddress(string address);

	void showAd_List();
	void showM_List();
	void showRecent_List();
	void showTrash_Folder();
	// 리스트 출력함수들

	void setFileDirectory();
	string getBaseFileDirectory() { return baseFileDirectory; }
	string getEachFileDir(enum FileDirNum temp);

	//폴더생성함수들


	bool operator ==(User& item)const
	{
		if (email_add == item.get_email_add() && password ==item.get_password()) return true;
		return false;
	}

	User& operator =(User& item);

	Contact readContact(ifstream& fin);
	Mail readMail(ifstream& fin);
	void writeContact(Contact temp, ofstream& fout);
	void writeMail(Mail temp, ofstream& fout);

	void ReadAd_ListFromFile();
	void Readm_ListFromFile();
	//void ReadRecent_ListFromFile(ifstream& fin);
	void Readtrash_folderFromFile();
	void Readtemp_folderFromFile();
	//지운편지함,주소록,받은편지함 불러오기

	void WriteAd_ListToFile();
	void Writem_ListToFile();
	//void WriteRecent_ListToFile(ofstream& fout);
	void Writetrash_folderToFile();
	void Writetemp_folderToFile();
protected:
	ifstream fin;
	ofstream fout;

	string email_add; // 이메일
	string password; // 비밀먼호
	string baseFileDirectory; //폴더위치변수
	DoublySortedLinkedList<Contact> Ad_List;  ///< 주소록.
	//SortedLinkedList<Mail> m_List; // 받은 메일함
	vector<Mail> m_List; // 실험
	hQueueType<Contact> Recent_List;/// 최근 주소록 저장 배열
	DoublySortedLinkedList<Mail> trash_folder; // 지운 메일함
	DoublySortedLinkedList<Folder> Data_List; // 데이터리스트
	vector<Mail> temp_folder; // 임시저장함
};