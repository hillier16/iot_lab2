// GPIO Access Library ������� ����
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
// �� FND�� ����� ��������� ��(S0, S1, ��, S5)
const int FndSelectPin[6] = { 4, 17, 18, 27, 22, 23 };
// FND�� LED�� ����� ��������� ��(A, B, ��, H)
const int FndPin[8] = { 6, 12, 13, 16, 19, 20, 26, 21 };
// FND�� ��µǴ� ���� (0~9) �迭
const int FndFont[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66,
0x6D, 0x7D, 0x07, 0x7F, 0x67 };
// �ʱ�ȭ �Լ�, WiringPi ���̺귯�� �ʱ�ȭ, Select �� �� LED �� �ʱ�ȭ�� ���)

void Init() {
	int i;
	if (wiringPiSetupGpio() == -1) {
		printf(��wiringPiSetupGpio() error\n��);
		exit(-1);
	}
	for (i = 0; i < 6; i++) {
		pinMode(FndSelectPin[i], OUTPUT); // Select ���� ������� ����
		digitalWrite(FndSelectPin[i], HIGH); // Select �� OFF
	}
	for (i = 0; i < 8; i++) {
		pinMode(FndPin[i], OUTPUT); // LED ���� ������� ����
		digitalWrite(FndPin[i], LOW); // LED ���� OFF
	}
}

// FND�� �����ϴ� �Լ�, S0 ~ S5 �� �Ķ����(position)�� �ش��ϴ� FND ����
void FndSelect(int position) {
	int i;
	for (i = 0; i < 6; i++) {
		if (i == position) {
			digitalWrite(FndSelectPin[i], LOW); // ���õ� FND�� Select �� ON
		}
		else {
			digitalWrite(FndSelectPin[i], HIGH); // ���õ��� ���� FND�� Select �� OFF
		}
	}
}

// FND�� ����ϴ� �Լ�
void FndDisplay(int position, int num) {
	int i;
	int flag = 0; // FndPin[ ]�� ON/OFF
	int shift = 0x01; // FndFont�� And �����Ͽ� ����� LED�� ���� ����
	FndSelect(position);
	for (i = 0; i < 8; i++) {
		flag = (FndFont[num] & shift); // i = 0, FndFont[ 0 ] = 0x3F�� �ϸ� (0b00111111 & 0b00000001 = 1) �̴�.
		if(position == 2 && i == 7)
			digitalWrite(FndPin[i], 1);
		else
			digitalWrite(FndPin[i], flag); // FndPin[ ]�� flag( 0�Ǵ� 1 )�� ON/OFF
		shift <<= 1; // �������� �� ��Ʈ ����Ʈ�Ѵ�. i = 0�̶� �ϸ�, ( shift = 0b00000001 )���� ( shift = 0b00000010)�� ���Ѵ�.
	}
}

int main() {
	int pos;
	int time = 0;
	int data[6]; // ����� ���� ������
	Init();
	while (1) {
		data[0] = time % 10;
		data[1] = (time / 10) % 10;
		data[2] = (time / 100) % 10;
		data[3] = (time / 1000) % 10;
		data[4] = (time / 10000) % 10;
		data[5] = time / 100000 % 10;
		for (pos = 0; pos < 6; pos++) {
			FndDisplay(pos, data[pos]);
			delay(1); // WiringPi ���̺귯������ ���ǵ� delay() �Լ�, void delay( unsinged int howLong )
		}
		time++;
	}
	return 0;
}
