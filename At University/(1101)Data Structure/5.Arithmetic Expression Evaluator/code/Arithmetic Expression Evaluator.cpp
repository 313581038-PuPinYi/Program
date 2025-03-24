//10927207 �Z�~�� 10927234 �d���
// �p�G�L�k���� �Цb�W�� �I�u��>�sĶ���ﶵ>�sĶ���]�w>�{���X����>�y���з�>��ISO C++ 11 
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <istream>
#include <sstream>
 
using namespace std;

class Stack {
	public:
	struct Formula {
		string fml;
		Formula*next;
	};
	typedef Formula*ForPtr ;
	ForPtr formula, opera, walk, walkopera , insert, takeout;
	
	void TakeOutOpera() ; // �L�X�u���v���j���Ÿ��çR�� 
	void AddInformula() ; // �s�W�@���O���� 
	void Run() ; // �쥻��main�̪��F�� 
	int Postfix( string temp ) ; // (���ȤG) �������� 
	int FindError( string temp ) ; // (���Ȥ@) ��B�⦡���~ 
	bool Compare( string before, string after ); // ���i�u���e�O�_����i�p 
	void CalulateTotal() ; // (���ȤT) ��X����  
};


int main() {
	Stack stack ;
	stack.Run() ; 
} // main() 


// (���Ȥ@) ��B�⦡���~ 
int Stack::FindError( string temp ) {
	int left = 0, right = 0, sum = 0 ;
	for ( int i = 0; i < temp.size() ; i++ )  {
		if ( !isdigit(temp[i]) && temp[i] != '+' && temp[i] != '-' 
			&& temp[i] != '*' && temp[i] != '/' && temp[i] != '(' && temp[i] != ')' ) {
			cout << "Error 1: "<< temp[i] << " is not a legitimate character." << endl ; 
			return 1 ; // Error1: temp[i] is not a legitimate character.
		} // if
		
		if ( temp[i] == '(' || temp[i] == ')' ) { // �P�_�A������ 
			if ( temp[i] == '(' ) left++ ;
			else right++ ; 
			if ( right > left ) return 21 ; // �P�_�O�_���h �k�A��
			 // Error 2: there is one extra close parenthesis.
		} // if
		if ( temp[0] == '+' || temp[0] == '-' || temp[0] == '*' || temp[0] == '/' )	
			return 31 ; // Error 3: there is one extra operator.
		if ( i+1 < temp.size() ) {
			if ( temp[i] == '(' && !isdigit(temp[i+1]) && temp[i+1] != '(' ) // ���A���k�䤣���Ʀr 
				return 32 ; // Error 3: it is not infix in the parentheses.
			if ( temp[i] == ')' && isdigit(temp[i+1]) )	// �k�A���k�䬰�Ʀr 
				return 33 ; // Error 3: there is one extra operand.			
			if ( temp[i] == ')' && temp[i+1] == '(' )	// �k�A���k�䬰���A�� 
				return 33 ; // Error 3: there is one extra operand.				
			if ( temp[i+1] == '(' && isdigit(temp[i]) )	// �Ʀr�k�䬰���A�� 
				return 33 ; // Error 3: there is one extra operand.
			if ( ( temp[i] == '+' || temp[i] == '-' || temp[i] == '*' 
				|| temp[i] == '/' ) && temp[i+1] == ')' )	// *+-/ �k�䬰�A�� 
				return 32 ; // Error 3: it is not infix in the parentheses.
			if ( ( temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' ) 
				&& (temp[i+1] == '+' || temp[i+1] == '-'|| temp[i+1] == '*' || temp[i+1] == '/') )	// *+-/ �k�䬰 *+-/
				return 31 ; // Error 3: there is one extra operator.
		} // if
		else if ( i == temp.size()-1 ) {
			if ( temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' ) 
				return 31; // Error 3: there is one extra operator.
		} // else if
	} // for

	
	sum = left - right ;
	if ( sum != 0 ) return 22 ; // �P�_�O�_���h ���A�� 
	// Error 2: there is one extra open parenthesis.
} // Stack::FindError()


// ���i�u���e�O�_����i�p 
bool Stack::Compare( string before, string after ) {
	if ( ( before == "+" || before == "-" ) && ( after == "*" || after == "/" ) ) {
		return true; // ����(���i)���u���v�j��[��(��i) 
	} // if
	else if ( ( before == "+" || before == "-" ) && ( after == "+" || after == "-" ) ) {
		return true; // �[��(���i)���u���v�j��[��(��i) 
	} // else if
	else if ( ( before == "*" || before == "/" ) && ( after == "*" || after == "/" ) ) {
		return true; // ����(���i)���u���v�j�󭼰�(��i) 
	} // else if
	else return false;
} //  Stack::Compare()


// (���ȤG) �������� 
int Stack::Postfix( string temp ) {
	walkopera = NULL;
	insert = NULL;
	opera = NULL ;
	walk = NULL ; // �] formula
	for ( int i = 0; i < temp.size() ; i++ ) {
		
		if ( isdigit(temp[i]) ) { // �O�Ʀr 
			if ( formula != NULL ) cout << ", " ;
			AddInformula() ;
			while ( isdigit(temp[i]) ) { // Ū�J����Ʀr 
				cout << temp[i] ;
				if ( walk->fml == "\0" ) walk->fml = temp[i];
				else walk->fml = walk->fml + temp[i];
				i++;
			} // if
			
			i--;
		} // if
		else { // �O�[����άA�� 
			insert = new Formula;
			insert->fml = temp[i];
			insert->next = opera ;
			opera = insert ;
			if ( opera->fml == "(" );
			else if ( opera->next == NULL ) ;
			else if ( opera->fml != ")" ) {
		    	while ( opera != NULL && opera->next != NULL && Compare( opera->fml, opera->next->fml ) ) {
		    		TakeOutOpera();
				} // while
			} // else if
			else if ( opera->fml == ")" ) { // �k�A�� 
				walkopera = opera;
				while ( walkopera->fml != "(" ) { // �L�X����J�쥪�A�� 
					if ( walkopera->fml != ")" )  {
						cout << ", " << walkopera->fml;
						AddInformula() ; 
						walk->fml = walkopera->fml;
					} // if
					walkopera = walkopera->next;
				} // while
					
				if ( walkopera->next == NULL ) opera = NULL; // �u���@�ӲŸ� 
				else {
					opera = walkopera->next ;
					walkopera->next = NULL ;
					delete walkopera ;
				} // else
			} // else if
			
		} // else 
	} // for
	walkopera = opera;
	while ( walkopera != NULL ) { // �L�X�̫�ѤU���Ÿ� 
		if ( walkopera->fml != "(" && walkopera->fml != ")" ) {
			cout << ", " << walkopera->fml;
			AddInformula() ; 
			walk->fml = walkopera->fml ;	
		} // if
		walkopera = walkopera->next;
	} // whie 
	delete opera;

} // Stack::Postfix( string temp )


// �L�X�u���v���j���Ÿ��çR�� 
void Stack::TakeOutOpera() { 
	cout << ", " << opera->next->fml ;	
	takeout = opera->next ;
	if ( opera->next->next == NULL ) opera->next = NULL;
	else opera->next = opera->next->next ;
	takeout->next = NULL;
	
	AddInformula() ; 
	walk->fml = takeout->fml ;
	delete takeout ;
} // Stack::TakeOutOpera()


// �s�W�@���O����
void Stack::AddInformula() {
	if ( formula == NULL ) {
		walk = new Formula;
		walk->next = NULL ;
		formula = walk ;
	} // if
	else {
		walk->next = new Formula;
		walk = walk->next ;	
		walk->next = NULL ;
	} // else
} // Stack::AddInformula()


// �쥻��main�̪��F�� 
void Stack::Run() {
	string num ;
	int error = 0 ; // �ĴX�ӿ��~ 
	bool exe = true;
	
	while ( exe ) {
		error = 0;
		formula = NULL;
		cout << "\n* Arithmetic Expression Evaluator *" ;
		cout << "\n* 0. QUIT                         *" ;
		cout << "\n* 1. Infix2postfix Evaluation     *" ;
		cout << "\n***********************************" ;
		cout << "\nInput a choice(0, 1): " ;
		getline( cin, num ) ;
		cout << endl ;

		if ( num == "1" ) {
			string str, temp ;
			cout << "Input an infix expression: " ;
			getline( cin, str ) ;
			for ( int i = 0; i < str.size() ; i++ ) 
				if ( str[i] != ' ' ) temp = temp + str[i] ; // �����Ů� 
			
			if ( temp[0] != '\0' ) error = FindError( temp ) ;
			else error = 31 ;
			if ( error == 21 ) cout << "Error 2: there is one extra close parenthesis." << endl;
			else if ( error == 22 ) cout << "Error 2: there is one extra open parenthesis." << endl;
			else if ( error == 31 ) cout << "Error 3: there is one extra operator." << endl;
			else if ( error == 32 ) cout << "Error 3: it is not infix in the parentheses." << endl;
			else if ( error == 33 ) cout << "Error 3: there is one extra operand." << endl;
			else if ( error == 0 ) {
				cout << "It is a legitimate infix expression." << endl;
				cout << "Postfix expression: " ;
				Postfix( temp ) ;
				CalulateTotal();	
			} // else if
			
			
			if ( formula != NULL ) delete formula ;	
		} // if
	
		else if ( num == "0" ) exe = false ;
		
	} // while
} // Stack::Run()


// (���ȤT) ��X����  
void Stack::CalulateTotal() {
	walk = NULL, opera = NULL, walkopera = NULL ;
	bool divisorZore = false ; // ���ƬO�_���s 
	walkopera = new Formula ;
	walk = formula ;
	int a = 0, b = 0;
	while ( walk != NULL ) {
		if ( isdigit(walk->fml[0]) ) {
			if ( opera == NULL ) { // ��opera�@���O���� 
				opera = walkopera;
				opera->next = NULL ;
			} // if
			
			else { // �s�W�@���O����bopera�̫e�� 
				walkopera = new Formula;
				walkopera->next = opera;
				opera = walkopera;
			} //else 
			
			walkopera->fml = walk->fml;
		} // if
		else {
			a = stoi(opera->next->fml) ; // ��Ū�i�hopera���� 
			b = stoi(opera->fml) ; // ��Ū�i�hopera����  
			
			if ( walk->fml == "+" ) a = a + b;
			else if ( walk->fml == "-" ) a = a - b;
			else if ( walk->fml == "*" ) a = a * b;
			else if ( walk->fml == "/" ) {
				if ( b == 0 ) { // ���Ƭ��s 
					cout << "\n### Error: Divided by ZERO! ### " << endl;
					cout << "### It cannot be successfully evaluated! ###" << endl;
					divisorZore = true ;
				} // else 
				else a = a / b;
			} // else 
			 
			if ( divisorZore == false ) {
				opera->next->fml = to_string(a);
				walkopera = opera;
				opera = opera->next;
				walkopera->next = NULL;
				delete walkopera;					
			} // if
		} // else 
		
		walk = walk->next;
		if ( divisorZore == true ) walk = NULL ; 
	} // while
	if ( divisorZore == false ) cout << "\nAnswer: " << a << endl;
	delete opera ;
} // Stack::CalulateTotal()
