#include<iostream>
#include<fstream>
#include<string>

using namespace std;


//структура "Лес"
struct Forest {
	string location;//строковое поле "расположние"
	string type;//тип леса
	double fireDanger;//пожароопасность

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
	Forest kind;//вид леса 
	double height;//высота
	int thickness;//полщина
	bool hasHollow;//есть ли в дереве дупло
	int shadowSquare;//площадь тени от дерева
};

Forest coniferous("Ufa", "coniferous", 0.2);//хвойный
Forest foliar("Russia", "foliar", 0.3);//лиственный

Tree* coniferousTrees;//хвойные деревья
int coniferousTreesCount = 0;

Tree* foliarTrees;//лиственные деревья
int foliarTreesCount = 0;


//вывод дерева в консоль
std::ostream& operator << (std::ostream& os, const Tree&tree){
	os<<"Тип: \'coniferous\' - хвойный \'foliar\' - лиственный"<<endl;
		
	if( coniferous==tree.kind){
		os<<"coniferous"<<endl;
	}
	if(foliar==tree.kind){
		os<<"foliar"<<endl;
	}
	
	os<<"Высота"<<endl;
	os<<tree.height<<endl;
	
	os<<"Толщина"<<endl;
	os<<tree.thickness<<endl;


	os<<"Есть ли в дереве дупла (\'Y\' или \'N\')"<<endl;

	if(tree.hasHollow){
		os<<"Y"<<endl;
	}else{
		os<<"N"<<endl;
	}	

	os<<"Площадь отбрасываемой тени"<<endl;
	os<<tree.shadowSquare<<endl;

	return os;
}

//вывод дерева в файл
std::ofstream& operator << (std::ofstream& ofs, const Tree&tree){
	ofs<<"Тип: \'coniferous\' - хвойный \'foliar\' - лиственный"<<endl;
		
	if( coniferous==tree.kind){
		ofs<<"coniferous"<<endl;
	}
	if(foliar==tree.kind){
		ofs<<"foliar"<<endl;
	}
	
	ofs<<"Высота"<<endl;
	ofs<<tree.height<<endl;
	
	ofs<<"Толщина"<<endl;
	ofs<<tree.thickness<<endl;


	ofs<<"Есть ли в дереве дупла (\'Y\' или \'N\')"<<endl;

	if(tree.hasHollow){
		ofs<<"Y"<<endl;
	}else{
		ofs<<"N"<<endl;
	}	

	ofs<<"Площадь отбрасываемой тени"<<endl;
	ofs<<tree.shadowSquare<<endl;

	return ofs;
}



std::istream& operator >> (std::istream& is, Tree& tree){
	string kind;
	while(kind!="coniferous" && kind!="foliar"){
		cout<<"Введите тип: \'coniferous\' - хвойный \'foliar\' - лиственный"<<endl;
		is>>kind;
		if(kind=="coniferous"){
			tree.kind=coniferous;
		}
		if(kind=="foliar"){
			tree.kind=foliar;
		}
	}
	cout<<"Введите высоту"<<endl;
	is>>tree.height;
	
	cout<<"Введите толщину"<<endl;
	is>>tree.thickness;

	string hasHollow;
	while(hasHollow!="Y" && hasHollow!="N"){
		cout<<"Введите есть ли в дереве дупла (\'Y\' или \'N\')"<<endl;
		is>>hasHollow;

		if(hasHollow=="Y"){
			tree.hasHollow = true;
		}
		if(hasHollow=="N"){
			tree.hasHollow = false;
		}
	}

	cout<<"Введите площадь отбрасываемой тени"<<endl;
	is >> tree.shadowSquare;
	return is;
}

std::ifstream& operator >> (std::ifstream& is, Tree& tree){
	string kind;
	string header;

	is >> header;//пропускаем заголовки
	is>>kind;
	if(kind=="coniferous"){
		tree.kind=coniferous;
	}
	if(kind=="foliar"){
		tree.kind=foliar;
	}
	
	is >> header;//пропускаем заголовки
	is>>tree.height;
	
	is >> header;//пропускаем заголовки
	is>>tree.thickness;

	is >> header;//пропускаем заголовки
	string hasHollow;

	is >> header;//пропускаем заголовки
	is>>hasHollow;

	if(hasHollow=="Y"){
		tree.hasHollow = true;
	}
	if(hasHollow=="N"){
		tree.hasHollow = false;
	}
	
	is >> header;//пропускаем заголовки
	is >> tree.shadowSquare;
	return is;
}

void readFromKeyboard(){
	int n;
	cout<<"Введите размер массива"<<endl;
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
	cout<<"Введите размер массива"<<endl;
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

	cout<<"Деревьев с дуплом "<<treesCountWithHollow<<endl;
	for(int i =0; i< treesCountWithHollow; ++i){
		cout<<treesWithHollow[i]<<endl;
	}
	//int count = sizeof(withHollow)

	system("pause");
	return 0;
}