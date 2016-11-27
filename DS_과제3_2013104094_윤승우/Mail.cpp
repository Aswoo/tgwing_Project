#include "Mail.h"
#define _CRT_NONSTDC_NO_WARNINGS
#pragma warning(disable : 4996)



// 송신자 키보드로부터 입력받고 설정
void Mail::SetSenderFromKB()
{
	cout << "\tSender : ";
	cin >> m_sSender;
}
//  student address 키보드로부터 입력받고 설정
void Mail::SetAddressFromKB()
{
	cout << "\tAddress : ";
	cin >> m_sAddress;

}
// 수신자 키보드로부터 입력받고 설정
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
	//// 헤더 파일에 가보면 'typedef long time_t'로 되어 있습니다. 즉, long과 동일하다고 보면 됩니다.
	//time_t curr_time;
	//// 시간 표시를 위한 구조체를 선언합니다.
	//struct tm *curr_tm;
	//// time 함수는 1970년 1월 1일 이후 몇초가 지났는지를 계산합니다. NULL을 인자로 사용합니다.
	//curr_time = time(NULL);
	//// 지역 시간을 기준으로 변환 및 출력 편의를 위하여 tm 구조체에 저장합니다.(포맷팅)
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

//  student record 키보드로부터 입력받고 설정
void Mail::SetRecordFromKB()
{
	SetTimeFromReal();
	SetLabelFromKB();
	SetSenderFromKB();
	SetAddressFromKB();
	SetsubjectFromKB();
	SetcontentFromKB();
}


// 파일로부터 record 읽어옴
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


// 파일로 record 기록
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