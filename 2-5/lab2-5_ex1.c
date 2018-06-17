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
void MotorControl(int rotate) {
	if (rotate == LEFT_ROTATE) {
		digitalWrite(MOTOR_MT_P_PIN, LOW);
		softPwmWrite(MOTOR_MT_N_PIN, 50);
	}
	else if (rotate == RIGHT_ROTATE) {
		digitalWrite(MOTOR_MT_N_PIN, LOW);
		softPwmWrite(MOTOR_MT_P_PIN, 50);
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
	softPwmCreate(MOTOR_MT_N_PIN, 0, 100);
	softPwmCreate(MOTOR_MT_P_PIN, 0, 100);
	while (1)
	{
		MotorControl(LEFT_ROTATE); // Motor �������� ȸ��
		delay(2000);
		MotorStop(); // Motor ����
		delay(1000);
		MotorControl(RIGHT_ROTATE); // Motor ���������� ȸ��
		delay(2000);
		MotorStop(); // Motor ����
		delay(1000);
	}
	return 0;
}
