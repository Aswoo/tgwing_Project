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
			MailMenu(); // 받은 메일함 메뉴
			break;
		case 2:
			AddressMenu(); // 주소록 메뉴
			break;
		case 3:		// delete all the mails in list
			AddMail(); //메일 쓰기
			break;
		case 4:
			TrashFolderMenu(); // 지운편지함 메뉴
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
cout << "이름 : " << data.GetName() << endl;
cout << "주소 : " << data.GetAddress() << endl;
return 0;
}*/
/*int Application::delete_item()
{
int _id;
bool found = false;
cout << "삭제할 아이디를 입력하세요 : ";
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
	cout << "\t   1 : 받은 편지함" << endl;
	cout << "\t   2 : 주소록" << endl;
	cout << "\t   3 : 메일쓰기" << endl;
	cout << "\t   4 : 지운 편지함" << endl;
	cout << "\t   0 : Quit" << endl;
	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}


void Application::findUserByAddress(string address, User*& tempUser)
{
	DoublyIterator<User> iter_user(user_List); //유저리스트 이터레이터
	//user_List.ResetList();
	for (int i = 0; i < user_List.GetLength(); i++) {
		User temp;
		temp = iter_user.GetCurrentNode().data;
		//user_List.GetNext();
		//user_List.GetCurrentItem(temp);
		if (address == temp.get_email_add()) {
			//user_List.GetCurrentItemPtr(tempUser); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 의심
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
	Contact dummy; // 중복검색하기위한 더미
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
    //메일추가
    User* tempUser = NULL;
    findUserByAddress(mail.GetAddress(), tempUser);
    if (tempUser == nullptr) {
    	cout << "잘 못된 메일주소입니다." << endl;
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
		cout << "\t 목록이 비어있습니다." << endl << endl;
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
		//if(iterator.NextNotNull()) mail = iterator.Next(); // 다음이 NULL이 아니라면 다음 노드로 이동
	}
	
	cout << "------------------------------------------------------" << endl;
	int num;
	while (!Turn)
	{
		cout << "\t 원하는 메일이 이 페이지 존재합니까? (y/n) : ";
		cin >> choose;
		vector<Mail>::iterator iterator = m_List->begin(); // 이터레이터 처음 초기화
		switch (choose)
		{
		case 'y':
			//mail = iterator.First();
			cout << "번호 입력 :";
			cin >> num;
			//current_user->getM_List()->ResetList();
			if (index >= num)
			{
				for (int j = 1; j != num; j++)
				{
					iterator++;
				}
				mail = *iterator;
				mail.SetReadMark(1); // ReadMark를 1로 << 읽음표시
				mail.DisplayRecordOnScreen();
				Turn = true;
				break;
			}
			else
				cout << "\t 없는 번호입니다." << endl;
			break;
		case 'n':
			// 작성후 새로등록
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

void Application::CreateDir(string tempPath) //폴더 생성 함수
{
	char DirName[256] = "";  //생성할 디렉초리 이름
	char tempPathCharP[256] = "";
	strcpy_s(tempPathCharP, 256, tempPath.c_str());
	char* p = tempPathCharP;     //인자로 받은 디렉토리
	char* q = DirName;
	wchar_t wcDirName[256];

	mbstowcs(wcDirName, tempPathCharP, strlen(tempPathCharP) + 1);
	LPCWSTR lpcwstrDirName = wcDirName;
	while (*p)
	{
		if (('\\' == *p) || ('/' == *p))   //루트디렉토리 혹은 Sub디렉토리
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
	cout << "\t찾으시는 주소(Address)을 입력하세요 : ";
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
		cout << "\t 메일을 찾지 못하였습니다." << endl;
		return 0;
	}*/
	return 0;
}

int Application::DeleteMail()
{

	bool found = false;
	cout << "\t찾으시는 보낸사람 주소(SenderAddress)을 입력하세요 : ";
	string Sender;

	cin >> Sender;
	vector<Mail>* m_List = current_user->getM_List(); // 받은편지함 이터레이터
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
		cout << "\t찾으시는 메일의 제목을 입력하세요 : ";
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
		cout << "\t메일을 찾을 수 없습니다." << endl;
	}
	return 0;
}


void Application::DisplayRecentAddress() // 최근 주소록 출력
{
	//variable.DisplayRecentAddress();
	cout << endl;
	cout << "\t" << "최근 주소록" << endl;
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
	cout << "\t삭제하려는 주소(E-mail)를 입력해주세요 : ";
	cin >> address;
	if (current_user->deleteContactFromAd_ListByAddress(address))
		return 1;
	else {
		cout << "\t찾지 못하였습니다" << endl;
		return 0;
	}
	return 0;
}
int Application::SearchMailAddress()
{
	string address;
	cout << "\t검색하려는 주소록의 주소(E-mail)를 입력해주세요 :";
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

	//current_user->getAd_List().ResetList();	// 리스트 초기화
											// list의 모든 데이터를 화면에 출력

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
		cout << "\t\t 지운 편지함" << endl;
		cout << "\t 1. 지운 편지함 출력" << endl;
		cout << "\t 2. 지운 편지 복구" << endl;
		cout << "\t 3. 앞선 메뉴로 이동" << endl;
		cout << "\t 번호를 입력하세요 : ";
		cin >> Num;
		switch (Num)
		{
		case 1:
			PrintTrashFolder();// 지운편지함 출력
			break;
		case 2:
			RecoveryTrashFolder();
			// 복구할 편지 선택
			// 지운 편지 복구 지운편지함에서 삭제 후 받은편지함으로 이동
			break;
		case 3:
			return;
			break; // 종료 숫자
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
		cout << "\t\t 주소록 메뉴 " << endl;
		cout << "\t 1. 주소록 추가" << endl;
		cout << "\t 2. 주소록 검색" << endl;
		cout << "\t 3. 주소록 삭제" << endl;
		cout << "\t 4. 주소록 출력" << endl;
		cout << "\t 5. 앞선 메뉴로 이동" << endl;
		cout << "\t 번호를 선택하세요 : ";
		cin >> Num;
		switch (Num)
		{
		case 1:
			address.SetRecordFromKB();
			AddMailAddress(address); // 메일 주소 추가
			break;
		case 2:
			SearchMailAddress();// 검색
			break;
		case 3:
			PrintMailAddress(); // 출력후
			DeleteMailAddress(); //삭제값 선택
			break;
		case 4:
			PrintMailAddress();
			break; // 주소록 출력
		case 5:
			return;
			break; // 종료 숫자
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
	cout << "\t복구하시려는 메일의 보낸사람 주소(Sender)를 입력해주세요 : " << endl;
	cin >> sender;
	cout << "\t제목을 입력해주세요 : ";
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
			cout << "\t성공적으로 복구하였습니다." << endl;
			return;
		}
		if (iter.NextNotNull()) iter.Next(); // 다음노드로 이동
	}
	cout << "\t찾지 못했습니다.";
}

int Application::LoginPage() // 로그인 함수 성공할때 까지
{
	int selectNum = 0;
	bool Access = false;
	while (Access == false)
	{
		cout << endl;
		cout << endl;
		cout << "\t로그인 페이지" << endl;
		cout << "\t 1.로그인" << endl;
		cout << "\t 2.회원가입" << endl;
		cout << "\t 3.나가기" << endl;
		cout << "\t 번호를 입력하세요 :";
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
				cout << "\t 잘못된 입력입니다." << endl;
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
	cout << "\t이메일 주소를 입력해 주세요: ";
	cin >> email;
	cout << "\t패스워드를 입력해주세요: ";
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
	cout << "\t사용하실 이메일을 입력해주세요: ";
	cin >> email;
	for (int i = 0; i < user_List.GetLength(); i++) {
		User temp;
		temp = iter_user.GetCurrentNode().data;
		//user_List.GetNext();
		//user_List.GetCurrentItem(temp);
		if (email == temp.get_email_add()) {
			cout << "\t이메일이 중복됩니다" << endl;
			return;
		}
		if (iter_user.NextNotNull()) iter_user.Next();
	}
	cout << "\t사용하실 패스워드를 입력해주세요: ";
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
	cout << "\t 검색하고자하는 보낸사람 이름을 입력하세요 :";
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
		cout << "\t 찾지 못했습니다";
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
	cout << "\t 검색하고자하는 메일 제목을 입력하세요 :";
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
		cout << "\t 찾지 못했습니다";
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
		cout << "\t 검색하고자하는 메일 내용을 입력하세요 :";
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
			cout << "\t 찾지 못했습니다";
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
		cout << "\t 찾지 못했습니다";
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
	cout << "\t 원하는 메일이 이 페이지 존재합니까? (y/n) : ";
	int num;
	while (!Turn)
	{
		cin >> choose;
		switch (choose)
		{
		case 'y':
			cout << "번호 입력 :";
			cin >> num;
			tempList.ResetList();
			if (index > num)
			{
				for (int j = 0; j != num; j++)
				{
					tempList.GetNext();
					tempList.GetCurrentItem(data);
					data.DisplayRecordOnScreen();
					data.SetReadMark(1); // ReadMark를 1로 << 읽음표시
				}
				Turn = true;
				break;
			}
			else
				cout << "\t 없는 번호입니다." << endl;
			break;
		case 'n':
			// 작성후 새로등록
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
		cout << "\t   1 : 메일쓰기" << endl;
		cout << "\t   2 : 메일 출력" << endl;
		cout << "\t   3 : 모든 메일 비우기" << endl;
		cout << "\t   4 : 메일 지우기" << endl;
		cout << "\t   5 : 메일 검색 메뉴" << endl;
		cout << "\t   6 : 메인 메뉴로 돌아가기" << endl;
		cout << "\t   번호를 입력하세요: ";
		cin >> m_Command;
		while (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "숫자를 입력하세요." << endl;
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
			DeleteMail(); // 메일 삭제			//	FindNDisplayMail();
			break;
		case 5:	   // delete mails in the given time interval
			SearchMailMenu(); // 메일 검색 메뉴
			break;
		case 6:
			Access = false; // return to main menu			
			break;
		default:
			cout << "\t 잘못된 입력!!" << endl;
		}
	}
}

void Application::SearchMailMenu()
{
	bool Access = true;
	cout << "\t   1 : 이름으로 찾기" << endl; // 이름검색
	cout << "\t   2 : 제목으로 찾기" << endl; // 제목검색
	cout << "\t   3 : 날짜별으로 찾기" << endl; // 날짜별 검색
	cout << "\t   4 : 내용으로 찾기" << endl; // 내용 검색
	cout << "\t   5 : 안읽은 메일 찾기" << endl; // 안읽은메일 표시
	cout << "\t   6 : 메인메뉴로 돌아가기" << endl;
	while (Access != false)
	{
		cout << " \t	번호를 입력하세요 :";
		cin >> m_Command;
		switch (m_Command)
		{
		case 1:
			savetempListBySender(); // 보낸사람이름검색
			Access = true;
			break;
		case 2:
			savetempListBySubject(); // 제목검색
			Access = true;
			break;
		case 3:
			FindNDisplayMailByTime(); // 날짜별 검색
			Access = true;
			break;
		case 4:
			savetempListByContent(); // 내용 검색
			Access = true;
			break;
		case 5:
			savetempListByReadMark(); // 안읽은메일만 검색
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
	cout << "처음 시작 시간를 입력하세요 " << endl;
	F_time.SetTimeFromKB(); // 키보드값으로 처음시작시간입력
	cout << "마지막 시간를 입력하세요 " << endl;
	L_time.SetTimeFromKB();// 키보드값으로 마지막시간입력

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
		cout << "\t 해당 메일이 존재하지 않습니다. 날짜 확인요망" << endl;
	}
	else PrinttempList();
	*/
	return 0;
}

bool Application::IsTherePattern(std::string source, std::string pattern)
{
	// Source string 에 pattern 이 존재하는지 안하는지 boolean value를 리턴한다.
	if (source.find(pattern) != std::string::npos)
	{
		// 존재하면 
		return true;
	}
	else
	{
		return false;
	}
}