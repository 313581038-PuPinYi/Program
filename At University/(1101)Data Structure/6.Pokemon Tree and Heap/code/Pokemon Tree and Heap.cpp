// �Z�~�� 10927207   �d��� 10927234 
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
using namespace std ;

struct PokemonData {
	int i = 0 ;
	string name = "" ;
	string type = "" ;
	int num = 0 ;
	int HP = 0 ;
	int attack = 0 ;
	int defense = 0 ;	
};

bool sfile = true ;
string command ;
vector<PokemonData> PokemonList ;
PokemonData oneR ;
void ReadTxt() ; // Ū��
void Print() ; // �L��� 
bool isNumber(string& str) ; // �r��O�_���Ʀr 
	
		
class PokeBalls {
	private: 
		struct TreeNode {
			PokemonData item;
			TreeNode * left;
			TreeNode * right;
		};
		
		typedef TreeNode * TreePtr ;
		TreePtr HpPtr = NULL ;
		
	public:	
		int HpTH = 0 ;
		void reset( TreePtr & walk ) ; // ��l�� 
		void HpTree() ; // �ؾ�
		void searchLeft( TreePtr HpPtr ) ; // �j�M ��̤p�� 
		void searchRight( TreePtr HpPtr ) ; // �j�M ��̤j�� 
};

class Heap {
	public:	
		vector<PokemonData> HeapList ;
		void arrayBST( int i ) ; // ���ȤG �ΰʺA�}�C�ؾ�  
		void countH() ; // ��� �M�̥��B�̩��� 
		void Delete() ;	// �R��ROOT 
		void CopyList() ; // �ƻs PokemonList
		void PrintHeap() ; // �L HeapList
};

int main() {
	PokeBalls pokeBalls ;
	Heap heap ;
	while ( true ) {
		sfile = true ;
		cout << endl << "***** Pokemon Tree and Heap *****" ;
		cout << endl << "* 0. QUIT                       *" ;
		cout << endl << "* 1. Read a file to build BST   *" ;
		cout << endl << "* 2. Transform it into Max Heap *" ;
		cout << endl << "*********************************" ;
		cout << endl << "* 3. Delete max from Max Heap   *" ;
		cout << endl << "*********************************" ;
		cout << endl << "Input a choice(0, 1, 2, 3): " ;
		cin >> command ;
		sfile = true ;
		
		if ( command.compare("1") == 0 ) {
			ReadTxt() ; 
			if ( sfile == true ) {
				pokeBalls.HpTree() ;
			} // if
		} // if
		
		else if ( command.compare("2") == 0 ) {
			if ( PokemonList.size() != 0 ) {
				heap.CopyList() ; // �ƻsPokemonList��HeapList
				int i = ( heap.HeapList.size() - 1 ) / 2 ; // ���`�I�Ӽ� 
				heap.arrayBST( i ) ; // �ΰʺA�}�C�ؾ� 
				heap.PrintHeap() ; // �LHeapList
				heap.countH() ;	// ��� �M�̥��B�̩���
			} // if
			
			else cout << endl << "----- Execute Mission 1 first! -----" << endl ; 
		} // eise if
		
		else if ( command.compare("3") == 0 ) {
			if ( heap.HeapList.size() == 0 ) cout << "----- Execute Mission 2 first! -----\n" ;
			else {
				heap.Delete();	
				if ( heap.HeapList.size() != 0 ) { // ����� 
					int i = ( heap.HeapList.size() - 1 ) / 2 ; // ���`�I�Ӽ� 
					heap.arrayBST( i ) ; // �ΰʺA�}�C�ؾ�  
					heap.PrintHeap() ; // �LHeapList 
					heap.countH() ;	// ��� �M�̥��B�̩���
				}
			} // else
		} // else if
		
		else if ( command.compare("0") == 0 ) return 0 ;
		
		else cout << endl << "Command does not exist!" << endl ;
	} // while 	
} // main()

void ReadTxt() { // Ū��
	PokemonList.clear() ;
	string num, name ;
	cout << endl << "Input a file number [0: quit]: " ;
	cin >> num ;
	cout << endl ;	

	name = "input" + num + ".txt" ;  
	ifstream file ;
	file.open(name, ios_base::in) ; // ��󥴶} 

    if (!file.is_open()) {
        cout << "### " << name << " does not exist! ###\n" ;
        cout << endl << "There is no data!" << endl ;
        num = "" ;
        sfile = false ;
    } // if
    else {
		string line, tok ;
		vector<string> temp ;
 		getline( file, line ) ;
		while (getline( file, line )) {
			int count = 0 ;
			istringstream stream(line) ; // Ū�J�@�� 
			temp.clear() ;
			while ( getline(stream, tok, '\t') ) temp.push_back(tok) ; // ��tab 

    		for ( int i = 0 ; i < temp.size() ; i++ ) {  
				if ( i == 0 ) oneR.num = atoi(temp[i].c_str()) ;
				else if ( i == 1 ) oneR.name = temp[i] ;
				else if ( i == 2 ) oneR.type = temp[i] ;
				else if ( i == 5 ) oneR.HP = atoi(temp[i].c_str()) ;
				else if ( i == 6 ) oneR.attack = atoi(temp[i].c_str()) ;
				else if ( i == 7 ) oneR.defense = atoi(temp[i].c_str());
							
				else if ( i == 3 ) // �ư��LType2�����p 
					if ( isNumber(temp[i]) ) i++ ;
			} // for
			
			PokemonList.push_back(oneR) ; // �NoneR�[�JPokemonList
			stream.clear() ; // ����O����				
		} // while
		
		file.close() ; // �����ɮ� 
		
		if ( !PokemonList.size()) {
			cout << "### Get nothing from the file " << name << "!###" << endl ;
			cout << endl << "There is no data!" << endl ;
			sfile = false ;
		} // if		
		
		else Print() ;
	} // else	
	
} // ReadTxt()

void Print() { // �L��� 
	cout << "	#	Name				Type 1		HP	Attack	Defense" << endl ;
	for ( int i = 0; i < PokemonList.size() ; i++ ) {
		PokemonList[i].i = i+1 ;
		cout << "["<< PokemonList[i].i << "]" << "\t" << PokemonList[i].num << "\t" << PokemonList[i].name ; 
		if ( PokemonList[i].name.length() <= 4 ) cout << setw(25) ;
		else if ( PokemonList[i].name.length() <= 15 )  cout << setw(20) ;		
		else cout << setw(8) ;	
		cout << "\t" << PokemonList[i].type << setw(6) << "\t" << PokemonList[i].HP << "\t" << PokemonList[i].attack << "\t" << PokemonList[i].defense << endl;	
	} // for
} // Print()

bool isNumber(string& str) { // �r��O�_���Ʀr 
    for (char &c : str) {
        if (isdigit(c) == 0) return false;
    } // for
    return true;
} // isNumber()

void PokeBalls::reset( TreePtr & walk ) { // ��l�� 
	if ( walk == NULL ) return ;	
	if ( walk->left != NULL ) reset( walk->left ) ;	
   	if ( walk->right != NULL ) reset( walk->right ) ;	
   	if ( walk != NULL ) {
   		delete walk ;
		walk = NULL ;	
	} // if 
} // PokeBalls::reset()

void PokeBalls::HpTree() { // �ؾ�
	int currH = 0 ;
	HpTH = 0 ;
	if ( HpPtr != NULL ) reset( HpPtr ) ;
	for ( int i = 0; i < PokemonList.size() ; i++ ) { 
		// �طs�`�I 
		TreePtr temp = new TreeNode;
		temp->item = PokemonList[i] ;
		temp->right = NULL ;
		temp->left = NULL ;
		
		if ( HpPtr == NULL ) HpPtr = temp ; // ���J�`�I  
		else {
			currH = 1;
			int k = 0 ;
			TreePtr walk = HpPtr ;  
			while ( k == 0 ) {
				if ( PokemonList[i].HP >= walk->item.HP ) { // HP:���>=�`�I 
					if ( walk->right == NULL ) { // �̥k 
						walk->right = temp; // ���J�`�I 
						k = 1; // �X�j�� 
					} // if
					walk = walk->right; // ���k 
				} // if
				else { // HP:���<�`�I 
					if ( walk->left == NULL ) { // �̥� 
						walk->left = temp; // ���J�`�I 
						k = 1; // �X�j�� 
					} // if
					walk = walk->left; // ����  
				} // else
				
				currH++ ; // ��� 
			} // while				
		} // else
		
		if ( currH > HpTH ) HpTH = currH ; // �����̤j�� 
	} // for

	cout << endl << "HP tree height = " << HpTH << endl ;
	
	searchLeft( HpPtr )	;
	searchRight( HpPtr ) ;
} // PokeBalls::HpTree()

void PokeBalls::searchLeft( TreePtr HpPtr ) { // �j�M ��̤p�� 
	// �̥��`�I���̤p��->�����]����̫�@��
	if ( HpPtr->left == NULL ) {
		cout << "Leftmost node:\n" ;
		cout << "	#	Name				Type 1		HP	Attack	Defense" << endl ;
		cout << "["<< HpPtr->item.i << "]" << "\t" << HpPtr->item.num << "\t" << HpPtr->item.name ;
		if ( HpPtr->item.name.length() <= 4 ) cout << setw(25) ;
		else if ( HpPtr->item.name.length() <= 15 )  cout << setw(20) ;		
		else cout << setw(8) ;		
		cout << "\t" <<  HpPtr->item.type << setw(6) << "\t" << HpPtr->item.HP << "\t" << HpPtr->item.attack << "\t" << HpPtr->item.defense << endl;	
	} // if 
	else searchLeft( HpPtr->left ) ; 
} // PokeBalls::searchLeft()

void PokeBalls::searchRight( TreePtr HpPtr ) { // �j�M ��̤j�� 
	// �̥k�`�I���̤j��->���k�]����̫�@�� 
	if ( HpPtr->right == NULL ) {
		cout << "Rightmost node:\n" ;
		cout << "	#	Name				Type 1		HP	Attack	Defense" << endl ;
		cout << "["<< HpPtr->item.i << "]" << "\t" << HpPtr->item.num << "\t" << HpPtr->item.name ;
		if ( HpPtr->item.name.length() <= 4 ) cout << setw(25) ;
		else if ( HpPtr->item.name.length() <= 15 )  cout << setw(20) ;		
		else cout << setw(8) ;		
		cout << "\t" << HpPtr->item.type << setw(6) << "\t" << HpPtr->item.HP << "\t" << HpPtr->item.attack << "\t" << HpPtr->item.defense << endl;	
	} // if 
	else searchRight( HpPtr->right ) ; 
} // PokeBalls::searchRight()

void Heap::arrayBST( int i ) { // ���ȤG �ΰʺA�}�C�ؾ� 
	while ( i >= 0 ) {
		// �l�`�I�Ҥj����`�I 
		if ( i*2+2 < HeapList.size() && HeapList[i].HP < HeapList[i*2+1].HP && HeapList[i].HP < HeapList[i*2+2].HP ) {
			if ( HeapList[i*2+1].HP >= HeapList[i*2+2].HP ) { // ���j��k�l�`�I 
				swap( HeapList[i] , HeapList[i*2+1] ) ;	
				if ( i*2+1 < HeapList.size() ) arrayBST( i*2+1 ) ;
			} // if
			else { // �k�j�󥪤l�`�I 
				swap( HeapList[i] , HeapList[i*2+2] ) ;
				if ( i*2+2 < HeapList.size() ) arrayBST( i*2+2 ) ;	
			}
		} // if
		// ���l�`�I�j����`�I  
		else if ( i*2+1 < HeapList.size() && HeapList[i].HP < HeapList[i*2+1].HP ) {
			swap( HeapList[i] , HeapList[i*2+1] ) ;
			if ( i*2+1 < HeapList.size() ) arrayBST( i*2+1 ) ;
		} // else if 
		// �k�l�`�I�j����`�I  
		else if ( i*2+2 < HeapList.size() && HeapList[i].HP < HeapList[i*2+2].HP ) {
			swap( HeapList[i] , HeapList[i*2+2] ) ;
			if ( i*2+2 < HeapList.size() ) arrayBST( i*2+2 ) ;		
		} // else if 
		i-- ;
	} // while 

} // Heap::arrayBST()

void Heap::PrintHeap() { // �L HeapList 

	cout << "	#	Name				Type 1		HP	Attack	Defense" << endl ;
	for ( int i = 0; i < HeapList.size() ; i++ ) {
		HeapList[i].i = i ;
		cout << "["<< HeapList[i].i << "]" << "\t" << HeapList[i].num << "\t" << HeapList[i].name ; 
		if ( HeapList[i].name.length() <= 4 ) cout << setw(25) ;
		else if ( HeapList[i].name.length() <= 15 )  cout << setw(20) ;		
		else cout << setw(8) ;	
		cout << "\t" << HeapList[i].type << setw(6) << "\t" << HeapList[i].HP << "\t" << HeapList[i].attack << "\t" << HeapList[i].defense << endl;	
	} // for
	
} // Heap::PrintHeap()

void Heap::countH() { // ��� �M�̥��B�̩��� 
	int i = HeapList.size() ;
	// ��� 
	int count = 0 ;
	while ( i > 0 ) {
		i = i / 2 ;
		count++ ;
	} // for 
	// �L�� 
	cout << "HP heap height = " << count << endl ;
	
	// �L�̥��� 
	cout << "Leftmost node:" << endl ;
	i = pow( 2,(count-1) ) -1 ;
	cout << "	#	Name				Type 1		HP	Attack	Defense" << endl ;
	cout << "["<< HeapList[i].i << "]" << "\t" << HeapList[i].num << "\t" << HeapList[i].name ; 
	if ( HeapList[i].name.length() <= 4 ) cout << setw(25) ;
	else if ( HeapList[i].name.length() <= 15 )  cout << setw(20) ;		
	else cout << setw(8) ;	
	cout << "\t" << HeapList[i].type << setw(6) << "\t" << HeapList[i].HP << "\t" << HeapList[i].attack << "\t" << HeapList[i].defense << endl ;	
			
	// �L�̩��� 
	cout << "Bottom:" << endl ;
	i = HeapList.size() - 1 ;
	cout << "	#	Name				Type 1		HP	Attack	Defense" << endl ;
	cout << "["<< HeapList[i].i << "]" << "\t" << HeapList[i].num << "\t" << HeapList[i].name ; 
	if ( HeapList[i].name.length() <= 4 ) cout << setw(25) ;
	else if ( HeapList[i].name.length() <= 15 )  cout << setw(20) ;		
	else cout << setw(8) ;	
	cout << "\t" << HeapList[i].type << setw(6) << "\t" << HeapList[i].HP << "\t" << HeapList[i].attack << "\t" << HeapList[i].defense << endl;	
} // Heap::countH() 

void Heap::CopyList() { // �ƻs PokemonList 
	HeapList.clear() ;
	for ( int i = 0 ; i < PokemonList.size() ; i++ ) {
		oneR = PokemonList[i] ;
		HeapList.push_back(oneR) ;
	} // for
	
} // Heap::CopyList() 

void Heap::Delete() { // �R��ROOT  
	// �̫ᶵ�PROOT���� 
	swap( HeapList[0], HeapList[HeapList.size()-1] ) ;
	vector<PokemonData>::iterator it ;
	it = HeapList.end() - 1;
	// �L�Q�R���� 
	cout << "The removed root:\n" ;
	cout << "	#	Name				Type 1		HP	Attack	Defense" << endl ;
	int i = HeapList.size()-1 ;
	cout << "\t" << HeapList[i].num << "\t" << HeapList[i].name ; 
	if ( HeapList[i].name.length() <= 4 ) cout << setw(25) ;
	else if ( HeapList[i].name.length() <= 15 )  cout << setw(20) ;		
	else cout << setw(8) ;	
	cout << "\t" << HeapList[i].type << setw(6) << "\t" << HeapList[i].HP << "\t" << HeapList[i].attack 
		<< "\t" << HeapList[i].defense << endl << endl;	
	// �R��ROOT 
	HeapList.erase(it) ;

} // Heap::Delete()

