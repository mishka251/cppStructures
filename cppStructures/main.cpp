#include<iostream>
#include<fstream>
#include<string>
#include<string.h>

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

std::ostream& operator << (std::ostream& os, const Forest&forest){
	os<<"������������ "<<forest.location<<endl;
	os<<"��� "<<forest.type<<endl;
	os<<"��������������� "<<forest.fireDanger<<endl;
	return os;
}

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
	getline(is, header);
	getline(is, header);//���������� ���������
	getline(is, kind);
	if(kind=="coniferous"){
		tree.kind=coniferous;
	}
	if(kind=="foliar"){
		tree.kind=foliar;
	}

	getline(is, header);//���������� ���������
	is>>tree.height;

	getline(is, header);//���������� ���������
	getline(is, header);//���������� ���������
	is>>tree.thickness;

	getline(is, header);//���������� ���������
	string hasHollow;

	getline(is, header);//���������� ���������
	is>>hasHollow;

	if(hasHollow=="Y"){
		tree.hasHollow = true;
	}
	if(hasHollow=="N"){
		tree.hasHollow = false;
	}

	getline(is, header);//���������� ���������
	getline(is, header);//���������� ���������
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
	ifstream ifs(filename);
	ifs>>n;
	Tree* trees = new Tree[n];
	for(int i =0; i< n; ++i){
		ifs>>trees[i];
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
	Tree& highest = coniferousTreesCount> 0? coniferousTrees[0] : foliarTrees[0];
	for(int i = 0; i< coniferousTreesCount; ++i){
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

void sortArraysByShaowSquare(){
	for(int i = 0; i< foliarTreesCount; ++i){
		for(int j = 0; j< i; ++j){
			if(foliarTrees[i].shadowSquare>foliarTrees[j].shadowSquare){
				Tree& tmp = foliarTrees[i];
				foliarTrees[i] = foliarTrees[j];
				foliarTrees[j] = tmp;
			}
		}
	}

	for(int i = 0; i< coniferousTreesCount; ++i){
		for(int j = 0; j < i; ++j){
			if(coniferousTrees[i].shadowSquare>coniferousTrees[j].shadowSquare){
				Tree& tmp = coniferousTrees[i];
				coniferousTrees[i] = coniferousTrees[j];
				coniferousTrees[j] = tmp;
			}
		}
	}
}

void printAll(){
		for(int i = 0; i< foliarTreesCount; ++i){
			cout<<foliarTrees[i]<<endl;
	}

	for(int i = 0; i< coniferousTreesCount; ++i){
		cout<<coniferousTrees[i]<<endl;
	}
}

void printForest(){
	for(int i = 0; i< foliarTreesCount; ++i){
		cout<<foliarTrees[i].kind<<endl;
	}

	for(int i = 0; i< coniferousTreesCount; ++i){
		cout<<coniferousTrees[i].kind<<endl;
	}
}

void menu(){
	while(true){
		cout<<"������� �������: 0 - �����, 1 - ���� � ����������, 2 - ���� �� �����, 3 - ����� �� �����, 4 - ����� ������ �������� ������, 5 - ����� �������� � ������, 6 - ���������� ��������, 7 - ����� ���������� ��� ���"<<endl;
		int command;
		cin>>command;

		switch(command){
		case 0:
			return;
		case 1:
			readFromKeyboard();
			break;
		case 2:
			readFromFile();
			break;
		case 3:
			printAll();
			break;
		case 4:{
			Tree& highest = findHighestTree();
			cout<<highest<<endl;
			break;
			   }
		case 5:
			getTreesWithHollow();

			cout<<"�������� � ������ "<<treesCountWithHollow<<endl;
			for(int i =0; i< treesCountWithHollow; ++i){
				cout<<treesWithHollow[i]<<endl;
			}
			break;
		case 6:
			sortArraysByShaowSquare();
			break;
		case 7:
			printForest();
			break;
		}
	}
}

int main(){
	setlocale(LC_ALL, "Russian");

	menu();
	system("pause");
	return 0;
}