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
Tree* foliarTrees;//���������� �������


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

/*
struct Person 
{
    std::string name;
    int age;
};
std::ostream& operator << (std::ostream &os, const Person &p)
{
    return os << p.name << " " << p.age;
}

std::istream& operator >> (std::istream& in, Person& p)
{
    in >> p.name >> p.age;
    return in;
}*/

void readFromKeyboard(){
	int n;
	cout<<"������� ������ �������"<<endl;
	cin>>n;
	Tree* trees = new Tree[n];
	for(int i =0; i< n; ++i){
		cin>>trees[i];
	}
	
	int foliarCount = 0;
	int coniferousCount = 0;

	for(int i = 0; i< n; ++i){
		if(trees[i].kind == foliar){
			foliarCount++;
		}
		if(trees[i].kind == coniferous){
			coniferousCount++;
		}
	}

	if(coniferousTrees){
		delete[] coniferousTrees;
	}

	if(foliarTrees){
		delete[] foliarTrees;
	}

	coniferousTrees = new Tree[coniferousCount];
	foliarTrees = new Tree[foliarCount];

	coniferousCount = 0;
	foliarCount = 0;

	for(int i = 0; i< n; ++i){
		if(trees[i].kind == foliar){
			foliarTrees[foliarCount] = trees[i];
			foliarCount++;

		}
		if(trees[i].kind == coniferous){
			coniferousTrees[coniferousCount] = trees[i];
			coniferousCount++;
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
	
	int foliarCount = 0;
	int coniferousCount = 0;

	for(int i = 0; i< n; ++i){
		if(trees[i].kind == foliar){
			foliarCount++;
		}
		if(trees[i].kind == coniferous){
			coniferousCount++;
		}
	}

	if(coniferousTrees){
		delete[] coniferousTrees;
	}

	if(foliarTrees){
		delete[] foliarTrees;
	}

	coniferousTrees = new Tree[coniferousCount];
	foliarTrees = new Tree[foliarCount];

	coniferousCount = 0;
	foliarCount = 0;

	for(int i = 0; i< n; ++i){
		if(trees[i].kind == foliar){
			foliarTrees[foliarCount] = trees[i];
			foliarCount++;

		}
		if(trees[i].kind == coniferous){
			coniferousTrees[coniferousCount] = trees[i];
			coniferousCount++;
		}
	}

}

int main(){
	setlocale(LC_ALL, "Russian");
	Tree t;
	std::cin>>t;
	
	ofstream ofs("file.txt");
	ofs<<t;
	ofs.close();
	
	ifstream ifs("file.txt");
	ifs>>t;
	ifs.close();
	
	cout<<endl;
	std::cout<<t;


	system("pause");
	return 0;
}