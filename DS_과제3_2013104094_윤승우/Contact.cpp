#include "Contact.h"
#define _CRT_NONSTDC_NO_WARNINGS
#pragma warning(disable : 4996)



// �۽��� Ű����κ��� �Է¹ް� ����

void Contact::SetReceiverFromKB()
{
	cout << "\tReceiver : ";
	cin >> m_sReceiver;
}
// address Ű����κ��� �Է¹ް� ����
void Contact::SetAddressFromKB() 
{
	cout << "\tAddress : ";
	cin >> m_sAddress;
}

//  record Ű����κ��� �Է¹ް� ����
void Contact::SetRecordFromKB()
{
	SetReceiverFromKB();
	SetAddressFromKB();
}
