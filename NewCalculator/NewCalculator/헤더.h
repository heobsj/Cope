
/**  num1, num2, ope, result
  */
typedef struct _Info;


/** Thread
  */
void Thread_Input(void* adr);
void Thread_Calculation(void* ad);
void Thread_Output(void* ad);

/** script
  */
void script_Start();
void script_End();
void script_Number1();
void script_Operator();
void script_Operator_Error();
void script_Number2();


/** Input
  */
int input_Number1(int num);
int input_Number2(int num);
char input_Operator();


/** Calculation
  */
int calc_Add(int num1, int num2);
int calc_Sub(int num1, int num2);
int calc_Mul(int num1, int num2);
double calc_Div(int num1, int num2);


/** Output
  */
void output_Number(int num);
void output_dNumber(double num);


/** Function used in callback
  */
typedef int (*calculate)(int, int);
int Calculate(calculate operation, int number1, int number2)