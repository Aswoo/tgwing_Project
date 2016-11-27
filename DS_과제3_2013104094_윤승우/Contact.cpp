#include "Contact.h"
#define _CRT_NONSTDC_NO_WARNINGS
#pragma warning(disable : 4996)



// 송신자 키보드로부터 입력받고 설정

void Contact::SetReceiverFromKB()
{
	cout << "\tReceiver : ";
	cin >> m_sReceiver;
}
// address 키보드로부터 입력받고 설정
void Contact::SetAddressFromKB() 
{
	cout << "\tAddress : ";
	cin >> m_sAddress;
}

//  record 키보드로부터 입력받고 설정
void Contact::SetRecordFromKB()
{
	SetReceiverFromKB();
	SetAddressFromKB();
}
