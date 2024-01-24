#include <iostream>
#include <cstdlib>
#include "tree.h"

void bin_tree::out_menu_tree(){
	std::cout << "������� 1, ����� �������� ����\n";
	
	std::cout << "������� 2, ����� ������� ����\n";// ������� ����� Insert-a �� ��������� 
			
	std::cout << "������� 3, ����� ������� � ���� �������\n";		
			
	std::cout << "������� 4, ����� �������� ������ � ���� �� �����\n"; // ��������� ���� � ��� �������� ���� � ��� ������������ ����
	
	std::cout << "������� 5, ����� �������� �������\n"; 
	
	std::cout << "������� 6, ����� ��������� ������ � �������\n";// ��� - ��������� ������ ��� ������ � ������ �������� ��� �������� 
	
	std::cout << "������� 7, ����� �������� ������� ������ � ������ ��� ����� ������\n";// ����� �������
	
	std::cout << "������� 8, ����� �������� ������� ������ � ������ � ������ ������\n";// ������� ���������� ��������  
	
	std::cout << "������� 9, ����� ������� ������ ������\n"; // ������ - ������������ ���-�� ����� ���������� ������ (����� ��������� ��� insert)
	
	std::cout << "������� 10, ����� ������� ���������� ����� ������\n"; 
	
	std::cout << "������� 11, ����� ��������� ������\n"; 
	
	std::cout << "������� 0 ��� ������\n";
}

template<class Type>
void input_check(Type *t){
	while (std::cin >> *t, std::cin.fail()){
		std::cin.clear();
		std::cin.ignore(500, '\n');
		std::cout << "������������ ����\n";
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
			case 1: /* �������� ����*/
				std::cout << "������� ����\n";
				input_check(&key);
				this->insert(this->root, key);
				break;
			case 2: /* ������� ���� */
				std::cout << "������� ���� �� �������� ������ ������� ����\n";
				input_check(&key);
				this->remove(root, key);
				break;
			case 3: /* �����*/
				this->out();
				break;
			case 4: /* ���� �� ����� */
				std::cout << "������� ����\n";
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
				std::cout << "������ = " << (int)this->root->get_height() << "\n";
				break;
			case 10:
				std::cout << "� ������ "<< count << " �����\n";
				break;
			case 11:
				this->save();
				break;
			case 0:
				break;
			default:
				std::cout << "������������ ����\n";
				break;
		}	
			
	}
} 

void bin_tree::out_menu(){
	std::cout << "������� 1, ����� ������� ������ ������\n";
	
	std::cout << "������� 2, ����� ��������� ������\n";
	
	std::cout << "������� 3, ����� �������� �������\n";
	
	std::cout << "������� 0 ��� ������\n";
}

void bin_tree::menu(){
	int menu = 1, i=0;
	
	bin_tree * tree;
	while (menu){
		out_menu();
		input_check(&menu);
		switch(menu){
			case 1: /* ������ ������*/
				tree = new bin_tree();
				tree->menu_tree();
				delete tree;
				break;
			case 2: /* ��������� ������ */
				bin_tree::load()->menu_tree();
				break;
				
			case 3:
				system("cls");
				break;
			default:
				std::cout << "������������ ����\n"; 
		
		}
	}
}
