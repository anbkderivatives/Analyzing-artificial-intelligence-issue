////////////////////////////////////		UNIFORM-COST SEARCH ( U C S )		//////////////////////////////////////////////////////
//		Σε αυτόν τον αλγόριθμο ακολουθούνται περιγραφικός οι εξής ενέργειες:
//  -Τοποθετείται σε μια ουρά η αρχική κατάσταση του προβλήματος (ριζικός κόμβος)
//	-Κάθε κόμβος που τοποθεταίται στην ουρα εξετάζεται με την λογική της μεθόδου FIFO
//	-Επεκτείνονται οι κόμβοι που εξετάζονται (δηλ. τοποθετούνται στην ουρά) εφόσον οι κόμβοι αυτοί δεν είναι επαναλαμβανόμενοι
//	-Καθε φορά επεκτείνονται οι κόμβοι με το λιγότερο κόστος
//	-Όλοι οι κόμβοι που επεκτείνονται κρατούνται στην ουρά και απο την ουρά ελέγχεται έαν ένας τρέχοντος κόμβος ειναι επαναλαμβανόμενος
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

//Η υλοποίηση αυτής της ουράς γίνεται με την σκεπτική: 
//όταν καλείται η συνάρτηση insert για την εισαγωή ενός κόμβου, αυτός ο κόμβος πρέπει
//να τοποθετηθεί στην κατάλληλη θέση της ουράς όπου το κόστος του κόμβου αυτού να μην παραβαίνει
//την αύξουσα ροή των κοστών των κάθε κόμβων που βρίσκονται ήδη στην ουρά
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
		Oura *temp = new Oura();	//temp δείτης που δείχνει τον τρέχον κόμβο προς εισαγωγή
		temp->nodekomvos=komvos;
		temp->next=NULL;

		if(front==NULL) front=temp;
		else
		{
			Oura *trexwn = front; 
			Oura *trexwnNext=front->next;
			while(trexwn != NULL)	//παίρνουμε τους κατάλληλους ελέγχους για την τοποθέτηση κόμβου προς εισαγωγή στην ουρά 
			{
				if(temp->nodekomvos->Cost <= trexwn->nodekomvos->Cost && trexwn==front) //στην περίπτωση να εισαχθεί πρώτο
				{
					temp->next=trexwn;
					trexwn=temp;
					front=trexwn;
					break;
				}
				else if(trexwnNext == NULL)//στην περίπτωση να εισαχθεί τελευταίο
				{
					trexwn->next=temp;
					rear=temp;
					break;
				}
				else if(temp->nodekomvos->Cost <= trexwnNext->nodekomvos->Cost)//στην περίπτωση να εισαχθεί ενδιάμεσα
				{
					temp->next=trexwn->next;
					trexwn->next=temp;
					break;
				}
								
				trexwn=trexwn->next;
				if(trexwnNext != NULL) trexwnNext=trexwnNext->next;
			}			
		}
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

	Oura oura;		//αντικείμενο που θα δείχνει την ροή της ουράς
	Oura *first_oura;	//δείκτης που θα δείχνει πάντα στην αρχή της ουράς
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
		for(int i=0;i<n;i++) cost_array[i]=1+rand()%20;
	else
		for(int i=0;i<n;i++) 
			{cout<<"\nCost (minutes) for Person"<<i+1<<": \t"; cin>>cost_array[i];}

////////////////////////////	STARTS UNIFORM-COST SEARCH ( U C S )	////////////////////////////////

//  Για όλους τους καινούργιους κόμβους που δημιουργούνται θα παίρνουν ως όρισμα την αρχικοποίηση (n+1)
// για τον λόγο της χρησημοποίησης του φακού στην πρώτη θέση του πίνακα καταστάσεων
//----------------	Αρχικοποίηση του Ριζικού κόμβοβυ	----------------------------------------------
	Komvos *k;
	k=new Komvos((n+1));  //Δημιουργία καινούργιου κόμβου

	for(int i=0;i<k->sizeElem;i++)	//αρχικοποίηση της κατάστασης του ριζικού κόμβου με μηδενικά
	{
		k->Element[i]=0;		
	}
	oura.insert(k);		//εισαγωγή στην ουρά τον καινούργιο κόμβο
	first_oura=oura.front;	
//-----------------------------------------------------------------------------------------------------

	bool NodeCheck;
	bool foundsolution;
	Oura *tempfirst;

while(1)	//  Γνωρίζουμε ότι ο αλγόριθμος UCS είναι πλήρης (βρίσκει λύση) για αυτό το πρόβλημα, άρα δεν θα γίνεται 
{			// ατέρμων βρόγχος. Για αυτο βάζουμε while(1). θα μπορούσαμε να βάλουμε και while(oura.front->nodekomvos != NULL),
			// δηλ. αν δεν υπάρχουμ άλλοι επεκτανόμενοι κόμβοι στην ουρά
	PlithosKomvwn++;
//--------------	ΕΛΕΓΧΟΣ ΕΠΑΝΑΛΑΜΒΑΝΟΜΕΝΩΝ ΚΑΤΑΣΤΑΣΕΩΝ	---------------
		tempfirst=first_oura;
		NodeCheck=true;		//Υποθέτουμε αρχικά ότι μπορεί να γίνει ο έλεγχος του κόμβου. Στην συνέχεια επιβαιβεώνεται για αυτήν την έγκριση.
		while(tempfirst != oura.front)
		{
			int v; //δεικτης που χρησιμοποείται για να δούμε εάν είναι ίδιοι οι πίνακες καταστάσεων απο δύο κόμβους 
			for(v=0;v<oura.front->nodekomvos->sizeElem;v++)
				if(tempfirst->nodekomvos->Element[v] != oura.front->nodekomvos->Element[v]) break;

			if(v == oura.front->nodekomvos->sizeElem)
			{
				NodeCheck=false;
				//cout<<"======Vrika epanalipsi!!======\n";
				break;
			}	
			tempfirst=tempfirst->next;
		}
//----------------------------------------------------------------------

////--------------	ΕΞΕΤΑΣΗ ΤΟΥ ΤΡΕΧΟΝΤΑ ΚΟΜΒΟΥ	--------------------------------
	foundsolution=true; //Υποθέτουμε αρχικά ότι έχει βρεθεί λύση. Στην συνέχεια επιβαιβεώνεται για αυτό.
	if(NodeCheck==true)		
	{
		//-------Typwsi eksetazomenwn komvwn pou eksetazontai--------
		//for(int t=0;t<oura.front->nodekomvos->sizeElem;t++)
		//		cout<<oura.front->nodekomvos->Element[t];
		//	cout<<endl;

		for(int ch=0;ch<oura.front->nodekomvos->sizeElem;ch++) //σε περίπτωση που έχουμε έρθει στην Τελική κατάσταση
		{
			if(oura.front->nodekomvos->Element[ch]!=1)
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
//	-Εισάγουμε στην Ουρα τον αντίστοιχο κόμβο

	int fakos=oura.front->nodekomvos->Element[0]; //ο φακός ορίζεται στην 1η θέση του πίνακα κατάστασης 
	int sizeEl=oura.front->nodekomvos->sizeElem;

	for(int i=1;i<sizeEl;i++)	//ενέργειες για ένα άτομο
	{
		if(oura.front->nodekomvos->Element[i]==fakos)
		{
			k=new Komvos(sizeEl);
			for(int a=0;a<sizeEl;a++)	//αντιγραφή
				k->Element[a]=oura.front->nodekomvos->Element[a];

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

			k->Pateras = oura.front->nodekomvos;
			k->Cost = oura.front->nodekomvos->Cost + cost_array[i-1];
			k->Depth = oura.front->nodekomvos->Depth + 1;	

			oura.insert(k);

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
            if(oura.front->nodekomvos->Element[i]==fakos && oura.front->nodekomvos->Element[j]==fakos && i!=j)
            {
				k=new Komvos(sizeEl);
				for(int a=0;a<sizeEl;a++)
					k->Element[a]=oura.front->nodekomvos->Element[a];

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

				k->Pateras = oura.front->nodekomvos;
				if(cost_array[i-1]>cost_array[j-1]) k->Cost = oura.front->nodekomvos->Cost + cost_array[i-1];
				else k->Cost = oura.front->nodekomvos->Cost + cost_array[j-1];
				k->Depth = oura.front->nodekomvos->Depth + 1;

				oura.insert(k);

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

	oura.front=oura.front->next;
}//end while

int SynolikosXronosLysis=oura.front->nodekomvos->Cost;
int VathosLysis=oura.front->nodekomvos->Depth;
SolutionNodes solNodes; 

	while(oura.front->nodekomvos->Pateras != NULL)	//Αντιγραφή των κόμβων του μονοπατιού της λύσης σε μια Στοίβα ώστε να
	{												//εμφανίσουμε αργότερα τους κόμβους απο την αρχική στην τελική κατάσταση
		solNodes.addNode(oura.front->nodekomvos);
		oura.front->nodekomvos = oura.front->nodekomvos->Pateras;
	}
	solNodes.addNode(oura.front->nodekomvos); //όταν ο κόμβος του πατέρα oura.front->nodekomvos->Pateras γίνει NULL

	cout<<"\n\nMia lysi pou dinei o UCS einai:\n\n";
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
	cout<<"\nTo Plithos twn Komvwn opou episkefthike o UCS, einai :"<<PlithosKomvwn<<endl;
	cout<<"\nH Lysi vrethike se vathos :"<<VathosLysis<<endl<<endl;
	
//-------------------Typwsi Stoixeiwn Ouras--------------------------
/*	Oura *tempfirst2=first_oura;
	while(tempfirst2 != NULL)
	{
		for(int i=0;i<tempfirst2->nodekomvos->sizeElem;i++)
			cout<<tempfirst2->nodekomvos->Element[i];
		cout<<endl;
		tempfirst2=tempfirst2->next;
	}
*/

//------Typwsi Stoixeiwn Ouras mi-epanalamvanomenwn katastasewn-----
/*	Oura *tempfirst2;
	oura.front=first_oura;
	bool check;
	
	while(oura.front != NULL)
	{
		check=true;
		tempfirst2=first_oura;
		while(tempfirst2 != oura.front)
		{
			int v; //δεικτης που χρησιμοποείται για να δούμε αν είναι ίδιες οι πίνακες καταστάσεων δύο κόμβων 
			for(v=0;v<oura.front->nodekomvos->sizeElem;v++)
				if(tempfirst2->nodekomvos->Element[v] != oura.front->nodekomvos->Element[v]) break;

			if(v == oura.front->nodekomvos->sizeElem)
			{
				check=false;
				//cout<<"======Vrika epanalipsi======\n";
				break;
			}	
			tempfirst2=tempfirst2->next;
		}
		
		if(check==true)
		{
			for(int t=0;t<oura.front->nodekomvos->sizeElem;t++)
				cout<<oura.front->nodekomvos->Element[t];
			cout<<endl;				
		}
		oura.front=oura.front->next;
	}
*/
system("pause");
return 0;
}