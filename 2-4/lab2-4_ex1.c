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

// FND�� ����ϴ� �Լ�
void FndDisplay(int position, int num) {
	int i;
	int flag = 0; // FndPin[ ]�� ON/OFF
	int shift = 0x01; // FndFont�� And �����Ͽ� ����� LED�� ���� ����
	digitalWrite(FndSelectPin[position], LOW); // Select �� ON
	for (i = 0; i < 8; i++) {
		flag = (FndFont[num] & shift); // i = 0, FndFont[ 0 ] = 0x3F�� �ϸ� (0b00111111 & 0b00000001 = 1) �̴�.
		digitalWrite(FndPin[i], flag); // FndPin[ ]�� flag( 0�Ǵ� 1 )�� ON/OFF
		shift <<= 1; // �������� �� ��Ʈ ����Ʈ�Ѵ�. I = 0�̶� �ϸ�, ( shift = 0b00000001 )���� ( shift = 0b00000010)�� ���Ѵ�.
	}
}

int main(int argc, char **argv) {
	if (argc != 3) {
		printf(��Usage: %s[position][number] ��, arvg[0]);
		exit(-1);
	}
	Init();
	// argv[1] = position, argv[2] = number
	// argv�� ���� ��Ʈ���̹Ƿ� ������ ��ȯ
	// int atoi( const char *string )
	FndDisplay(atoi(argv[1]), atoi(argv[2]));
	return 0;
}
