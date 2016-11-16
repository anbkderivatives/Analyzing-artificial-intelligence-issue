////////////////////////////////////		DEPTH-FIRST SEARCH ( D F S )		//////////////////////////////////////////////////////
//		Σε αυτόν τον αλγόριθμο ακολουθούνται περιγραφικός οι εξής ενέργειες:
//  -Τοποθετείται σε μια στοίβα η αρχική κατάσταση του προβλήματος (ριζικός κόμβος)
//	-Κάθε κόμβος που τοποθεταίται στην στοίβα εξετάζεται με την λογική της μεθόδου LIFO
//	-Επεκτείνονται οι κόμβοι που εξετάζονται (δηλ. τοποθετούνται στην στοίβα) εφόσον οι κόμβοι αυτοί δεν είναι επαναλαμβανόμενοι
//	-Σε μια ουρά κρατούνται οι κόμβοι που έχουν επισκεφθεί. Η χρήση της ουράς διευκολίνει να ελεγχθεί εάν ένας κόμβος είναι επαναλαμβανόμενος
//	-Όλοι οι κόμβοι που επεκτείνονται κρατούνται στην στοίβα και απο την ουρά ελέγχεται έαν ένας τρέχοντος κόμβος είναι επαναλαμβανόμενος

#include <iostream>
#include <string>
#include <time.h>
using namespace std;

class Komvos
{
public:
	Komvos *Pateras;
	int *Element;		//Πίνακας κατάστασης του κόμβου, όπου δηλώνονται με 0 τα άτομα και ο φακός εάν είναι στην αρχική όχθη και 1 
						//εάν είναι στην όχθη προορισμού. Π.χ: Αρχική κατάσταση [0,0,0,0,...] και Τελική κατάσταση [1,1,1,1,...]
	int sizeElem;
	int Cost;
	int Depth;
	//Ενέργειες που εκτελούν τα άτομα
	int Persons[2]; //στην 1η και 2η θέση του πίνακα αυτου καταχωρούνται τα συγκεκριμένα άτομα ή άτομο που κάνει μια ενέργεια (Action)
	int Action; //εάν είναι 0 σημαίνει οτι ένας ή δύο άτομα πάνε απο την όχθη προορισμού στην αρχική όχθη ή βρίσκονται σε αυτήν (αρχική όχθη)
				//εάν είναι 1 σημαίνει οτι ένας ή δύο άτομα πάνε απο την αρχική όχθη στην όχθη προορισμού

	Komvos(int size)
	{
		sizeElem=size;
		Element=new int[size];
		Pateras=NULL;
		Cost=0;
		Depth=0;
		Action=0;
		Persons[0]=0;
		Persons[1]=0;
	}
};

//Κράτηση των επεκτανόμενων κόμβων εφόσον δεν είναι επαναλαμβανόμενοι
class Stoiva
{
public:
	Komvos *nodekomvos;
	Stoiva *head;
	Stoiva *next;

	Stoiva()
	{
		head=NULL;
		next=NULL;
	}
	void addNode(Komvos *komvos)
	{
		Stoiva *temp = new Stoiva();
		temp->nodekomvos = komvos;

		temp->next = head;
		head=temp;
	}
	void deleteNode()	//διαγράφει πάντα τον δείκτη που βρίσσκεται στην κορυφή, ο οποίος δείχνει σε κόμβο 
	{
		Stoiva *temp = new Stoiva();
		if(head != NULL)
		{
			temp=head;
			head=head->next;
			delete temp;
		}
	}
};

//Σε μια ουρά κρατούνται οι κόμβοι που έχουν επισκεφθεί. 
//Η χρήση της ουράς διευκολίνει να ελεγχθεί εάν ένας κόμβος είναι επαναλαμβανόμενος
class Oura
{
public:
	Komvos *nodekomvos;
	Oura  *front,*rear;
	Oura  *next;
	
	Oura()
	{
		next=NULL;
		front=NULL;
		rear=NULL;
	}
	void insert(Komvos *komvos)  
	{
		Oura *temp = new Oura();
		temp->nodekomvos=komvos;	//temp δείτης που δείχνει τον τρέχον κόμβο προς εισαγωγή
		temp->next=NULL;

		if(front==NULL){ front=temp;}
		else rear->next=temp;

		rear=temp;
	}
};

//κλάση στην οποία κρατάμε τους κόμβους της λύσης του προβλήματος
class SolutionNodes		//Υλοποίηση Στοίβας
{
public:
	Komvos *nodekomvos;
	SolutionNodes *head;
	SolutionNodes *next;

	SolutionNodes()
	{
		head=NULL;
		next=NULL;
	}
	void addNode(Komvos *komvos)
	{
		SolutionNodes *temp = new SolutionNodes();
		temp->nodekomvos = komvos;

		temp->next = head;
		head=temp;
	}
};

int main()
{
srand(time(NULL));

	Oura oura;	//αντικείμενο που θα δείχνει την ροή της ουράς
	Stoiva stoiva;	//αντικείμενο που θα δείχνει την ροή της στοίβας
	int n; //πλήθος ατόμων
	int *cost_array;	//πίνακας με τα κόστη των ατόμων
	int PlithosKomvwn=0;
	
	cout<<"Eisagete Atoma:\t";cin>>n;cout<<endl;

	cost_array=new int[n];

	int cost;
	char epilogi; 
	cout<<"Na ginei i symplirwsi tou pinaka cost_array automata?\n Gia nai -->'y'\tGia oxi -->otidipote\nEpilogi:\t";
	cin>>epilogi;
	if(epilogi == 'y')
		for(int i=0;i<n;i++) {cost_array[i]=1+rand()%20;}
	else
		for(int i=0;i<n;i++) 
			{cout<<"\nCost (minutes) for Person"<<i+1<<": \t"; cin>>cost_array[i];}


////////////////////////////	STARTS DEPTH-FIRST SEARCH ( D F S )	////////////////////////////////

//  Για όλους τους καινούργιους κόμβους που δημιουργούνται θα παίρνουν ως όρισμα την αρχικοποίηση (n+1)
// για τον λόγο της χρησημοποίησης του φακού στην πρώτη θέση του πίνακα καταστάσεων
//----------------	Αρχικοποίηση του Ριζικού κόμβοβυ	----------------------------------------------
	Komvos *k;
	k=new Komvos((n+1));  //Δημιουργία καινούργιου κόμβου

	for(int i=0;i<k->sizeElem;i++)	//αρχικοποίηση της κατάστασης του ριζικού κόμβου με μηδενικά
	{
		k->Element[i]=0;		
	}
	stoiva.addNode(k);	//εισαγωγή στην στοίβα τον καινούργιο κόμβο
	
//-----------------------------------------------------------------------------------------------------

	bool NodeCheck;
	bool foundsolution;
	Oura *tempfirst;

while(stoiva.head != NULL)	// Γνωρίζουμε ότι γενικό ο αλγόριθμος DFS δεν είναι πλήρης (μπορεί να μην βρίσκει λύση).
{							// Με τον έλεγχο της while(stoiva.head != NULL), αποτρεπόμαστε απο τον ατέρωω βρόγχο.
							// Στο ήδη υπάρχον πρόβλημα ο DFS βρίσκει πάντα λύση
	PlithosKomvwn++;
//--------------	ΕΛΕΓΧΟΣ ΕΠΑΝΑΛΑΜΒΑΝΟΜΕΝΩΝ ΚΑΤΑΣΤΑΣΕΩΝ	---------------
		tempfirst=oura.front;
		NodeCheck=true;		//Υποθέτουμε αρχικά ότι μπορεί να γίνει ο έλεγχος του κόμβου. Στην συνέχεια επιβεβαιώνεται για αυτήν την έγκριση.
		while(tempfirst != oura.rear)
		{
			int v; //δεικτης που χρησιμοποείται για να δούμε εάν είναι ίδιοι οι πίνακες καταστάσεων απο δύο κόμβους 
			for(v=0;v<tempfirst->nodekomvos->sizeElem;v++)
				if(tempfirst->nodekomvos->Element[v] != stoiva.head->nodekomvos->Element[v]) break;

			if(v == stoiva.head->nodekomvos->sizeElem)
			{
				NodeCheck=false;
				stoiva.deleteNode();	//διαγράφει τον δείκτη που δείχνει στον τρέχον κόμβο και κάνει τον δείκτη stoiva.head να δείξει τον προηγούμενο κόμβο
				//cout<<"======Vrika epanalipsi!!======\n";
				break;
			}	
			tempfirst=tempfirst->next;
		}
//----------------------------------------------------------------------
		
////--------------	ΕΞΕΤΑΣΗ ΤΟΥ ΤΡΕΧΟΝΤΑ ΚΟΜΒΟΥ	--------------------------------
	foundsolution=true; //Υποθέτουμε αρχικά ότι έχει βρεθεί λύση. Στην συνέχεια επιβεβαιώνεται για αυτό.
	if(NodeCheck==true)		
	{
		//Ektypwsi Kwmvwn pou eksetazontai----------------------------
		//for(int t=0;t<stoiva.head->nodekomvos->sizeElem;t++)
		//		cout<<stoiva.head->nodekomvos->Element[t];
		//	cout<<endl;

		oura.insert(stoiva.head->nodekomvos);
		for(int ch=0;ch<stoiva.head->nodekomvos->sizeElem;ch++) //σε περίπτωση που έχουμε έρθει στην Τελική κατάσταση
		{
			if(stoiva.head->nodekomvos->Element[ch]!=1)
			{ 
				foundsolution=false;
				break;
			}
		}
		if(foundsolution==true) break;
//----------------------------------------------------------------------
	
//--------------------    ΕΠΕΚΤΑΣΗ ΤΟΥ ΤΡΕΧΟΝΤΑ ΚΟΜΒΟΥ    -------------------------
// Στην επέκταση ακολουθείται τα εξής:	 
//	-Ανάλογα με την τιμή του φακού (δηλ. την τοποθεσία) αλλάζουμε τις τιμές (μεταφορά) των ατόμων.
//	 Η σκεπτική είναι οτι όπου έχει ίδια τιμή ο φακός με τα άτομα, αυτοί μπορούν να τον χρησημοποίησουν 
//	 και να δράσουν κατάλληλα. Έτσι θα έχουμε ενέργειες για ένα άτομο, όπου θα πηγαίνει ή θα έρχεται με τον φακό
//	 και ενέργειες για δύο άτομα , όπου αντίστοιχα θα πάνε και θα γυρίζουν μαζί με τον φακό.
//	-Αντιγράφουμε απο τον πατρικό κόμβο τον πίνακα καταστάσεων στον καινούργιο κόμβο προς επέκταση
//  -Περνάμε στον καινούργιο κόμβο τις κατάλληλες αρχικοποιήσεις και τιμές των πεδίων
//	-Εισάγουμε στην Στοίβσ τον αντίστοιχο κόμβο

	int fakos=stoiva.head->nodekomvos->Element[0]; //ο φακός ορίζεται στην 1η θέση του πίνακα κατάστασης 
	int sizeEl=stoiva.head->nodekomvos->sizeElem;
	Stoiva *temp_father=stoiva.head;

	for(int i=1;i<sizeEl;i++)	//ενέργειες για ένα άτομο
	{
		if(temp_father->nodekomvos->Element[i]==fakos)
		{
			k=new Komvos(sizeEl);
			for(int a=0;a<sizeEl;a++)	//αντιγραφή
				k->Element[a]=temp_father->nodekomvos->Element[a];

			if(fakos==0)
			{
				k->Element[0]=1;
				k->Element[i]=1;
				k->Action=1;	 //πηγαίνε στην απέναντι όχθη
				k->Persons[0]=i; //το άτομο i πηγαίνει στην απέναντι όχθη
				k->Persons[1]=0; //δεν θπάρχει άτομο να κάνει καμιά ενέργγεια
			}
			else if(fakos==1)
			{
				k->Element[0]=0;
				k->Element[i]=0;
				k->Action=0;	 //έλα στην αρχική όχθη
				k->Persons[0]=i; //το άτομο i έρχεται στην αρχική όχθη
				k->Persons[1]=0; //δεν θπάρχει άτομο να κάνει καμιά ενέργγεια
			}

			k->Pateras = temp_father->nodekomvos;
			k->Cost = temp_father->nodekomvos->Cost + cost_array[i-1];
			k->Depth = temp_father->nodekomvos->Depth + 1;	

			stoiva.addNode(k);

			//-----Εκτύπωση στοιχείων του κάθε κόμβου που επεκτείνεται------
			//cout<<"Stin 1 for\n";
			//for(int typ=0;typ<sizeEl;typ++)
			//	cout<<k->Element[typ];
			//cout<<endl;
		}
	}

	for(int i=1;i<sizeEl;i++) //ενέργειες για δύο άτομα
	{
		
        for(int j=1;j<sizeEl;j++)
        {
			
            if(temp_father->nodekomvos->Element[i]==fakos && temp_father->nodekomvos->Element[j]==fakos && i!=j)
            {
				
				k=new Komvos(sizeEl);
				for(int a=0;a<sizeEl;a++)
					k->Element[a]=temp_father->nodekomvos->Element[a];

				if(fakos==0)
				{
					k->Element[0]=1;
					k->Element[i]=1;
					k->Element[j]=1;
					k->Action=1;		//πηγαίνετε στην απέναντι όχθη
					k->Persons[0]=i;	//Τα άτομα i και j πηγαίνουν 
					k->Persons[1]=j;	//στην απέναντι όχθη.
				}
				else if(fakos==1)
				{
					k->Element[0]=0;
					k->Element[i]=0;
					k->Element[j]=0;
					k->Action=0;		//ελάτε στην αρχική όχθη
					k->Persons[0]=i;	//Τα άτομα i και j έρχονται
					k->Persons[1]=j;	//στην αρχική όχθη.
				}

				k->Pateras = temp_father->nodekomvos;
				if(cost_array[i-1]>cost_array[j-1]) k->Cost = temp_father->nodekomvos->Cost + cost_array[i-1];
				else k->Cost = temp_father->nodekomvos->Cost + cost_array[j-1];
				k->Depth = temp_father->nodekomvos->Depth + 1;

				stoiva.addNode(k);

				//-----Εκτύπωση στοιχείων του κάθε κόμβου που επεκτείνεται------
				//cout<<"Stin 2 for\n";
				//for(int typ=0;typ<sizeEl;typ++)
				//	cout<<k->Element[typ];
				//cout<<endl;
            }
		}
	}
//------------------	ΤΕΛΟΣ ΕΠΕΚΤΑΣΗΣ		---------------------------
	}//end if (NodeCheck)
	//stoiva.head=stoiva.head->next;
	
}//end while

if(stoiva.head == NULL) {cout<<"\nGia to provlima auto den vrethike lysi!\n"; system("pause");exit(0);}

int SynolikosXronosLysis=stoiva.head->nodekomvos->Cost;
int VathosLysis=stoiva.head->nodekomvos->Depth;
SolutionNodes solNodes; 

	while(stoiva.head->nodekomvos->Pateras != NULL)		//Αντιγραφή των κόμβων του μονοπατιού της λύσης σε μια καινούργια Στοίβα ώστε να
	{													//εμφανίσουμε αργότερα τους κόμβους απο την αρχική στην τελική κατάσταση
		solNodes.addNode(stoiva.head->nodekomvos);	
		stoiva.head->nodekomvos = stoiva.head->nodekomvos->Pateras;
	}
	solNodes.addNode(stoiva.head->nodekomvos); //όταν ο κόμβος του πατέρα stoiva.head->nodekomvos->Pateras γίνει NULL

	cout<<"\n\nMia lysi pou dinei o DFS einai:\n\n";
	cout<<"Oloi oi anthrwpoi einai stin arxiki oxthi (arxiki katastasi)\n";	//όλα μηδενικά

	solNodes.head = solNodes.head->next;	//επειδή ο ριζικός κόμβος δεν περιέχει καμιά ενέργεια προχωράμε στον επόμενο κόμβο

	//πραρακάτω ανάλογα με τις περιπτώσεις που φαίνονται παρουσιάζεται το μονοπάτι της λύσης περιγραφικός
	while(solNodes.head != NULL)
	{
		if(solNodes.head->nodekomvos->Action == 1)
		{
			if(solNodes.head->nodekomvos->Persons[1] == 0)
			{
				cout<<"To atomo "<<solNodes.head->nodekomvos->Persons[0]<<" perna tin gefyra se :";
				cout<<cost_array[solNodes.head->nodekomvos->Persons[0] - 1]<<" lepta."<<endl;
			}
			else
			{
				if(cost_array[solNodes.head->nodekomvos->Persons[0] - 1] > cost_array[solNodes.head->nodekomvos->Persons[1] - 1])
				{
					cout<<"Ta atoma "<<solNodes.head->nodekomvos->Persons[0]<<" kai "<<solNodes.head->nodekomvos->Persons[1];
					cout<<" pernane tin gefyra se :";
					cout<<cost_array[solNodes.head->nodekomvos->Persons[0] - 1]<<" lepta."<<endl;
				}
				else
				{
					cout<<"Ta atoma "<<solNodes.head->nodekomvos->Persons[0]<<" kai "<<solNodes.head->nodekomvos->Persons[1];
					cout<<" pernane tin gefyra se :";
					cout<<cost_array[solNodes.head->nodekomvos->Persons[1] - 1]<<" lepta."<<endl;
				}
			}
		}
		else if(solNodes.head->nodekomvos->Action == 0)
		{
			if(solNodes.head->nodekomvos->Persons[1] == 0)
			{
				cout<<"To atomo "<<solNodes.head->nodekomvos->Persons[0]<<" gyrizei se :";
				cout<<cost_array[solNodes.head->nodekomvos->Persons[0] - 1]<<" lepta."<<endl;
			}
			else
			{
				if(cost_array[solNodes.head->nodekomvos->Persons[0] - 1] > cost_array[solNodes.head->nodekomvos->Persons[1] - 1])
				{
					cout<<"Ta atoma "<<solNodes.head->nodekomvos->Persons[0]<<" kai "<<solNodes.head->nodekomvos->Persons[1];
					cout<<" gyrizoyn se :";
					cout<<cost_array[solNodes.head->nodekomvos->Persons[0] - 1]<<" lepta."<<endl;
				}
				else
				{
					cout<<"Ta atoma "<<solNodes.head->nodekomvos->Persons[0]<<" kai "<<solNodes.head->nodekomvos->Persons[1];
					cout<<" gyrizoyn tin gefyra se :";
					cout<<cost_array[solNodes.head->nodekomvos->Persons[1] - 1]<<" lepta."<<endl;
				}
			}
		}
		solNodes.head = solNodes.head->next;
	}

	cout<<"\nO Synolikos xronos, pou apaitithike gia tin lysi auti, einai : "<<SynolikosXronosLysis<<" lepta."<<endl;
	cout<<"\nTo Plithos twn Komvwn opou episkefthike o DFS, einai :"<<PlithosKomvwn<<endl;
	cout<<"\nH Lysi vrethike se vathos :"<<VathosLysis<<endl<<endl;

system("pause");
return 0;
}