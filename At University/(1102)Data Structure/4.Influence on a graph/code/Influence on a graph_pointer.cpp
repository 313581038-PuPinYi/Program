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

using namespace std ;

struct Info {
    char putID[10] ;       // �o�T��
    char getID[10] ;       // ���T��
    float weight ;
} ;

// ���ȤG�ΨӦs�v�T�O��C��

class Linklist {
	
	struct link { 
		int No ;
		link * next ;
	};
	
	link * head = NULL ;
	int size = 0 ;

	public :	
		void add( int a ) {
            link * walk = head, * pre = NULL ;
            if ( head == NULL ) {
                head = new link ;
                head->next = NULL ;
                head->No = a ;   
                size = 1 ;       
            } // if()

            else {
                while ( walk != NULL && walk->No <= a ) {
                    pre = walk ;
                    walk = walk->next ;
                } // while()

                link * t = new link ;
                t->No = a ;
                t->next = walk ;
                size ++ ;

                if ( walk == head ) {
                    head = t ;
                } // if()

                else {
                    pre->next = t ;
                } // else 
            } // else 
		} // add()
		
        int Size() {
            return size ;
        } // Size()

        bool exist( int a ) {
            link * walk = head ;

            while ( walk != NULL ) {

                if ( walk->No == a ) {
                    return true ;
                } // if()

                walk = walk->next ;

            } // while()

            return false ;
        } // exist()

        int get( int i ) {
            int len = 1 ;
            link * walk = head ;
            while ( len != i ) {
                len ++ ;
                walk = walk->next ;
            } // while()

            return walk->No ;
        } // get

};

class AdjList {

    struct node {
        char ID[10] ;
        float weight ;
        node * next ;
    } ; 

    struct item {
        char ID[10] ;           // �D�}�C�Ǹ�
        node * getList ;        // ���T��
    } ;

    struct pitem {
        char ID[10] ;
        Linklist pList ;
    } ;

    typedef node * Node ;
    typedef item * Item ;

    vector<item> list ;
    vector<pitem> bfsList ;
    vector<pitem> dfsList ;
    
    // ��o�ӾǸ��b�D�}�C���Ǹ�
    int FindIndex( char temp[10] ) {
        
        bool find = false ;
        int L = 0, R = list.size() - 1, M = ( L + R ) / 2 ;
        while ( L <= R && ! find ) {

            if ( strcmp( temp, list[M].ID ) == 0 ) {
                find = true ;
            } // if()
        
            else if ( strcmp( temp, list[M].ID ) > 0 ) {
                L = M + 1 ;
                M = ( L + R ) / 2 ; 
            } // else if()

            else {
                R = M - 1 ;
                M = ( L + R ) / 2 ;
            } // else
        } // while()

        if ( ! find ) {
            return -1 ;
        } // if()

        return M ;
    } // FindIndex()

    // check if the getID or PutID exist 
    // if Not exist then push in the list 
    int Exist( Info t ) {
   
        int index ;
        if ( FindIndex( t.getID ) == -1 ) {
            item temp1 ;
            temp1.getList = NULL ;
            strcpy( temp1.ID, t.getID ) ;
            SortList( temp1 ) ;  
        } // if()

        index = FindIndex( t.putID ) ;
        if ( index == -1 ) {
            item temp ;
            temp.getList = NULL ;
            strcpy( temp.ID, t.putID ) ;
            index = SortList( temp ) ;            
        } // if() 

        return index ;

    } // Exist()

    // �ƧǥD�}�C
    int SortList( item temp ) {

        int i = 0 ;
        while ( i < list.size() && strcmp( list[i].ID, temp.ID ) <= 0 ) {
            i ++ ;
        } // while()

        list.insert( list.begin() + i, temp ) ;
        return i ;
    } // SortList() 

    // Bfs or dfs�v�T�O�}�C�Ƨ�
    void SortpList( pitem temp, vector<pitem> & path ) {
    
        int i = 0 ;
        while ( i < path.size() && temp.pList.Size() <= path[i].pList.Size() ) {
            i ++ ;
        } // while()

        path.insert( path.begin() + i, temp ) ;
    } // SortpList()

    // ���Ȥ@�g��
    void Write( string filenum, int size ) {
    
        string temp = "pairs" + filenum + ".adj" ;
        fstream file( temp.c_str(), ios :: out ) ;

        file << "<<< There are " << list.size() << " IDs in total. >>>" << endl ; 

        for ( int i = 0 ; i < list.size() ; i ++ ) {
            int k = 1 ; 
            file << '[' << setw(3) << i + 1 << "] "  ;
            file << list[i].ID << ": " << endl ;
            Node walk = list[i].getList ;

            while ( walk != NULL ) {
                file << "\t(" << setw(2) << k << ") " << walk->ID << ',' << setw(6) << walk->weight ;

                if ( k % 10 == 0 ) {
                    file << endl ; 
                } // if()

                k ++ ;
                walk = walk->next ;
            } // while()
            
            file << endl ;
        } // for()

        file <<  "<<< There are " << size << " nodes in total. >>>" << endl ;
        file.close() ;

    } // Write()

    // ���Ȥ@ �[�J���T�̦�C
    void addGet( Node & head, Info temp ) { 
        Node walk = head, pre = NULL ;
        if ( head == NULL ) {
            head = new node ;
            head->next = NULL ;
            strcpy( head->ID, temp.getID ) ;
            head->weight = temp.weight ;                
        } // if()

        else {
            while ( walk != NULL && walk->weight >= temp.weight ) {
                pre = walk ;
                walk = walk->next ;
            } // while()

            Node t = new node ;
            strcpy( t->ID, temp.getID ) ;
            t->weight = temp.weight ;
            t->next = walk ;

            if ( walk == head ) {
                head = t ;
            } // if()

            else {
                pre->next = t ;
            } // else 
        } // else 
    } // Add()

    // ���ȤG���ȤT�g��
    void WritePath( string name, vector<pitem> path ) {
        fstream file( name.c_str(), ios :: out ) ;

        file << "<<< There are " << path.size() << " IDs in total. >>>" << endl ; 

        for ( int i = 0 ; i < path.size() ; i ++ ) {
            int k = 0, j ; 
            file << '[' << setw(3) << i + 1 << "] "  ;
            file << path[i].ID << '(' << path[i].pList.Size() << ')' << ": " << endl ;
            for ( int k = 1 ; k <= path[i].pList.Size() ; k ++ ) {
                j = path[i].pList.get( k ) ; 
                file << "\t(" << setw(2) << k << ") " << list[j].ID  ;

                if ( k % 10 == 0 ) {
                    file << endl ;
                } // if ()
            } // for()

            file << endl ;
        } // for()

        file.close() ;
    } // WritePath()

    int findpIndex( vector<pitem> path, char temp[10] ) {
        int index = 0 ;
        while ( strcmp( path[index].ID, temp ) != 0 ) {
            index ++ ;
        } // while()

        return index ;
    } // findpIndex()

    // ���b �p���ˬd
    bool Check( string temp ) {  
        int i = 0 ;
        bool test = false, oneDot = false ;
        while ( ! test ) {

            if ( temp[0] == '.' || temp[temp.size()-1] == '.' ) {
                // �Ĥ@�өM�̫�@�Ӥ��O�I
                return false ;
            } // else if()
            
            else if ( oneDot && temp[i] == '.' ) {
                // ������I
                return false ;
            } // else if()

            else if ( temp[i] == '.' ) {
                // �Ĥ@���I
                oneDot = true ;
            } // else if()

            else if ( temp[i] < '0' || temp[i] > '9' ) {
                // ���O�Ʀr
                return false ;
            } // else if()

            i ++ ;

            if ( i == temp.size() ) {
                return true ;
            } // if()

        } // while()

        return true ;
    } // Check()


    public :
        void Build( string filenum, vector<Info> data ) {
            int index ;
            for ( int i = 0 ; i < data.size() ; i ++ ) {
                // ���o�T�̪�index
                index = Exist( data[i] ) ;
                addGet( list[index].getList, data[i] ) ;
            } // for()

            Write( filenum, data.size() ) ;
            cout << endl << "<<< There are " << list.size() << " IDs in total. >>>" << endl ;
            cout << "<<< There are " << data.size() << " nodes in total. >>>" << endl ;

        } // Build()

        void BFS( string filenum ) {
            bfsList.clear() ;       // ��l�ư}�C
            int index ;
            double start, end ;

            start = clock() ;
            for ( int i = 0 ; i < list.size() ; i ++ ) {
                deque<int> q ;          // �s�D�}�C�Ǹ�, FIFO=>queue
                q.push_back( i ) ;
                pitem path ;
                strcpy( path.ID, list[i].ID ) ;
                bool infAll = false ;

                while ( ! q.empty() && ! infAll ) {
                    Node walk = list[q.front()].getList ;
                    q.pop_front() ;

                    while ( walk != NULL && ! infAll ) {  // 
                        // walk �٨S���� �B �٨S�v�T�Ҧ��H
                        index = FindIndex( walk->ID ) ;     // ��D�}�C�Ǹ�
                        
                        if ( index != i && ! path.pList.exist( index ) ) {
                            // �٨S�����L�B��list[i]���PID
                            // �̷ӾǸ��j�p��iplist
                            path.pList.add( index ) ;
                            if ( index < i ) {

                                int infIndex = findpIndex(bfsList, walk->ID) ;

                                for ( int j = 1 ; j <= bfsList[infIndex].pList.Size() ; j ++ ) {
                                    // �ˬd�Qindex�v�T���H���S���Q���L 
                                    // �S���Q���L�N��path
                                    int temp = bfsList[infIndex].pList.get( j ) ;
                                    if ( ! path.pList.exist( temp ) && temp != i ) {
                                        path.pList.add( temp ) ;
                                    } // if()

                                } // for()

                            } // if()

                            else {  
                                q.push_back( index ) ;
                            } // else 

                            if ( path.pList.Size() == list.size() - 1 ) {
                                // �v�T�Ҧ��H�F
                                infAll = true ;
                            } // if()
                        
                        } //if()

                        walk = walk->next ;

                    } // while()

                } // while() 
                
                // �̼v�T�O��ibfsList
                SortpList( path, bfsList ) ;                
            } // for ()
            
            end = clock() ;
            string name = "pairs" + filenum + ".cnt" ;
            WritePath( name, bfsList ) ;  
            cout << endl << "<<< There are " << list.size() << " IDs in total. >>>" << endl ;
            cout << "time:: " << end - start << endl ;
        } // BFS()

        void dfsBuild( string filenum ) {
            dfsList.clear() ;
            double start, end ;
            float weight ;
            string temp ;
            do {
                cout << "Input a weight : "  ;
                cin >> temp ;
                weight = atof( temp.c_str() ) ;
                if ( ! Check( temp ) ) {
                    weight = 2.0 ;
                } // if()
            } while( weight < 0.0 || weight > 1.0 ) ;

            start = clock() ;
            for ( int i = 0 ; i < list.size() ; i ++ ) {
                pitem path ;
                strcpy( path.ID, list[i].ID ) ;

                // ���j����DFS
                // DFS( path, list[i].getList, weight, i ) ;      
                
                // �j�骩 
                DFSLoop( path, i, weight ) ; 
                
                // �̷Ӽv�T�O�Ƨ�
                SortpList( path, dfsList ) ;             
            } // for()
            end = clock() ;

            WritePath( "pairs" + filenum + ".inf", dfsList ) ;
            end = clock() ;
            cout << endl << "<<< There are " << list.size() << " IDs in total. >>>" << endl ;
            cout << "time:: " << end - start << endl ;
        } // dfsBuild()

        // ���j����
        void DFS( pitem & path, Node vertex , float weight, int mainIndex ) {

            Node walk = vertex ;
            while ( walk != NULL && path.pList.Size() != list.size() - 1 ) {
                // �۾F�̦�C�٨S���� �B �٨S�v�T�Ҧ��H
                int index = FindIndex( walk->ID ) ;     // ��D�}�C�Ǹ�

                if ( walk->weight < weight ) {
                    // walk ���v���p�� input
                    // �^��W�@�h
                    return ;
                } // if()

                if ( strcmp( path.ID, walk->ID ) != 0 && ! path.pList.exist( index ) && walk->weight >= weight ) {
                    // �٨S�����L�B��path���PID
                    // �̷ӾǸ��j�p��iplist
                    path.pList.add( index ) ;

                    if ( index < mainIndex ) {

                        int infIndex = findpIndex(dfsList, walk->ID) ;

                        for ( int j = 1 ; j <= dfsList[infIndex].pList.Size() ; j ++ ) {
                            // �ˬd�Qindex�v�T���H���S���Q���L 
                            // �S���Q���L�N��path
                            int temp = dfsList[infIndex].pList.get( j ) ;
                            if ( ! path.pList.exist( temp ) && temp != mainIndex ) {
                                path.pList.add( temp ) ;
                            } // if()

                        } // for()

                    } // if()

                    else {
                        DFS( path, list[index].getList, weight, mainIndex ) ;
                    } // else 
                } // if()

                walk = walk->next ;
                if ( walk == NULL  ) {
                    // walk ����
                    // �^��W�@�h 
                    return ;
                } // if()
            } // while()

        } // DFS()

		// �j�骩DFS
		void DFSLoop( pitem & path, int mainIndex, float weight ) {
            
            deque<int> s ;  // dfs FILO
            s.push_back( mainIndex ) ;
            bool infAll = false ;

            while ( ! s.empty() && ! infAll ) {

                Node walk = list[s.back()].getList ;
                bool godepth = false ;
                while( walk != NULL && ! infAll && ! godepth ) {
                    // getlist�٨S���� �B�٨S�v�T�Ҧ��H �B �٨S���n���U�@�Ӳ`�ר� 

                    int index = FindIndex( walk->ID ) ;    

                    if ( walk->weight < weight ) {
                        // �]���v�����Ƨ�, �ҥH�u�n������v���p�����T��
                        // �N�i�Hpop��,�����ˬd
                        s.pop_back() ;
                        // ���L�^��e�@�ӧø��A�����o��while�j��
                        godepth = true ;
                    } // if()

                    else if ( index != mainIndex && ! path.pList.exist( index ) && walk->weight >= weight ) {
                        // �v�� �j�� input�n�D �B ���O�ۤv���� �]���s�b�b�v�T�O�M��
                        path.pList.add( index ) ; 

                        if ( index < mainIndex ) {

                            int infIndex = findpIndex(dfsList, walk->ID) ;

                            for ( int j = 1 ; j <= dfsList[infIndex].pList.Size() ; j ++ ) {
                                // �ˬd�Qindex�v�T���H���S���Q���L 
                                // �S���Q���L�N��path
                                int temp = dfsList[infIndex].pList.get( j ) ;
                                if ( ! path.pList.exist( temp ) && temp != mainIndex ) {
                                    path.pList.add( temp ) ;
                                } // if()

                            } // for()

                        } // if()  

                        else {                         
                            s.push_back( index ) ;    
                            godepth = true ;
                        } // else               
                    } // if ()
                    
                    if ( path.pList.Size() == list.size() - 1 ) {
                        // �v�T�Ҧ��H
                        infAll = true ;
                    } // if()

                    walk = walk->next ;

                } // while()

                if ( ! godepth && walk == NULL ) {
                    // ���T�̦�C�ˬd���F
                    s.pop_back() ;
                } // if()

            } // while()
            
		} // DFSLoop()
//*/
        void Initial() {
            list.clear() ;
        } // Initial()

} ;

bool Read( vector<Info> & data, string & filenum ) {

    fstream bin ;
    Info t ; 
    int len ;

    cout << endl << "Input a file number ([0] Quit): " ;
    cin >> filenum ;
    string binname = "pairs" + filenum + ".bin" ;
    bin.open( binname.c_str(), ios:: in | ios_base:: binary ) ;

    while( true ) {
        
        if ( bin.is_open() ) {
            // has binary file 
            // �p���`�@���h�ֵ����
            bin.seekg( 0, bin.end ) ;
            len = bin.tellg() / sizeof( t ) ;
            bin.seekg( 0, bin.beg ) ;
            for( int i = 0 ; i < len ; i ++ ) {
                bin.read( (char*)&t, sizeof(t) ) ;
                data.push_back( t ) ;
            } // for()

            return true ;
        } // if()

        else if ( filenum.compare( "0" ) == 0 ) {
            return false ;
        } // else if 

        else {
            cout << endl << "### The file does not exist ! ###" << endl ;
            cout << endl << "Input a file number ([0] Quit): " ;
            cin >> filenum ;
            binname = "pairs" + filenum + ".bin" ;
            bin.open( binname.c_str(), ios:: in | ios_base:: binary ) ;
        } // else

    } // while()

    bin.close() ;

    return true ;
} // Read()

void Preface() {
    cout << endl << "***** Influence on a graph  ****" ;
    cout << endl << "* 0. QUIT                      *" ;
    cout << endl << "* 1. Build adjacency lists     *" ;
    cout << endl << "* 2. Compute influence values  *" ;
    cout << endl << "* 3. Estimate influence values *" ;
    cout << endl << "********************************" ;
    cout << endl << "Input a choice(0, 1, 2, 3):" ;
} // Preface()

int main() {
    vector<Info> Data ;
    string filenum, command  ;
    AdjList adj ;
    double start, end ;

    Preface() ;
    cin >> command ;

    while ( command.compare( "0" ) != 0 ) {

        if ( command.compare( "1" ) == 0 ) {
            Data.clear() ;
            adj.Initial() ;
            if ( Read( Data, filenum ) ) {
                adj.Build( filenum, Data ) ;
            } // if()
        } // if()

        else if ( command.compare( "2" ) == 0 ) {
            if ( filenum.empty() ) {
                cout << "### Choose command 1 first ! ###" << endl ;
            } // if()
            
            else {
                adj.BFS( filenum ) ;
            } // else

        } // else if()

        else if ( command.compare( "3" ) == 0 ) {
            if ( filenum.empty() ) {
                cout << "### Choose command 1 first ! ###" << endl ;
            } // if()
            
            else {
                adj.dfsBuild( filenum ) ;
            } // else            
        } // else if()

        else {
            cout << endl << "Command does not exist!" << endl ;
        } // else 

        Preface() ;
        cin >> command ; 
    } // while()

    
} // main()
