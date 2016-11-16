////////////////////////////////////		UNIFORM-COST SEARCH ( U C S )		//////////////////////////////////////////////////////
//		�� ����� ��� ��������� ������������� ������������ �� ���� ���������:
//  -������������ �� ��� ���� � ������ ��������� ��� ����������� (������� ������)
//	-���� ������ ��� ������������ ���� ���� ���������� �� ��� ������ ��� ������� FIFO
//	-������������� �� ������ ��� ����������� (���. ������������� ���� ����) ������ �� ������ ����� ��� ����� �����������������
//	-���� ���� ������������� �� ������ �� �� �������� ������
//	-���� �� ������ ��� ������������� ���������� ���� ���� ��� ��� ��� ���� ��������� ��� ���� ��������� ������ ����� �����������������
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

//� ��������� ����� ��� ����� ������� �� ��� ��������: 
//���� �������� � ��������� insert ��� ��� ������� ���� ������, ����� � ������ ������
//�� ����������� ���� ��������� ���� ��� ����� ���� �� ������ ��� ������ ����� �� ��� ����������
//��� ������� ��� ��� ������ ��� ���� ������ ��� ���������� ��� ���� ����
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
		Oura *temp = new Oura();	//temp ������ ��� ������� ��� ������ ����� ���� ��������
		temp->nodekomvos=komvos;
		temp->next=NULL;

		if(front==NULL) front=temp;
		else
		{
			Oura *trexwn = front; 
			Oura *trexwnNext=front->next;
			while(trexwn != NULL)	//��������� ���� ����������� �������� ��� ��� ���������� ������ ���� �������� ���� ���� 
			{
				if(temp->nodekomvos->Cost <= trexwn->nodekomvos->Cost && trexwn==front) //���� ��������� �� �������� �����
				{
					temp->next=trexwn;
					trexwn=temp;
					front=trexwn;
					break;
				}
				else if(trexwnNext == NULL)//���� ��������� �� �������� ���������
				{
					trexwn->next=temp;
					rear=temp;
					break;
				}
				else if(temp->nodekomvos->Cost <= trexwnNext->nodekomvos->Cost)//���� ��������� �� �������� ���������
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

	Oura oura;		//����������� ��� �� ������� ��� ��� ��� �����
	Oura *first_oura;	//������� ��� �� ������� ����� ���� ���� ��� �����
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
		for(int i=0;i<n;i++) cost_array[i]=1+rand()%20;
	else
		for(int i=0;i<n;i++) 
			{cout<<"\nCost (minutes) for Person"<<i+1<<": \t"; cin>>cost_array[i];}

////////////////////////////	STARTS UNIFORM-COST SEARCH ( U C S )	////////////////////////////////

//  ��� ����� ���� ������������ ������� ��� �������������� �� �������� �� ������ ��� ������������ (n+1)
// ��� ��� ���� ��� �������������� ��� ����� ���� ����� ���� ��� ������ �����������
//----------------	������������ ��� ������� �������	----------------------------------------------
	Komvos *k;
	k=new Komvos((n+1));  //���������� ����������� ������

	for(int i=0;i<k->sizeElem;i++)	//������������ ��� ���������� ��� ������� ������ �� ��������
	{
		k->Element[i]=0;		
	}
	oura.insert(k);		//�������� ���� ���� ��� ���������� �����
	first_oura=oura.front;	
//-----------------------------------------------------------------------------------------------------

	bool NodeCheck;
	bool foundsolution;
	Oura *tempfirst;

while(1)	//  ���������� ��� � ���������� UCS ����� ������ (������� ����) ��� ���� �� ��������, ��� ��� �� ������� 
{			// ������� �������. ��� ���� ������� while(1). �� ���������� �� ������� ��� while(oura.front->nodekomvos != NULL),
			// ���. �� ��� �������� ����� ������������� ������ ���� ����
	PlithosKomvwn++;
//--------------	������� ����������������� �����������	---------------
		tempfirst=first_oura;
		NodeCheck=true;		//���������� ������ ��� ������ �� ����� � ������� ��� ������. ���� �������� �������������� ��� ����� ��� �������.
		while(tempfirst != oura.front)
		{
			int v; //������� ��� �������������� ��� �� ����� ��� ����� ����� �� ������� ����������� ��� ��� ������� 
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

////--------------	������� ��� �������� ������	--------------------------------
	foundsolution=true; //���������� ������ ��� ���� ������ ����. ���� �������� �������������� ��� ����.
	if(NodeCheck==true)		
	{
		//-------Typwsi eksetazomenwn komvwn pou eksetazontai--------
		//for(int t=0;t<oura.front->nodekomvos->sizeElem;t++)
		//		cout<<oura.front->nodekomvos->Element[t];
		//	cout<<endl;

		for(int ch=0;ch<oura.front->nodekomvos->sizeElem;ch++) //�� ��������� ��� ������ ����� ���� ������ ���������
		{
			if(oura.front->nodekomvos->Element[ch]!=1)
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
//	-��������� ���� ���� ��� ���������� �����

	int fakos=oura.front->nodekomvos->Element[0]; //� ����� �������� ���� 1� ���� ��� ������ ���������� 
	int sizeEl=oura.front->nodekomvos->sizeElem;

	for(int i=1;i<sizeEl;i++)	//��������� ��� ��� �����
	{
		if(oura.front->nodekomvos->Element[i]==fakos)
		{
			k=new Komvos(sizeEl);
			for(int a=0;a<sizeEl;a++)	//���������
				k->Element[a]=oura.front->nodekomvos->Element[a];

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

			k->Pateras = oura.front->nodekomvos;
			k->Cost = oura.front->nodekomvos->Cost + cost_array[i-1];
			k->Depth = oura.front->nodekomvos->Depth + 1;	

			oura.insert(k);

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

				k->Pateras = oura.front->nodekomvos;
				if(cost_array[i-1]>cost_array[j-1]) k->Cost = oura.front->nodekomvos->Cost + cost_array[i-1];
				else k->Cost = oura.front->nodekomvos->Cost + cost_array[j-1];
				k->Depth = oura.front->nodekomvos->Depth + 1;

				oura.insert(k);

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

	oura.front=oura.front->next;
}//end while

int SynolikosXronosLysis=oura.front->nodekomvos->Cost;
int VathosLysis=oura.front->nodekomvos->Depth;
SolutionNodes solNodes; 

	while(oura.front->nodekomvos->Pateras != NULL)	//��������� ��� ������ ��� ���������� ��� ����� �� ��� ������ ���� ��
	{												//����������� �������� ���� ������� ��� ��� ������ ���� ������ ���������
		solNodes.addNode(oura.front->nodekomvos);
		oura.front->nodekomvos = oura.front->nodekomvos->Pateras;
	}
	solNodes.addNode(oura.front->nodekomvos); //���� � ������ ��� ������ oura.front->nodekomvos->Pateras ����� NULL

	cout<<"\n\nMia lysi pou dinei o UCS einai:\n\n";
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
			int v; //������� ��� �������������� ��� �� ����� �� ����� ����� �� ������� ����������� ��� ������ 
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