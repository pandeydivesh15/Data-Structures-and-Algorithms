#include <iostream>
using namespace std;

// First, I define a structure named Tree_node. It consists of three pointers.
struct Tree_node
{
	int data;
	int key;
	struct Tree_node* parent = NULL;
	struct Tree_node* l_child = NULL;
	struct Tree_node* r_child = NULL;
}*root = NULL;

bool insert_into_bst(int _data, int _key){
	// Firstly some memory is allocated for the new data.
	struct Tree_node* ptr = (Tree_node*)malloc(sizeof(Tree_node));
	ptr->data = _data;
	ptr->key = _key;

	struct Tree_node* y = NULL;
	struct Tree_node* x = root;

	while(x!=NULL){
		// While traversing the tree, if some node's key comes out to be equal to the new key
		// value, then this new data can't be inserted into the BST.
		if (x->key == _key)
		{
			return false;
		}
		// y represents parent of node x
		y = x;
		if(_key < x->key)
			x = x->l_child;
		else
			x = x->r_child;
	}
	// Set the parent of new node(to be inserted) equal to y
	ptr->parent = y;
	if(!y)
		// if node to be inserted is the very first node of BST, then that node must become root
		root = ptr;
	else if(_key < y->key)
		y->l_child = ptr;
	else
		y->r_child = ptr;
	return true;
}

struct Tree_node* iterative_BST_search(int _key){
	//This function searches for a specific key value in the BST.
	struct Tree_node* ptr = root;
	while(ptr!=NULL && ptr->key != _key){
		if(ptr->key > _key)
			ptr = ptr->l_child;
		else
			ptr = ptr->r_child;
	}
	// If query key is not found, then while loop will only terminate when ptr becomes 
	// equal to NULL. This ensures that a NULL pointer is returned when the search fails. 
	return ptr;
}

void replace_node(struct Tree_node* initial_node, struct Tree_node* new_node){
	// This function replaces a node from BST with some new node.

	if(initial_node->parent == NULL)
		root = new_node;
	else if(initial_node == (initial_node->parent)->l_child)
		(initial_node->parent)->l_child = new_node;
	else
		(initial_node->parent)->r_child = new_node;

	if(new_node)
		new_node->parent = initial_node->parent;

}

struct Tree_node* minimum_key_node(struct Tree_node* ptr){
	// Finds the node with minimum key value in a specific subtree, subtree is decided by ptr.
	while(ptr->l_child)
		ptr = ptr->l_child;
	return ptr;
}

bool _delete(int _key){
	//For deleting, we first have to ensure that query key is present in the BST.
	struct Tree_node* ptr = iterative_BST_search(_key);
	//If NULL is returned, then no deletion is performed.
	if(!ptr)
		return false;
	//First case, if left child is not present, then simply replace node by its right child.
	if (ptr->l_child == NULL){
		replace_node(ptr,ptr->r_child);
	}
	//Second case, if right child is not present, then simply replace node by its left child.
	else if(ptr->r_child == NULL){
		replace_node(ptr,ptr->l_child);
	}
	// This case will contain two sub cases.
	else{
		struct Tree_node* temp = minimum_key_node(ptr->r_child);
		// If temp is not the right child of node to be deleted, then two replacements have
		// to be made. Else, only one replacement.
		if(temp->parent != ptr){
			replace_node(temp,temp->r_child);
			temp->r_child = ptr->r_child;
			(temp->r_child)->parent = temp;
		}
		replace_node(ptr,temp);
		temp->l_child = ptr->l_child;
		(temp->l_child)->parent = temp;
	}
	return true;
}

void view_bst(struct Tree_node* ptr, int level){
	// This recursive function shows the Inorder form of tree nodes.(sorted order) 
	 if(!ptr)
	 	return;
	 view_bst(ptr->l_child,level+1);
	 cout<<ptr->data<<"(level:"<<level<<", key: "<<ptr->key<<")\n";
	 view_bst(ptr->r_child,level+1);
	 return;
}

int main()
{
	int data;
	int choice,key;
	// Initial sample tree. 
	// insert_into_bst(1212,12);
	// insert_into_bst(12122,5);
	// insert_into_bst(122,18);
	// insert_into_bst(12,2);
	// insert_into_bst(112,9);
	// insert_into_bst(1542,15);
	// insert_into_bst(13332,19);
	// insert_into_bst(1222,17);

	struct Tree_node* check = NULL;
	do{
		cout<<"Enter your choice...\n"<<
			"1.Insert element in BST\n"<<
			"2.Search an item\n"<<
			"3.View BST(Inorder Traversal)"<<
			"4.Exit\n";
		cin>>choice;

		switch(choice){
			case 1: cout<<"Enter data?\n";
					cin>>data;
					cout<<"Enter key?\n";
					cin>>key;
					if(!insert_into_bst(data,key))
						cout<<"That key value exists. Try again\n";
					break;

			case 2: cout<<"Enter query key?\n";
					cin>>key;
					check = iterative_BST_search(key);
					if(!check)
						cout<<"No data found\n";
					else
						cout<<"Found data: "<<check->data<<'\n';
					break;

			case 3: view_bst(root,0);
					break;

			case 4: return 0;

			case 5: cout<<"Enter query key?\n";
					cin>>key;
					if(!_delete(key))
						cout<<"No such key found.\n";
					break;

			default: cout<<"Enter correct no.\n"; break;
		}

	}while(true);

	
	return 0;
}