// 10927207 �Z�~�� 
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <sstream> // stringstream�� integer To int
#include<time.h> // ��ɶ� 

using namespace std ;


typedef unsigned long long int Ulli ;


struct Series {
	int serialnum[100] ; // �s�� 
	Ulli num[100] ; // �Ʀr 
	Ulli factor1[100] ; // �]��1	
	Ulli factor2[100] ; // �]��2 
	Ulli innerloop[100] ; // ���`������ 
	
    // [�s��] �Ʀr  =  �]��1 * �]��2 (Inner loop: ���`������ times) 
};


struct OneLine { // ���j"�ƦC"�զX�Ҩϥ� 
	char ch_Line[10] ;	
	Ulli int_temp = 0 ;	
	
};

static int N = 0 ; // ���j"�ƦC"�զX�Ҩϥ�  N: �N��N��� 


//main�ϥ�function 
void Initialization ( int & outerLoop , Series & value ) ; // ��l��
int SetType() ; // �]�wsetType�@��Ū ����Ū�� 0 or 1 or 2 �~�^�� 
int InputNumber() ; // �]�wŪ�J�Ʀr ����j��s�� �~�^��

//����1.2�@��function 
void PrintSerialNum( int serialNum ) ; // �L�s��
string intTostring( Ulli i ) ; // // integer To int
void WhiteSpace( int spacecount, Ulli numlong, Ulli factor1long, Ulli factor2long ) ; // �L�ť� 
void PrintInnerloop( Ulli innerloop ) ; // �L���j�馸���� 
void PrintAllNumber( Ulli num, Ulli factor1, Ulli factor2 )  ; // �L�X�]�ƭ��]�Ƹ�ť�

//����1
void CalculateFactor( Ulli num , Ulli & factor1, Ulli & factor2, Ulli & innerloop ) ; // �j�� ��]��  
//����2
void IterativeCalculateFib( int number, Series & value, int & outerLoop ) ; // �j�� �D�n:���O��ƦC  + ���n:��]��+�L�X�Ҧ��F�� 
 
 
//����1 �M�� function 
void RecursionCalculateFib( int i, int number, Series & value, int & outerLoop ) ;  // ���j �O��ƦC ���� 
//����2 �M�� function 
void RecurCalculateFactor( Ulli sqrtnum, Ulli num , Ulli & factor1, Ulli & factor2, Ulli & innerloop ) ; //���j ��]�� 



//�ƦC�զX�Τ���  
bool RepeatYn( OneLine num ) ; // ���j  �ƦC  
void Prem( OneLine num, Ulli & serialNum, Ulli temp ) ; // �P�_Ū�Ʀr �p��N��� �i�Ĥ@��if �Ϥ��ielse 
void ScanfNum( OneLine & num, Ulli temp ); //�P�_ 1�C�� ���L���ƼƦr



int main() {
	
	int command = 0 ; // �]�w�O 0 Quit �� 1. Iterative generation �� 2. Recursive generation 	
	Series value ; // �j��λ��j�@�t�C����  
	int inputNumber = 0 ; // ��J���Ʀr 
	int outerLoop = 0 ; // �~�`������ 
	
	Initialization ( outerLoop , value ) ; // ��l�� 
    command = SetType() ;
		
	while( command != 0 ) {
		
		inputNumber = InputNumber() ; 
		if ( command == 1 ) 
			IterativeCalculateFib( inputNumber, value, outerLoop ) ;
	
		else if ( command == 2 ) {
			RecursionCalculateFib( 1, inputNumber, value, outerLoop ) ; // 1 �ƨ� InputNumber()
		}
		
		else if ( command == 3 ) { 
			while ( inputNumber < 2 || inputNumber > 10 ) {
				cout << endl << "### The number must be in [2,10] ###" << endl;	 
				inputNumber = InputNumber() ;							
			}

			N = inputNumber ; // N��� 
			OneLine num ;
			Ulli serialNum = 0 ;
			for ( int i = 0 ; i < N ; i++ ) { // ��l�]�w 
				num.int_temp = i + (num.int_temp * 10) ; 
				num.ch_Line[i] = 48 + i ; // ASCLL 48��0 
			}	

			double start, end ;
			start = clock() ;
			Prem( num, serialNum, num.int_temp ) ;	
			end = clock() ;
			cout << "Recursion:  " << end - start << " ms" << endl ;
		}
		
		command = SetType() ;
		Initialization ( outerLoop, value ) ; // ��l��  
	}
	return 0 ;
	
}

// ��l��
void Initialization ( int & outerLoop , Series & value ) {
	outerLoop = 0 ;
	for ( int j = 0 ; j <= 100 ; j++ ) {
		value.serialnum[j] = 0 ;
		value.num[j] = 0 ;
		value.factor1[j] = 0 ; 	
		value.factor2[j] = 0 ; 
		value.innerloop[j] = 0 ; 
	}
}



// �]�wsetType�@��Ū ����Ū�� 0 or 1 or 2 �~�^��  
int SetType( ) {
	int command = 0 ; 
	
	cout << endl << "** Fibonacci Series Generator **" ;
	cout << endl << "* 0. Quit                      *" ;	
	cout << endl << "* 1. Iterative generation      *" ;	
	cout << endl << "* 2. Recursive generation      *" ;
	cout << endl << "* 3. Permutation generator     *" ;  
	cout << endl << "********************************" ;
	
	cout << endl << "Input a command(0, 1, 2, 3): " ;
	cin >> command ;
	while ( command > 3 || command < 0 ) { ///
		cout << endl << "Command does not exist!" << endl;
		
		cout << endl << "** Fibonacci Series Generator **" ;
		cout << endl << "* 0. Quit                      *" ;	
		cout << endl << "* 1. Iterative generation      *" ;	
		cout << endl << "* 2. Recursive generation      *" ;
		cout << endl << "* 3. Permutation generator     *" ;  
		cout << endl << "********************************" ;
		cout << endl << "Input a command(0, 1, 2, 3): " ;
		cin >> command ;		
	}
	
	return command ;
}

// �]�wŪ�J�Ʀr ����j��s�� �~�^�� 
int InputNumber() {
	int number = 0 ;
	
	cout << endl << "Input a number: " ;
	cin >> number ;
	
	while ( cin.fail() ) {
    	cin.clear() ;
     	cin.ignore( 30000,'\n' ) ;
     	cout << endl << "Input a number: " ;
		cin >> number ;
    }
    
 	while ( number <= 0 ) {
		if ( number == 0 ) cout << endl << "### The number must be in [1,999999] ###" << endl ;
		cout << endl << "Input a number: " ;
		cin >> number ;
		
		while ( cin.fail() ) {
    		cin.clear() ;
    	 	cin.ignore( 30000,'\n' ) ;
    	 	cout << endl << "Input a number: " ;
			cin >> number ;
    	}
	}	   	

	return number ;
}

// �L�s��
void PrintSerialNum( int serialNum ) {
	cout << "[" << " " ;
	if ( serialNum > 0 && serialNum < 10 ) cout << " " ;
	cout << serialNum << "]" ;	
}


// integer To int
string intTostring( Ulli i ) {
	string str ;
	stringstream toInt(str) ;
	toInt << i ;
	
	return toInt.str() ;
}

//�L�ť� 
void WhiteSpace( int spacecount, Ulli numlong, Ulli factor1long, Ulli factor2long ) {
   // 1.�L�]��2��(�������ť� 2.�LInner loop:�� Inner loop���Ƥ������ť�               	
                 	
	spacecount = spacecount - numlong - factor1long - factor2long ;
	while ( spacecount > 0 ) {
		cout << " " ;	
		spacecount-- ;
	}
}


// �L���j�馸�� 
void PrintInnerloop( Ulli innerloop ) {       
	int whitespace = 12 - intTostring(innerloop).length() ;
	for ( int i = 1 ; i < whitespace ; i++ ) cout << " " ;
	cout << innerloop <<" times)" << endl ;	// �n��̫�Ů� 	
}



// �L�X�]�ƭ��]�Ƹ�ť�
void PrintAllNumber( Ulli num, Ulli factor1, Ulli factor2 ) {    	 
		              	
	Ulli numlong = intTostring( num ).length() ; // num�Ʀr���� 
	Ulli factor1long = intTostring( factor1 ).length() ; // �]��1����	
	Ulli factor2long = intTostring( factor2 ).length() ; // �]��2����	

	cout << " " << factor1 << " * " << factor2 ;
	
	if( numlong <= 1 ) cout << " " ; 
	
	else if ( numlong <= 5 ) 
		WhiteSpace( 13, numlong, factor1long, factor2long ) ; // 13�N��쥻�n�[��whiteSpace�ƶq 
	
	else if ( numlong <= 9 ) 
		WhiteSpace( 20, numlong, factor1long, factor2long ) ; // 20�N��쥻�n�[��whiteSpace�ƶq 
		
	
	else if ( numlong <= 13 ) 
		WhiteSpace( 30, numlong, factor1long, factor2long ) ;	// 30�N��쥻�n�[��whiteSpace�ƶq 	
	
	else if ( numlong <= 17 ) 
		WhiteSpace( 37, numlong, factor1long, factor2long ) ;	// 40�N��쥻�n�[��whiteSpace�ƶq 		

	else 
		WhiteSpace( 42, numlong, factor1long, factor2long ) ;	// 45�N��쥻�n�[��whiteSpace�ƶq  
	
}



// �j�� ��]�� 
void CalculateFactor( Ulli num , Ulli & factor1, Ulli & factor2, Ulli & innerloop ) {
	Ulli sqrtnum = sqrt(num) ;
	int yn = 0 ;
	for ( sqrtnum = sqrtnum ; sqrtnum > 0 && yn == 0  ; sqrtnum-- ) {
		if ( num % sqrtnum == 0 ) {
			factor1 = sqrtnum ;		
			factor2 = num / sqrtnum ;			
			yn = 1 ;	
		}
		
		innerloop++ ;
	}
}

// �j�� �D�n:���O��ƦC  + ���n:��]��+�L�X�Ҧ��F�� 
void IterativeCalculateFib( int number, Series & value, int & outerLoop ) {
	//�O��ƦC
	//�q��2�Ӥ���
	//�s�Ʀr�A�|�O�̫�@�ӼƩM�˼ƲĤG�Ӽƪ��`�M 
	for ( int i = 1 ; i <= number ; i++ ) {
		
		value.serialnum[i] = i ;
		
		if ( i == 1 ) value.num[i] = 1 ;			
		else if ( i == 2 ) value.num[i] = 2 ;							
		else value.num[i] = value.num[i-1] + value.num[i-2] ;  

		CalculateFactor( value.num[i] , value.factor1[i], value.factor2[i], value.innerloop[i] ) ; // ��]�� 
		
		PrintSerialNum( value.serialnum[i] ) ; // �L�s��
		cout << " " << value.num[i] << " = " ; // �L�Ʀr
		PrintAllNumber( value.num[i] , value.factor1[i], value.factor2[i] ) ; // �L�X�]�ƭ��]�Ƹ�ť�
		cout << "(Inner loop:" ; 
		PrintInnerloop( value.innerloop[i]) ; // �L���j�馸�� 
		
		
		outerLoop++ ; 
	}

	cout << "<Outer loop:   " << outerLoop <<" times>" << endl ;
}


// ���j �O��ƦC ���� 
void RecursionCalculateFib( int i, int number, Series & value, int & outerLoop ) {
	if ( i <= number )  {
		value.serialnum[i] = i ;
		
		if ( i == 1 ) value.num[i] = 1 ;			
		else if ( i == 2 ) value.num[i] = 2 ;							
		else value.num[i] = value.num[i-1] + value.num[i-2] ; 
		
			
		Ulli sqrtnum = sqrt( value.num[i] ) ; // num�}�ڸ�	
	
		RecurCalculateFactor( sqrtnum, value.num[i], value.factor1[i], value.factor2[i], value.innerloop[i]) ; // ��]�� 		
		
		PrintSerialNum( value.serialnum[i] ) ; // �L�s��
		cout << " " << value.num[i] << " = " ; // �L�Ʀr 
		
		if ( value.innerloop[i] > 10000000 ) 
			cout << "(Inner recursion: more than   10000000 times)" << endl ; // �L���j�馸�� 	 
			
		else {
			PrintAllNumber( value.num[i] , value.factor1[i], value.factor2[i] ) ; // �L�X�]�ƭ��]�Ƹ�ť� 
			cout << "(Inner recursion:" ;   
			PrintInnerloop( value.innerloop[i] ) ; // �L���j�馸�� 
		}
		
		outerLoop++ ;
		RecursionCalculateFib( i + 1 , number, value, outerLoop ) ;	
	}
	
	else cout << "<<Outer recursion:  " << outerLoop <<" times>" << endl ;

}


//���j ��]�� 
void RecurCalculateFactor( Ulli sqrtnum, Ulli num , Ulli & factor1, Ulli & factor2, Ulli & innerloop ) {
	int yn = 0 ; 
	innerloop++ ; 
	if ( innerloop <= 10000000 ) {
	
		if ( num % sqrtnum == 0 && yn == 0 ) {	
			factor1 = sqrtnum ;		
			factor2 = num / sqrtnum ;	
			yn = 1 ; // �X���j 
		}
	
		else 
			RecurCalculateFactor( sqrtnum - 1 , num , factor1, factor2, innerloop ) ;				
	}	
}






// ���j  �ƦC 
void Prem( OneLine num, Ulli & serialNum, Ulli temp ) {
	Ulli deline = pow( 10, N ) ; // N��Ʀr ����j��N+1��Ʀr �����I 
	if ( temp < deline ) {
		
		ScanfNum( num, temp ) ; // �P�_Ū�Ʀr	
		
		if ( RepeatYn( num ) ) { // ������ 
			serialNum++ ;
			cout << "[" << serialNum << "]" ;
			for ( int i = 0 ; i < N ; i++ ) {
				cout << " " << num.ch_Line[i] ; 			
			}
			cout << endl ; 
		}
		
		Prem( num, serialNum, temp + 1 ) ;			
	}
}

 // �P�_Ū�Ʀr �p��N��� �i�Ĥ@��if �Ϥ��ielse 	
void ScanfNum( OneLine & num, Ulli temp ) {
	
	Ulli demarcation = pow( 10, N-1 ) ; // N��Ʀr ��N��Ʀr�H�U���� �����I 
	if ( temp < demarcation ) { // �N�Ʀr��J�}�C �q�̫�}�l�� 
		for ( int i = N-1 ; i > 0 ; i-- ) { // ���|�ʨ�num.ch_Line[0]
			num.ch_Line[i] = 48 + temp % 10 ; //  // ASCLL 48��0 
			temp = temp / 10 ;
		}	 				
	}
		
	else sprintf(num.ch_Line, "%d", temp );
	
}


//�P�_ 1�C�� ���L���ƼƦr 
bool RepeatYn( OneLine num ) {
	for ( int i = 0 ; i < N ; i++ ) {
		for ( int j = i+1 ; j < N ; j++ ) {
			if ( num.ch_Line[i] == num.ch_Line[j] )
				return false ;
		}
	}
	
	return true ;
}








