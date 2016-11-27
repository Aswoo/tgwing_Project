#include "User.h"

User::User()
{
	email_add = " ";
	password = " ";
}
User::User(User & temp)
{
	*this = temp;
}
User::~User()
{

}

void User::set_email_add(string _email_add)
{
	email_add = _email_add;
}
void User::set_password(string _password)
{
	password = _password;
}
string User::get_email_add()
{
	return email_add;
}
string User::get_password()
{
	return password;
}

void User::set_email_addFromKB()
{
	cout << "\t Email Address : ";
	cin >> email_add;
}
void User::set_passwordFromKB()
{
	cout << "\t Password : ";
	cin >> password;
}


void User::set_user(string _email_add, string _password)
{
	email_add = _email_add;
	password = _password;
	setFileDirectory();
}

Contact User::readContact(ifstream & fin)
{
	Contact temp;
	string tempReceiver;
	string tempAddress;
	fin>> tempReceiver;
	fin>>tempAddress;
	temp.SetReceiver(tempReceiver);
	temp.SetAddress(tempAddress);
	return temp;
}

Mail User::readMail(ifstream & fin)
{
	Mail temp;
	string templabel;
	string tempSubject;
	string tempSender;
	string tempReceiver;
	string tempAddress;
	string tempContent;
	string tempTime;
	int tempReadmark;
	fin >> templabel >> tempSubject >> tempSender >> tempReceiver
		>> tempAddress;
	char c;
	while (fin.get(c)) {
		if (c == '#') {
			break;
		}
		else if (c == '\n') {
		}
		else {
			string temp(1, c);
			tempContent.append(temp);
		}
	}
	fin>>tempTime >> tempReadmark;
	temp.SetRecord(templabel, tempSubject, tempSender, tempReceiver, tempAddress, tempContent, tempTime, tempReadmark);
	return temp;
}
void User::writeContact(Contact temp, ofstream& fout) {
	fout << endl
		<< temp.GetReceiver() << endl
		<< temp.GetAddress();
};
void User::writeMail(Mail temp, ofstream& fout) {
	fout << endl
		<< temp.GetLabel() << endl
		<< temp.GetSubject() << endl
		<< temp.GetSender() << endl
		<< temp.GetReceiver() << endl
		<< temp.GetAddress() << endl
		<< temp.GetContent() <<"#"<< endl
		<< temp.GetTime() << endl
		<< temp.GetReadmark();
}
void User::ReadAd_ListFromFile()
{
	fin.open(getEachFileDir(AD_LIST));
	int tempSize;
	fin >> tempSize;
	for (int i = 0;i < tempSize;i++) {
		Ad_List.Add(readContact(fin));
	}
	fin.close();
}
void User::Readm_ListFromFile()
{
	fin.open(getEachFileDir(M_LIST));
	int tempSize;
	fin >> tempSize;
	for (int i = 0;i < tempSize;i++) {
		m_List.push_back(readMail(fin));
	}
	fin.close();
}
/*
void User::ReadRecent_ListFromFile(ifstream & fin)
{
	int tempSize;
	fin >> tempSize;
	for (int i = 0;i < tempSize;i++) {
		Recent_List.EnQueue(readContact(fin));
	}
}
*/
void User::Readtrash_folderFromFile()
{
	fin.open(getEachFileDir(TRASH_FOLDER));
	int tempSize;
	fin >> tempSize;
	for (int i = 0;i < tempSize;i++) {
		trash_folder.Add(readMail(fin));
	}
	fin.close();
}
void User::Readtemp_folderFromFile()
{
	fin.open(getEachFileDir(TEMP_FOLDER));
	int tempSize;
	fin >> tempSize;
	for (int i = 0; i < tempSize; i++) {
		m_List.push_back(readMail(fin));
	}
	fin.close();
}
void User::WriteAd_ListToFile()
{
	fout.open(getEachFileDir(AD_LIST));
	int tempSize = Ad_List.GetLength();
	fout << tempSize;
	DoublyIterator<Contact> iter(Ad_List); // 주소록 이터레이터
	//Ad_List.ResetList();
	for (int i = 0;i < tempSize;i++) {
		Contact temp;
		temp = iter.GetCurrentNode().data;
		//Ad_List.GetNext();
		//Ad_List.GetCurrentItem(temp);
		writeContact(temp,fout);
		if (iter.NextNotNull()) iter.Next();
	}
	fout.close();
}
void User::Writem_ListToFile()
{
	fout.open(getEachFileDir(M_LIST));
	int tempSize = m_List.size();
	fout << tempSize;
	vector<Mail>::iterator iter = m_List.begin();  // 받은편지함 이터레이터
	//m_List.ResetList();
	for (int i = 0;i < tempSize;i++)
	{
		Mail temp;
		temp = *iter;
		//m_List.GetNext();
		//m_List.GetCurrentItem(temp);
		writeMail(temp,fout);
		iter++;
		//if (iter.NextNotNull()) iter.Next();
	}
	fout.close();
}
/*
void User::WriteRecent_ListToFile(ofstream & fout)
{
}
*/
void User::Writetrash_folderToFile()
{
	fout.open(getEachFileDir(TRASH_FOLDER));
	int tempSize = trash_folder.GetLength();
	fout << tempSize;
	DoublyIterator<Mail> iter(trash_folder); // 지운편지함 이터레이터
	//trash_folder.ResetList();
	for (int i = 0;i < tempSize;i++) {
		Mail temp;
		temp = iter.GetCurrentNode().data;
		//trash_folder.GetNext();
		//trash_folder.GetCurrentItem(temp);
		writeMail(temp, fout);
		if (iter.NextNotNull()) iter.Next();
	}
	fout.close();
}

void User::Writetemp_folderToFile()
{
	fout.open(getEachFileDir(TEMP_FOLDER));
	int tempSize = temp_folder.size();
	fout << tempSize;
	vector<Mail>::iterator iter = temp_folder.begin();  // 받은편지함 이터레이터
												   //m_List.ResetList();
	for (int i = 0; i < tempSize; i++)
	{
		Mail temp;
		temp = *iter;
		//m_List.GetNext();
		//m_List.GetCurrentItem(temp);
		writeMail(temp, fout);
		iter++;
		//if (iter.NextNotNull()) iter.Next();
	}
	fout.close();
}


LinkedList<Mail>& User::getMailFromM_ListByAddress(string address)
{
	LinkedList<Mail> tempList;
	/*m_List.ResetList();
	
	Mail temp;
	for (int i = 0;i < m_List.GetLength();i++) {
		m_List.GetNext();
		m_List.GetCurrentItem(temp);
		if (address == temp.GetAddress())
		{
			tempList.Add(temp);
		}
	}
	return tempList;
	*/
	return  tempList;
}

Contact User::getContactFromAd_ListByAddress(string address)
{
	DoublyIterator<Contact> iter(Ad_List); // 주소록 이터레이터
	//Ad_List.ResetList();
	for (int i = 0;i < Ad_List.GetLength();i++) {
		Contact temp;
		temp = iter.GetCurrentNode().data;
		//Ad_List.GetNext();
		//Ad_List.GetCurrentItem(temp);
		if (address == temp.GetAddress())
			return temp;
	}
	if (iter.NextNotNull()) iter.Next();
}

int User::deleteContactFromAd_ListByAddress(string address)
{
	DoublyIterator<Contact> iter(Ad_List);  // 주소록 이터레이터
	//Ad_List.ResetList();
	for (int i = 0;i < Ad_List.GetLength();i++) {
		Contact temp;
		temp = iter.GetCurrentNode().data;
		//Ad_List.GetNext();
		//Ad_List.GetCurrentItem(temp);
		if (address == temp.GetAddress()) {
			Ad_List.Delete(temp);
			return 1;
		}
		if (iter.NextNotNull()) iter.Next();
	}
	return 0;
}

void User::showAd_List()
{
	DoublyIterator<Contact> iter(Ad_List);  // 주소록 이터레이터
	//Ad_List.ResetList();
	for (int i = 0;i < Ad_List.GetLength();i++) {
		Contact temp;
		temp = iter.GetCurrentNode().data;
		//Ad_List.GetNext();
		//Ad_List.GetCurrentItem(temp);
		temp.DisplayRecordOnScreen();
		if (iter.NextNotNull()) iter.Next();
	}
}

void User::showM_List()
{
	vector<Mail>::iterator iter = m_List.begin();  // 받은편지함 이터레이터
	for (iter; iter != m_List.end(); iter++)
	{
		cout << *iter;
	}
}

void User::showRecent_List()
{
	Recent_List.DisplayAllItems();
	/*
	while (!Recent_List.IsEmpty()) {
		Contact temp;
		Recent_List.DeQueue(temp);
		temp.DisplayRecordOnScreen();
	}
	*/
}

void User::showTrash_Folder()
{
	DoublyIterator<Mail> iter(trash_folder); // 받은편지함 이터레이터
	//trash_folder.ResetList();
	for (int i = 0;i < trash_folder.GetLength();i++) {
		Mail temp;
		temp = iter.GetCurrentNode().data;
		//trash_folder.GetNext();
		//trash_folder.GetCurrentItem(temp);
		temp.DisplayRecordOnScreen();
		if (iter.NextNotNull()) iter.Next();
	}

}
User& User::operator =(User& item) {
	this->email_add = item.email_add;
	this->password = item.password;
	this->baseFileDirectory = item.baseFileDirectory;

	DoublyIterator<Contact> iter_ad(item.getAd_List());
	//item.getAd_List().ResetList();
	for (int i = 0;i < item.getAd_List().GetLength();i++) {
		Contact temp;
		temp = iter_ad.GetCurrentNode().data;
		//item.getAd_List().GetNext();
		//item.getAd_List().GetCurrentItem(temp);
		this->getAd_List().Add(temp);
		if (iter_ad.NextNotNull()) iter_ad.Next();
	}
	vector<Mail>::iterator iter_m;
	iter_m = (*item.getM_List()).begin();
	//item.getM_List()->ResetList();
	for (int i = 0;i < item.getM_List()->size();i++) {
		Mail temp;
		temp = *iter_m;
		//temp = iter_m.GetCurrentNode().data;
		//item.getM_List()->GetNext();
		//item.getM_List()->GetCurrentItem(temp);
		this->getM_List()->push_back(temp);
		iter_m++;
		//if (iter_m.NextNotNull()) iter_m.Next();
	}
	DoublyIterator<Mail> iter_trash(item.getTrash_Folder());
	//item.getTrash_Folder().ResetList();
	for (int i = 0;i < item.getTrash_Folder().GetLength();i++) {
		Mail temp;
		temp = iter_trash.GetCurrentNode().data;
		//item.getTrash_Folder().GetNext();
		//item.getTrash_Folder().GetCurrentItem(temp);
		this->getTrash_Folder().Add(temp);
		if (iter_trash.NextNotNull()) iter_trash.Next();
	}

	return *this;
}

void User::setFileDirectory()
{
	baseFileDirectory = "./" + get_email_add();
}

string User::getEachFileDir(enum FileDirNum temp)
{
	string dir;
	dir.append(baseFileDirectory);
	switch (temp) {
	case AD_LIST: dir.append("/").append("Ad_List.txt"); break;
	case M_LIST: dir.append("/").append("m_List.txt"); break;
	case RECENT_LIST: dir.append("/").append("Recent_List.txt"); break;
	case TRASH_FOLDER: dir.append("/").append("trash_folder.txt"); break;
	default: break;
	}
	return dir;
}
