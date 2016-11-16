////////////////////////////////////		DEPTH-FIRST SEARCH ( D F S )		//////////////////////////////////////////////////////
//		�� ����� ��� ��������� ������������� ������������ �� ���� ���������:
//  -������������ �� ��� ������ � ������ ��������� ��� ����������� (������� ������)
//	-���� ������ ��� ������������ ���� ������ ���������� �� ��� ������ ��� ������� LIFO
//	-������������� �� ������ ��� ����������� (���. ������������� ���� ������) ������ �� ������ ����� ��� ����� �����������������
//	-�� ��� ���� ���������� �� ������ ��� ����� ����������. � ����� ��� ����� ����������� �� �������� ��� ���� ������ ����� �����������������
//	-���� �� ������ ��� ������������� ���������� ���� ������ ��� ��� ��� ���� ��������� ��� ���� ��������� ������ ����� �����������������

#include <iostream>
#include <string>
#include <time.h>
using namespace std;

class Komvos
{
public:
	Komvos *Pateras;
	int *Element;		//������� ���������� ��� ������, ���� ���������� �� 0 �� ����� ��� � ����� ��� ����� ���� ������ ���� ��� 1 
						//��� ����� ���� ���� ����������. �.�: ������ ��������� [0,0,0,0,...] ��� ������ ��������� [1,1,1,1,...]
	int sizeElem;
	int Cost;
	int Depth;
	//��������� ��� �������� �� �����
	int Persons[2]; //���� 1� ��� 2� ���� ��� ������ ����� ������������� �� ������������ ����� � ����� ��� ����� ��� �������� (Action)
	int Action; //��� ����� 0 �������� ��� ���� � ��� ����� ���� ��� ��� ���� ���������� ���� ������ ���� � ���������� �� ����� (������ ����)
				//��� ����� 1 �������� ��� ���� � ��� ����� ���� ��� ��� ������ ���� ���� ���� ����������

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

//������� ��� ������������� ������ ������ ��� ����� �����������������
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
	void deleteNode()	//��������� ����� ��� ������ ��� ���������� ���� ������, � ������ ������� �� ����� 
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

//�� ��� ���� ���������� �� ������ ��� ����� ����������. 
//� ����� ��� ����� ����������� �� �������� ��� ���� ������ ����� �����������������
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
		temp->nodekomvos=komvos;	//temp ������ ��� ������� ��� ������ ����� ���� ��������
		temp->next=NULL;

		if(front==NULL){ front=temp;}
		else rear->next=temp;

		rear=temp;
	}
};

//����� ���� ����� ������� ���� ������� ��� ����� ��� �����������
class SolutionNodes		//��������� �������
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

	Oura oura;	//����������� ��� �� ������� ��� ��� ��� �����
	Stoiva stoiva;	//����������� ��� �� ������� ��� ��� ��� �������
	int n; //������ ������
	int *cost_array;	//������� �� �� ����� ��� ������
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

//  ��� ����� ���� ������������ ������� ��� �������������� �� �������� �� ������ ��� ������������ (n+1)
// ��� ��� ���� ��� �������������� ��� ����� ���� ����� ���� ��� ������ �����������
//----------------	������������ ��� ������� �������	----------------------------------------------
	Komvos *k;
	k=new Komvos((n+1));  //���������� ����������� ������

	for(int i=0;i<k->sizeElem;i++)	//������������ ��� ���������� ��� ������� ������ �� ��������
	{
		k->Element[i]=0;		
	}
	stoiva.addNode(k);	//�������� ���� ������ ��� ���������� �����
	
//-----------------------------------------------------------------------------------------------------

	bool NodeCheck;
	bool foundsolution;
	Oura *tempfirst;

while(stoiva.head != NULL)	// ���������� ��� ������ � ���������� DFS ��� ����� ������ (������ �� ��� ������� ����).
{							// �� ��� ������ ��� while(stoiva.head != NULL), ������������� ��� ��� ������ ������.
							// ��� ��� ������� �������� � DFS ������� ����� ����
	PlithosKomvwn++;
//--------------	������� ����������������� �����������	---------------
		tempfirst=oura.front;
		NodeCheck=true;		//���������� ������ ��� ������ �� ����� � ������� ��� ������. ���� �������� �������������� ��� ����� ��� �������.
		while(tempfirst != oura.rear)
		{
			int v; //������� ��� �������������� ��� �� ����� ��� ����� ����� �� ������� ����������� ��� ��� ������� 
			for(v=0;v<tempfirst->nodekomvos->sizeElem;v++)
				if(tempfirst->nodekomvos->Element[v] != stoiva.head->nodekomvos->Element[v]) break;

			if(v == stoiva.head->nodekomvos->sizeElem)
			{
				NodeCheck=false;
				stoiva.deleteNode();	//��������� ��� ������ ��� ������� ���� ������ ����� ��� ����� ��� ������ stoiva.head �� ������ ��� ����������� �����
				//cout<<"======Vrika epanalipsi!!======\n";
				break;
			}	
			tempfirst=tempfirst->next;
		}
//----------------------------------------------------------------------
		
////--------------	������� ��� �������� ������	--------------------------------
	foundsolution=true; //���������� ������ ��� ���� ������ ����. ���� �������� �������������� ��� ����.
	if(NodeCheck==true)		
	{
		//Ektypwsi Kwmvwn pou eksetazontai----------------------------
		//for(int t=0;t<stoiva.head->nodekomvos->sizeElem;t++)
		//		cout<<stoiva.head->nodekomvos->Element[t];
		//	cout<<endl;

		oura.insert(stoiva.head->nodekomvos);
		for(int ch=0;ch<stoiva.head->nodekomvos->sizeElem;ch++) //�� ��������� ��� ������ ����� ���� ������ ���������
		{
			if(stoiva.head->nodekomvos->Element[ch]!=1)
			{ 
				foundsolution=false;
				break;
			}
		}
		if(foundsolution==true) break;
//----------------------------------------------------------------------
	
//--------------------    �������� ��� �������� ������    -------------------------
// ���� �������� ������������ �� ����:	 
//	-������� �� ��� ���� ��� ����� (���. ��� ���������) ��������� ��� ����� (��������) ��� ������.
//	 � �������� ����� ��� ���� ���� ���� ���� � ����� �� �� �����, ����� ������� �� ��� ��������������� 
//	 ��� �� ������� ���������. ���� �� ������ ��������� ��� ��� �����, ���� �� �������� � �� ������� �� ��� ����
//	 ��� ��������� ��� ��� ����� , ���� ���������� �� ���� ��� �� �������� ���� �� ��� ����.
//	-������������ ��� ��� ������� ����� ��� ������ ����������� ���� ���������� ����� ���� ��������
//  -������� ���� ���������� ����� ��� ���������� �������������� ��� ����� ��� ������
//	-��������� ���� ������ ��� ���������� �����

	int fakos=stoiva.head->nodekomvos->Element[0]; //� ����� �������� ���� 1� ���� ��� ������ ���������� 
	int sizeEl=stoiva.head->nodekomvos->sizeElem;
	Stoiva *temp_father=stoiva.head;

	for(int i=1;i<sizeEl;i++)	//��������� ��� ��� �����
	{
		if(temp_father->nodekomvos->Element[i]==fakos)
		{
			k=new Komvos(sizeEl);
			for(int a=0;a<sizeEl;a++)	//���������
				k->Element[a]=temp_father->nodekomvos->Element[a];

			if(fakos==0)
			{
				k->Element[0]=1;
				k->Element[i]=1;
				k->Action=1;	 //������� ���� �������� ����
				k->Persons[0]=i; //�� ����� i �������� ���� �������� ����
				k->Persons[1]=0; //��� ������� ����� �� ����� ����� ���������
			}
			else if(fakos==1)
			{
				k->Element[0]=0;
				k->Element[i]=0;
				k->Action=0;	 //��� ���� ������ ����
				k->Persons[0]=i; //�� ����� i ������� ���� ������ ����
				k->Persons[1]=0; //��� ������� ����� �� ����� ����� ���������
			}

			k->Pateras = temp_father->nodekomvos;
			k->Cost = temp_father->nodekomvos->Cost + cost_array[i-1];
			k->Depth = temp_father->nodekomvos->Depth + 1;	

			stoiva.addNode(k);

			//-----�������� ��������� ��� ���� ������ ��� ������������------
			//cout<<"Stin 1 for\n";
			//for(int typ=0;typ<sizeEl;typ++)
			//	cout<<k->Element[typ];
			//cout<<endl;
		}
	}

	for(int i=1;i<sizeEl;i++) //��������� ��� ��� �����
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
					k->Action=1;		//��������� ���� �������� ����
					k->Persons[0]=i;	//�� ����� i ��� j ��������� 
					k->Persons[1]=j;	//���� �������� ����.
				}
				else if(fakos==1)
				{
					k->Element[0]=0;
					k->Element[i]=0;
					k->Element[j]=0;
					k->Action=0;		//����� ���� ������ ����
					k->Persons[0]=i;	//�� ����� i ��� j ��������
					k->Persons[1]=j;	//���� ������ ����.
				}

				k->Pateras = temp_father->nodekomvos;
				if(cost_array[i-1]>cost_array[j-1]) k->Cost = temp_father->nodekomvos->Cost + cost_array[i-1];
				else k->Cost = temp_father->nodekomvos->Cost + cost_array[j-1];
				k->Depth = temp_father->nodekomvos->Depth + 1;

				stoiva.addNode(k);

				//-----�������� ��������� ��� ���� ������ ��� ������������------
				//cout<<"Stin 2 for\n";
				//for(int typ=0;typ<sizeEl;typ++)
				//	cout<<k->Element[typ];
				//cout<<endl;
            }
		}
	}
//------------------	����� ���������		---------------------------
	}//end if (NodeCheck)
	//stoiva.head=stoiva.head->next;
	
}//end while

if(stoiva.head == NULL) {cout<<"\nGia to provlima auto den vrethike lysi!\n"; system("pause");exit(0);}

int SynolikosXronosLysis=stoiva.head->nodekomvos->Cost;
int VathosLysis=stoiva.head->nodekomvos->Depth;
SolutionNodes solNodes; 

	while(stoiva.head->nodekomvos->Pateras != NULL)		//��������� ��� ������ ��� ���������� ��� ����� �� ��� ���������� ������ ���� ��
	{													//����������� �������� ���� ������� ��� ��� ������ ���� ������ ���������
		solNodes.addNode(stoiva.head->nodekomvos);	
		stoiva.head->nodekomvos = stoiva.head->nodekomvos->Pateras;
	}
	solNodes.addNode(stoiva.head->nodekomvos); //���� � ������ ��� ������ stoiva.head->nodekomvos->Pateras ����� NULL

	cout<<"\n\nMia lysi pou dinei o DFS einai:\n\n";
	cout<<"Oloi oi anthrwpoi einai stin arxiki oxthi (arxiki katastasi)\n";	//��� ��������

	solNodes.head = solNodes.head->next;	//������ � ������� ������ ��� �������� ����� �������� ��������� ���� ������� �����

	//��������� ������� �� ��� ����������� ��� ��������� ������������� �� �������� ��� ����� ������������
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