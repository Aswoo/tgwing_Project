#include "Folder.h"
/*
void Folder::Add_Folder(const char *full_path)
{
	char temp[256], *sp;
	strcpy(temp, full_path); // ��ι��ڿ��� ����
	sp = temp;
	{
		int nResult = mkdir(full_path);

		if (nResult == 0)
		{
			printf("���� ���� ����");
		}
		else if (nResult == -1)
		{
			perror("���� ���� ���� - ������ �̹� �ְų� ����Ȯ��\n");
			printf("errorno : %d", errno);
		}
	}
}
*/
/*
int Folder::setFileList(LinkedList<string>& value)
{
	/*_finddata_t fd;
	long handle;
	int result = 1;
	handle = _findfirst(".\\*.*", &fd);  //���� ���� �� ��� ������ ã�´�.

	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}

	while (result != -1)
	{
		//printf("File: %s\n", fd.name);
		value.Add(fd.name);
		fileList = value;
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
	*/
/*
	WIN32_FIND_DATA FindData;
	HANDLE hFind;
	char path[255];

	strcpy(path, "c:\windows\*");

	hFind = FindFirstFile((LPCWSTR)path, &FindData);
	if (hFind == INVALID_HANDLE_VALUE)
		return 0;

	do {
		printf("%s", FindData.cFileName);
	} while (FindNextFile(hFind, &FindData));

	FindClose(hFind);
	*/

/*
void Folder::setFolderName(string _currentFolderName)
{
	currentFolderName = _currentFolderName;
}
*/