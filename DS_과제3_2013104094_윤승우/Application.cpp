#include "Application.h"
#include <windows.h>
Application::Application()
{
	m_Command = 10;
	ReadUserFromFile();
	ReadUserFile();
}
Application::~Application() {
	WriteUserFromList();
	WriteUserFile();
}
// Program driver.
void Application::Run()
{

	if (LoginPage() < 0) return;
	while (m_Command != 0)
	{
		m_Command = GetCommand();

		switch (m_Command)
		{
		case 1:
			MailMenu(); // ���� ������ �޴�
			break;
		case 2:
			AddressMenu(); // �ּҷ� �޴�
			break;
		case 3:		// delete all the mails in list
			AddMail(); //���� ����
			break;
		case 4:
			TrashFolderMenu(); // ���������� �޴�
			break;
		case 0:
			system("exit");
			break;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}


/*int Application::get_item()
{

int _id;
bool found = false;
cin >> _id;
ItemType data;
data.SetId(_id);
n_List.Get(data);
cout << "id" << data.GetId() << endl;
cout << "�̸� : " << data.GetName() << endl;
cout << "�ּ� : " << data.GetAddress() << endl;
return 0;
}*/
/*int Application::delete_item()
{
int _id;
bool found = false;
cout << "������ ���̵� �Է��ϼ��� : ";
cin >> _id;
ItemType data;
data.SetId(_id);
n_List.(data);
n_List.Delete(data);

return 0;
}*/
// Display command on screen and get a input from keyboard.
int Application::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : ���� ������" << endl;
	cout << "\t   2 : �ּҷ�" << endl;
	cout << "\t   3 : ���Ͼ���" << endl;
	cout << "\t   4 : ���� ������" << endl;
	cout << "\t   0 : Quit" << endl;
	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}


void Application::findUserByAddress(string address, User*& tempUser)
{
	DoublyIterator<User> iter_user(user_List); //��������Ʈ ���ͷ�����
	//user_List.ResetList();
	for (int i = 0; i < user_List.GetLength(); i++) {
		User temp;
		temp = iter_user.GetCurrentNode().data;
		//user_List.GetNext();
		//user_List.GetCurrentItem(temp);
		if (address == temp.get_email_add()) {
			//user_List.GetCurrentItemPtr(tempUser); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! �ǽ�
			iter_user.GetCurrentItemPtr(tempUser);
			return;
		}
		if (iter_user.NextNotNull()) iter_user.Next();
	}
	//tempUser = nullptr;
}

int Application::AddMail()
{
	string temp;
	bool Turn = false;
	Mail mail;
	Contact Recent_mail;
	Contact dummy; // �ߺ��˻��ϱ����� ����
	mail.SetTimeFromReal();
	mail.SetLabelFromKB();
	mail.setSender(current_user->get_email_add());
	DisplayRecentAddress();
	cout << "\t Recent Address you sent" << endl;
	mail.SetAddressFromKB();
	mail.SetReceiverFromdKB();
	Recent_mail.SetRecord(mail.GetReceiver(), mail.GetAddress());
	mail.SetsubjectFromKB();
	mail.SetcontentFromKB();
	mail.SetReadMark(0);
    //�����߰�
    User* tempUser = NULL;
    findUserByAddress(mail.GetAddress(), tempUser);
    if (tempUser == nullptr) {
    	cout << "�� ���� �����ּ��Դϴ�." << endl;
    	return -1;
    }
    tempUser->getM_List()->push_back(mail);
    if ((current_user->getRecent_List().IsItInQueue(Recent_mail, dummy) != true))
    {
    	current_user->getRecent_List().EnQueue(Recent_mail);
    }
    
	AddMailAddress(Recent_mail);
	WriteUserFile();
	return 1;
}


void Application::DisplayM_List()
{
	vector<Mail>* m_List = current_user->getM_List();
	vector<Mail>::iterator iterator = m_List->begin();
	if (m_List->size() == 0)
	{
		cout << "\t ����� ����ֽ��ϴ�." << endl << endl;
	}
	else {
	Mail mail;
	Mail _mail;
	int index = 0;
	bool Turn = false;
	char choose;
	string readMark = "new";
	//current_user->getM_List()->ResetList();
	
	cout << "\t" << "\t" << "Sender" << "\t" << "\t" << "Subject" << endl;
	
	cout << "------------------------------------------------------" << endl;
	for (index = 0; index < current_user->getM_List()->size(); index++)
	{
		mail = *iterator;
		if (mail.GetReadmark() == 1) { readMark = "read"; }
		else { readMark = "new"; }
		cout << setw(2) << "[" << index + 1 << "]" << setw(5) << readMark
			<< "\t" << mail.GetSender() << "\t" << "\t" << mail.GetSubject() << endl;
		iterator++;
		//if(iterator.NextNotNull()) mail = iterator.Next(); // ������ NULL�� �ƴ϶�� ���� ���� �̵�
	}
	
	cout << "------------------------------------------------------" << endl;
	int num;
	while (!Turn)
	{
		cout << "\t ���ϴ� ������ �� ������ �����մϱ�? (y/n) : ";
		cin >> choose;
		vector<Mail>::iterator iterator = m_List->begin(); // ���ͷ����� ó�� �ʱ�ȭ
		switch (choose)
		{
		case 'y':
			//mail = iterator.First();
			cout << "��ȣ �Է� :";
			cin >> num;
			//current_user->getM_List()->ResetList();
			if (index >= num)
			{
				for (int j = 1; j != num; j++)
				{
					iterator++;
				}
				mail = *iterator;
				mail.SetReadMark(1); // ReadMark�� 1�� << ����ǥ��
				mail.DisplayRecordOnScreen();
				Turn = true;
				break;
			}
			else
				cout << "\t ���� ��ȣ�Դϴ�." << endl;
			break;
		case 'n':
			// �ۼ��� ���ε��
			Turn = true;
			break;
		default:
			cout << "\t Wrong Number!";
		}
	}
	WriteUserFile();
	}
}

// Display all records in the list on screen.


int Application::WriteUserFromList()
{
 m_OutFile.open("user.txt");
 if (!m_OutFile) return 0;
 DoublyIterator<User> iter_user(user_List);
 int tempSize = user_List.GetLength();
 m_OutFile << tempSize;
 //user_List.ResetList();
 User *tempUser = NULL;
 //tempUser = &iter_user.First();
 for (int i = 0; i < tempSize; i++) {
 	m_OutFile << endl;
	iter_user.GetCurrentItemPtr(tempUser);
 	//user_List.GetNext();
 	//user_List.GetCurrentItemPtr(tempUser);
 	m_OutFile << tempUser->get_email_add() << endl;
 	m_OutFile << tempUser->get_password();
	if (iter_user.NextNotNull()) iter_user.Next();
 }
 m_OutFile.close();

	return 1;
}
int Application::ReadUserFromFile() {
	m_InFile.open("user.txt");
	if (!m_InFile) return 0;

	int tempSize;
	m_InFile >> tempSize;
	for (int i = 0; i < tempSize; i++) {
		User tempUser;
		string temp_email_add;
		string temp_password;
		m_InFile >> temp_email_add >> temp_password;
		tempUser.set_user(temp_email_add, temp_password);
		user_List.justadd(tempUser);
	}
	m_OutFile.close();

	return 1;
}

void Application::CreateDir(string tempPath) //���� ���� �Լ�
{
	char DirName[256] = "";  //������ ���ʸ� �̸�
	char tempPathCharP[256] = "";
	strcpy_s(tempPathCharP, 256, tempPath.c_str());
	char* p = tempPathCharP;     //���ڷ� ���� ���丮
	char* q = DirName;
	wchar_t wcDirName[256];

	mbstowcs(wcDirName, tempPathCharP, strlen(tempPathCharP) + 1);
	LPCWSTR lpcwstrDirName = wcDirName;
	while (*p)
	{
		if (('\\' == *p) || ('/' == *p))   //��Ʈ���丮 Ȥ�� Sub���丮
		{
			if (':' != *(p - 1))
			{
				CreateDirectory(lpcwstrDirName, NULL);
			}
		}
		*q++ = *p++;
		*q = '\0';
	}
	CreateDirectory(lpcwstrDirName, NULL);
}


// Open a file by file descriptor as an input file.
void Application::ReadUserFile()
{
	DoublyIterator<User> iter_user(user_List);
	int tempSize = user_List.GetLength();
	//user_List.ResetList();
	User* temp = NULL;
	//temp = &iter_user.First();
	for (int i = 0; i < tempSize; i++) {
		iter_user.GetCurrentItemPtr(temp);
		//user_List.GetNext();
		//user_List.GetCurrentItemPtr(temp);
		temp->ReadAd_ListFromFile();
		temp->Readm_ListFromFile();
		temp->Readtrash_folderFromFile();
		if (iter_user.NextNotNull()) iter_user.Next();
	}
}


// Open a file by file descriptor as an output file.
void Application::WriteUserFile()
{
	DoublyIterator<User> iter_user(user_List);
	int tempSize = user_List.GetLength();
	//user_List.ResetList();
	User* tempUser = NULL;
	//tempUser = &iter_user.First();
	for (int i = 0; i < tempSize; i++) {
		iter_user.GetCurrentItemPtr(tempUser);
		//user_List.GetNext();
		//user_List.GetCurrentItemPtr(tempUser);
		CreateDir(tempUser->getBaseFileDirectory());
		tempUser->WriteAd_ListToFile();
		tempUser->Writem_ListToFile();
		tempUser->Writetrash_folderToFile();
		tempUser->Writetemp_folderToFile();
		if (iter_user.NextNotNull()) iter_user.Next();
	}
}


// Open a file as a read mode, read all data on the file, and set list by the data.



// Open a file as a write mode, and write all data into the file,


int Application::FindMail()
{
	/*bool found = false;
	cout << "\tã���ô� �ּ�(Address)�� �Է��ϼ��� : ";
	string address;
	cin >> address;
	LinkedList<Mail> tempList = current_user->getMailFromM_ListByAddress(address);
	tempList.ResetList();
	for (int i = 0; i < tempList.GetLength(); i++) {
		Mail temp;
		tempList.GetNext();
		tempList.GetCurrentItem(temp);
		temp.DisplayRecordOnScreen();
		found = true;
	}
	if (found) return 1;
	else {
		cout << "\t ������ ã�� ���Ͽ����ϴ�." << endl;
		return 0;
	}*/
	return 0;
}

int Application::DeleteMail()
{

	bool found = false;
	cout << "\tã���ô� ������� �ּ�(SenderAddress)�� �Է��ϼ��� : ";
	string Sender;

	cin >> Sender;
	vector<Mail>* m_List = current_user->getM_List(); // ���������� ���ͷ�����
	vector<Mail>:: iterator iterator = m_List->begin();
	//current_user->getM_List()->ResetList();
	for (int i = 0; i < current_user->getM_List()->size(); i++) {
		Mail temp;
		temp = *iterator;
		//current_user->getM_List()->GetNext();
		//current_user->getM_List()->GetCurrentItem(temp);
		if (temp.GetSender() == Sender) {
			temp.DisplayRecordOnScreen();
			found = true;
		}
		iterator++;
		//if (iterator.NextNotNull()) iterator.Next();
	}
	if (found) {
		cout << "\tã���ô� ������ ������ �Է��ϼ��� : ";
		string subject;
		cin >> subject;
		vector<Mail>::iterator iter = m_List->begin();
		//current_user->getM_List()->ResetList();
		for (int i = 0; i < current_user->getM_List()->size(); i++) {
			Mail temp;
			temp = *iter;
			//current_user->getM_List()->GetNext();
			//current_user->getM_List()->GetCurrentItem(temp);
			if (temp.GetSubject() == subject && temp.GetSender() == Sender) {
				current_user->getTrash_Folder().Add(temp);
				iter = current_user->getM_List()->erase(iter);
				return 1;
			}
			iter++;//if (iterator.NextNotNull()) iterator.Next();
		}
		return 0;
	}
	else {
		cout << "\t������ ã�� �� �����ϴ�." << endl;
	}
	return 0;
}


void Application::DisplayRecentAddress() // �ֱ� �ּҷ� ���
{
	//variable.DisplayRecentAddress();
	cout << endl;
	cout << "\t" << "�ֱ� �ּҷ�" << endl;
	cout << "\t" << "Name" << "\t"  << "Address" << endl;
	cout << "\t------------------------------------------------------" << endl;
	current_user->showRecent_List();
	cout << "\t------------------------------------------------------" << endl;
}


int Application::AddMailAddress(Contact address)
{
	DoublySortedLinkedList<Contact> ad_List = current_user->getAd_List();
	DoublyIterator<Contact> iter(ad_List);
	Contact temp;
	//->getAd_List().ResetList();
	for (int i = 0; i < current_user->getAd_List().GetLength(); i++)
	{
		temp = iter.GetCurrentNode().data;
		//current_user->getAd_List().GetNext();
		//current_user->getAd_List().GetCurrentItem(temp);
		if ((address.GetAddress()) == temp.GetAddress())
		{
			return 0;
		}
		if (iter.NextNotNull()) iter.Next();
	}
	current_user->getAd_List().Add(address);
	return 1;
}
int Application::DeleteMailAddress()
{
	string address;
	cout << "\t�����Ϸ��� �ּ�(E-mail)�� �Է����ּ��� : ";
	cin >> address;
	if (current_user->deleteContactFromAd_ListByAddress(address))
		return 1;
	else {
		cout << "\tã�� ���Ͽ����ϴ�" << endl;
		return 0;
	}
	return 0;
}
int Application::SearchMailAddress()
{
	string address;
	cout << "\t�˻��Ϸ��� �ּҷ��� �ּ�(E-mail)�� �Է����ּ��� :";
	cin >> address;
	Contact temp = current_user->getContactFromAd_ListByAddress(address);
	temp.DisplayRecordOnScreen();
	return 0;
}

void Application::PrintMailAddress()
{
	DoublySortedLinkedList<Contact> ad_List = current_user->getAd_List();
	DoublyIterator<Contact> iter(ad_List);
	Contact data;
	cout << "\t" << "Name" << "\t" << "\t" << "Address" << endl;
	cout << "\t------------------------------------------------------" << endl;

	//current_user->getAd_List().ResetList();	// ����Ʈ �ʱ�ȭ
											// list�� ��� �����͸� ȭ�鿡 ���

	for (int i = 0; i < current_user->getAd_List().GetLength(); i++)
	{
		data = iter.GetCurrentNode().data;
		//current_user->getAd_List().GetNext();
		//current_user->getAd_List().GetCurrentItem(data);
		data.DisplayRecordOnScreen();
		if (iter.NextNotNull()) iter.Next();
	}
}

void Application::TrashFolderMenu()
{
	int Num = 0;
	while (Num != 3)
	{
		cout << "\t\t ���� ������" << endl;
		cout << "\t 1. ���� ������ ���" << endl;
		cout << "\t 2. ���� ���� ����" << endl;
		cout << "\t 3. �ռ� �޴��� �̵�" << endl;
		cout << "\t ��ȣ�� �Է��ϼ��� : ";
		cin >> Num;
		switch (Num)
		{
		case 1:
			PrintTrashFolder();// ���������� ���
			break;
		case 2:
			RecoveryTrashFolder();
			// ������ ���� ����
			// ���� ���� ���� ���������Կ��� ���� �� �������������� �̵�
			break;
		case 3:
			return;
			break; // ���� ����
		default:
			cout << "you've got the Wrong Number" << endl;
		}
	}
}

void Application::PrintTrashFolder()
{
	cout << "\t Trash Folder " << endl;
	current_user->showTrash_Folder();
}

void Application::AddressMenu()
{
	Contact address;
	int Num = 0;
	while (Num != 5)
	{
		cout << "\t\t �ּҷ� �޴� " << endl;
		cout << "\t 1. �ּҷ� �߰�" << endl;
		cout << "\t 2. �ּҷ� �˻�" << endl;
		cout << "\t 3. �ּҷ� ����" << endl;
		cout << "\t 4. �ּҷ� ���" << endl;
		cout << "\t 5. �ռ� �޴��� �̵�" << endl;
		cout << "\t ��ȣ�� �����ϼ��� : ";
		cin >> Num;
		switch (Num)
		{
		case 1:
			address.SetRecordFromKB();
			AddMailAddress(address); // ���� �ּ� �߰�
			break;
		case 2:
			SearchMailAddress();// �˻�
			break;
		case 3:
			PrintMailAddress(); // �����
			DeleteMailAddress(); //������ ����
			break;
		case 4:
			PrintMailAddress();
			break; // �ּҷ� ���
		case 5:
			return;
			break; // ���� ����
		default:
			cout << "you've got the Wrong Number" << endl;
		}
	}

}

void Application::RecoveryTrashFolder()
{
	DoublySortedLinkedList<Mail> trash_List = current_user->getTrash_Folder();
	DoublyIterator<Mail> iter(trash_List);
	current_user->showTrash_Folder();
	string sender;
	string subject;
	cout << "\t�����Ͻ÷��� ������ ������� �ּ�(Sender)�� �Է����ּ��� : " << endl;
	cin >> sender;
	cout << "\t������ �Է����ּ��� : ";
	cin >> subject;
	//current_user->getTrash_Folder().ResetList();
	for (int i = 0; i < current_user->getTrash_Folder().GetLength(); i++) {
		Mail temp;
		temp = iter.GetCurrentNode().data;
		//current_user->getTrash_Folder().GetNext();
		//current_user->getTrash_Folder().GetCurrentItem(temp);
		if (temp.GetSender() == sender && temp.GetSubject() == subject) {
			current_user->getM_List()->push_back(temp);
			current_user->getTrash_Folder().Delete(temp);
			cout << "\t���������� �����Ͽ����ϴ�." << endl;
			return;
		}
		if (iter.NextNotNull()) iter.Next(); // �������� �̵�
	}
	cout << "\tã�� ���߽��ϴ�.";
}

int Application::LoginPage() // �α��� �Լ� �����Ҷ� ����
{
	int selectNum = 0;
	bool Access = false;
	while (Access == false)
	{
		cout << endl;
		cout << endl;
		cout << "\t�α��� ������" << endl;
		cout << "\t 1.�α���" << endl;
		cout << "\t 2.ȸ������" << endl;
		cout << "\t 3.������" << endl;
		cout << "\t ��ȣ�� �Է��ϼ��� :";
		cin >> selectNum;
		switch (selectNum)
		{
		case 1:
			if (Login())
			{
				Access = true;
			}
			else {
				Access = false;
				cout << "\t �߸��� �Է��Դϴ�." << endl;
			}
			break;
		case 2:
			SignUp();

			break;
		case 3:
			return -1;
			break;
		}
	}
	return 1;
}
bool Application::Login()
{
	DoublyIterator<User> iter_user(user_List);
	//user_List.ResetList();
	User temp;
	string email;
	string password;
	cout << "\t�̸��� �ּҸ� �Է��� �ּ���: ";
	cin >> email;
	cout << "\t�н����带 �Է����ּ���: ";
	cin >> password;
	for (int i = 0; i < user_List.GetLength(); i++) {
		temp = iter_user.GetCurrentNode().data;
		//user_List.GetNext();
		//user_List.GetCurrentItem(temp);
		if (temp.get_email_add() == email &&
			temp.get_password() == password) {
			iter_user.GetCurrentItemPtr(current_user);
			//user_List.GetCurrentItemPtr(current_user);
			return true;
		}
		if (iter_user.NextNotNull()) iter_user.Next();
	}
	return false;
}
void Application::SignUp()
{
	DoublyIterator<User> iter_user(user_List);
	//user_List.ResetList();
	string email;
	string password;
	cout << "\t����Ͻ� �̸����� �Է����ּ���: ";
	cin >> email;
	for (int i = 0; i < user_List.GetLength(); i++) {
		User temp;
		temp = iter_user.GetCurrentNode().data;
		//user_List.GetNext();
		//user_List.GetCurrentItem(temp);
		if (email == temp.get_email_add()) {
			cout << "\t�̸����� �ߺ��˴ϴ�" << endl;
			return;
		}
		if (iter_user.NextNotNull()) iter_user.Next();
	}
	cout << "\t����Ͻ� �н����带 �Է����ּ���: ";
	cin >> password;
	User newUser;
	newUser.set_user(email, password);
	user_List.justadd(newUser);
	WriteUserFromList();
}

int Application::savetempListBySender()
{
	Mail data;
	string Sender;
	bool found = false;
	cout << "\t �˻��ϰ����ϴ� ������� �̸��� �Է��ϼ��� :";
	cin >> Sender;
	//tempList.MakeEmpty();
	//tempList.ResetList();
	vector<Mail>* m_List = current_user->getM_List();
	vector<Mail>::iterator iter = m_List->begin();
	for (iter; iter != m_List->end(); iter++)
	{
		data = *iter;
		if (Sender == data.GetSender())
		{
			tempList.Add(data);
			found = true;
		}
	}

	if (!found)
		cout << "\t ã�� ���߽��ϴ�";
	else {
		PrinttempList();
	}
	
	return 0;
}
int Application::savetempListBySubject()
{
	Mail data;
	string Subject;
	bool found = false;
	cout << "\t �˻��ϰ����ϴ� ���� ������ �Է��ϼ��� :";
	cin >> Subject;
	//tempList.MakeEmpty();
	//tempList.ResetList();
	vector<Mail>* m_List = current_user->getM_List();
	vector<Mail>::iterator iter = m_List->begin();
	for (iter; iter != m_List->end(); iter++)
	{
		data = *iter;
		if (Subject == data.GetSubject())
		{
			tempList.Add(data);
			found = true;
		}
	}
	if (!found)
		cout << "\t ã�� ���߽��ϴ�";
	else
	PrinttempList();
	tempList.MakeEmpty();
	return 0;
}

int Application::savetempListByContent()
{
		Mail key;
		Mail data;
		string Content;
		bool found = false;
		cout << "\t �˻��ϰ����ϴ� ���� ������ �Է��ϼ��� :";
		cin >> Content;
		key.setContent(Content);
		//tempList.MakeEmpty();
		//tempList.ResetList();
		vector<Mail>* m_List = current_user->getM_List();
		vector<Mail>::iterator iter = m_List->begin();
		for (iter; iter != m_List->end(); iter++)
		{
			data = *iter;
			string srcString = data.GetContent();
			if (IsTherePattern(srcString, Content))
			{
				tempList.Add(data);
				found = true;
			}
		}
		if (!found)
			cout << "\t ã�� ���߽��ϴ�";
		else
		PrinttempList();
		tempList.MakeEmpty();
		return 0;
}

void Application::savetempListByReadMark()
{
	Mail data;
	int ReadMark;
	bool found = false;
	//data.SetReadMark(0);
	//tempList.MakeEmpty();
	//tempList.ResetList();
	vector<Mail>* m_List = current_user->getM_List();
	vector<Mail>::iterator iter = m_List->begin();
	for (iter; iter != m_List->end(); iter++)
	{
		if (data.GetReadmark() == 0)
		{
			data = *iter;
			tempList.Add(data);
			found = true;
		}
	}
	if (!found)
		cout << "\t ã�� ���߽��ϴ�";
	else
		PrinttempList();
}
int Application::savetempListReadMail()
{
	return 0;
}
void Application::PrinttempList()
{/*
	DoublyIterator<Mail> iter(tempList);
	Mail data;
	//tempList.ResetList();
	for (int i = 0; i < tempList.GetLength(); i++)
	{
		iter.Next();
		data = iter.GetCurrentNode().data;
		//tempList.GetNext();
		//tempList.GetCurrentItem(data);
		data.DisplayRecordOnScreen();
	}
	*/
}

void Application::SimplePrinttempList()
{/*
	Mail data;
	tempList.ResetList();
	char choose;
	bool Turn = false;
	int index;
	cout << "\t" << "\t" << "Sender" << "\t" << "\t" << "Subject" << endl;
	cout << "------------------------------------------------------" << endl;
	for (index = 0; index < tempList.GetLength(); index++)
	{
		tempList.GetNext();
		tempList.GetCurrentItem(data);
		if (data.GetReadmark() == 0) {
			cout << setw(2) << "[" << index + 1 << "]" << setw(5)
				<< "\t" << data.GetSender() << "\t" << "\t" << data.GetSubject() << endl;
		}
	}
	cout << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "\t ���ϴ� ������ �� ������ �����մϱ�? (y/n) : ";
	int num;
	while (!Turn)
	{
		cin >> choose;
		switch (choose)
		{
		case 'y':
			cout << "��ȣ �Է� :";
			cin >> num;
			tempList.ResetList();
			if (index > num)
			{
				for (int j = 0; j != num; j++)
				{
					tempList.GetNext();
					tempList.GetCurrentItem(data);
					data.DisplayRecordOnScreen();
					data.SetReadMark(1); // ReadMark�� 1�� << ����ǥ��
				}
				Turn = true;
				break;
			}
			else
				cout << "\t ���� ��ȣ�Դϴ�." << endl;
			break;
		case 'n':
			// �ۼ��� ���ε��
			Turn = true;
			break;
		default:
			cout << "\t Wrong Number!";
			continue;
		}
	}
	*/
}

void Application::MailMenu()
{
	bool Access = true;
	while (Access != false) {
		cout << "\t   1 : ���Ͼ���" << endl;
		cout << "\t   2 : ���� ���" << endl;
		cout << "\t   3 : ��� ���� ����" << endl;
		cout << "\t   4 : ���� �����" << endl;
		cout << "\t   5 : ���� �˻� �޴�" << endl;
		cout << "\t   6 : ���� �޴��� ���ư���" << endl;
		cout << "\t   ��ȣ�� �Է��ϼ���: ";
		cin >> m_Command;
		while (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "���ڸ� �Է��ϼ���." << endl;
			cout << "> ";
			cin >> m_Command;
		}
		switch (m_Command)
		{
		case 1:		// Get a mail from keyboard and add to list
			AddMail();
			break;
		case 2:		// display all the mail in list on screen.
			DisplayM_List();
			break;
		case 3:		// delete all the mails in list.
			makeMailListEmpty();
			break;
		case 4:		// display mails in the given time interval
			DeleteMail(); // ���� ����			//	FindNDisplayMail();
			break;
		case 5:	   // delete mails in the given time interval
			SearchMailMenu(); // ���� �˻� �޴�
			break;
		case 6:
			Access = false; // return to main menu			
			break;
		default:
			cout << "\t �߸��� �Է�!!" << endl;
		}
	}
}

void Application::SearchMailMenu()
{
	bool Access = true;
	cout << "\t   1 : �̸����� ã��" << endl; // �̸��˻�
	cout << "\t   2 : �������� ã��" << endl; // ����˻�
	cout << "\t   3 : ��¥������ ã��" << endl; // ��¥�� �˻�
	cout << "\t   4 : �������� ã��" << endl; // ���� �˻�
	cout << "\t   5 : ������ ���� ã��" << endl; // ���������� ǥ��
	cout << "\t   6 : ���θ޴��� ���ư���" << endl;
	while (Access != false)
	{
		cout << " \t	��ȣ�� �Է��ϼ��� :";
		cin >> m_Command;
		switch (m_Command)
		{
		case 1:
			savetempListBySender(); // ��������̸��˻�
			Access = true;
			break;
		case 2:
			savetempListBySubject(); // ����˻�
			Access = true;
			break;
		case 3:
			FindNDisplayMailByTime(); // ��¥�� �˻�
			Access = true;
			break;
		case 4:
			savetempListByContent(); // ���� �˻�
			Access = true;
			break;
		case 5:
			savetempListByReadMark(); // ���������ϸ� �˻�
			Access = true;
			break;
		case 6:
			Access = false;  // return to main menu
			break;
		default:
			cout << "\t Enter the Wrong Number!" << endl;
		}
	}
}

void Application::makeMailListEmpty()
{
	current_user->getM_List()->empty();
}

int Application::FindNDisplayMailByTime()
{
	/*
	Mail F_time;
	Mail L_time;
	Mail data;
	bool found = false;
	cout << "ó�� ���� �ð��� �Է��ϼ��� " << endl;
	F_time.SetTimeFromKB(); // Ű���尪���� ó�����۽ð��Է�
	cout << "������ �ð��� �Է��ϼ��� " << endl;
	L_time.SetTimeFromKB();// Ű���尪���� �������ð��Է�

	DoublySortedLinkedList<Mail>* m_List = current_user->getM_List();
	//m_List->ResetList();
	tempList.MakeEmpty();
	tempList.ResetList();
	for (int i = 0; i < m_List->GetLength(); i++)
	{
		m_List->GetNext();
		m_List->GetCurrentItem(data);
		if (F_time.GetTime() < data.GetTime() && L_time.GetTime() > data.GetTime())
		{
			tempList.Add(data);
			found = true;
		}
	}
	if (!found)
	{
		cout << "\t �ش� ������ �������� �ʽ��ϴ�. ��¥ Ȯ�ο��" << endl;
	}
	else PrinttempList();
	*/
	return 0;
}

bool Application::IsTherePattern(std::string source, std::string pattern)
{
	// Source string �� pattern �� �����ϴ��� ���ϴ��� boolean value�� �����Ѵ�.
	if (source.find(pattern) != std::string::npos)
	{
		// �����ϸ� 
		return true;
	}
	else
	{
		return false;
	}
}