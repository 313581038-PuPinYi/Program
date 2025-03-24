// 10927207_�Z�~��_��T�G�A
#include <iostream>
#include <vector> // vector 
#include <fstream> // Ū�� 
#include <time.h> // �p��ɶ� 
#include <conio.h> // �����N���~�� 
#include <sstream> // istringstream stream�Ψ� 
#include <cstdlib> // atoi
#include <cstring>
#include <iomanip> // �ϥΤp���I���� 
#include <cmath>
#include <time.h>
using namespace std ; 

struct GradData {
	int int_serialNum = 0 ;
	int int_studNum = 0 ;	
};


bool sfile = true ; // no file or no data 
string command ;
vector<GradData> tempList ;
GradData oneData ;
int TurnToNumber( string temp ) ;
void ReadTxt() ; // Ū��
void Print( vector<GradData> list ) ; // �L��� 
void PrintAnswer( vector<GradData> list ) ; // print root(Task1), leftmost bottom,bottom

class Max_Heap {
	public:
		vector<GradData> heapList ;
		void GradHeap() ; // made max heap
		void ReUp( int child, int father ) ; // Add Data and up
};

class Deap {
	public:
		int middle = 0 ; // �{�bNewNode�b�����@�檺���I 
		int corrNode = 0 ; // ���k�����[�����I] 
		vector<GradData> deapList ;
		void GradDeap() ; // made Double heap( min heap and max heap )		
		int SwapFR( int i ) ; // swap correspondence left and right node
		void MinReUp( int child, int father ) ; // Min Heap Add Data and up		
		void MaxReUp( int child, int father ) ; // Max Heap Add Data and up	
};

class Min_Max {
	public:
		int level = 0 ; // ���h��1-N 
		int fatherNode = 0 ; // ���k�����[�����I] 	
		vector<GradData> minMaxList ;
		void minMaxHeap() ;	
		int SwapCF( int i ) ; // swap �l�`�I���`�I 
		void MinReUp( int child, int grandfather ) ; // Min Heap Add Data and up	�l�`�I �P �����`�I	
		void MaxReUp( int child, int grandfather ) ; // Max Heap Add Data and up �l�`�I �P �����`�I			
};


int main() {
	Max_Heap heap ;
	Deap deap ;
	Min_Max minMaxHeap ;
	while ( true ) {
		//double start = 0 ,end = 0, time = 0 ; 
		sfile = true ;
		cout << endl << "****** Heap Construction ******" ;
		cout << endl << "* 0. QUIT                     *" ;
		cout << endl << "* 1. Build a max heap         *" ;
		cout << endl << "* 2. Build a deap             *" ;
		cout << endl << "* 3. Build a min max Heap     *" ;		
		cout << endl << "*******************************" ;
		cout << endl << "Input a choice(0, 1, 2, 3): " ;
		cin >> command ;
		sfile = true ;
		
		if ( command.compare("1") == 0 || command.compare("2") == 0 || command.compare("3") == 0 ) {
			ReadTxt() ; 
			if ( sfile == true ) {
				if ( command.compare("1") == 0 ) {
					//start = clock() ;
					heap.GradHeap() ;	
					//end = clock() ;
					//time = end - start ;
					//cout << "time: " << time << endl ;
				} // if
				if ( command.compare("2") == 0 ) {
					//start = clock() ;
					deap.GradDeap() ;	
					//end = clock() ;
					//time = end - start ;
					//cout << "time: " << time << endl ;
				} // if
				if ( command.compare("3") == 0 ) {
					minMaxHeap.minMaxHeap();
				} // if
			} // if
		} // if
		
		else if ( command.compare("0") == 0 ) return 0 ;
		
		else cout << endl << "Command does not exist!" << endl ;
	} // while 	
} // main()


int TurnToNumber( string temp ) {
	int number = 0 ;
	for ( int j = 0 ; j < temp.length() ; j++ ) 
		if ( temp[j] != '\"' &&  temp[j] != ',' )  
			number =  ( temp[j] - '0') + number * 10 ;		
	return number ;	
} // int TurnToNumber()

void ReadTxt() { // Ū��
	tempList.clear() ;
	string num, name ;
	ifstream file ;
	cout << endl << "Input a file number (101,102,103......[0] Quit): " ;
	while ( cin >> num ) {
		name = "input" + num + ".txt" ;
		file.open(name, ios_base::in) ; 
		if ( ( num.compare("0") == 0 ) ) {
			sfile = false ;
			break ;
		} // if
		
    	if (file.is_open()) break ;
		else cout << "\n### " << name << " does not exist! ###\n" ;
		cout << endl << "Input a file number(101,102,103,......): " ;	  		
	} // while 

	if (file.is_open()) {	
    	int count = 0 ;
		string line, tok ;
		vector<string> temp ;
 		getline( file, line ) ;
 		getline( file, line ) ;
 		getline( file, line ) ;
		while (getline( file, line )) {
			count++ ;
			oneData.int_serialNum = count ;
			temp.clear() ;
			istringstream stream(line) ; // Ū�J�@�� 
			while ( getline(stream, tok, '\t') ) temp.push_back(tok) ; // ��tab 
    		for ( int i = 0 ; i < temp.size() ; i++ ) {
  				if ( i == 6 ) {
  					if ( temp[i][0] == '\"' ) oneData.int_studNum = TurnToNumber( temp[i] ) ; // ���I105.txt�Ʀr�W�L1000->"1,000" 
  					else oneData.int_studNum = atoi(temp[i].c_str()) ;  
				} // if
			} // for
			
			tempList.push_back(oneData) ; // oneData into tempList
			stream.clear() ; // ����O����				
		} // while
		
		file.close() ; // �����ɮ� 
		if ( !tempList.size()) {
			cout << "### Get nothing from the file " << name << "!###" << endl ;
			cout << endl << "There is no data!" << endl ;
			sfile = false ;
		} // if		
		//else Print() ;
	} // if
} // ReadTxt()

void Print( vector<GradData> list ) { // �L��� 
	for ( int i = 0; i < list.size() ; i++ ) {
		cout << "[" << list[i].int_serialNum << "] " << list[i].int_studNum << endl ; 
	} // for
} // Print()

void PrintAnswer( vector<GradData> list ) { // print root,leftmost bottom,bottom	
	int i = 0 ;
	if ( command.compare("1") == 0 || command.compare("3") == 0 ) 
		cout << "root: " << "[" << list[i].int_serialNum << "] " << list[i].int_studNum << endl ; 	

	i = list.size() - 1 ;
	cout << "bottom: " << "[" << list[i].int_serialNum << "] " << list[i].int_studNum << endl ;

	i = log2( list.size() ) ;
	i = pow( 2, i ) - 1 ;
	cout << "leftmost bottom: " << "["<< list[i].int_serialNum << "] " << list[i].int_studNum << endl ; 				
} // PrintAnswer() 

void Max_Heap::GradHeap() { // made max heap
	heapList.clear() ;
	for ( int i = 0 ; i < tempList.size() ; i++ ) {
		oneData = tempList[i] ;
		heapList.push_back(oneData) ;
		if ( i != 0 ) ReUp( i, (i-1)/2 ) ; // not root
	} // for	
	
	cout << "<Max Heap>" << endl ;
	PrintAnswer( heapList ) ;
} // Max_Heap::GradHeap

void Max_Heap::ReUp( int child, int father ) { // Add Data and up 
    if ( child == 0 && father == 0 ) return ;
	else if ( heapList[child].int_studNum <= heapList[father].int_studNum ) return ;	
	else swap( heapList[child], heapList[father] ) ;
		
	ReUp( father, (father-1)/2 ) ; 
} // Max_Heap::ReUp()

void Deap::GradDeap() { // made Double heap( min heap and max heap )
	deapList.clear() ;
	int NewNodeSplace = 0 ;
	oneData.int_serialNum = 0 ;
	oneData.int_studNum = 0 ;
	deapList.push_back(oneData) ;
	for ( int i = 0 ; i < tempList.size() ; i++ ) {
		oneData = tempList[i] ;
		deapList.push_back(oneData) ;
		NewNodeSplace = SwapFR( i+1 ) ;	
		if ( NewNodeSplace < middle )  // new node in min heap
			MinReUp( NewNodeSplace, (NewNodeSplace-1)/2 ) ; 
		else // new node in max heap	
			MaxReUp( NewNodeSplace, (NewNodeSplace-1)/2 ) ;
	} // for	
	
	cout << "<Deap>" << endl ;
	PrintAnswer( deapList ) ;
} // Deap::GradDeap

int Deap::SwapFR( int i ) { // swap correspondence left and right node
	int power = log2( i+1 ) ;
	middle = pow( 2, power ) - 1 +  pow( 2, power ) / 2 ; // �p���e�椤�I 	
	if ( i <= 1 ) return i ; // �e��� node, root and real first node 
	else {
		if ( i < middle ) { // min tree node more then max tree node [left child Compare Rigth father]
			corrNode = ( ( i + pow( 2, power ) / 2 ) - 1 ) / 2 ; // �k��������`�I
			if ( deapList[i].int_studNum > deapList[corrNode].int_studNum ) { // ���l�`�I > �k���`�I 
				swap( deapList[i], deapList[corrNode] ) ;
				middle = pow( 2, power-1 ) - 1 +  pow( 2, power-1 ) / 2 ; // �p�����`�I���@�檺���I
				return corrNode ;
			} // if
		} // if 
		else { // [left child Compare Rigth child]
			corrNode = i - pow( 2, power ) / 2 ; // ��������l�`�I 			
			if ( deapList[i].int_studNum < deapList[corrNode].int_studNum ) { // �k�l�`�I < ���l�`�I
				swap( deapList[i], deapList[corrNode] ) ;
				return corrNode ;
			} // if
		} // else 			
	} // else
	
	return i ;
} // Deap::SwapFR()

void Deap::MinReUp( int child, int father ) { // Min Heap Add Data and up	
    if ( father == 0 ) return ;
	else if ( deapList[child].int_studNum >= deapList[father].int_studNum ) return ;	
	else swap( deapList[child], deapList[father] ) ;
		
	MinReUp( father, (father-1)/2 ) ; 	
} // Deap::MinReUp()

void Deap::MaxReUp( int child, int father ) { // Max Heap Add Data and up	
    if ( father == 0 ) return ;
	else if ( deapList[child].int_studNum <= deapList[father].int_studNum ) return ;	
	else swap( deapList[child], deapList[father] ) ;
		
	MaxReUp( father, (father-1)/2 ) ; 	
} // Deap::MaxReUp()

void Min_Max::minMaxHeap() {
	minMaxList.clear() ;
	int NewNodeSplace = 0 ;
	for ( int i = 0 ; i < tempList.size() ; i++ ) {
		oneData = tempList[i] ;
		minMaxList.push_back(oneData) ;
		NewNodeSplace = SwapCF( i ) ;
		if ( level % 2 == 1 )  // min heap
			MinReUp( NewNodeSplace, ((NewNodeSplace-1)/2-1)/2 ) ; 
		else if( level % 2 == 0 ) // max heap	
			MaxReUp( NewNodeSplace, ((NewNodeSplace-1)/2-1)/2 ) ;	
	} // for	
	
	cout << "<Min_Max Heap>" << endl ;
	//Print( minMaxList ) ;
	PrintAnswer( minMaxList ) ;		
} // Min_Max:minMaxHeap()

int Min_Max::SwapCF( int i ) {
	level = log2(i+1) + 1 ; // ���h 
	fatherNode = ( i - 1 ) / 2 ;
	if ( i == 0 ) ;
	else {
		if ( level % 2 == 1 ) { // �s�`�I�bmin heap 
			if (  minMaxList[i].int_studNum > minMaxList[fatherNode].int_studNum ) {
				swap( minMaxList[i], minMaxList[fatherNode] ) ;
				level = level - 1 ;
				return fatherNode ;
			} // if
		} // else if
		else if ( level % 2 == 0 ) { // �s�`�I�bmax heap 
			if (  minMaxList[i].int_studNum < minMaxList[fatherNode].int_studNum ) {
				swap( minMaxList[i], minMaxList[fatherNode]) ;
				level = level - 1 ;
				return fatherNode ;
			} // if
		} // else if		
	} // else
	
	return i;
} // Min_Max::SwapCF()

void Min_Max::MinReUp( int child, int grandfather ) {
	if ( child == 0 && grandfather == 0 ) return ;
	else if ( minMaxList[child].int_studNum >= minMaxList[grandfather].int_studNum ) return ;	
	else swap( minMaxList[child], minMaxList[grandfather] ) ;
		
	MinReUp( grandfather, ((grandfather-1)/2-1)/2 ) ; 
} // Min_Max::MinReUp()

void Min_Max::MaxReUp( int child, int grandfather ) {
	if ( grandfather <= 0 ) return ;
	else if ( minMaxList[child].int_studNum <= minMaxList[grandfather].int_studNum ) return ;	
	else swap( minMaxList[child], minMaxList[grandfather] ) ;
		
	MaxReUp( grandfather, ((grandfather-1)/2-1)/2 ) ; 	
} // Min_Max::MaxReUp()
