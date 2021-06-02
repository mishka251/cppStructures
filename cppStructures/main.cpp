#include<iostream>
#include<fstream>
#include<string>
#include<string.h>

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

std::ostream& operator << (std::ostream& os, const Forest&forest){
	os<<"расположение "<<forest.location<<endl;
	os<<"тип "<<forest.type<<endl;
	os<<"пожароопасность "<<forest.fireDanger<<endl;
	return os;
}

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
	getline(is, header);
	getline(is, header);//пропускаем заголовки
	getline(is, kind);
	if(kind=="coniferous"){
		tree.kind=coniferous;
	}
	if(kind=="foliar"){
		tree.kind=foliar;
	}

	getline(is, header);//пропускаем заголовки
	is>>tree.height;

	getline(is, header);//пропускаем заголовки
	getline(is, header);//пропускаем заголовки
	is>>tree.thickness;

	getline(is, header);//пропускаем заголовки
	string hasHollow;

	getline(is, header);//пропускаем заголовки
	is>>hasHollow;

	if(hasHollow=="Y"){
		tree.hasHollow = true;
	}
	if(hasHollow=="N"){
		tree.hasHollow = false;
	}

	getline(is, header);//пропускаем заголовки
	getline(is, header);//пропускаем заголовки
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
		cout<<"Введите команду: 0 - выход, 1 - ввод с клавиатуры, 2 - ввод из файла, 3 - вывод на экран, 4 - поиск самого высокого дерева, 5 - вывод деревьев с дуплом, 6 - сортирвока массивов, 7 - вывод информации про лес"<<endl;
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

			cout<<"Деревьев с дуплом "<<treesCountWithHollow<<endl;
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