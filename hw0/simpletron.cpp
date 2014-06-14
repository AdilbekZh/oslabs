#include <iostream>
#include <iomanip>
using namespace std;

const int READ = 10; // reads data from keyboard to memory
const int WRITE = 11; // writes data from memory to display
const int LOAD = 20; // loads data from memory to accumulator
const int STORE = 21; // stores data from accumulator to memory
const int ADD = 30; // adds a value from memory to accumulator
const int SUBTRACT = 31; // … 
const int DIVIDE = 32; // … 
const int MULTIPLY = 33; // … 
const int BRANCH = 40; // branches to a specific location in memory
const int BRANCHNEG = 41; // … if accumulator is negative
const int BRANCHZERO = 42; // … if accumulator is zero
const int HALT = 43; // halts the program

int accumulator=0;
int counter=0;
int instructionRegister=0;
int operationCode=0;
int operand=0;

int memory[100];

void dump(){
cout << endl;
cout << "REGISTERS:" << endl;

cout << "accumulator          " << showpos << setw(5) << setfill('0') << internal << accumulator << endl;
cout << "counter                 " << noshowpos << setw(2) << setfill('0') << counter << endl;
cout << "instructionRegister  " << showpos << setw(5) << setfill('0') << internal << instructionRegister << endl;
cout << "operationCode           " << noshowpos << setw(2) << setfill('0') << operationCode << endl;
cout << "operand                 " << setw(2) << setfill('0') << operand << endl;

cout << endl << "MEMORY:" << endl;
cout << "  " << noshowpos << setfill(' ');
for(int i=0;i<10; i++) cout << setw(6)<< i;
	cout << endl;

	for(int i=0;i<100;i++)
	{
		if (i%10==0) cout << noshowpos << setw(2) << i/10*10;
			cout << " " << setw(5) << setfill('0') << internal << showpos << memory[i];
		if ((i+1)%10==0) cout << endl;
	}
	cout << endl;
}

int main(){
	/*cout << "*** Welcome to Simpletron! ***" << endl;
	cout << "*** Please enter your program one instruction ***" << endl;
	cout << "*** (or data word) at a time. I will type the ***" << endl;
	cout << "*** location number and a question mark (?).  ***" << endl;
	cout << "*** You then type the word for that location. ***" << endl;
	cout << "*** Type the sentinel -99999 to stop entering ***" << endl;
	cout << "*** your program. ***" << endl;*/
	int x;
	for(int i=0;i<100;i++){
		cout << setw(2);
		cout << setfill('0');
		cout << i << " ? ";
		cin >> x;
		if (x==-99999) break;
			else 
			if (x > 9999 || x < -9999 ){
				cout << "*** Fatal error while loading your program ***" << endl;
				dump();
				return 1;
			}
				else memory[i] = x;
	}
	
	cout << "*** Program loading completed ***" << endl;
	cout << "*** Program execution begins  ***" << endl;
	
	while( counter<100 ){
		instructionRegister = memory[counter++];
		operationCode = instructionRegister / 100;
		operand = instructionRegister % 100;
		switch (operationCode){
			case READ:
				cin >> x;
				if (x >9999 || x < -9999){
					cout << "*** Runtime error (wrong input) ***" << endl;
					dump();
					return 1;
				}
				memory[operand] = x;
				break;
			case WRITE:
				cout << memory[operand] << endl;
				break;
			case LOAD:
				accumulator = memory[operand];
				break;
			case STORE:
				memory[operand] = accumulator;
				break;
			case ADD:
				accumulator+=memory[operand];
				if (accumulator >9999 || accumulator < -9999){
					cout << "*** Runtime error (accumulator overflow) ***" << endl;
					dump();
					return 1;
				}
				break;
			case SUBTRACT:
				accumulator-=memory[operand];
				if (accumulator >9999 || accumulator < -9999){
					cout << "*** Runtime error (accumulator overflow) ***" << endl;
					dump();
					return 1;
				}				
				break;
			case MULTIPLY:
				accumulator*=memory[operand];
				if (accumulator >9999 || accumulator < -9999){
					cout << "*** Runtime error (accumulator overflow) ***" << endl;
					dump();
					return 1;
				}				
				break;
			case DIVIDE:
				if (memory[operand] == 0){
					cout << "*** Runtime error (division by zero) ***" << endl;
					dump();
					return 1;
				}			
				accumulator/=memory[operand];
				if (accumulator >9999 || accumulator < -9999){
					cout << "*** Runtime error (accumulator overflow) ***" << endl;
					dump();
					return 1;
				}
				break;
			case BRANCH:
				counter = operand;
				break;
			case BRANCHNEG:
				if (accumulator<0) counter = operand;
				break;
			case BRANCHZERO:
				if (accumulator==0) counter = operand;
				break;
			case HALT:
				dump();
				cout << "*** Simpletron execution terminated ***" << endl;
				return 0;
				break;
			default:
				cout << "*** Runtime error (wrong operation) ***" << endl;
				dump();
				return 1;
				break;
		}
	}
	return 0;
}

/*
+1007
+1008
+2007
+3008
+2109
+1109
+4300
+0000
+0000
+0000
*/
