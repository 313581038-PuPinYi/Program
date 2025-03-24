// �Z�~�� 10927207   �d��� 10927234 
// �p�G�L�k���� �Цb�W�� �I�u��>�sĶ���ﶵ>�sĶ���]�w>�{���X����>�y���з�>��ISO C++ 11 
#include <iostream>
#include <vector> // vector 
#include <fstream> // Ū�� 
#include <time.h> // �p��ɶ� 
#include <conio.h> // �����N���~�� 
#include <sstream> // istringstream stream�Ψ� 
#include <iomanip> // �ϥΤp���I���� 
using namespace std ;
 

static bool sfile = true ; // �O�_���ɮ�  
static string num = "" ; // �ɦW �Ʀr���� 
static int command = 0 ;

struct Person { 	
	int oid = 0 ; // �u�@�s�� 
	int arrival = 0 ; // �i�J�ɨ� 
	int duration = 0 ; // �u�@�Ӯ� 
	int timeOut = 0 ; // �O�ɮɨ�  
};	 

struct Done { // �����M�� 
	int cid = 0 ; // CPU�s�� 
	int oid = 0 ; // �u�@�s�� 
	int departure = 0 ; // �����ɶ� 
	int delay = 0 ;  // ����ɶ�
};

struct Abort { // �����M�� 
	int cid = 0 ; // CPU�s�� 
	int oid = 0 ; // �u�@�s�� 
	int abort = 0 ; // �����ɨ�
	int delay = 0 ;  // ����ɶ�
}; 

class Queue {
	private:
		struct QueueNode {
			Person item ;
			QueueNode * next ; // ���U�@�� 
		};	 
		
		QueueNode * backPtr = NULL ; // ��C	
	public:		
		bool IsEmpty() ; // ��C���� 
		bool IsFull() ; // ��C���� 
		void Enqueue( Person newitem ) ; // ��ݷs�W vector<Person> data
		void Dequeue( Person & newitem ) ; // �e���^���R�� 
		int Size() ; // ����� 
};

struct Cpu {
	int curtime = 0 ; // CPU�{�b�ɶ� 
	int cid = 0 ; // CPU�s��	
	Person temp ; // CPU����Ϭq 
	Queue que ; // ��C 
};

class Sort {				
	public:	
		// Mission1 
		vector<string> header ; // ���ئW�� old�Aarrival�Aduration�A timeOut
		vector<Person> data ; // ��ơAŪ�J��s�� 
		Person persNew ; // struct Person���O �W�� 	
		double readT = 0 , sortT = 0 , writeT = 0 ; // Ū�ɡA�ƧǡA�g�ɮɶ� 
		void ReadTxt() ; // Ū�� 
		void ShellSort() ; // �ƺ��Ƨ� 
		void Writefile() ; // �g�� 	
		void Printdata() ; // �L�X��� 		
		void Printtime() ; // �L�X�ɶ� 
		
		// Mission2 
		vector<Done> donelist ; // �����M�� 
		Done done ;
		vector<Abort> abortlist ; // �����M�� 
		Abort abort ; 		
		void Add_done( Person & temp, int & curtime, int cid  ) ; // �s�W�ܧ����M�� 
		void Add_abort( Person & temp, int curtime, int error, int cid  ) ; // �s�W�ܨ����M�� 
		void RunQue( Queue & que, Person & temp , int & curtime, int error, int cid ) ; // �iCPU���� 
		void OnlyOneCpuDone( Cpu & cpu, int & i, int error ) ;
		void WritefileOutput() ; // �g��
		void WritefileOutput3() ; // �g��3 
		void Que() ; // ��C����
		void Que3() ; // ��C����3 
		void ChooseCpu( Cpu & cpu1, Cpu & cpu2, int & i ) ;
		void DataArrivalOrNot( Cpu & cpu, int error, int i );
		void PopQueToCpu( Cpu & cpu, int error );	
		bool Compare( Queue que1, Queue que2 ) ;
		int BoolChooseCpu( Queue que1, Queue que2 );	
};  

int main() {
	Sort sort ;
	
	while ( true ) {
	
		cout << endl << "**** Simulate FIFO Queues by SQF *****" ;
		cout << endl << "* 0. Quit                            *" ;
		cout << endl << "* 1. Sort a file                     *" ;
		cout << endl << "* 2. Simulate one FIFO queue         *" ;
		cout << endl << "* 3. Simulate two queues by SQF      *" ;		
		cout << endl << "**************************************" ;
		cout << endl << "Input a command(0, 1, 2, 3): " ;
		cin >> command ;
		sfile = true ; 
		
		if ( command == 1 ) {
			sort.ReadTxt() ; // Ū�� 
			if ( sfile == true ) {
				sort.Printdata() ; // �L�X��� (�L�Ƨ�)				
				sort.ShellSort() ; // �ƺ��Ƨ�
				sort.Writefile() ; // �g�� 
				system("pause"); // �Ы����N���~�� . . .
				sort.Printtime() ; // �L�X�ɶ� 
				cout << "See sorted" << num << ".txt" << endl;	
			} // if			
		} // if
		
		else if ( command == 2 ) {
			sort.ReadTxt() ; // Ū�� 
			if ( sfile == true ) {
				sort.Que() ; // ��C����
				sort.donelist.clear() ;
				sort.abortlist.clear() ;
			} // if	
			num = "" ;		     
		} // eise if
		
		else if ( command == 3 ) {
			sort.ReadTxt() ; // Ū�� 
			if ( sfile == true ) {
				sort.Que3() ; // ��C����
				sort.donelist.clear() ;
				sort.abortlist.clear() ;
			} // if	
			num = "" ;		     
		} // eise if		
		
				
		else if ( command == 0 ) return 0;
		
		else cout << endl << "Command does not exist!" << endl ;
		
		if ( command == 1 || command == 2 || command == 3 ) {
			sort.header.clear() ; // ����O����Ŷ� 
			sort.data.clear() ; // ����O����Ŷ�
		} // if
	} // while 
} // main()

// Ū�� 
void Sort::ReadTxt() {
	double start, end ;
	if ( num == "" || command == 1 ) {
		cout << "Input a file number (e.g., 401, 402, 403, ...): " ;
		cin >> num ;
		cout << endl ;			
	} // if	
						
	string name ;
	if ( command == 1 ) name = "input" + num + ".txt" ; 
	if ( command == 2 || command == 3 ) name = "sorted" + num + ".txt" ; 
	ifstream file ;
	file.open(name, ios_base::in) ; // ��󥴶} 

    if (!file.is_open()) {
        cout << "### " << name << " does not exist! ###\n" ;
        num = "" ;
        sfile = false ;
    } // if
	
    else {
    	start = clock() ;
    	int temp, count ;
    	string line ;
    	
    	getline( file, line ) ;
    	header.push_back(line) ; // Ū�J���ئW
    	
    	while( getline( file, line ) ) { // Ū�J��� 
    		istringstream stream(line) ;
    		count = 0 ;
    		while( stream >> temp ) {
    			if ( count == 0 ) persNew.oid = temp ;
    			else if ( count == 1 ) persNew.arrival = temp ;
    			else if ( count == 2 ) persNew.duration = temp ;
    			else if ( count == 3 ) persNew.timeOut = temp ;
    			count++ ;
			} // while
			
			data.push_back(persNew) ; 
			stream.clear() ;
		} // while
				
		file.close() ; // ������� 	
			
		end = clock() ;
		readT = end - start ;
	} // else	
} // Sort::ReadTxt()

// �ƺ��Ƨ�
void Sort::ShellSort() { 
	double start = clock() ;
	Person temp ;
	for ( int h = data.size() / 2 ; h > 0 ; h = h / 2 ) { // h�N���j�� 
		for ( int unsorted = h ; unsorted < data.size() ; unsorted++ ) {  
			for ( int loc = unsorted ; ( loc >= h ) ; loc = loc - h ) { 
				if ( data[loc-h].arrival > data[loc].arrival ) 
					swap( data[loc-h], data[loc] ) ;
					
				else if ( data[loc-h].arrival == data[loc].arrival ) 
					if ( data[loc-h].oid > data[loc].oid )
						swap( data[loc-h], data[loc] ) ;
			} // for
		} // for
	} // for
	
	double end = clock() ;
	sortT = end - start ;		
} // Sort::ShellSort()

// �g�� 
void Sort::Writefile() { 
	double start = clock() ;
	ofstream newFile ; // Create a new file
	string name = "sorted" + num + ".txt" ;
    newFile.open(name, ios_base::out) ; // ��󥴶} 
  	for ( int i = 0 ; i < header.size() ; i++ )  // ���ئW
  		if ( i == 0 ) newFile << header[i] ;
 		else newFile << '\t' << header[i] ;
			
	newFile << endl ;
   	for ( int i = 0 ; i < data.size() ; i++ )   
  	    newFile << data[i].oid << '\t' << data[i].arrival << '\t' << data[i].duration << '\t' << data[i].timeOut << endl;

	double end = clock() ;
	writeT = end - start ;    
} // Sort::Writefile()

void Sort::Printdata() { // �L�X��� 		
    for ( int i = 0 ; i < header.size() ; i++ ) { // ���ئW
    	cout << '\t' << header[i] ;
	} // for
	cout << endl ;
		
	for ( int i = 0 ; i < data.size() ; i++ ) // ���  
		cout << "(" << i+1 << ")" << '\t' << data[i].oid << '\t' << data[i].arrival << '\t' << data[i].duration << '\t' << data[i].timeOut << endl;	
} // Sort::Printdata()

void Sort::Printtime() { // �L�X�ɶ� 
	cout << endl ;
	cout << "Reading data:\t" << readT << " clocks(" << readT << ".00 ms).\n" ;
	cout << "Sorting data:\t" << sortT << " clocks(" << sortT << ".00 ms).\n" ;
	cout << "Writing data:\t" << writeT << " clocks(" << writeT << ".00 ms).\n" ;	
} // Sort::Printtime() 

// ��C����3
void Sort::Que3() {
	
	int i = 0, error = 0 ;
	Cpu cpu1, cpu2 ;
	cpu1.cid = 1;
	cpu2.cid = 2;
	
	while ( i < data.size() ) { 
		error = 0 ;
		if ( data[i].arrival >= cpu1.curtime && data[i].arrival >= cpu2.curtime ) { // ��F�ɶ��j�󵥩�{�b�ɶ�  ����C 
			if ( cpu1.que.IsEmpty() ) { // que1 size = 0 -> 1
				DataArrivalOrNot( cpu2, error, i );
				ChooseCpu( cpu1, cpu2, i ) ;	
			} // if
			else if ( cpu2.que.IsEmpty() ) { // que2 size = 0 -> 2
				DataArrivalOrNot( cpu1, error, i );
				ChooseCpu( cpu1, cpu2, i ) ;
			} // else if
			else { // ��C�Ҧ��F�� 
				while ( (!cpu1.que.IsEmpty() && data[i].arrival >= cpu1.curtime) || (!cpu2.que.IsEmpty() && data[i].arrival >= cpu2.curtime) ) {
 					if ( (cpu1.curtime <= cpu2.curtime && !cpu1.que.IsEmpty()) || cpu2.que.IsEmpty() ) PopQueToCpu( cpu1, error );
					else if ( (cpu1.curtime > cpu2.curtime && !cpu1.que.IsEmpty()) || cpu1.que.IsEmpty() ) PopQueToCpu( cpu2, error );
				} // while
			} // else
		} // if
		
		else if ( data[i].arrival < cpu1.curtime && data[i].arrival >= cpu2.curtime ) OnlyOneCpuDone( cpu2, i, error ) ;
		
		else if ( data[i].arrival < cpu2.curtime && data[i].arrival >= cpu1.curtime ) OnlyOneCpuDone( cpu1, i, error ) ;
		
		else { // ��F�F�ɶ��Ҥp��{�b�ɶ� 
			if ( !cpu1.que.IsFull() && !cpu2.que.IsFull() ) {
				if ( Compare( cpu1.que, cpu2.que ) ) cpu1.que.Enqueue( data[i] );
				else cpu2.que.Enqueue( data[i] );
			} // else if
			else if ( !cpu1.que.IsFull() ) cpu1.que.Enqueue( data[i] );
			else if ( !cpu2.que.IsFull() ) cpu2.que.Enqueue( data[i] );
			else if ( cpu1.que.IsFull() && cpu2.que.IsFull() ) Add_abort( data[i], cpu1.curtime, 1, 0 ) ; // �s�W�ܨ����M�� 
			
			i++;
		} // else
		
	} // while
	
	// ���ѤU��C 
	while ( !cpu1.que.IsEmpty() || !cpu2.que.IsEmpty() ) { // que1 || que2 size=1~3 
	
		if ( !cpu1.que.IsEmpty() && !cpu2.que.IsEmpty() ) { // que1 && que2 size=1~3 
			if( cpu1.curtime <= cpu2.curtime ) PopQueToCpu( cpu1, error ); // �{�b�ɶ�:1<=2 -> 1 
			else PopQueToCpu( cpu2, error );	// �{�b�ɶ�:1>2 -> 2			
		} // if
		else if( !cpu1.que.IsEmpty() ) PopQueToCpu( cpu1, error ); // que1 size=1~3
		else if( !cpu2.que.IsEmpty() ) PopQueToCpu( cpu2, error ); // que2 size=1~3 
		
	} // while
	
	cout << "The simulation is running..." << endl;
	WritefileOutput3() ; 
	cout << "See double" << num << ".txt" << endl;
	
} // Sort::Que()

// ��C����
void Sort::Que() {
	int i = 0 ;
	int error = 0 ;
	Cpu cpu ;
	
	while ( i < data.size() ) { 
		error = 0 ;
		if ( data[i].arrival < cpu.curtime ) { // ��F�ɶ��p��{�b�ɶ� 
			if ( !cpu.que.IsFull() ) // ��C����  
				cpu.que.Enqueue( data[i] ) ;
				
			else { // ���~4.1�i�J��C�ɵo�{��C�w�� 
				error = 1 ;
				Add_abort( data[i], cpu.curtime, error, 1 ) ; // �s�W�ܨ����M�� 
			} // else 
			
			i++;
		} // if
		
		else { // ��F�ɶ��j��ε���{�b�ɶ� ������C 
			if ( !cpu.que.IsEmpty() ) { // ��C���� 
				cpu.que.Dequeue( cpu.temp ) ;
				if ( data[i].arrival == cpu.curtime ) { // �p�G ��F�ɶ�=�{�b�ɶ� 
					cpu.que.Enqueue( data[i] ) ;
					i++ ;
				} // if 			
				
				RunQue( cpu.que, cpu.temp , cpu.curtime, error, 1 ) ; // �iCPU���� 
			} // if
			else { // ��C�w�� 
				cpu.curtime = data[i].arrival ;
				Add_done( data[i], cpu.curtime, 1 ) ; // �s�W�ܧ����M�� 
				i++ ;
			} // else 
		} // else 	
	} // while
	
	while ( !cpu.que.IsEmpty() ) {
		cpu.que.Dequeue( cpu.temp ) ;
		RunQue( cpu.que, cpu.temp , cpu.curtime, error, 1 ) ;
	} // if	
	
	cout << "The simulation is running..." << endl;
	WritefileOutput() ; 
	cout << "See output" << num << ".txt" << endl;
} // Sort::Que()

// �s�W�ܧ����M�� 
void Sort::Add_done( Person & temp, int & curtime, int cid ) {
	done.cid = cid ;
	done.oid = temp.oid;
	done.departure = curtime + temp.duration ;
	done.delay = curtime - temp.arrival ;
	donelist.push_back( done ) ;
	curtime = done.departure ;
} // Sort::Add_done()

// �s�W�ܨ����M�� 
void Sort::Add_abort( Person & temp, int curtime, int error, int cid ) {
	abort.cid = cid ;
	abort.oid = temp.oid ;
	if ( error == 1 ) {
		abort.abort = temp.arrival ;
		abort.delay = 0 ;
	} // if
	
	else if ( error == 2 ) {
		abort.abort = curtime ;
		abort.delay = abort.abort - temp.arrival ;	
	} // else if
	
	else if ( error == 3 ) {
		abort.abort = temp.timeOut ;
		abort.delay = abort.abort - temp.arrival ;			
	} // else if 
		
	abortlist.push_back( abort ) ;
} // Sort::Add_abort()

// �iCPU���� 
void Sort::RunQue( Queue & que, Person & temp , int & curtime, int error, int cid  ) { // ����C 

	if ( curtime >= temp.timeOut ) { // �{�b�ɶ��j�󵥩�O�ɮɶ��A4.2�i�JCPU�ɤw�O�� 
		error = 2 ;
		Add_abort( temp, curtime, error, cid ) ;	// �s�W�ܨ����M�� 	
	} // if
		 
	else { // �{�b�ɶ��p��O�ɮɶ��A�S�w�O�� 
		if ( curtime + temp.duration > temp.timeOut ) { // 4.3�i�JCPU���椤�o�͹O�� 
			error = 3 ;
			Add_abort( temp, curtime, error, cid ) ; // �s�W�ܨ����M�� 
			curtime = temp.timeOut ;					
		} // if 
				
		else { // �S�O�ɡA�����M�� 
			Add_done( temp, curtime, cid ) ; // �s�W�ܧ����M�� 
		} // else
	} // else
} // Sort::RunQue() 

void Sort::OnlyOneCpuDone( Cpu & cpu, int & i, int error ) {
	if ( !cpu.que.IsEmpty() ) DataArrivalOrNot( cpu, error, i );
	else {
		cpu.curtime = data[i].arrival;
		Add_done( data[i], cpu.curtime, 2 ) ;
		i++;
	} // else 
} // Sort::OnlyOneCpuDone()
 
// ���CPU 
int Sort::BoolChooseCpu( Queue que1, Queue que2 ) {
	if ( que1.IsEmpty() ) return 1;
	else if ( que2.IsEmpty() ) return 2;
	else if ( !que1.IsFull() && !que2.IsFull() ) {
		if ( Compare( que1, que2 ) ) return 1;
		else return 2;
	} // else if
	else if ( !que1.IsFull() ) return 1;
	else if ( !que2.IsFull() ) return 2;
	else if ( que1.IsFull() && que2.IsFull() ) return 0; // �s�W�ܨ����M�� 
} // Sort::BoolChooseCpu()
  
void Sort::DataArrivalOrNot( Cpu & cpu, int error, int i ) {
	while ( !cpu.que.IsEmpty() && data[i].arrival >= cpu.curtime ) {
		cpu.que.Dequeue( cpu.temp ) ;
		RunQue( cpu.que, cpu.temp , cpu.curtime, error, cpu.cid ) ;
	} // while
} // Sort::DataArrivalOrNot()
  
// �g��
void Sort::WritefileOutput() {
	
	double total = 0.0 ; 
	double averageDelay = 0.0, successRate = 0.0 ; 
	ofstream newFile ; // Create a new file
	string name = "output" + num + ".txt" ;
    newFile.open(name, ios_base::out) ; // ��󥴶}
	 
	newFile << '\t' << "[Abort Jobs]" << endl ;
	newFile << '\t' << "OID" << '\t' << "Abort" << '\t' << "Delay" << endl ;
   	for ( int k = 0 ; k < abortlist.size() ; k++ ) {
   		total = total + abortlist[k].delay;
  	    newFile << "[" << k+1 << "]" << '\t' << abortlist[k].oid << '\t' << abortlist[k].abort << '\t' << abortlist[k].delay << endl;
  	}
  	    
  	newFile << '\t' << "[Jobs Done]" << endl ;
  	newFile << '\t' << "OID" << '\t' << "Departure" << '\t' << "Delay" << endl ;
	for ( int k = 0 ; k < donelist.size() ; k++ ) {
		total = total + donelist[k].delay;
		newFile << "[" << k+1 << "]" << '\t' << donelist[k].oid << '\t' << donelist[k].departure << '\t' << donelist[k].delay << endl;
	}
		
	averageDelay = total/(double)data.size() ;
	successRate = 100 * (double)donelist.size()/(double)data.size() ;
	newFile << "[Average Delay]" << '\t' << setprecision(2) << fixed << averageDelay <<  "ms" << endl ;
	newFile << "[Success Rate ]" << '\t' << setprecision(2) << fixed << successRate << "%" << endl ;
	
	newFile.close()	;
} // Sort::WritefileOutput()

// �g��3 
void Sort::WritefileOutput3() {
	
	double total = 0.0 ; 
	double averageDelay = 0.0, successRate = 0.0 ; 
	ofstream newFile ; // Create a new file
	string name = "double" + num + ".txt" ;
    newFile.open(name, ios_base::out) ; // ��󥴶}
	 
	newFile << '\t' << "[Abort Jobs]" << endl ;
	newFile << '\t' << "OID" << '\t' << "CID" << '\t' << "Abort" << '\t' << "Delay" << endl ;
   	for ( int k = 0 ; k < abortlist.size() ; k++ ) {
   		total = total + abortlist[k].delay;
  	    newFile << "[" << k+1 << "]" << '\t' << abortlist[k].oid << '\t' << abortlist[k].cid << '\t' << abortlist[k].abort << '\t' << abortlist[k].delay << endl;
  	}
  	    
  	newFile << '\t' << "[Jobs Done]" << endl ;
  	newFile << '\t' << "OID" << '\t' << "CID" << '\t' << "Departure" << '\t' << "Delay" << endl ;
	for ( int k = 0 ; k < donelist.size() ; k++ ) {
		total = total + donelist[k].delay;
		newFile << "[" << k+1 << "]" << '\t' << donelist[k].oid << '\t' << donelist[k].cid << '\t' << donelist[k].departure << '\t' << donelist[k].delay << endl;
	}
		
	averageDelay = total/(double)data.size() ;
	successRate = 100 * (double)donelist.size()/(double)data.size() ;
	newFile << "[Average Delay]" << '\t' << setprecision(2) << fixed << averageDelay <<  "ms" << endl ;
	newFile << "[Success Rate ]" << '\t' << setprecision(2) << fixed << successRate << "%" << endl ;
	
	newFile.close()	;
} // Sort::WritefileOutput3()

void Sort::ChooseCpu( Cpu & cpu1, Cpu & cpu2, int & i ) {
	if ( BoolChooseCpu( cpu1.que, cpu2.que ) == 1 ) {
		cpu1.curtime = data[i].arrival;
		Add_done( data[i], cpu1.curtime, 1 ) ; // �s�W�ܧ����M��  
	}
	else if ( BoolChooseCpu( cpu1.que, cpu2.que ) == 2 ) {
		cpu2.curtime = data[i].arrival;
		Add_done( data[i], cpu2.curtime, 2 ) ; // �s�W�ܧ����M��  
	}
	else ;
				
	i++;
} // Sort::ChooseCpu()

bool Sort::Compare( Queue que1, Queue que2 ) {
	if ( que1.Size() > que2.Size() ) return false ;
	return true ;	
} // Sort::Compare()

void Sort::PopQueToCpu( Cpu & cpu, int error ) {
	cpu.que.Dequeue( cpu.temp ) ;
	RunQue( cpu.que, cpu.temp , cpu.curtime, error, cpu.cid ) ;
} // Sort::PopQueToCpu()



int Queue::Size() {
	int i = 0;
	if ( IsEmpty() ) return i;
	else {
		i = 1 ;
		QueueNode * walk = backPtr->next ;
		if ( walk == backPtr ) return i;
		while ( walk != backPtr ) { 
			i++ ;
			walk = walk->next ;
		} // while	
		return i ;	
	} // else 
} // Queue::Size()

// ��C���� 
bool Queue::IsEmpty() {
	if ( backPtr == NULL ) return true ;
	return false ;
} // Queue::IsEmpty()

// ��C����
bool Queue::IsFull() {
	if ( IsEmpty() ) return false ;
	else {
		int i = 1 ;
		QueueNode * walk = backPtr->next ;
		while ( walk != backPtr ) { 
			i++ ;
			walk = walk->next ;
		} // while	
		if ( i == 3 ) return true ; // �񺡤T�� 
		return false ;	
	} // else
} // Queue::IsFull()

// ��ݷs�W 
void Queue::Enqueue( Person newitem ) { 
	QueueNode * newPtr = new QueueNode ;
	newPtr->item = newitem ;
	if (IsEmpty())
		newPtr->next = newPtr ;
	else { 
		newPtr->next = backPtr->next ;
		backPtr->next = newPtr ;
	} // else 
	
	backPtr = newPtr ;
	newPtr = NULL;
	delete newPtr;
} // Queue::Enqueue

// �e���^���R�� 
void Queue::Dequeue( Person & newitem ) { 

	if(IsEmpty()) 
		return ;
	else {
		QueueNode * tempPtr = backPtr->next ;		
		newitem = tempPtr->item ;
		if ( backPtr == backPtr->next )	backPtr = NULL ;
		else backPtr->next = tempPtr->next ;
		
		tempPtr->next = NULL;
		delete tempPtr ;	
	} // else
	
} // Queue::Dequeue

