#pragma once
#ifndef _FOLDER_H
#define _FOLDER_H

#include "LinkedList.h"
#include "User.h"
#include <stdio.h>
#include <direct.h>       //mkdir
#include <errno.h>        //errno
#include "Contact.h"
#include <io.h>
#include <conio.h>
#include <Windows.h>
class Folder
{
public:
	Folder() { }
	~Folder() {}
	//void Add_Folder(const char *strFolderPath); // ���� �߰� �Լ�
	//nt setFileList(LinkedList<string> &value); //���Ͼ��� ����Ʈ ����
	//void setFolderName(string _currentFolderName);

private:
	//LinkedList<string> fileList; // ���Ͼȿ� �������ִ� ����Ʈ�� ����
	//string currentFolderName; // ���� ������ �̸�
	//LinkedList<Contact> m_Folder; // �� ������ ����� �ּҷ� ����Ʈ
};
#endif