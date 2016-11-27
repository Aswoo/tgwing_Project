#include "Mail.h"
#define _CRT_NONSTDC_NO_WARNINGS
#pragma warning(disable : 4996)



// �۽��� Ű����κ��� �Է¹ް� ����
void Mail::SetSenderFromKB()
{
	cout << "\tSender : ";
	cin >> m_sSender;
}
//  student address Ű����κ��� �Է¹ް� ����
void Mail::SetAddressFromKB()
{
	cout << "\tAddress : ";
	cin >> m_sAddress;

}
// ������ Ű����κ��� �Է¹ް� ����
void Mail::SetReceiverFromdKB()
{
	cout << "\tReceiver : ";
	cin >> m_sReceiver;
	cin.ignore();
}

void Mail::SetLabelFromKB()
{
	cout << "\tLabel : ";
	cin >> m_slabel;
}

void Mail::SetsubjectFromKB()
{
	cout << "\tSubject : ";
	getline(cin, m_sSubject);

}

void Mail::SetcontentFromKB()
{
	cout << "\tContent : ";
	char test[256];
	cin.getline(test, 256);
	m_sContent = test;
}

void Mail::SetTimeFromReal()
{
	//// ��� ���Ͽ� ������ 'typedef long time_t'�� �Ǿ� �ֽ��ϴ�. ��, long�� �����ϴٰ� ���� �˴ϴ�.
	//time_t curr_time;
	//// �ð� ǥ�ø� ���� ����ü�� �����մϴ�.
	//struct tm *curr_tm;
	//// time �Լ��� 1970�� 1�� 1�� ���� ���ʰ� ���������� ����մϴ�. NULL�� ���ڷ� ����մϴ�.
	//curr_time = time(NULL);
	//// ���� �ð��� �������� ��ȯ �� ��� ���Ǹ� ���Ͽ� tm ����ü�� �����մϴ�.(������)
	//= localtime(&curr_time);
	//cout << "ccc" << endl;
	//string timeString = "";

	struct _timeb itb;
	struct tm *lt;
	_ftime(&itb);
	lt = localtime(&itb.time);

	int time = itb.millitm * 100 / 100;
	char buf[1024];
	itoa(lt->tm_year + 1900, buf, 10);
	string year = buf;
	string month;
	itoa(lt->tm_mon + 1, buf, 10);
	if ((lt->tm_mon + 1) < 10)
	{
		month = buf;
		month = "0" + month;
	}
	else
	{
		month = buf;
	}
	string day;
	itoa(lt->tm_mday, buf, 10);
	if ((lt->tm_mday) < 10)
	{
		day = buf;
		day = "0" + day;
	}
	else {
		day = buf;
	}
	string hour;
	itoa(lt->tm_hour, buf, 10);
	if ((lt->tm_hour) < 10)
	{
		hour = buf;
		hour = "0" + hour;
	}
	else hour = buf;
	string min;
	itoa(lt->tm_min, buf, 10);
	if ((lt->tm_min) < 10)
	{
		min = buf;
		min = "0" + min;
	}
	else min = buf;
	string sec;
	itoa(lt->tm_sec, buf, 10);
	if ((lt->tm_sec) < 10)
	{
		sec = buf;
		sec = "0" + sec;
	}
	else sec = buf;

	string timeTemp = year + month + day + hour + min + sec;
	//printf("%02d.%02d %02d:%02d:%02d.%02d",
	//	lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec, itb.millitm);
	m_sTime = timeTemp;
}

//  student record Ű����κ��� �Է¹ް� ����
void Mail::SetRecordFromKB()
{
	SetTimeFromReal();
	SetLabelFromKB();
	SetSenderFromKB();
	SetAddressFromKB();
	SetsubjectFromKB();
	SetcontentFromKB();
}


// ���Ϸκ��� record �о��
int Mail::ReadDataFromFile(ifstream& fin)
{
	fin >> m_slabel;
	fin >> m_sSender;
	fin >> m_sAddress;
	fin >> m_sSubject;
	char c;
	while (fin.get(c)) {
		if (c == '#') {
			break;
		}
		else {
			string temp(1, c);
			m_sContent.append(temp);
		}
	}
	fin >> m_sTime;

	return 1;
};


// ���Ϸ� record ���
int Mail::WriteDataToFile(ofstream& fout)
{
	fout << endl;
	fout << m_slabel << " ";
	fout << m_sSender << " ";
	fout << m_sAddress << " ";
	fout << m_sSubject << " ";
	fout << m_sContent << "#";
	fout << m_sTime << " ";

	return 1;
}



RelationType2 Mail::CompareBytime(const Mail &data)
{
	if (this->m_sTime > data.m_sTime)
		return bigger;
	else if (this->m_sTime < data.m_sTime)
		return smaller;
	else
		return same;
	return smaller;
}

void Mail::SetTimeFromKB()
{
	cout << "\t Time:";
	cin >> m_sTime;
}