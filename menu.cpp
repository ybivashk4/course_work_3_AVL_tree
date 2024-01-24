#include <iostream>
#include <cstdlib>
#include "tree.h"

void bin_tree::out_menu_tree(){
	std::cout << "Введите 1, чтобы добавить узел\n";
	
	std::cout << "Введите 2, чтобы удалить узел\n";// Вовремя теста Insert-a всё сломалось 
			
	std::cout << "Введите 3, чтобы вывести в виде таблицы\n";		
			
	std::cout << "Введите 4, чтобы получить доступ к узлу по ключу\n"; // Выводится узел и его дочерние узлы и его родительский ключ
	
	std::cout << "Введите 5, чтобы очистить консоль\n"; 
	
	std::cout << "Введите 6, чтобы прибавить дерево к другому\n";// изи - загрузить дерево как массив и просто вставить все элементы 
	
	std::cout << "Введите 7, чтобы сравнить текущие дерево с другим без учёта ключей\n";// Нужна глубина
	
	std::cout << "Введите 8, чтобы сравнить текущие дерево с другим с учётом ключей\n";// сначала переделать удаление  
	
	std::cout << "Введите 9, чтобы вывести высоту дерева\n"; // Ширина - максимальное кол-во узлов одинаковой высоты (можно обновлять при insert)
	
	std::cout << "Введите 10, чтобы вывести количество узлов дерева\n"; 
	
	std::cout << "Введите 11, чтобы сохранить дерево\n"; 
	
	std::cout << "Введите 0 для выхода\n";
}

template<class Type>
void input_check(Type *t){
	while (std::cin >> *t, std::cin.fail()){
		std::cin.clear();
		std::cin.ignore(500, '\n');
		std::cout << "Неправильный ввод\n";
	}
}

void bin_tree::menu_tree(){
	int i=0;
	int menu = 1;
	double key = 0;
	Node * node = NULL;
	
	while (menu){	
		out_menu_tree();
		
		input_check(&menu);
		
		switch(menu){
			case 1: /* Добавить узел*/
				std::cout << "Введите ключ\n";
				input_check(&key);
				this->insert(this->root, key);
				break;
			case 2: /* Удалить узел */
				std::cout << "Введите ключ по которому хотите удалить узел\n";
				input_check(&key);
				this->remove(root, key);
				break;
			case 3: /* Вывод*/
				this->out();
				break;
			case 4: /* Узел по ключу */
				std::cout << "Введите ключ\n";
				input_check(&key);
				std::cout << "---------------------\n";
				std::cout << "self\t" << "left\t" << "right\n";
				std::cout << "---------------------\n";
				this->find(this->root, key)->out();
				break;
			case 5: 
				system("cls");
				break;
			case 6:
				sum_tree();
				break;
			case 7:
				cmp_struct(bin_tree::load());
				break;		
			case 8:
				cmp_keys(bin_tree::load());
				break;
			case 9:
				std::cout << "Высота = " << (int)this->root->get_height() << "\n";
				break;
			case 10:
				std::cout << "В дереве "<< count << " узлов\n";
				break;
			case 11:
				this->save();
				break;
			case 0:
				break;
			default:
				std::cout << "Неправильный ввод\n";
				break;
		}	
			
	}
} 

void bin_tree::out_menu(){
	std::cout << "Введите 1, чтобы создать пустое дерево\n";
	
	std::cout << "Введите 2, чтобы загрузить дерево\n";
	
	std::cout << "Введите 3, чтобы очистить консоль\n";
	
	std::cout << "Введите 0 для выхода\n";
}

void bin_tree::menu(){
	int menu = 1, i=0;
	
	bin_tree * tree;
	while (menu){
		out_menu();
		input_check(&menu);
		switch(menu){
			case 1: /* пустое дерево*/
				tree = new bin_tree();
				tree->menu_tree();
				delete tree;
				break;
			case 2: /* Загрузить дерево */
				bin_tree::load()->menu_tree();
				break;
				
			case 3:
				system("cls");
				break;
			default:
				std::cout << "Неправильный ввод\n"; 
		
		}
	}
}
