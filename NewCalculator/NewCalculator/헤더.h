
/**  num1, num2, ope, result
  */
typedef struct _Info;									// Struct for information


/** Thread
  */
void Thread_Input(void* adr);							// Thread Input Fuction
void Thread_Calculation(void* ad);						// Thread Calculation Function
void Thread_Output(void* ad);							// Thread Output Fuction

/** script
  */
void script_Start();									// Script : Calculator Start
void script_End();										// Script : Calculator End
void script_Number1();									// Script : Type Number1
void script_Operator();									// Script : Type Operator
void script_Operator_Error();							// Script : Typed Operator is error
void script_Number2();									// Script : Type Number2


/** Input
  */
int input_Number1(int num);								// Type Number1
int input_Number2(int num);								// Type Number2
char input_Operator();									// Type Operator


/** Calculation
  */
int calc_Add(int num1, int num2);						// Addition
int calc_Sub(int num1, int num2);						// Subtraction
int calc_Mul(int num1, int num2);						// Multiplication
double calc_Div(int num1, int num2);					// Division


/** Output
  */
void output_Number(int num);							// Result (used for Addition, Subtraction, and Multiplication)
void output_dNumber(double num);						// Result (used for division)


/** Function used in callback
  */
typedef int (*calculate)(int, int);									// Function Pointer (used for Addition, Subtraction, and Multiplication)
int Calculate(calculate operation, int number1, int number2);		// Function (including the Function Pointer 'calculate')
typedef double (*dcalculate)(int, int);								// Function Pointer (used for division)
double dCalculate(dcalculate operation, int number1, int number2);	// Function (including the Function Pointer 'dcalculate')