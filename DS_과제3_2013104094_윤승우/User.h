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

class User // Login ��� class 
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

	// �̸��ϰ� ��й�ȣ�� �����ϴ� get,set �Լ���

	DoublySortedLinkedList<Contact>& getAd_List() { return Ad_List; };
	vector<Mail>* getM_List() { return &m_List; }
	hQueueType<Contact>& getRecent_List() { return Recent_List; }
	DoublySortedLinkedList<Mail>& getTrash_Folder() { return trash_folder; }
	vector<Mail>* getTemp_Folder() { return &temp_folder; }
	

	//Application class ���� ����Ʈ �����⸦ ���� �Լ�

	LinkedList<Mail>& getMailFromM_ListByAddress(string address);
	Contact getContactFromAd_ListByAddress(string address);

	// �˻��� ���� �Լ� ����

	int deleteContactFromAd_ListByAddress(string address);

	void showAd_List();
	void showM_List();
	void showRecent_List();
	void showTrash_Folder();
	// ����Ʈ ����Լ���

	void setFileDirectory();
	string getBaseFileDirectory() { return baseFileDirectory; }
	string getEachFileDir(enum FileDirNum temp);

	//���������Լ���


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
	//����������,�ּҷ�,���������� �ҷ�����

	void WriteAd_ListToFile();
	void Writem_ListToFile();
	//void WriteRecent_ListToFile(ofstream& fout);
	void Writetrash_folderToFile();
	void Writetemp_folderToFile();
protected:
	ifstream fin;
	ofstream fout;

	string email_add; // �̸���
	string password; // ��и�ȣ
	string baseFileDirectory; //������ġ����
	DoublySortedLinkedList<Contact> Ad_List;  ///< �ּҷ�.
	//SortedLinkedList<Mail> m_List; // ���� ������
	vector<Mail> m_List; // ����
	hQueueType<Contact> Recent_List;/// �ֱ� �ּҷ� ���� �迭
	DoublySortedLinkedList<Mail> trash_folder; // ���� ������
	DoublySortedLinkedList<Folder> Data_List; // �����͸���Ʈ
	vector<Mail> temp_folder; // �ӽ�������
};