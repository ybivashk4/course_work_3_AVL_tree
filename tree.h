#include <string>
using namespace std;
class Node;
class bin_tree;
class Node{
	private:
		char diff; // Разница высот левого и правого поддерева
		char height; // Расчитывается, получить всегда можно
		bin_tree *owner; // Задаётся в конструкторе, получить можно всегда
		double key; // Только задавать, изменить нельзя
	public:
		Node *left;
		Node *right;
		Node * parent;
		bool visited;// Для обхода
		
		char get_diff(){
			if (right && left)
				return right->height - left->height; 
			else if (left)
				return 0 - left->height;
			else if(right)
				return right->height - 0;
			else
				return 0;
		}
		
		char set_diff(){
			if (right && left)
				diff = right->height - left->height; 
			else if (left)
				diff = 0 - left->height;
			else if(right)
				diff = right->height - 0;
			else
				diff = 0;
		}
		
		void calc_height(){
			if (right && left)
				height = right->height>left->height? right->height + 1 : left->height + 1; 
			else if (left)
				height = left->height+1;
			else if(right)
				height = right->height+1;
			else
				height = 1;
		}
		char get_height(){ return height; }
		double get_key(){ return key; }
		bin_tree * get_owner(){ return owner; }
		
		void out();
		Node(double key){
			left = NULL; right = NULL; visited = 0; parent = NULL;
			this->key = key; owner = NULL; diff = 0; height = 1;
			}
			
		Node(double key, bin_tree * owner){
			left = NULL; parent = NULL;
		    right = NULL; visited = 0; this->key = key;
		    this->owner = owner; diff = 0; height = 1;
		  }
		~Node(){};
};

class bin_tree {
	public:
		Node *root;
		int count; // кол-во узлов, увеличивается при добавлении в дерево, уменьшается при удалении  
		
		static void out_menu_tree();
		static void out_menu();
		static void menu();
		static bin_tree * load();
		
		void menu_tree();
		void dfs(Node * a, char flag, string path="", double * sum = NULL);
		void dfs_support(Node * a);
		void out();
		void insert(Node * node, double key);
		Node * find(Node * node, double key); // Доступ к узлу по ключу
		Node * remove(Node * node, double key);
		Node * rotate_left(Node * node);
		Node * rotate_right(Node * node);
		Node * balance(Node * node);
		void save();
		void sum_tree();
		Node * find_min(Node * node = NULL);
		Node * remove_min(Node * node = NULL);
		Node * find_max(Node * node = NULL);
		double find_avg();
		
		// Сравнение без учёта ключей
		void cmp_struct(bin_tree * tree){
			cout << "Высота загруженного дерева = " << (int)(tree->root->get_height())
			 << "\t" << "Высота исходного дерева = " << (int)(root->get_height()) << "\n";
			cout << "Количество узлов загруженного дерева = " << tree->count
			 << "\t" << "Количество узлов исходного дерева = " << count << "\n";
		}
		
		// Сравнение с учётом ключей
		void cmp_keys(bin_tree * tree){
			cout << "Максимальный узел загруженного дерева = " << tree->find_max()->get_key()
			 << "\t" << "Максимальный узел исходного дерева = " << find_max()->get_key() << "\n";
			cout << "Минимальный узел загруженного дерева = " << tree->find_min(tree->root)->get_key()
			 << "\t" << "Минимальный узел исходного дерева = " << find_min(root)->get_key() << "\n";
			cout << "Среднее значение по узлам у загруженного дерева = " << tree->find_avg()
			 << "\t" << "Среднее значение по узлам у исходного дерева = " << find_avg() << "\n";
		}
		

		
		bin_tree() : root(NULL), count(0) {}
		bin_tree(Node * rt) : root(rt), count(1){}
		~bin_tree(){};
};

template<class Type>
void input_check(Type *t);
