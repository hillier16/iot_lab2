#include <wiringPi.h> // GPIO Access Library ������� ����
#include <softPwm.h> // Software PWM library ������� ����
// Motor �� ����
#define MOTOR_MT_N_PIN 17
#define MOTOR_MT_P_PIN 4
// Motor ȸ�� ���� ����
#define LEFT_ROTATE 1
#define RIGHT_ROTATE 2
// Motor ���� �Լ�
void MotorStop() {
	softPwmWrite(MOTOR_MT_N_PIN, 0);
	softPwmWrite(MOTOR_MT_P_PIN, 0);
}
// Motor ȸ�� �Լ�
void MotorControl(int rotate, int speed) {
	if (rotate == LEFT_ROTATE) {
		digitalWrite(MOTOR_MT_P_PIN, LOW);
		softPwmWrite(MOTOR_MT_N_PIN, speed);
	}
	else if (rotate == RIGHT_ROTATE) {
		digitalWrite(MOTOR_MT_N_PIN, LOW);
		softPwmWrite(MOTOR_MT_P_PIN, speed);
	}
}
int main(void)
{
	if (wiringPiSetupGpio() == -1)
		return 1;
	// Motor �� ������� ����
	pinMode(MOTOR_MT_N_PIN, OUTPUT);
	pinMode(MOTOR_MT_P_PIN, OUTPUT);
	// Motor �� PWM ���� ������ ����
	// �ֱ�: 100ms
	softPwmCreate(MOTOR_MT_N_PIN, 0, 128);
	softPwmCreate(MOTOR_MT_P_PIN, 0, 128);
	while (1)
	{
		int speed;
		for (speed = 32; speed <= 128; speed += 32)
		{
			MotorControl(LEFT_ROTATE, speed); // Motor �������� speed�ӵ��� ȸ��
			delay(2000);
			MotorStop(); // Motor ����
			delay(1000);
		}
		for (speed = 128; speed >= 32; speed -= 32)
		{
			MotorControl(RIGHT_ROTATE, speed); // Motor �������� speed�ӵ��� ȸ��
			delay(2000);
			MotorStop(); // Motor ����
			delay(1000);
		}
	}
	return 0;
}
