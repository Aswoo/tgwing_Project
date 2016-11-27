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
	//void Add_Folder(const char *strFolderPath); // 폴더 추가 함수
	//nt setFileList(LinkedList<string> &value); //파일안의 리스트 설정
	//void setFolderName(string _currentFolderName);

private:
	//LinkedList<string> fileList; // 파일안에 가지고있는 리스트를 만듬
	//string currentFolderName; // 현재 폴더의 이름
	//LinkedList<Contact> m_Folder; // 이 폴더에 저장된 주소록 리스트
};
#endif