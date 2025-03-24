// 10927207_�Z�~��_��T�G�A 10927248_�s���w 
#include <iostream>
#include <vector> // vector 
#include <fstream> // Ū�� 
#include <cstdlib> // atoi
#include <cstring>

using namespace std ; 

struct Data {
	int no = 0 ; // �Ǹ� 
	string schoolNo = "" ; // �ǮեN�� 
	string schoolName = "" ; // �ǮզW�� 
	string deptNo = "" ; // ��t�N�X 
	string deptName = "" ; // ��t�W�� 
	string advancedStudy = "" ; // �鶡/�i�קO 
	string level = "" ; // ���ŧO 
	string student = "" ; // �ǥͼ� 
	string teacher = "" ; // �Юv�� 
	string graduate = "" ; // �W�~�ײ��~�ͤH�� 
	string country = "" ; // �����W�� 
	string system = "" ; // ��t�O 
};

struct schData {
	string schoolName =  "" ;
	vector<int> no ;
};
 
struct deptData {
	string deptName =  "" ;
	vector<int> no ;
};

bool sfile = true ; // no file or no data 
string command ;
vector<Data> tempList ;
string TurnToNumber( string temp ) { // �N����Ʀr�A�Ҧp "1,199" �ন 1199 
	string number = "" ;
	for ( int j = 0 ; j < temp.length() ; j++ ) 
		if ( temp[j] != '\"' &&  temp[j] != ',' )  
			number =  number + temp[j] ;	
	return number ;	
} // int TurnToNumber()

void ReadTxt() { // Ū��
	sfile = true ;
	tempList.clear() ;
	string num, name ;
	ifstream file ;
	cout << endl << "Input a file number ([0] Quit): " ;
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
    	Data oneData ;
		string line ;
 		getline( file, line ) ;
 		getline( file, line ) ;
 		getline( file, line ) ;
		while ( getline( file, oneData.schoolNo, '\t' ) ) {
			count++ ; // �p��Ǹ� 
			oneData.no = count ;  
			getline( file, oneData.schoolName, '\t' ) ;
			getline( file, oneData.deptNo, '\t' ) ;
			getline( file, oneData.deptName, '\t' ) ;
			getline( file, oneData.advancedStudy, '\t' ) ;			
			getline( file, oneData.level, '\t' ) ;
			getline( file, oneData.student, '\t' ) ;
			if ( oneData.student[0] == '\"' ) oneData.student = TurnToNumber( oneData.student ) ;
			
			getline( file, oneData.teacher, '\t' ) ;
			getline( file, oneData.graduate, '\t' ) ;
			getline( file, oneData.country, '\t' ) ;							
			getline( file, oneData.system, '\n') ;												  
			
			tempList.push_back(oneData) ; // oneData into tempList		
		} // while
		
		file.close() ; // �����ɮ� 
		if ( !tempList.size()) {
			cout << "### Get nothing from the file " << name << "!###" << endl ;
			cout << endl << "There is no data!" << endl ;
			sfile = false ;
		} // if		
		//Print_All_Data( tempList ) ;		
	} // if
} // ReadTxt()

void Print_All_Data( vector<Data> list ) { // �L��� 
	for ( int i = 0; i < list.size() ; i++ ) {
		cout << i+1 << ": [" << tempList[i].no << "] " << tempList[i].schoolName << "\t" << tempList[i].deptName << "\t" << tempList[i].advancedStudy << "\t" << tempList[i].level << "\t" << tempList[i].student << endl ;					
	} //for
} // Print_All_Data()

void PrintDatas( vector<int> noList, int count ) { // �L�X�d�߸�� 
	for( int i = 0 ; i < noList.size() ; i++ ) {
		cout << count+1 << ": [" << noList[i] << "] " << tempList[noList[i]-1].schoolName << "\t" << tempList[noList[i]-1].deptName << "\t" << tempList[noList[i]-1].advancedStudy << "\t" << tempList[noList[i]-1].level << "\t" << tempList[noList[i]-1].student << endl ;					
		count++ ;			
	} // for
} // PrintData()

void compare( string college, string department, vector<int> noCollege, vector<int> noDepart ) { // ��� �ǮզW�ٸ�� �P �t�ҦW�ٸ�� ���L�۵L�Ǹ� �æL�X 
	int count = 0 ;
	if ( department == "*" ) PrintDatas( noCollege, count ) ;
	else if ( college == "*" ) PrintDatas( noDepart, count ) ;	
	else {
		for ( int i = 0 ; i < noCollege.size() ; i++ ) {
			for ( int j = 0 ; j < noDepart.size() ; j++ ) {
				if ( noCollege[i] == noDepart[j] ) {
					cout << count+1 << ": [" << noCollege[i] << "] " << tempList[noCollege[i]-1].schoolName << "\t" << tempList[noCollege[i]-1].deptName << "\t" << tempList[noCollege[i]-1].advancedStudy << "\t" << tempList[noCollege[i]-1].level << "\t" << tempList[noCollege[i]-1].student << endl ;					
					count++ ;	
				} // if
			} // for	
		} // for
	} // else
} // compare()  


class TwoThreeTree {
	private:
		struct TreeNode {
			vector<schData> item ;
			TreeNode * left ;	
			TreeNode * middle ;
			TreeNode * right ;
			TreeNode * temp ;
		};
	
		typedef TreeNode * TreePtr ;	
	
	public:		
		TreePtr tempPtr = NULL ;					
		TreePtr headPtr = NULL ;
		float tempmiddle ; // ���X�T������ �j�p��󤤶�������  
		string afterDirection = "" ; // �P�_ now �`�I �O�q����/����/�k�� ���W�Ӫ� 
		bool inToTree = false ; // �s�����O�_�w�g�Q�[�J2-3��
			
		void BuildTree() {		
			clear( headPtr ) ; // �M�ž�ʾ� 
			headPtr = NULL ; 		
			float oneData ;
			TreePtr pre = NULL, now = NULL ;
			for ( int i = 0 ; i < tempList.size() ; i++ ) {
				oneData.no.push_back( tempList[i].no ) ;
				oneData.schoolName = tempList[i].schoolName ;
				if ( i == 0 ) AddNode( headPtr, oneData ) ; // first Data
				else {
					pre = headPtr ;
					now = headPtr ;
					recurAddNewElement( now, pre, oneData ) ;
					headPtr = pre ; // �]����ڦ��ɷ|�Q�ܰʡA�ҥH�ö��NheadPtr����(pre)��ڪ��a�� 
				} // else
				
				oneData.no.clear() ;
				tempmiddle.schoolName = "" ;
				tempmiddle.no.clear() ; 
			} // for	
			
			cout << "Tree height = " << countHeight( headPtr ) << endl ; // �L���� 
			PrintRoot( headPtr ) ; // �L�X��� 	
		} // BuildTree()
		
		void recurAddNewElement( TreePtr now, TreePtr & pre, schData oneData ) { // add new element in correct place 		
			if ( now->item.size() == 1 && oneData.schoolName == now->item[0].schoolName ) { // one element same name, add no
				now->item[0].no.push_back( oneData.no[0] ) ;	
				return ;				
			} // if					
			else if ( now->item.size() == 2 && ( oneData.schoolName == now->item[0].schoolName || oneData.schoolName == now->item[1].schoolName ) ) { 
				// two element same name, add no
				if ( oneData.schoolName == now->item[0].schoolName ) now->item[0].no.push_back( oneData.no[0] ) ;	
				if ( oneData.schoolName == now->item[1].schoolName ) now->item[1].no.push_back( oneData.no[0] ) ;
				return ;	
			} // if									
			else if ( now ->left == NULL && now->middle == NULL && now->right == NULL && now->temp == NULL ) {
				// two element different name, add new element	
				now->item.push_back( oneData ) ; 		
				if ( now->item.size() == 2 ) {
					if ( now->item[0].schoolName > now->item[1].schoolName ) swap( now->item[0], now->item[1] ) ;						
				} // if							
				else if ( now->item.size() == 3 ) { // three element different name, find middle element, and spilt			
					Findtempmiddle( now ) ; // �Ƨ� ���T������ �j�p��󤤶�������  
					Spilt( pre, now ) ;	// �����`�I		
				} // if
				
				return ;	
			} // if
				
			if ( now->item.size() == 1 ) { // one Node�� �u���@�Ӥ���, �٥��[�J�s�`�I 
				// �p�G�s�����p�� now�`�I������ �����U��		
				if ( oneData.schoolName < now->item[0].schoolName ) recurAddNewElement( now->left, now, oneData ) ; 
				// �p�G�s�����j�� now�`�I������ ���k�U��		
				else if ( oneData.schoolName > now->item[0].schoolName ) recurAddNewElement( now->right, now, oneData ) ; 						
			} // if			
			else if ( now->item.size() == 2 ) { // one Node�� ����Ӥ���, �٥��[�J�s�`�I 
				//�p�G�s�����Ҥp�� now�`�I������ �����U��
				if ( oneData.schoolName < now->item[0].schoolName ) recurAddNewElement( now->left, now, oneData ) ;	
				//�p�G�s�������� now�`�I���������� �����U��	
				else if ( oneData.schoolName > now->item[0].schoolName && oneData.schoolName < now->item[1].schoolName ) recurAddNewElement( now->middle, now, oneData ) ; // middle								
				// �p�G�s�����Ҥj�� now�`�I������ ���k�U��
				else if ( oneData.schoolName > now->item[1].schoolName ) recurAddNewElement( now->right, now, oneData ) ; // right				 				
			} // else if
			
			if ( tempmiddle.schoolName != "" ) { // tempmiddle������ơA�N����~�򩹤W���� 
				Findtempmiddle( now ) ; // �Ƨ� ���T������ �j�p��󤤶�������   
				Spilt( pre, now ) ;	// �����`�I	
			} // if			
		} // recurFindNode()

		void Findtempmiddle( TreePtr now ) { // �Ƨ� ���T������ �j�p��󤤶�������  	
		    // �@�}�l �s�[�J������(�αq�U�����`�I�W�Ӫ���������) �|�Q�s�b�{�b�`�I�Ҧ��������̧���	
			if ( now->item[2].schoolName < now->item[0].schoolName ) { // �s�[�J������ �Ҥp�� �`�I�����Ҧ�����  
				swap( now->item[0], now->item[2] ) ; // �N�쥻�̤p������ �� �s�[�J�������洫 
				afterDirection = "left" ; // �i�H���D now �O�q���U���W�Ӫ� 
			} // if		
			else if ( now->item[2].schoolName > now->item[1].schoolName ) {	// �s�[�J������ �Ҥj�� �`�I�����Ҧ�����  
				swap( now->item[1], now->item[2] ) ; // �N�쥻�̤j������ �� �s�[�J�������洫
				afterDirection = "right" ; // �i�H���D now �O�q�k�U���W�Ӫ�
			} // else if
			else afterDirection = "middle" ; // �i�H���D now �O�q���U���W�Ӫ�				

			tempmiddle = now->item[2] ; // �N�j�p�b���������� �s��  tempmiddle
			now->item.pop_back() ; // �R���̥��ݤ��� 
		} // Findtempmiddle()		

		void AddNode( TreePtr & ptr, schData oneData ) { // �s�W�`�I 
			ptr = new TreeNode ;	
			ptr->item.push_back( oneData ) ;
			ptr->right = NULL ;
			ptr->middle = NULL ;
			ptr->left = NULL ;
			ptr->temp = NULL ;			
		} // AddNode()

		void Spilt( TreePtr & pre, TreePtr now ) {
			// ���ɤT���������������� �w�Q�s�� tempmiddle �ҥH now���u����Ӥ���(���������bFindtempmiddle()�w�qnow�`�I���R��) 
			tempPtr = NULL ;
			TreePtr middlePtr = NULL ;	
			AddNode( tempPtr, now->item[1] ) ; // �s�W�`�I �`�I�������O [now�`�I�� ���j������] 
			now->item.pop_back() ;
													
			if ( now == headPtr && pre == headPtr ) { // �p�G�w�g�]���� 
				AddNode( middlePtr, tempmiddle ) ; // �N �s�W�`�I �`�I�������O [tempmiddle(�T��������������)]  
				middlePtr->left = now ;                          
				middlePtr->right = tempPtr ;                
				pre = middlePtr ; // �Npre���V���    
				tempmiddle.schoolName = "" ; // �����A���� 
			}  // if 
			else if ( pre->item.size() == 1 ) {	// �p�Gpre�`�I�� �u���@�Ӥ���
				// pre->left����now�N��Opre�����䪺�p�ġA�G�N tempPtr �s��  pre�� middle 
				if ( pre->left->item[0].schoolName == now->item[0].schoolName ) pre->middle = tempPtr ;
				else if ( pre->right->item[0].schoolName == now->item[0].schoolName ) {		
					// pre->left����now�N��Opre���k�䪺�p�ġA�ݥ��N now �s�� pre�� middle 	
					// �M�� tempPtr �s�� pre�� right
					pre->middle = now ;					
					pre->right = tempPtr ;																	
				} // else if
				
				pre->item.push_back( tempmiddle ) ; // �Nnow���j�p������������  �[�J�� pre�� 
				if ( pre->item[0].schoolName > pre->item[1].schoolName ) swap( pre->item[0] , pre->item[1] ) ; // �Ƨ� 
				tempmiddle.schoolName = "" ; // �����A���� 
			} // if			
			else if ( pre->item.size() == 2 ) {	// �p�Gpre�`�I�� ����Ӥ���				
				pre->temp = tempPtr ; // �����N tempPtr ���b pre ��  temp �� 
				pre->item.push_back( tempmiddle ) ;	// �Nnow���j�p������������  �[�J�� pre�� 	
			} // else if	
			
			
			if ( now->left != NULL && now->right != NULL && now->middle != NULL && now->temp != NULL ) { // Spilt not leaf			
				if ( afterDirection == "left" ) { // now�O�ѥ��U���W�� �N���e�w�g�����L�@�����`�I��� ���U 
					// ���Nnow�� middle�Bright ���t�� tempPtr              
					tempPtr->left = now->middle ;                	
					tempPtr->right = now->right ;          
					now->right = now->temp ;               
				} // if
				if ( afterDirection == "middle" ) { // now�O�Ѥ��U���W�� �N���e�w�g�����L�@�����`�I��� ���U 
					// ���Nnow�� temp�Bright ���t�� tempPtr   
					tempPtr->left = now->temp ;
					tempPtr->right = now->right ;	
					now->right = now->middle ;												
				} // if
				if ( afterDirection == "right" ) { // now�O�ѥk�U���W�� �N���e�w�g�����L�@�����`�I��� �k�U 
					// ���Nnow�� right�Btemp ���t�� tempPtr  
					tempPtr->left = now->right ;
					tempPtr->right = now->temp ;	
					now->right = now->middle ;				 
				} // if		
				
				// �]�� now �����L��u�|�ѤU�A���k��Ӥp�ġA�ҥH���N�ѤU���`�I�]NULL 
				now->temp = NULL ;
				now->middle = NULL ;	
			} // if
		} // Spilt()
	
		int countHeight( TreePtr walk ) { // ��X�� 
			 if( walk == NULL ) return 0;
		     else return max(countHeight(walk->left),countHeight(walk->right)) + 1;
		} // countHeight()
		
		void PrintRoot( TreePtr walk ) { // �L�X��� 
			int count = 1 ;
			if ( headPtr->item.size() == 1 ) // �p�G�`�I���u���@�Ӥ����A�N�����L 
				for ( int i = 0 ; i < headPtr->item[0].no.size() ; i++, count++ ) 
					cout << count << ": [" << headPtr->item[0].no[i] << "] " << tempList[headPtr->item[0].no[i]-1].schoolName << "\t" << tempList[headPtr->item[0].no[i]-1].deptName << "\t" << tempList[headPtr->item[0].no[i]-1].advancedStudy << "\t" << tempList[headPtr->item[0].no[i]-1].level << "\t" << tempList[headPtr->item[0].no[i]-1].student << endl ;
					
			else if ( headPtr->item.size() == 2 ) { // �Y����Ӥ����A���P�_�֪��Ǹ��b�e�����L 
				if ( headPtr->item[0].no[0] < headPtr->item[1].no[0] ) { // �j�p���p�������Ǹ��b�e�A���L���p����-->�b�L�j�� 
					for ( int i = 0 ; i < headPtr->item[0].no.size() ; i++, count++ ) 
						cout << count << ": [" << headPtr->item[0].no[i] << "] " << tempList[headPtr->item[0].no[i]-1].schoolName << "\t" << tempList[headPtr->item[0].no[i]-1].deptName << "\t" << tempList[headPtr->item[0].no[i]-1].advancedStudy << "\t" << tempList[headPtr->item[0].no[i]-1].level << "\t" << tempList[headPtr->item[0].no[i]-1].student << endl ;
					for ( int i = 0 ; i < headPtr->item[1].no.size() ; i++ ) 
						cout << count << ": [" << headPtr->item[1].no[i] << "] " << tempList[headPtr->item[1].no[i]-1].schoolName << "\t" << tempList[headPtr->item[1].no[i]-1].deptName << "\t" << tempList[headPtr->item[1].no[i]-1].advancedStudy << "\t" << tempList[headPtr->item[1].no[i]-1].level << "\t" << tempList[headPtr->item[1].no[i]-1].student << endl ;			
				} // if
				
				else if ( headPtr->item[0].no[0] > headPtr->item[1].no[0] ) { // �M�W���ۤ� 
					for ( int i = 0 ; i < headPtr->item[1].no.size() ; i++, count++ ) 
						cout << count << ": [" << headPtr->item[1].no[i] << "] " << tempList[headPtr->item[1].no[i]-1].schoolName << "\t" << tempList[headPtr->item[1].no[i]-1].deptName << "\t" << tempList[headPtr->item[1].no[i]-1].advancedStudy << "\t" << tempList[headPtr->item[1].no[i]-1].level << "\t" << tempList[headPtr->item[1].no[i]-1].student << endl ;			
					for ( int i = 0 ; i < headPtr->item[0].no.size() ; i++, count++ ) 
						cout << count << ": [" << headPtr->item[0].no[i] << "] " << tempList[headPtr->item[0].no[i]-1].schoolName << "\t" << tempList[headPtr->item[0].no[i]-1].deptName << "\t" << tempList[headPtr->item[0].no[i]-1].advancedStudy << "\t" << tempList[headPtr->item[0].no[i]-1].level << "\t" << tempList[headPtr->item[0].no[i]-1].student << endl ;		
				} // else if
			} // else if 
		} // PrintRoot()
			
		void clear( TreePtr & walk ) { // �R����ʾ� 
			if ( walk == NULL ) return ;
			
			clear( walk->left ) ;
			clear( walk->middle ) ;
			clear( walk->right ) ;
			delete walk ;
		} // clear()		
		
		void search( string schoolname, vector<int> & noCollege, TreePtr walk ) {
			if ( walk == NULL ) return ;
			else if ( walk != NULL ) {
		 		for ( int j = 0 ; j < walk->item.size() ; j++ ) {	 			
					if ( walk->item[j].schoolName == schoolname ) {
						for ( int i = 0 ; i < walk->item[j].no.size() ; i++ ) noCollege.push_back( walk->item[j].no[i] ) ;						
						return ;	 
					} // if
				} // for
			} // if
			
			if ( schoolname < walk->item[0].schoolName ) search( schoolname, noCollege, walk->left ) ;
			else if ( walk->item.size() == 2 && schoolname > walk->item[0].schoolName && schoolname < walk->item[1].schoolName  ) search( schoolname, noCollege, walk->middle ) ;
			else if ( walk->item.size() == 2 && schoolname > walk->item[1].schoolName ) search( schoolname, noCollege, walk->right ) ;		
			else if ( schoolname > walk->item[0].schoolName ) search( schoolname, noCollege, walk->right ) ;
		} // search()		
};


class AVLTree {
	private:
		struct TreeNode {
			deptData item ;
			TreeNode * left ;
			TreeNode * right ;
		};
		
		typedef TreeNode * Ptr ;	
				
	public:
		Ptr headPtr = NULL ;
		bool sameDeptName = false ;
		
		void BuildAVL() {
			clear( headPtr ) ; // �M�ž�ʾ�   
			headPtr = NULL ;			
			deptData oneData ;
			Ptr after = NULL ;
			for ( int i = 0 ; i < tempList.size() ; i++ ) {
				oneData.no.push_back( tempList[i].no ) ;
				oneData.deptName = tempList[i].deptName ;
				if ( i == 0 ) headPtr = AddNode( oneData ) ; // first Data
				else {
					after = headPtr ;
					RecurAddNewElement( headPtr, after, oneData ) ;	
				} // else
				
				oneData.no.clear() ;
				sameDeptName = false ;
			} // for


			cout << "Tree height = " << countHeight( headPtr ) << endl ; // �L�� 
			PrintRoot( headPtr ) ; // �L���				
		} // BuildAVL()
		
		void RecurAddNewElement( Ptr & now, Ptr & after, deptData oneData ) {	
			if ( now == NULL ) { // now��NULL �s�W�`�I 
				now = AddNode( oneData ) ;
				after = now ;
				return ;
			} // if
			
			if ( oneData.deptName == now->item.deptName ) { // �s���� ���� �`�I���� add, no 
				now->item.no.push_back( oneData.no[0] ) ;	
				sameDeptName = true ;
				return ;
			} // if					
			else if ( oneData.deptName < now->item.deptName ) { // �s���� �p�� �`�I���� add, no 
				RecurAddNewElement( now->left, after, oneData ) ; // �������j 
				if ( now->left == NULL ) now->left = after ;  
			} // else if			
			else if ( oneData.deptName > now->item.deptName ) {
				RecurAddNewElement( now->right, after, oneData ) ; // ���k���j			
				if ( now->right == NULL ) now->right = after ;
			} // else if

			if ( sameDeptName == false ) RotationToBalance( now, after ) ; // �B�zAVL�𤣥���			
		} // recurAddNewElement()

		void RotationToBalance( Ptr & now, Ptr & after ) { // �B�zAVL�𤣥��� 
			int nowHighGap = countHeight( now->left ) - countHeight( now->right ) ;	// ��X�{�b�`�I�����k�𰪮t		
			if ( nowHighGap == 2 || nowHighGap == -2 ) { // ������ 
				int afterHighGap = countHeight( after->left ) - countHeight( after->right ) ; // ��Xafter�`�I�����k�𰪮t				
				if ( nowHighGap == 2 && ( afterHighGap == 1 || afterHighGap == 0 ) ) // ++ LL 
					now = rotateLL( now ) ;				
				else if ( nowHighGap == -2 && ( afterHighGap == -1 || afterHighGap == 0 ) ) // -- RR 
					now = rotateRR( now ) ;								
				else if ( nowHighGap == 2 && afterHighGap == -1 ) // +- LR 
					now = rotateLR( now ) ; 			
				else if ( nowHighGap == -2 && afterHighGap == 1 )  // -+ RL 
					now = rotateRL( now ) ; 
			} // if
			
			after = now ;					
		} // RotationToBalance()

		Ptr rotateLL( Ptr x ) {  
			Ptr y = x->left ;
			x->left = y->right ; 
			y->right = x ;
			return y ;
		} // AVLTree::rotateLL()	
			
		Ptr rotateRR( Ptr x ) {
			Ptr y = x->right ;
			x->right = y->left ; 
			y->left = x ;
			return y ;
		} // AVLTree::rotateRR()

		Ptr rotateLR( Ptr x ) {
			x->left = rotateRR( x->left ) ;
			return rotateLL( x ) ;
		} // AVLTree::rotateRR()		

		Ptr rotateRL( Ptr x ) {
			x->right = rotateLL( x->right ) ;
			return rotateRR( x ) ;
		} // AVLTree::rotateRR()
		
		Ptr AddNode( deptData oneData ) {
			Ptr tempPtr = new TreeNode ; 
			tempPtr->item = oneData ;
			tempPtr->left = NULL ;
			tempPtr->right = NULL ;
			return tempPtr ;
		} // AddNode()
		
		int countHeight( Ptr walk ) {
			if ( walk == NULL ) return 0;
    	 	else return max(countHeight(walk->left),countHeight(walk->right)) + 1 ;			
		} // countHeight()
		
		void PrintRoot( Ptr walk ) {
			for ( int i = 0 ; i < headPtr->item.no.size() ; i++ ) 
				cout << i+1 << ": [" << headPtr->item.no[i] << "] " << tempList[headPtr->item.no[i]-1].schoolName << "\t" << tempList[headPtr->item.no[i]-1].deptName << "\t" << tempList[headPtr->item.no[i]-1].advancedStudy << "\t" << tempList[headPtr->item.no[i]-1].level << "\t" << tempList[headPtr->item.no[i]-1].student << endl ;
		} // PrintRoot()					

		void clear( Ptr & walk ) {
			if ( walk == NULL ) return ;
			
			clear( walk->left ) ;
			clear( walk->right ) ;
			delete walk ;
		} // clear()
		
		void search( string deptname, vector<int> & noDepart, Ptr walk ) {	
			if ( walk == NULL ) return ;
			else if ( walk != NULL ) {
			 	if ( walk->item.deptName == deptname ) {
					for ( int i = 0 ; i < walk->item.no.size() ; i++ ) noDepart.push_back( walk->item.no[i] ) ;  								
					return ;	 
				} // if			 
			} // if
			
			if ( deptname < walk->item.deptName ) search( deptname, noDepart, walk->left ) ;
			else if ( deptname > walk->item.deptName ) search( deptname, noDepart, walk->right ) ;	
		} // search()
};


int main() {
	TwoThreeTree twoThreeTree ;
	AVLTree avlTree ;
	while ( true ) {
		cout << endl << "****** Search Tree Utilities ******" ;
		cout << endl << "* 0. QUIT                         *" ;
		cout << endl << "* 1. Build Two-Three Tree         *" ;
		cout << endl << "* 2. Build AVL Tree               *" ;	
		cout << endl << "* 3. Intersection Query           *" ;
		cout << endl << "***********************************" ;
		cout << endl << "Input a choice(0, 1, 2, 3): " ;
		cin >> command ;

		
		if ( command.compare("1") == 0 ) {
			ReadTxt() ; 
			if ( command.compare("1") == 0 && sfile == true ) twoThreeTree.BuildTree() ; // �إ�2-3�� 		
		} // if
		
		else if ( command.compare("2") == 0 ) {
			if ( twoThreeTree.headPtr == NULL || sfile != true ) cout << "\n### Choose 1 first. ###\n" ;
			else avlTree.BuildAVL() ; // �إ�AVL�� 				
		} // if
		
		else if ( command.compare("3") == 0 ) {
				if ( twoThreeTree.headPtr == NULL || avlTree.headPtr == NULL || sfile != true ) cout << "\n### Choose 1 and 2 first. ###\n" ;
				else {	
					vector<int> noCollege, noDepart ; // �ǮզW�ٸ�� �P �t�ҦW�ٸ��
					string college, department ;
					cout << "Enter a college name to search [*]: " ;
					cin >> college ;
					cout << "Enter a department name to search [*]: " ;
					cin >> department ;
					cout << endl ;	
		
					if ( college == "*" && department == "*" ) Print_All_Data( tempList ) ;
					else {
						if ( department != "*" ) avlTree.search( department, noDepart, avlTree.headPtr ) ;										
						if ( college != "*" ) twoThreeTree.search( college, noCollege, twoThreeTree.headPtr ) ;  
						compare( college, department, noCollege, noDepart ) ;												
					} // else	
					
					noCollege.clear() ;
					noDepart.clear() ;	
				} // else
		} // else if
		
		else if ( command.compare("0") == 0 ) return 0 ;
		
		else cout << endl << "Command does not exist!" << endl ;
	} // while 	
} // main()




