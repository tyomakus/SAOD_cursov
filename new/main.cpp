#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>


using namespace std;

int amount = 0;
int lenght = 1;


struct rec
{
	char a[30];
	short int b;
	char c[22];
	char d[10];
//	int weight;
//	bool use;
};


struct tree {
	rec* data;
	int weight;
} *ArrayTree;

struct Vertex
{
	rec* Data;
	int Weight;
	Vertex* Left;
	Vertex* Right;
} *Root;



struct spis{
	spis *next;
	rec *data;
};

struct tle {spis *head; spis *tail;};

void list (spis *head) {
	spis *p;
	int i=0, g;
	p=head;
	cout<<"\t\t"<<"FIO"<<"\t\t"<<"  |N otdela"<<"     |Doljnost"<<"\t"<<"      |Date of birth    |"<<endl;
	while((i++)<4000)
	{ 
		cout<<"---------------------------------------------------------------------------------------"<<endl;
		cout<<i<<")   "<<p->data->a<<"|"<<"\t"<<p->data->b<<"\t"<<"|"<<p->data->c<<"|"<<"\t"<<p->data->d<<"\t"<<"|"<<endl;
		p=p->next;
		if (i%20==0){
				cout<<"Print 20 more? (1/0)\n";
				cin>>g;
				cout<<"\t\t"<<"FIO"<<"\t\t"<<"  |N otdela"<<"     |Doljnost"<<"\t"<<"      |Date of birth    |"<<endl;
				if (g==0){
					break;
				}
		}
	}
}

void SearchList(spis* head){
	spis *p;
	int i=1, g;
	p=head->next;
	for(p=head->next;p;p->next, i++)
	{ 
		ArrayTree[i - 1].data = p->data;
		ArrayTree[i - 1].weight = rand() % 100;
		cout<<i<<")   "<<p->data->a<<"\t"<<p->data->b<<"\t"<<p->data->c<<"\t"<<p->data->d<<"\t"<<endl;
		p=p->next;
	}
}

void SDP_nReq(tree D, Vertex*& Root_1) {
	Vertex** p = &Root_1;
	while ((*p) != NULL) {
		if (D.data->b <= (*p)->Data->b)
			p = &((*p)->Left);
		else if (D.data->b > (*p)->Data->b) p = &((*p)->Right);
		else break;
	}

	if (*p == NULL) {
		(*p) = new Vertex;
		(*p)->Data = D.data;
		(*p)->Weight = D.weight;
		(*p)->Left = NULL;
		(*p)->Right = NULL;
	}
}



spis *DigitalSort(spis *&S) {
	int j,i,g,k;
 	spis *p;
 	int KDI[]={1,0,4,3,7,6};
 	tle Q[256];
 	for (j=0;j<6;j++) { // инициализация очередей Q	
   		for (i=0;i<256;i++)
    		Q[i].tail=(spis *)&Q[i].head;
   		p=S;
   	//	cout<<"done1"<<endl;
   		while (p) {//расстановка элементов из списка S в очереди Q по j - ой цифре
    		g=p->data->d[KDI[j]];
    	//	cout<<g<<endl;
      		Q[g].tail->next=p;
      		Q[g].tail=p; 
      		p=p->next;
      		//cout<<"done-"<<j<<endl;
    	}
   		p=(spis*)&S; // соединение очередей Q в список S 
   		for (i=0;i<256;i++) {
    		if ( Q[i].tail!=(spis *)&Q[i].head) {
       			p->next=Q[i].head;
       			p=Q[i].tail;
      		}
    	}
   		p->next=NULL; 
  	}
	i=0, g;
	return S;
}


spis *MakeSpis(rec mas[], int n){
	spis *head, *p;
	int i;
	head=new spis;
	head->next=0;
	head->data=&mas[0];
	for (i=1; i<n; i++){
		p=new spis;
		p->data=&mas[i];
		p->next=head;
		head=p;
	}
	return head;
}	


void A2(tree* el, Vertex*& Root, int L, int R) {
	int wes, sum;
	wes = sum = 0;
	int i;
	if (L <= R) {
		for (i = L; i < R; i++) {
			wes += el[i].weight;
		}
		for (i = L; i < R - 1; i++) {
			if (sum < (wes / 2) && (sum + el[i].weight) > (wes / 2)) {
				break;
			}
			sum += el[i].weight;

		}
		SDP_nReq(el[i], Root);
		A2(el, Root, L, i - 1);
		A2(el, Root, i + 1, R);
	}
}


void BuildTree(spis* head) {
	spis* p;
	int i;
	int j;
	tree t;
	for (i = 1; i < amount; i++) {
		t = ArrayTree[i];
		j = i - 1;
		while (j >= 0 && (*t.data).b < (*ArrayTree[j].data).b) {	
			ArrayTree[j + 1] = ArrayTree[j];
			j--;
		}
		ArrayTree[j + 1] = t;
	}
	A2(ArrayTree, Root, 0, amount - 1);
}

void SearchInsp(Vertex* p, int key) {
	if (p != NULL) {
		SearchInsp(p->Left, key);
		if(p->Data->b == key)
			cout << p->Data->a<< "\t" << p->Data->b << "\t" << p->Data->c << "\t" << p->Data->d << "\t" << p->Weight << endl;
		SearchInsp(p->Right, key);
	}
}
 
void SearchTree(Vertex* p) {
	int key;
	cout << "Input the key for searching: ";
	cin >> key;
	while (p != NULL) {
		if (p->Data->b > key)
			p = (p->Left);
		else if (p->Data->b < key) p = p->Right;
		else break;
	}
	cout << endl;
	SearchInsp(p,key);
}



void Print(Vertex* p) {
	if (p != NULL) {
		Print(p->Left);
		cout << lenght << ")\t" << (*p->Data).a << "\t" << (*p->Data).b << "\t" << (*p->Data).c << "\t" << (*p->Data).d  <<"\t"<< p->Weight << endl;
		lenght++;
		Print(p->Right);
	}
}

void Search(spis* head, spis *tail, rec** a, int R, int date){
	int i=0;
	int y1[4000];
	for(i=0; i<4000; i++){
		y1[i]=(a[i]->d[6]-'0')*10+a[i]->d[7]-'0';
	}
	spis* p;
	int L=0, m;
	while (L<R){
		m=(L+R)/2;
		if (y1[m]<date) L=m+1;
		else R=m;
	}
	if (y1[R]==date){
		while (y1[R]==date){
			p=new spis;
			p->data = a[R];
			tail->next = p;
			tail=p;
			tail->next=NULL;
			R++;
			amount++;
		}
		ArrayTree = new tree[amount];
		SearchList(head);
		(head);
			BuildTree(head);
	cout<<"\n\n \n     Tree has been built!     \n\n";
	Print(Root);
	char a='1';
	while (a!='0'){
		SearchTree(Root);
		cout<<"\n\nsearch arain? (1/0)\n";
		cin>>a;
	}
	}
	else{
		cout<<"key doesnt exist"<<endl;
	}

}

int main()
{
	system("color 2");
	FILE *fp;
	fp=fopen("testBase2.dat", "rb");
	rec mas[4000]={0};
	int i;
	spis *head = MakeSpis(mas, 4000);
	int g;
	fread((rec *)mas, sizeof(rec), 4000, fp);
	i=0;	
	int c;
	spis *p=head;
	rec** A = new rec* [4000];
	
	head=DigitalSort(p);
	p=head;
	spis *p2=head;
list(p2);
	system("pause");
	for (i=0; i<4000; i++){
		A[i]=p->data;
		p=p->next;
	}
	c=1;
	while (c){
		system("cls");
		cout<<"input key"<<endl;
		int key;
		cin>>key;
		Search(head, head, A ,4000-1, key);
//		list(p);
		
		cout<<"Do u want to search again? (1/0)\n";
		cin>>c;
	}

	return 0;
}




