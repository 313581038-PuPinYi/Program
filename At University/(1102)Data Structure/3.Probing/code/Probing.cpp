// 10927207_�Z�~��_��T�G�A 10927248_�s���w 
#include <iostream>
#include <vector> // vector 
#include <fstream> // Ū�� 
#include <cstdlib> // atoi
#include <cstring>
#include <sstream> // istringstream stream�Ψ� 
#include <math.h>
#include <iomanip>
#include <iterator>
using namespace std ; 

struct Data {
	char id[10] = {'0'} ; // �Ǹ� 
    char name[10] = {'\0'}  ; // �W�r  
	unsigned char score1 = 0 ; // ���� 
	unsigned char score2 = 0 ; // ���� 
	unsigned char score3 = 0 ; // ���� 
	unsigned char score4 = 0 ; // ���� 
	unsigned char score5 = 0 ; // ���� 
	unsigned char score6 = 0 ; // ���� 				
	float average = 0.0 ; // �������� 
};

struct TableData {
	string Res = "\0" ; // �l�� 
	char id[10] = {'\0'} ;  // �Ǹ� 
    char name[10] = {'\0'}  ; // �W�r  			
	string average = "\0" ;  // �������� 
};

bool sfile = true ; // ���L�ɮ�
bool isbin = false ;  // ���Lbin�� 
string num ; //�ɦW 
string command ;  
vector<Data> tempList ; // �Ȧstxt�ɪ���� 


string FloatToString( float n ) { // �B�I����r�� 
    stringstream sstream;
    sstream << n;
    string str = sstream.str();
	return str ;
} // FloatToString

string IntToString( int n ) { // �����r�� 
	string str ;
	stringstream strtoint(str) ;
	strtoint << n ;
	return strtoint.str();
} // IntToString()

void Createbin() { //�зsbin��	 
	ofstream newFile ; // Create a new file
	string name = "input" + num + ".bin" ;
	newFile.open(name, ios::out | ios::binary ) ; // ��󥴶}	
	// �g�� 
	// ostream & write(char* buffer, int count);
	// �䤤�Abuffer �Ω���w�n�g�J�ɮת��G�i����ƪ��_�l��m�Fcount �Ω���w�g�J�줸�ժ��Ӽ�			    
	for ( int k = 0 ; k < tempList.size() ; k++ ) newFile.write( (char *) &tempList[k], sizeof(Data)) ; // �@��@��Ū��		 	   		  	
	newFile.close() ;	
	cout << "build the " << name << " !" << endl << endl ; 	   
	tempList.clear() ; 		
} // Createbin()

void ReadTxt() { // Ū��txt�� 
	ifstream file ;
	file.open("input" + num + ".txt", ios_base::in) ; 
	if (file.is_open()) {	
    	Data oneData ;
		string line, tok ;
		char temp2[10] ;
		vector<string> temp ;
		while (getline( file, line ) ) { 		
			istringstream stream(line) ; // Ū�J�@�� 
			while ( getline(stream, tok, '\t') ) temp.push_back(tok) ; // ��tab 
    		for ( int i = 0 ; i < temp.size() ; i++ ) {  
    			for ( int j = 0 ; j < 10 ; j++ ) temp2[j] = temp[i][j] ; 	

				if ( i == 0 ) strcpy( oneData.id, temp2 ) ;
				if ( i == 1 ) strcpy( oneData.name, temp2 ) ;				
				if ( i == 2 ) oneData.score1 = atoi(temp[i].c_str()) ;
				if ( i == 3 ) oneData.score2 = atoi(temp[i].c_str()) ;
				if ( i == 4 ) oneData.score3 = atoi(temp[i].c_str()) ;
				if ( i == 5 ) oneData.score4 = atoi(temp[i].c_str()) ;					
				if ( i == 6 ) oneData.score5 = atoi(temp[i].c_str()) ;
				if ( i == 7 ) oneData.score6 = atoi(temp[i].c_str()) ;
				if ( i == 8 ) oneData.average = atof(temp[i].c_str()) ;															
			} // for
																  			
			tempList.push_back(oneData) ; // oneData into tempList	
 			temp.clear() ;
 			stream.clear() ;				
		} // while
			
		file.close() ; // �����ɮ� 
		
		if ( !tempList.size()) {
			cout << "### Get nothing from the file " << "input" << num <<  ".txt" << "!###" << endl ;
			cout << endl << "There is no data!" << endl ;
			sfile = false ;
		} // if					
		else Createbin() ; //�зsbin��					
	} // if
} // ReadTxt()

void Readbin() { // Ūbin�� 
	tempList.clear() ;
	ifstream binFile ;
	Data oneData ; 
	binFile.open("input" + num + ".bin", ios_base::in | ios::binary ) ; // �}bin�� 
	if ( binFile.is_open() ) {	
        while (!binFile.eof()) { // �@��@��Ū��	 
	    	binFile.read((char *) &oneData, sizeof(oneData) ) ;
			tempList.push_back( oneData ) ;							
			if ( binFile.fail() ) tempList.pop_back() ;	
        } // while						
		binFile.close() ; // �����ɮ� 		
	} // if	
} // Readbin()

void CompareBinTxt() { // ����O�_�ݳ�bin��: �Lbin��  ��bin�ɱNtxt�ɪ���Ƽg�J 
	sfile = true ;
	ifstream file1, file2 ;
	cout << endl << "Input a file number ([0] Quit): " ;
		
	while ( cin >> num ) {
		file1.open("input" + num + ".txt", ios_base::in) ; 
		file2.open("input" + num + ".bin", ios_base::in) ; 		
		
		if ( ( num.compare("0") == 0 ) ) { 
			sfile = false ;
			break ;	
		} // if
    	else if ( file2.is_open() ) { // ��bin�� 
    		cout << "\nHave " << "input" << num << ".bin !" << endl << endl ;
    		file2.close() ;
    		break ;
		} // else if			
 		else if ( file1.is_open() ) { // �Lbin�ɡA��txt�� 
    		cout << "\nDon`t have " << "input " << num << ".bin."  << endl ; 			
    		ReadTxt() ;
    		file1.close() ;
    		break ;
		} // else if				
		else cout << "\n### " << "input" << num <<  ".txt" << " does not exist! ###\n" ;
		cout << endl << "Input a file number([0] Quit): " ;	  		
	} // while 		
} // CompareBinTxt()

class Hash {  
	protected:
		int range = 0 ; // ���j�p
		unsigned long long int  numSum = 0 ; // �Ʀr�`�M  
		vector<TableData> dataList ; // �Ȧsbin�ɪ����  
		string name = "" ; // �ɮץ[�榡�W��
		string xY = "" ; // X �� Y �� Hash Table 
		string type = "" ; // �ɮ����O 
		
			
		int GetPrime( int n ) { // �p���n�j���̤p��� 
			int sqrtI ;
			bool isprime = true ;
			for ( int i = n + 1;; i++ ) {
				isprime = true ;
				sqrtI = sqrt(i);
				for ( int j = 2 ; j <= sqrtI ; ++j ) {
					if (i % j == 0) {
						isprime = false ;
						break;
					} // if
				} // for
				if ( isprime == true ) return i;
			} // for
			
			return -1;
		} // GetPrime()
	
		void CreateArray() { // �гy��� 
			dataList.clear() ;
			TableData t ;
			for ( int i = 0 ; i < range ; i++ ) dataList.push_back(t) ;
		} // array()
		
		void numberSum( Data data ) { // �p��Ǹ���ASCII�ۭ����`�M 
			unsigned long long int size = 1 ; 
			int count = 1 ; 
			for( int i = 0 ; i < 10 ; i++ ) {
				if ( isdigit(data.id[i]) ) size = size * (int)data.id[i] ;			
			} // for	
			numSum = size ;
		} // CalTableSize()
	
		void CreateTxt() { //�зs***.txt�� 	 
			ofstream newFile ; // Create a new file
			int size = 11 ; // �����e�� 
			string strRange = IntToString(range) ;  
			newFile.open(name, ios::out ) ; // ��󥴶}
						    
			newFile << " --- Hash Table " << xY << " --- (" << type << ")" << endl ; 
			for ( int k = 0 ; k < range ; k++ ) { // �@��@��g�J�ɮ� 
				size = 11 ;
				newFile << "[" << setw(strRange.length()+1) << k << "]" ;
				if ( dataList[k].Res != "\0" ) 
					newFile << setw(11) << dataList[k].Res << "," << setw(11) << dataList[k].id << "," 
					<< setw(11)  << dataList[k].name << "," << setw(11) << dataList[k].average << endl ;		
				else 
					newFile << endl ;
			} // for
			
			newFile.close() ;		   
		} // CreateTxt()
} ;

class LinearHash: protected Hash {
	protected:		
		void average( float & unsuccAverage, float succAverage ) { // �p��unsuccessfuil�Bsuccessfuil����	�A�L�X		
			// unsuccessful
		 	int count = 0 ; // �j�M���� 
			float sum = 0.0 ; // �j�M�����`�M
			for ( int i = 0 ; i < range ; i++ ) {
				int j = i ;
				count = 1 ;
				while ( dataList[j].Res != "\0" ) { // �l�Ƭ�\0,������
					count++, j++ ; 	
					if ( j >= range ) j = j % range ;
				} // while 		 
				if ( count != 0 ) count = count - 1 ; 
			 	sum = sum + count ; 
			} // for
			
			unsuccAverage = sum / range ; 	// unsuccessful average
				
			cout << "Hash table X has been created." << endl ;
			cout << "unsuccessful search: " <<  fixed  <<  setprecision(4) << unsuccAverage << " comparisons on average" << endl ;
			cout << "successful search: " <<  fixed  <<  setprecision(4) << succAverage << " comparisons on average" << endl ;			
		} // average() 
	
	public:			
		void BuildLinearProbing() {
	 		int count = 1 ; // �j�M���� 
			float sum = 0.0 ; // �j�M�����`�M 
			float unsuccAverage = 0.0, succAverage = 0.0 ; // �������� 
			range = 1.2 * tempList.size() ; // ����`���*1.2  
			range = GetPrime( range ) ; // ���j�p
			CreateArray() ; // �Ъ��
			for ( int i = 0 ; i < tempList.size() ; i++ ) {
				numberSum( tempList[i] ) ;
				int reside = numSum  % range ; 
				int resTemp = reside ;
				count = 1 ;
				while ( dataList[resTemp].Res != "\0" ) { // �l�Ƭ�\0,������
					count++, resTemp++ ; 	
					if ( resTemp >= range ) resTemp = resTemp % range ;
				} // while 
				
				if ( dataList[resTemp].Res == "\0" ) { // �s�W��ƦܵL�I����m 
					dataList[resTemp].Res = IntToString( reside ) ;
					strcpy(dataList[resTemp].id, tempList[i].id ) ;
					strcpy( dataList[resTemp].name, tempList[i].name ) ;
					dataList[resTemp].average = FloatToString( tempList[i].average ) ;			
				} // if		  			  		
				
				sum = sum + count ; 
			} // for
			
			name = "linear" + num + ".txt" ; // �ɮץ[�榡�W��
			xY = "X" ; // X �� Y �� Hash Table 
			type = "linear probing" ; // �ɮ����O 
			CreateTxt() ;
			succAverage = sum / tempList.size() ; // successful average	
			average( unsuccAverage, succAverage ) ; // �p��unsuccessfuil�Bsuccessfuil�����A�L�X	
			tempList.clear() ;
		} // BuildLinearProbing()	
};

class DoubleHash: protected Hash { 
	protected:
		int stepsize = 0 ; // hash2 �첾�Z�� 			
		
	public:
		void BuildDoubleHash() {
			dataList.clear() ;
	 		int count = 1 ; // ���榸�� 
			float sum = 0.0 ; // �����`�M 
			float unsuccAverage = 0.0, succAverage = 0.0 ; // �������� 
			range = 1.2 * tempList.size() ; // ����`���*1.2 
			range = GetPrime( range ) ; // ���j�p 
			CreateArray() ;	// �Ъ��					
			for ( int i = 0 ; i < tempList.size() ; i++ ) {							
				numberSum( tempList[i] ) ;
				int reside = numSum  % range ; 
				int resTemp = reside ;
				count = 1 ;
				while ( dataList[resTemp].Res != "\0" ) { // �l�Ƭ�\0,������
					count++ ;
					if ( count == 2 )  stepsize = GetPrime( tempList.size() / 3 ) - numSum % ( GetPrime( tempList.size() / 3 ) ) ;						
					resTemp = resTemp + stepsize ;
					if ( resTemp >= range ) resTemp = resTemp % range ;		
				} // while 
				
				if ( dataList[resTemp].Res == "\0" ) { // �s�W��ƦܵL�I����m 
					dataList[resTemp].Res = IntToString( reside ) ;
					strcpy(dataList[resTemp].id, tempList[i].id ) ;
					strcpy( dataList[resTemp].name, tempList[i].name ) ;
					dataList[resTemp].average = FloatToString( tempList[i].average ) ;			
				} // if		  			  		
				
				sum = sum + count ; 
			} // for
			
			name = "double" + num + ".txt" ; // �ɮץ[�榡�W��
			xY = "Y" ; // X �� Y �� Hash Table 
 			type = "double hashing" ; // �ɮ����O 			
			CreateTxt() ; // ���� 
			succAverage = sum / tempList.size() ; // successful average	
			cout << "Hash table Y has been created." << endl ;
			cout << "successful search: " <<  fixed  <<  setprecision(4) << succAverage << " comparisons on average" << endl ;				
			tempList.clear() ;
		} // BuildLinearProbing()		
};


int main() {
	LinearHash lh ; 
	DoubleHash bh ; 	
	while ( true ) {
		cout << endl << "****** Heap Construction ******" ;
		cout << endl << "* 0. QUIT                     *" ;
		cout << endl << "* 1. Build linear probing     *" ;
		cout << endl << "* 2. Build double hash        *" ;	
		cout << endl << "*******************************" ;
		cout << endl << "Input a choice(0, 1, 2): " ;
		cin >> command ;

		
		if ( command.compare("1") == 0 ) { 
			CompareBinTxt()	; // ����O�_���ഫ: �Lbin��  ��bin�ɱNtxt�ɪ���Ƽg�J 
			if (sfile == true ) {
				Readbin() ;
				lh.BuildLinearProbing();				
			}
		} // if
		
		else if ( command.compare("2") == 0 ) {	
			CompareBinTxt() ;
			if (sfile == true ) {			
				Readbin() ;
				bh.BuildDoubleHash() ;
			}
		} // if
		
		else if ( command.compare("0") == 0 ) return 0 ;
		
		else cout << endl << "Command does not exist!" << endl ;
	} // while 	
} // main()




