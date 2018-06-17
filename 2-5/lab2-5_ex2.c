#include <wiringPi.h> // GPIO Access Library ������� ����
#include <softPwm.h> // Software PWM library ������� ����
// Motor �� ����
#define MOTOR_MT_N_PIN 17
#define MOTOR_MT_P_PIN 4
// Motor ȸ�� ���� ����
#define LEFT_ROTATE 1
#define RIGHT_ROTATE 2
// Motor ���� �Լ�
void MotorStop()
{
	softPwmWrite(MOTOR_MT_N_PIN, 0);
	softPwmWrite(MOTOR_MT_P_PIN, 0);
}
// Motor �ӵ� ���� �Լ�
void MotorControl(int speed)
{
	digitalWrite(MOTOR_MT_P_PIN, LOW);
	softPwmWrite(MOTOR_MT_N_PIN, speed);
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
	while (1) {
		MotorControl(25); // Duty Cycle 25% ����
		delay(2000);
		MotorStop(); // Motor ����
		delay(2000);
		MotorControl(50); // Duty Cycle 50% ����
		delay(2000);
		MotorStop(); // Motor ����
		delay(2000);
		MotorControl(75); // Duty Cycle 75% ����
		delay(2000);
		MotorStop(); // Motor ����
		delay(2000);
	}
	return 0;
}
