#include <wiringPi.h> // GPIO Access Library 헤더파일 선언
#include <softPwm.h> // Software PWM library 헤더파일 선언
#define LED 16
int main(void)
{
	if (wiringPiSetupGpio() == -1)
		return 1;
	pinMode(LED, OUTPUT);
	softPwmCreate(LED, 0, 128);
	while (1)
	{
		int i;
		for (i = 0; i <= 128; i++) {
			softPwmWrite(LED, i);
			delay(5);
		}
		delay(500);
		for (i = 128; i >= 0; i--) {
			softPwmWrite(LED, i);
			delay(5);
		}
		delay(500);
	}
	return 0;
}
