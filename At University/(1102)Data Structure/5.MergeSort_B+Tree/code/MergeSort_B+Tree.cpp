// 10927248 �s���w 10927207 �Z�~��

# include <iostream>
# include <vector>
# include <string>
# include <fstream>
# include <algorithm>
# include <string.h>
# include <deque>
# include <iomanip>
# include <time.h>
# include<conio.h>

using namespace std;

#define BUFFER 401 

struct Info {
    char putID[10] = {'\0'} ;       // �o�T��
    char getID[10] = {'\0'} ;       // ���T��
    float weight = 0.0 ;
} ;


class EXMS {
	private:
		int runs, nextRuns ;  
		int total = 0 ;		
		
			
	public: 	
		void BubbleSort( vector<Info> & data ) {
 		 	for ( int i = 0 ; i < data.size() ; i++ ) {
 		 		for ( int j = (data.size()-1) ; j >= i ; j-- ) {
 		 			if ( j-1 >= i ) {
	 		 			if ( data[j].weight > data[j-1].weight ) {
	 		 				swap( data[j], data[j-1] ) ;	
						} // if 		 				
					} // if
				} // for
			} // for		
		} // Sort()
			
		void Read( string & filenum ) {	  		 
		   
			fstream bin ;
 			string binname = "pairs" + filenum + ".bin" ;
        	bin.open( binname.c_str(), ios:: in | ios_base:: binary ) ;
        	
			// �p���ɮפj�p 			
       		bin.seekg( 0, bin.end ) ;
       		int len = bin.tellg() / sizeof( Info ) ;
       		bin.seekg( 0, bin.beg ) ;
			   
			vector<Info> data( BUFFER ) ; 
			   
			// �@���h�ֽw���ɮ�			
 			if ( len % BUFFER == 0 ) runs = len / BUFFER ; // ���� 
 			else runs = len / BUFFER + 1 ; // �_�� 
		   
			if ( bin.is_open() ) {				   
			    for( int i = 0 ; i < runs ; i++ ) { 
				 		
	           		// �����w�İϪŶ� �n�ק�size�j�p 
	           		if ( (i+1) == runs && runs % BUFFER != 0 ) {
	           			data.resize( len % BUFFER ) ;
					} // if			    
					
					// Ū�� 
	           		bin.read( (char*)&data[0] , sizeof(Info) * data.size() ) ;
         		
	           		// ��w�Ƨ� 
	           		BubbleSort( data ) ;
	           		
	           		// �g�� 
           			fstream outfile ;
           			string filename = "sorted" + to_string(runs-1) + "_" + to_string(i) + ".bin" ;
            		outfile.open( filename.c_str(), ios:: out | ios_base:: binary ) ;
            		outfile.write( (char*)&data[0], sizeof(Info) * data.size() ) ;
            		outfile.close() ;
			    } // while()
			     
			    bin.close() ;
			} // if	
			
			data.clear() ;
		} // Read()

		void Add( vector<Info> & outBuf, vector<Info> & InBuf, int & count ) {
			Info t ;
			t.weight = InBuf[0].weight ;
			strcpy(t.getID, InBuf[0].getID ) ;
			strcpy( t.putID, InBuf[0].putID ) ;
			outBuf.push_back( t ) ;
			count++ ;
		} // if
		
		void Merge() {
			int f1size1, f2size2 ;
 			fstream outfile, f1, f2 ;
		
			for ( int i = 0, j = 0 ; i < nextRuns && j < runs ; i = i + 1, j = j + 2 ) {

				string filename = "sorted" + to_string(nextRuns-1) + "_" + to_string(i) + ".bin" ;	
			    string f1name = "sorted" + to_string(runs-1) + "_" + to_string(j) + ".bin" ;
		    	string f2name = "sorted" + to_string(runs-1) + "_" + to_string(j+1) + ".bin" ;
		 		f1.open( f1name.c_str(), ios:: in | ios_base:: binary ) ;
				f2.open( f2name.c_str(), ios:: in | ios_base:: binary ) ;
				outfile.open( filename.c_str(), ios:: out | ios_base:: binary ) ;  


       			// �p��file1���X�����
        		if ( f1.is_open() ) {			
	      			f1.seekg( 0, f1.end ) ;
	     			f1size1 = f1.tellg() / sizeof(Info) ;
	    			f1.seekg( 0, f1.beg ) ;
				} // if() 

        		// ���o���ɮ�=>�p��file2���X�����
        		if ( f2.is_open() ) {
	     			f2.seekg( 0, f2.end ) ;
	        		f2size2 = f2.tellg() / sizeof(Info) ;
	        		f2.seekg( 0, f2.beg ) ;
				} // if()

				// ��l��Buffer_Size�j�p 
				vector<Info> InBuf1( BUFFER / 4 ), InBuf2( BUFFER / 4 ), outBuf ; 
		
				if ( f1size1 < BUFFER / 4 ) InBuf1.resize( f1size1 ) ;
				if ( f2size2 < BUFFER / 4 ) InBuf2.resize( f2size2 ) ;
		
				if ( f1.is_open() && f2.is_open() ) {
					
					int count1 = 0 , count2 = 0 ; 
					f1.read( (char*)&InBuf1[0] , sizeof(Info) * InBuf1.size() ) ;				 
					f2.read( (char*)&InBuf2[0] , sizeof(Info) * InBuf2.size() ) ;			

				 	while ( f1size1 != 0 || f2size2 != 0 ) {	
				 							
						if ( f2size2 == 0 ) { // �ɮ�2�wŪ��
							Add( outBuf, InBuf1, count1 ) ;
							InBuf1.erase( InBuf1.begin() ) ;
							f1size1-- ;
						} // if
						
						// �ɮ�1�wŪ��
					 	else if ( f1size1 == 0 ) { 
					 		Add( outBuf, InBuf2, count2 ) ;	
							InBuf2.erase( InBuf2.begin() ) ;
							f2size2-- ;
						} // else if
						
						// �ɮ�1.2��Ū�� 1>=2
						else if ( InBuf1[0].weight >= InBuf2[0].weight ) { 	
							Add( outBuf, InBuf1, count1 ) ;	
							InBuf1.erase( InBuf1.begin() ) ;
							f1size1-- ;		
						} // else if
						
						// �ɮ�1.2��Ū�� 1<2
						else if ( InBuf1[0].weight < InBuf2[0].weight ) {
							Add( outBuf, InBuf2, count2 ) ;			
							InBuf2.erase( InBuf2.begin() ) ;
							f2size2-- ;	
						} // else if
	
						
 						// ŪBUFFER/4�� 
						if ( count1 == BUFFER / 4 ) { 
							if ( f1size1 > ( BUFFER / 4 ) ) InBuf1.resize( BUFFER / 4 ) ;
							else InBuf1.resize( f1size1 ) ; 		
							
							f1.read( (char*)&InBuf1[0] , sizeof(Info) * InBuf1.size() ) ;		
							count1 = 0 ;							
						} // if
						
						// ŪBUFFER/4�� 
						else if ( count2 == BUFFER / 4 ) { 
							if ( f2size2 > ( BUFFER / 4 ) ) InBuf2.resize( BUFFER / 4 ) ;	
							else InBuf2.resize( f2size2 ) ;			
								
							f2.read( (char*)&InBuf2[0] , sizeof(Info) * InBuf2.size() ) ;
							count2 = 0 ;		
						} // if 
						
						// �g�JBUFFER/2�� 						
						if ( outBuf.size() == BUFFER / 2 || ( f1size1 == 0 && f2size2 == 0 ) ) {				
							outfile.write( (char*)&outBuf[0], sizeof(Info) * outBuf.size() ) ;
							outBuf.clear() ;	
						} // if										
					 } // while												 
				} // if 

							
				else { // �̫�@���ɮ׬��_���ɮ� 
					int count1 = 0 ; 
					f1.read( (char*)&InBuf1[0] , sizeof(Info) * InBuf1.size() ) ;						
					while ( f1size1 != 0 ) {
						Add( outBuf, InBuf1, count1 ) ;	
						InBuf1.erase( InBuf1.begin() ) ;
						f1size1-- ;	
						
						if ( count1 == BUFFER / 4 ) {
							if ( f1size1 > ( BUFFER / 4 ) ) InBuf1.resize( BUFFER / 4 ) ;						
							else InBuf1.resize( f1size1 ) ; 
												
							f1.read( (char*)&InBuf1[0] , sizeof(Info) * InBuf1.size() ) ;
							count1 = 0 ;
						} // if
						if ( outBuf.size() == BUFFER / 2 || f1size1 == 0 ) {
							outfile.write( (char*)&outBuf[0], sizeof(Info) * outBuf.size() ) ;
							outBuf.clear() ;		
						} // if		
								
					} // while	
				} // else
					
				f1.close() ;
				f2.close() ;
				outfile.close() ;					
	
				remove(f1name.c_str());
				remove(f2name.c_str());
			} // for
			
		} // Merge()	
			
		void BuidBigFile( string & filenum ) {   
		
			double end, start ;
			start = clock() ;	
    		    		
			Read( filenum ) ;		 
			cout << endl << "The internal sort is completed. Check the initial sorted runs!" << endl ;
			
			// �X���ɮ� 
			while ( runs != 1 ) {
				total = 0 ;
				nextRuns = runs / 2 ;
				if ( runs % 2 != 0 ) nextRuns = nextRuns + 1 ;
					
				Merge() ;
				cout << endl << "Now there are " << nextRuns << " runs." << endl ;
				runs = nextRuns ;				
			} // while()

			// ��sorted0_0.bin���ɦW 			
			string str = "sorted" + filenum + ".bin" ;
			char oldname[] = "sorted0_0.bin" ;
    		char newname[] = "\0" ;			 		
    		for ( int i = 0 ; i < str.size() ; i++ ) newname[i] = str[i] ;   
    		rename( oldname, newname ) ;
    		remove( oldname ) ;
			
			end = clock() ;
			cout << "Total Execution Time = "<< ( end - start ) << "ms" << endl ; 			    		   		
		} // Buid()			
};


class BPlusTree {
	
	private:
		
		struct Data {
			float weight = 0.0 ;
			int offset = 0 ;
		};
		
		struct TreeNode {
			vector<Data> item ; 
			TreeNode * left ;	
			TreeNode * middle ;
			TreeNode * right ;
			TreeNode * temp ;
			TreeNode * next ;		
		};
		
		typedef TreeNode * TreePtr ;				
		TreePtr headPtr = NULL ;
		Data item ; 
	 	
	public:
		void Read( string & filenum ) {									    
			headPtr = NULL ;			
			int size, offset = 0 ;
			
		    fstream bin ;
 			string binname = "sorted" + filenum + ".bin" ;
        	bin.open( binname.c_str(), ios:: in | ios_base:: binary ) ;

			// �p���ɮפj�p 			
       		bin.seekg( 0, bin.end ) ;
       		int len = bin.tellg() / sizeof( Info ) ;
       		bin.seekg( 0, bin.beg ) ;
       		
			// �`�@���h�֪��w���� 
			if ( len % BUFFER == 0 ) size = len / BUFFER ;
			else size = len / BUFFER + 1 ;
			
			vector<Info> data( BUFFER ) ; 
			
		   	    
			if ( bin.is_open() ) {
								   
			    for ( int i = 0 ; i < size ; i++ ) {  		    
					// �����w�İϪŶ� �n�ק�size�j�p 
	           		if ( (i+1) == size && size % BUFFER != 0 ) {
	           			data.resize( len % BUFFER ) ;
					} // if	
								    
	           		bin.read( (char*)&data[0] , sizeof(Info) * data.size() ) ;
	           		//cout << "data.size() " << data.size() << " size " << i << endl ;
	           		// ��B+Tree 
					for ( int j = 0 ; j < data.size() ; j++ ) {				
						if ( headPtr == NULL ) {
							item.weight = data[j].weight ;
							item.offset = offset ;
							AddNode( headPtr, item ) ;
						} // if
						else {							
							if ( item.weight != data[j].weight ) {
								item.weight = data[j].weight ;
								item.offset = offset ;
								BuildTree( headPtr, headPtr, item ) ;
							} // if
						} // else 
						
						offset++ ; // �bbin�ɪ�offset 
					} // for
					
			     } // for()
			    
			    bin.close() ;
				PrintOffset(headPtr) ;
			} // if		     
		} // Read()			

		void AddNode( TreePtr & ptr, Data d ) { // �s�W�`�I 
			ptr = new TreeNode ;	
			ptr->item.push_back( d ) ;
			ptr->middle = NULL ;
			ptr->right = NULL ;
			ptr->left = NULL ;
			ptr->temp = NULL ;
			ptr->next = NULL ;		
		} // AddNode()

		void Sort( vector<Data> & item ) {		
			if ( item.size() == 2 ) {
				if ( item[0].weight < item[1].weight ) { 
					swap( item[0], item[1] ) ;
				} // if			
			} // if
		
			if ( item.size() == 3 ) {
				for ( int i = 0 ; i < (item.size()-1) ; i++ ) {
					if ( item[i].weight < item[2].weight ) 
						swap( item[i], item[2] ) ;
				} // for								
			} // if					
		} // Sort()	
			
		void Spilt( TreePtr now, TreePtr & pre ) { // ���� 
					
			TreePtr leftPtr ;	
			AddNode( leftPtr, now->item[0] ) ; // �Х���Ptr							
				
			if ( pre == headPtr && now == headPtr ) { // �W�� �� headPtr 
				AddNode( pre, now->item[1] ) ; 
				pre->item[0].offset = -1 ; 	
				headPtr = pre ; 	
			} // if

			else {  // �W��  ���� headPtr 
				pre->item.push_back( now->item[1] ) ;
				pre->item[pre->item.size()-1].offset = -1 ;
				Sort( pre->item ) ;						
			} // else
			
			
			now->item.erase(now->item.begin()) ;
			// ���b�𸭸`�I �n�R���� 
			if ( now->left != NULL && now->middle != NULL && now->right != NULL ) now->item.erase(now->item.begin()) ;	
			
									
			// leftPtr�Mnow���k�s��
			leftPtr->next = now ;  
	
			// �s���W�U 			
			if ( pre->item.size() == 1 ) {
				pre->left = leftPtr ;
				pre->right = now ;	
			} // if
						
			else if ( pre->item.size() == 2 ) {
				if ( pre->left == now ) {
					pre->middle = now ;
					pre->left = leftPtr ;
				} // if
				
				else if ( pre->right == now ) {
					pre->middle = leftPtr ;
					// ���k�s�� 
					pre->left->next = leftPtr ;				
				} // else if			
			} // else if

			else if ( pre->item.size() == 3 ) {
				TreePtr temp1 = NULL , temp2 = NULL ;
				if ( pre->left == now ) {
					temp1 = pre->middle ;
					temp2 = pre->right ;
										
					pre->left = leftPtr ;
					pre->middle = now ;
					pre->right = temp1 ;
					pre->temp = temp2 ;
				} // if 
				
				else if ( pre->middle == now ) {
					temp1 = pre->left ;
					temp2 = pre->right ;
					
					pre->left = temp1 ;
					pre->middle = leftPtr ;
					pre->right = now ;
					pre->temp = temp2 ;	
					// ���k�s�� 
					pre->left->next = leftPtr ;									
				} // else if
				
				else if ( pre->right == now ) {
					temp1 = pre->left ;
					temp2 = pre->middle ;
					
					pre->left = temp1 ;
					pre->middle = temp2 ;
					pre->right = leftPtr ;
					pre->temp = now ;
					// ���k�s�� 
					pre->middle->next = leftPtr ; 											
				} // else if				
			} // else if

			// ���b�𸭸`�I 
			if ( now->left != NULL && now->right != NULL && now->middle != NULL && now->temp != NULL ) {
				leftPtr->left = now->left ;
				leftPtr->right = now->middle ;
				now->left = now->right ;
				now->right = now->temp ;
					
				now->middle = NULL ;
				now->temp = NULL ; 
			} // if
			
		} // Spilt
		
	
		void BuildTree( TreePtr now, TreePtr & pre, Data d ) {
				
			if ( now->left == NULL && now->right == NULL  && now->middle == NULL ) {
				now->item.push_back( d ) ;						
				if ( now->item.size() == 3 ) {
					Spilt( now, pre ) ;
				} //if
				
				return ;
			} // if
			
			else if( now->item.size() == 1 ) {
				if ( d.weight > now->item[0].weight ) {
					BuildTree( now->left, now, d ) ;	
				} // if	
				
				else if ( d.weight < now->item[0].weight ) {
					BuildTree( now->right, now, d ) ;									
				} // else if
											
			} // if
			
			else if ( now->item.size() == 2 ) {
				if ( d.weight > now->item[0].weight ) {
					BuildTree( now->left, now, d ) ;	
				} // if
							
				else if ( d.weight < now->item[0].weight &&  d.weight > now->item[1].weight ) {
					BuildTree( now->middle, now, d ) ;				
				} // else if
		
					
				else if ( d.weight < now->item[1].weight ) {
					BuildTree( now->right, now, d ) ;	
				} // else if 									
			} // else if


			if ( now->item.size() == 3 ) {
				Spilt( now, pre ) ;			
			} // if
				
			return ;
			
		} // BuildTree

		void PrintOffset( TreePtr walk ) {

			int i = 1 ; 
			while ( walk->left != NULL ) {
				walk = walk->left ;
			} // while	
			
			while ( walk != NULL ) {
				for ( int j = 0 ; j < walk->item.size() ; j++ ) {
					cout << "[" << i << "] (" << walk->item[j].weight << ", " << walk->item[j].offset << ")" << endl ;
					i++ ;
				} // for 
				 walk = walk->next ;
			} // for
			
		} // PrintOffset()
	
};


bool Check( string & filenum ) {
	fstream bin ;
    string binname = "pairs" + filenum + ".bin" ;
    bin.open( binname.c_str(), ios:: in | ios_base:: binary ) ; 
    
    while ( true ) {
		if ( bin.is_open() ) return true ;
		else if ( filenum.compare( "0" ) == 0 ) return false ;
		else {
	        cout << endl << binname << " does not exist !" << endl ;
	        cout << endl << "Input the file name: [0]Quit: " ;
	        cin >> filenum ;
	        binname = "pairs" + filenum + ".bin" ;
	        bin.open( binname.c_str(), ios:: in | ios_base:: binary ) ;		
		} // else 	
	} // while()

	bin.close() ;
	
	return true ;

} // Check()

void Preface() {
    cout << endl << "***********************************************" ;
    cout << endl << "On-machine Exercise 05                       *" ;
    cout << endl << "Mission 1: External Merge Sort on a Big File *" ;
    cout << endl << "Mission 2: Construction of Primary Index     *" ;
    cout << endl << "**********************************************" ;
    cout << endl << "########################################################" ;
    cout << endl << "Mission 1: External merge sort" ;
    cout << endl << "########################################################" ;
    cout << endl << "Input the file name: [0]Quit: " ;
    
} // Preface()

void Continue() {
	cout << endl ; 		
    system("pause") ;
    cout << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl ;
    cout << "Mission 2: Build the primary index" << endl ;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl ;	
} // Continue()


int main() {
    vector<Info> data ;
    string filenum, command  ;
	bool isEnd = false ;
    double start, end ;
	EXMS exns ;
	BPlusTree bPlusTree ; 
	
    while ( !isEnd ) {
    	Preface() ;
    	cin >> filenum ;
    	
        if ( Check( filenum ) ) {
        	exns.BuidBigFile( filenum ) ;  
        	Continue() ;
        	bPlusTree.Read( filenum ) ;
        	
        	
        	cout << endl << "[0]Quit or [Any other key]continue? " << endl ;
			cin >> command ;         	
		} // if
 		
		if ( command.compare( "0" ) == 0 || filenum.compare( "0" ) == 0 ) isEnd = true ;	
    } // while()
    
} // main()
