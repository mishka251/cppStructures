#include<iostream>
#include<fstream>
#include<string>

using namespace std;


//��������� "���"
struct Forest {
	string location;//��������� ���� "�����������"
	string type;//��� ����
	double fireDanger;//���������������

	Forest(){
		this->location="";
		this->type="";
		this->fireDanger=0;
	}

	Forest(const Forest&forest){
		this->fireDanger=forest.fireDanger;
		this->type=forest.type;
		this->location=forest.location;
	}

	Forest(string location, string type, double fireDanger){
		this->location=location;
		this->fireDanger=fireDanger;
		this->type=type;
	}

	bool operator==(const Forest& forest){
		return this->type==forest.type;
	}
};

struct Tree {
	Forest kind;//��� ���� 
	double height;//������
	int thickness;//�������
	bool hasHollow;//���� �� � ������ �����
	int shadowSquare;//������� ���� �� ������
};

Forest coniferous("Ufa", "coniferous", 0.2);//�������
Forest foliar("Russia", "foliar", 0.3);//����������

Tree* coniferousTrees;//������� �������
int coniferousTreesCount = 0;

Tree* foliarTrees;//���������� �������
int foliarTreesCount = 0;


//����� ������ � �������
std::ostream& operator << (std::ostream& os, const Tree&tree){
	os<<"���: \'coniferous\' - ������� \'foliar\' - ����������"<<endl;
		
	if( coniferous==tree.kind){
		os<<"coniferous"<<endl;
	}
	if(foliar==tree.kind){
		os<<"foliar"<<endl;
	}
	
	os<<"������"<<endl;
	os<<tree.height<<endl;
	
	os<<"�������"<<endl;
	os<<tree.thickness<<endl;


	os<<"���� �� � ������ ����� (\'Y\' ��� \'N\')"<<endl;

	if(tree.hasHollow){
		os<<"Y"<<endl;
	}else{
		os<<"N"<<endl;
	}	

	os<<"������� ������������� ����"<<endl;
	os<<tree.shadowSquare<<endl;

	return os;
}

//����� ������ � ����
std::ofstream& operator << (std::ofstream& ofs, const Tree&tree){
	ofs<<"���: \'coniferous\' - ������� \'foliar\' - ����������"<<endl;
		
	if( coniferous==tree.kind){
		ofs<<"coniferous"<<endl;
	}
	if(foliar==tree.kind){
		ofs<<"foliar"<<endl;
	}
	
	ofs<<"������"<<endl;
	ofs<<tree.height<<endl;
	
	ofs<<"�������"<<endl;
	ofs<<tree.thickness<<endl;


	ofs<<"���� �� � ������ ����� (\'Y\' ��� \'N\')"<<endl;

	if(tree.hasHollow){
		ofs<<"Y"<<endl;
	}else{
		ofs<<"N"<<endl;
	}	

	ofs<<"������� ������������� ����"<<endl;
	ofs<<tree.shadowSquare<<endl;

	return ofs;
}



std::istream& operator >> (std::istream& is, Tree& tree){
	string kind;
	while(kind!="coniferous" && kind!="foliar"){
		cout<<"������� ���: \'coniferous\' - ������� \'foliar\' - ����������"<<endl;
		is>>kind;
		if(kind=="coniferous"){
			tree.kind=coniferous;
		}
		if(kind=="foliar"){
			tree.kind=foliar;
		}
	}
	cout<<"������� ������"<<endl;
	is>>tree.height;
	
	cout<<"������� �������"<<endl;
	is>>tree.thickness;

	string hasHollow;
	while(hasHollow!="Y" && hasHollow!="N"){
		cout<<"������� ���� �� � ������ ����� (\'Y\' ��� \'N\')"<<endl;
		is>>hasHollow;

		if(hasHollow=="Y"){
			tree.hasHollow = true;
		}
		if(hasHollow=="N"){
			tree.hasHollow = false;
		}
	}

	cout<<"������� ������� ������������� ����"<<endl;
	is >> tree.shadowSquare;
	return is;
}

std::ifstream& operator >> (std::ifstream& is, Tree& tree){
	string kind;
	string header;

	is >> header;//���������� ���������
	is>>kind;
	if(kind=="coniferous"){
		tree.kind=coniferous;
	}
	if(kind=="foliar"){
		tree.kind=foliar;
	}
	
	is >> header;//���������� ���������
	is>>tree.height;
	
	is >> header;//���������� ���������
	is>>tree.thickness;

	is >> header;//���������� ���������
	string hasHollow;

	is >> header;//���������� ���������
	is>>hasHollow;

	if(hasHollow=="Y"){
		tree.hasHollow = true;
	}
	if(hasHollow=="N"){
		tree.hasHollow = false;
	}
	
	is >> header;//���������� ���������
	is >> tree.shadowSquare;
	return is;
}

void readFromKeyboard(){
	int n;
	cout<<"������� ������ �������"<<endl;
	cin>>n;
	Tree* trees = new Tree[n];
	for(int i =0; i< n; ++i){
		cin>>trees[i];
	}
	
	foliarTreesCount = 0;
	coniferousTreesCount = 0;

	for(int i = 0; i< n; ++i){
		if(trees[i].kind == foliar){
			foliarTreesCount++;
		}
		if(trees[i].kind == coniferous){
			coniferousTreesCount++;
		}
	}

	if(coniferousTrees){
		delete[] coniferousTrees;
	}

	if(foliarTrees){
		delete[] foliarTrees;
	}

	coniferousTrees = new Tree[coniferousTreesCount];
	foliarTrees = new Tree[foliarTreesCount];

	coniferousTreesCount = 0;
	foliarTreesCount = 0;

	for(int i = 0; i< n; ++i){
		if(trees[i].kind == foliar){
			foliarTrees[foliarTreesCount] = trees[i];
			foliarTreesCount++;

		}
		if(trees[i].kind == coniferous){
			coniferousTrees[coniferousTreesCount] = trees[i];
			coniferousTreesCount++;
		}
	}

}

void readFromFile(){
	string filename = "file.txt";

	int n;
	cout<<"������� ������ �������"<<endl;
	cin>>n;
	Tree* trees = new Tree[n];
	for(int i =0; i< n; ++i){
		cin>>trees[i];
	}
	
	foliarTreesCount = 0;
	coniferousTreesCount = 0;

	for(int i = 0; i< n; ++i){
		if(trees[i].kind == foliar){
			foliarTreesCount++;
		}
		if(trees[i].kind == coniferous){
			coniferousTreesCount++;
		}
	}

	if(coniferousTrees){
		delete[] coniferousTrees;
	}

	if(foliarTrees){
		delete[] foliarTrees;
	}

	coniferousTrees = new Tree[coniferousTreesCount];
	foliarTrees = new Tree[foliarTreesCount];

	coniferousTreesCount = 0;
	foliarTreesCount = 0;

	for(int i = 0; i< n; ++i){
		if(trees[i].kind == foliar){
			foliarTrees[foliarTreesCount] = trees[i];
			foliarTreesCount++;

		}
		if(trees[i].kind == coniferous){
			coniferousTrees[coniferousTreesCount] = trees[i];
			coniferousTreesCount++;
		}
	}

}


Tree& findHighestTree(){
	Tree& highest = coniferousTrees[0];
	for(int i = 1; i< coniferousTreesCount; ++i){
		if(coniferousTrees[i].height > highest.height){
			highest = coniferousTrees[i];
		}
	}

	for(int i = 0; i< foliarTreesCount; ++i){
		if(foliarTrees[i].height > highest.height){
			highest = foliarTrees[i];
		}
	}
	return highest;
}

int treesCountWithHollow = 0;
Tree* treesWithHollow;

void getTreesWithHollow(){

	if (treesCountWithHollow > 0) {
		delete[] treesWithHollow;
	}

	for(int i = 0; i< coniferousTreesCount; ++i){
		if(coniferousTrees[i].hasHollow){
			treesCountWithHollow++;
		}
	}

	for(int i = 0; i< foliarTreesCount; ++i){
		if(foliarTrees[i].hasHollow){
			treesCountWithHollow++;
		}
	}

	treesWithHollow = new Tree[treesCountWithHollow];
	treesCountWithHollow = 0;
	for(int i = 0; i< coniferousTreesCount; ++i){
		if(coniferousTrees[i].hasHollow){
			treesWithHollow[treesCountWithHollow] = coniferousTrees[i];
			treesCountWithHollow++;
		}
	}

	for(int i = 0; i< foliarTreesCount; ++i){
		if(foliarTrees[i].hasHollow){
			treesWithHollow[treesCountWithHollow] = foliarTrees[i];
			treesCountWithHollow++;
		}
	}
}


int main(){
	setlocale(LC_ALL, "Russian");
	/*Tree t;
	std::cin>>t;
	
	ofstream ofs("file.txt");
	ofs<<t;
	ofs.close();
	
	ifstream ifs("file.txt");
	ifs>>t;
	ifs.close();
	
	cout<<endl;
	std::cout<<t;*/

	readFromKeyboard();
	Tree& highest = findHighestTree();
	cout<<highest<<endl;

	getTreesWithHollow();

	cout<<"�������� � ������ "<<treesCountWithHollow<<endl;
	for(int i =0; i< treesCountWithHollow; ++i){
		cout<<treesWithHollow[i]<<endl;
	}
	//int count = sizeof(withHollow)

	system("pause");
	return 0;
}