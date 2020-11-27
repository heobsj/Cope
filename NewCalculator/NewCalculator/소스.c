#define HAVE_STRUCT_TIMESPEC

#include <stdio.h>
#include <pthread.h>
#include <Windows.h>

#define NUM_THREADS 3
pthread_mutex_t mute;

void (*call_Thread)(void*);

/**  num1, num2, ope, result
  */
typedef struct _Info {
	int number1;
	int number2;
	char ope;
	int result;
} Info;


/** Script
  */
void script_Start() {
	printf("사칙연산 시작\n");
}
void script_End() {
	printf("사칙연산 끝\n\n");
}
void script_Number1() {
	printf("첫 번째 숫자 입력 필요\n");
}
void script_Operator() {
	printf("연산자 입력 필요\n");
}
void script_Number2() {
	printf("두 번째 숫자 입력 필요\n");
}

/** Input
  */
int input_Number1() {
	int num = 0;
	script_Number1();
	scanf_s("%d", &num);
	getchar();
	return num;
}
int input_Number2() {
	int num = 0;
	script_Number2();
	scanf_s("%d", &num);
	getchar();
	return num;
}
char input_Operator() {
	script_Operator();
	char s;
	scanf_s("%c", &s);
	getchar();
	return s;
}


/** Calculation
  */
int calc_Add(int num1, int  num2) {
	return num1 + num2;
}
int calc_Sub(int num1, int num2) {
	return num1 - num2;
}
int calc_Mul(int num1, int num2) {
	return num1 * num2;
}
double calc_Div(int num1, int num2) {
	return num1 / num2;
}


void output_Number(int num) {
	printf("결과		%d\n", num);
}



typedef int (*calculate)(int, int);
void (*call_Thread)(void*);


int Calculate(calculate operation, int number1, int number2) {
	return operation(number1, number2);
}


void Thread_Input(void* adr) {

	Info* info = (Info*)adr;
	while (1) {
		
		Sleep(500);

		pthread_mutex_lock(&mute);

		script_Start();
		info->number1 = input_Number1();
		info->ope = input_Operator();
		info->number2 = input_Number2();

		pthread_mutex_unlock(&mute);
	}

}
void Thread_Calculation(void* adr) {

	Info* info = (Info*)adr;
	while (1) {
		
			pthread_mutex_lock(&mute);

			switch (info->ope) {
			case '+': info->result = Calculate(calc_Add, info->number1, info->number2); break;
			case '-': info->result = Calculate(calc_Sub, info->number1, info->number2); break;
			case '*': info->result = Calculate(calc_Mul, info->number1, info->number2); break;
			case '/': info->result = Calculate(calc_Div, info->number1, info->number2); break;
			default: Sleep(10);  break;
			}

			pthread_mutex_unlock(&mute);
		
	}
}

void Thread_Output(void* adr) {

	Info* info = (Info*)adr;
	while (1) {
		if (info->result != 0) {

			pthread_mutex_lock(&mute);

			output_Number(info->result);

			script_End();
			info->result = 0;
			Sleep(1000);

			pthread_mutex_unlock(&mute);
		}
		else {
			Sleep(10);
		}
	}
}






int main() {

	Info* info = (Info*)malloc(sizeof(Info));

	info->number1 = 0;
	info->number2 = 0;
	info->ope = NULL;
	info->result = 0;
	

	pthread_t threads[2];
	
	pthread_mutex_init(&mute, NULL);

	pthread_create(&threads[0], NULL, Thread_Input, (void*)info);

	pthread_create(&threads[1], NULL, Thread_Calculation, (void*)info);

	pthread_create(&threads[2], NULL, Thread_Output, (void*)info);

	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	

}