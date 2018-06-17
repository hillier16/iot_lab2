// Wiring Pi Library ������� ����
#include <wiringPi.h>
// LED ON/OFF ����
#define LED_ON 1
#define LED_OFF 0
// ��������� �� LED �� ����
const int Led[16] = {
	4, 17, 18, 27, 22, 23, 24, 25,
	6, 12, 13, 16, 19, 20, 26, 21
};

int main(void)
{
	int i; // for�� ����
	if (wiringPiSetupGpio() == -1) // GPIO �ʱ�ȭ
		return 1;
	for (i = 0; i<16; i++)
	{
		pinMode(Led[i], OUTPUT); // LED �� ��¸�� ����
		digitalWrite(Led[i], LED_OFF); // LED ��ü OFF
	}
	while (1)
	{
		digitalWrite(Led[0], LED_ON); // LED 1 ON
		delay(500); // 500ms ����
		digitalWrite(Led[0], LED_OFF); // LED 1 OFF
		delay(500); // 500ms ����
	}
	return 0;
}