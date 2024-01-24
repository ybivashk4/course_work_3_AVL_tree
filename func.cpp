#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include "tree.h"
using namespace std;
ofstream out1;

Node * bin_tree::rotate_left(Node * node){
	Node * b = node->right;
	node->right = b->left;
	if (node->right)
		b->left->parent = node;
	b->left = node;
	b->parent = node->parent;
	b->set_diff();
	node->set_diff();
	if (node == root){
		root = b;
		b->parent = NULL;
	}else if (node->parent->right == node){
		node->parent->right = b;	
	}else if (node->parent->left == node)
		node->parent->left = b;
	node->parent = b;
	node->calc_height();
	b->calc_height();
	b->set_diff();
	node->set_diff();
	return b;
}

Node * bin_tree::rotate_right(Node * node){
	Node * b = node->left;
	node->left = b->right;
	if (node->left)
		b->right->parent = node;
	b->right = node;
	b->parent = node->parent;
	b->set_diff();
	node->set_diff();
	if (node == root){
		root = b;
		b->parent = NULL;
	}else if (node->parent->right == node){
		node->parent->right = b;	
	}else if (node->parent->left == node)
		node->parent->left = b;
	node->parent = b;	
	node->calc_height();
	b->calc_height();
	b->set_diff();
	node->set_diff();
	return b;
}

Node * bin_tree::balance(Node * node){
	node->set_diff();
	if (node->get_diff() == 2){
		node->right->set_diff();
		if (node->right->get_diff() < 0)
			node->right = rotate_right(node);
		return rotate_left(node);
	}else if (node->get_diff() == -2){
		node->left->set_diff();
		if (node->left->get_diff() > 0)
			node->left = rotate_left(root);
		return rotate_right(node);
	}
	return node;
}



// Старт с корня 
void bin_tree::insert(Node * node, double key){
	if (node){
		Node * temp = node;
		if (fabs(node->get_key() - key) <= 0.00001){
			return;
		}else if (node->get_key() < key){
			if (node->right){
				temp = node;
				insert(node->right, key);
				node->calc_height();
				this->balance(node);
			}
				
			else{
				Node * new_node = new Node(key, this);
				new_node->parent = temp;
				node->right = new_node;
				count++; // + элемент
				node->calc_height();
				return;
			}
		}else{
			if (node->left){
				temp = node;
				insert(node->left, key);
				node->calc_height();
				this->balance(node);
			}
			else{
				Node * new_node = new Node(key, this);
				new_node->parent = temp;
				node->left = new_node;
				count++; // + элемент
				node->calc_height();
				return;
			}
		}
	}else{
		root = new Node(key);
		count++;
		return;
	}

}

Node * bin_tree::find(Node * node, double key){
	if (fabs(node->get_key() - key) <= 0.000001)
		return node;
	else if (node->get_key() < key){
		if (!node->right)
			return NULL;
		find(node->right, key);
	}
	else{
		if (!node->left)
			return NULL;
		find(node->left, key);
	}
}


Node * bin_tree::find_min(Node * node){
	Node * temp;
	if (node)
		temp = node;
	else
		temp = root;
	while (temp->left)
		temp = temp->left;
	return temp;
}

Node * bin_tree::find_max(Node * node){
	Node * temp;
	
	if (node)
		temp = node;
	else
		temp = root;
		
	while (temp->right)
		temp = temp->right;
		
	return temp;
}


Node * bin_tree::remove_min(Node * node){
	if (node){
		if (!node->left)
			return node->right;
	
		node->left = remove_min(node->left);
		return balance(node);
	}else{
		if (!root->left)
			return root->right;
	
		root->left = remove_min(root->left);	
		return balance(root);
	}

	
}

// Начинать с корня
Node * bin_tree::remove(Node * node, double key){
	if (!node) return 0;
	if (key < node->get_key())
		node->left = remove(node->left, key);
	else if (key > node->get_key()){
		node->right = remove(node->right, key);
	}else if (fabs(node->get_key() - key) < 0.0001 && node != root){
		Node * l = node->left;
		Node * r = node->right;
		if (l)
			l->parent = node->parent;
		if (r)
			r->parent = node->parent;
		delete node;
		count--;
		if(l)
			l->calc_height();
		if(r)
			r->calc_height();
		
		if (!r) return l;
		Node * min = find_min(r);
		min->right = remove_min(r);
		min->left = l;
		min->calc_height();
		return balance(min);
	}else if (fabs(node->get_key() - key) < 0.0001){
		Node * l = node->left;
		Node * r = node->right;
		if (!l && !r){
			count--;
			delete root;
			root = NULL;
			return NULL;
		}
		if (l)
			l->parent = node->parent;
		if (r)
			r->parent = node->parent;
			
		delete node;
		count--;
		if(l)
			l->calc_height();
		else if(r)
			r->calc_height();
		else if(l && r)
			l->calc_height(), r->calc_height();
		
		Node * min = find_min(r);
		min->right = remove_min(r);
		min->left = l;
		root = min;
		
		if (l){
			min->left->calc_height();
		}if (min->right){
			min->right->calc_height();
		}
		min->calc_height();
		return balance(min);
	}
	return balance(node);
}

// сброс visited после dfs
void bin_tree::dfs_support(Node * a){
	static int cnt = 0;
	if (a->visited){
		a->visited = 0;
		cnt++;
	}
	if (cnt != count && a->left)
		dfs_support(a->left);
	if(cnt != this->count && a->right)
		dfs_support(a->right);
}

// обход всех узлов дерева и применение на них функции f
void bin_tree::dfs(Node * a, char flag, string path, double * sum){
	if (a){
		dfs_support(root);
		static int cnt = 0;
		if (!a->visited){
			switch (flag){
				case 1:
					a->out();
					break;
				case 2:
					out1 << a->get_key() << " ";
					break;
				case 3:
					*sum += a->get_key();
					break;
			}
			
			a->visited = 1;
			cnt += 1;
		}
		if (cnt != this->count && a->left)
			dfs(a->left, flag, path, sum);
		if(cnt != this->count && a->right)
			dfs(a->right, flag, path, sum);

		dfs_support(root);
			
			
	}

}

double bin_tree::find_avg(){
	double sum;
	dfs(root, 3, "", &sum);
	return sum / count;
}


void Node::out(){
	cout << "---------------------------------\n";
	cout.width(4);
	if (!this)
		cout << "Pointer error\n";
	else if (this->left && this->right)
		cout << this->get_key() << "\t" << this->left->get_key() << "\t" << this->right->get_key() << "\t" << (parent ? parent->get_key() : 0) << "\n";
	else if (this->left)
		cout << this->get_key() << "\t" << this->left->get_key() << "\t" << "0000" << "\t" << (parent ? parent->get_key() : 0)<< "\n";
	else if (this->right)
		cout << this->get_key() << "\t" << "0000" << "\t" << this->right->get_key() << "\t" << (parent ? parent->get_key() : 0)<< "\n";
	else
		cout << this->get_key() << "\t" << "0000" << "\t" << "0000"<< "\t" << (parent ? parent->get_key() : 0) <<"\n";
	cout << "---------------------------------\n\n";
}



void bin_tree::out(){
	cout.width(4);
	cout << "---------------------------------\n";
	cout << "self\t" << "left\t" << "right\t" << "parent\n";
	cout << "---------------------------------\n";
	dfs(this->root, 1); 
	cout << "Количество узлов = " << count << "\n";
}

void bin_tree::save(){
	cout << "Если хотите ввести название нажмите 1 иначе 0\n";
	int i=0;
	string path;
	input_check(&i);
	if (i){
		while (std::cin >> path, std::cin.fail()){
			cin.clear();
			cin.ignore(500, '\n');
			cout << "Неправильный ввод\n";
		}
		path = "saves/" + path;
	}else
		path = "saves/save.txt";
	out1.open(path);
	if (out1.is_open()){
		dfs(root, 2, path);	
		out1.close();
	}
}

// Возвращает указатель на загруженный объект
bin_tree * bin_tree::load(){
	cout << "Если хотите ввести название нажмите 1 иначе 0\n";
	int i=0;
	string path;
	input_check(&i);
	if (i){
		
		while (std::cin >> path, std::cin.fail()){
			cin.clear();
			cin.ignore(500, '\n');
			cout << "Неправильный ввод\n";
		}
		
		
		path = "saves/" + path;
	}else{
		path = "saves/save.txt";
	}
	
	bin_tree * tree = NULL;
	tree = new bin_tree();
	double key;
	ifstream in(path);
	if (in.is_open()){
	
		while(in >> key){
			tree->insert(tree->root, key);
		}
	
	}
	in.close();
	return tree;
}

void bin_tree::sum_tree(){
		cout << "Загрузите дерево, с которым будет сложение\n";
		cout << "Если хотите ввести название нажмите 1 иначе 0\n";
		int i=0;
		string path;
		input_check(&i);
		if (i){
			while (std::cin >> path, std::cin.fail()){
				cin.clear();
				cin.ignore(500, '\n');
				cout << "Неправильный ввод\n";
			}
			path = "saves/" + path;
		}else
			path = "saves/save.txt";
		double key;
		ifstream in(path);
		if (in.is_open()){	
			while(in >> key){
				insert(root, key);
			}
		}
		in.close();
}

/*
1 тест
1
1
1
1
2
1
3
1
4
1
5
1
6
1
7
1
8
1
9
1
10

2 тест
1
1
10
1
9
1
8
1
7
1
6
1
5
1
4
1
3
1
2
1
1

3 тест
1
1
2
1
4
1
6
1
8
1
10
1
1
1
3
1
5
1
7
1
9
*/
