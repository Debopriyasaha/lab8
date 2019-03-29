//binary search tree
#include<iostream>
using namespace std;

//the node class
	class Node{
	public:
		int data;
		Node* l = NULL;
		Node* r = NULL;
		Node* p = NULL;

//constructor
	Node(int val){
	data = val;
	}
	};

	class BST{
	public:
		Node* root;
		int count = 0;

//constructor
	BST(){
	root = NULL;
	}
//things we have to do now
//insert
	void insert(int value){
//if tree is null insert and leave
	if(root==NULL){
	root = new Node(value);
	count++;
	return;
	}
	insertHelper(root, value);
	count++;
}

	void insertHelper(Node* curr, int value){
//move accordingly and check
	if(curr->data > value){
//if the next position is NULL, insert
	if(curr->l==NULL){
	curr->l = new Node(value);
	curr->l->p = curr;
	return;
}
//else recursion
		else{insertHelper(curr->l, value);}
	}
		else{
//if the next position is NULL then insert
			if(curr->r==NULL){
			curr->r = new Node(value);
			curr->r->p = curr;
			return;
		}
//otherwise go for recursion
		else {insertHelper(curr->r, value);}
	}

}

	void display(){
	display2(root);
	cout<<"\b "<<endl;
	}

//inorder display...
	void display2(Node* curr){
//base condition
	if(curr == NULL){return;}
//display left
	display2(curr->l);
//display current
	cout << curr->data << ",";
//display right
	display2(curr->r);
	}




//search
	Node* search(int val){
	return search2(val, root);
}

Node* search2(int val,Node* curr){
//if tree is empty or reached the end of tree or value found
	if(curr == NULL || curr->data == val){return curr;}
		else if(curr->data > val){return search2(val, curr->l);}
		else{return search2(val, curr->r);}
	}

//find min.
	Node* fmin(int val){
	Node* curr = search(val);
		if(root==NULL||curr==NULL){return NULL;}
		return fmin2(val,curr);
	}

	Node* fmin2(int val, Node* curr){
		if(curr->l==NULL){return curr;}
		else{fmin2(val, curr->l);}
}

//count
	int Count(){
	return count;
}

//delete
	void Delete(int val){
	Node* curr = search(val);
//if node doesn't exist
	if(curr==NULL){
	cout << "This value doesn't exist in the tree.\nTry 	again!"<<endl;
}
	else{
	count--;
//if it has only one kid
	if(curr->l&&curr->r==NULL||curr->l==NULL&&curr->r){
//if left child exist
	if(curr->l&&curr->r==NULL){
	Node* temp = curr->l;
//if current is root
	if(curr==root){root=temp;}
	else{
//wether curr is left child or right one
	if((curr->data)<(curr->p->data)){
	curr->p->l=temp;}

	else{curr->p->r=temp;}
	}
	temp->p=curr->p;
}
//if right child exist
	else{
	Node* temp = curr->r;
//if current is root
	if(curr==root){root=temp;}
	else{
//if curr is left child or right one
	if((curr->data)<(curr->p->data)){
	curr->p->l=temp;}
	else{curr->p->r=temp;}
	}
	temp->p=curr->p;
	} 
	delete curr;
	return;
}
//if it has 2 children
	if(curr->l&&curr->r){
//go for inorder succesor
	Node* temp = fmin(curr->r->data);
	curr->data = temp->data;
//now remove previous links
//note:- The minimum may have a right child
	if(temp->r){
	temp->p->l=temp->r;
	temp->r->p=temp->p;
}
		else{
		temp->p->l=NULL;
	}
	delete temp;
	return;
}
//if it is impotent
	if(curr->l==NULL&&curr->r==NULL){
//if current is root
	if(curr==root){root=NULL;}
//remove previous links
	if((curr->data)<(curr->p->data)){
	curr->p->l=NULL;
}
		else{curr->p->r=NULL;}
		delete curr;
		}
	}
}

//the function to print all values in between the range 
	void printrange(int low,int high){ 
	printrange2(root,low,high);
	}
	void printrange2(Node* curr,int low,int high){
//base condition
	if(curr == NULL){return;}
//display left
	printrange2(curr->l,low,high);
//display current if within range
	if((curr->data)>=low && (curr->data)<=high){cout << 	curr->data << ",";}
//display right
	printrange2(curr->r,low,high);
}

//the function to count nodes with values within the range
	int rangecount(int low,int high){ 
	return rangecount2(root,low,high);
}

	int rangecount2(Node* curr,int low,int high){
//base case
	if(!curr){return 0;}
//special Optional case for improving efficiency
	if(curr->data == high && curr->data == low){return 1;}

//if current node is in range, then include it in count and recur for left and right children of it
	if((curr->data)<=high && (curr->data)>=low)
	{return 1 + rangecount2(curr->l,low,high) + 		rangecount2(curr->r,low,high);}

//if current node is smaller than low, then recur for right child
	else if((curr->data)<low){return rangecount2(curr-	>r,low,high);}

// else recur for left child
	else{return rangecount2(curr->l,low,high);}
}

//the function for height of the tree
	int height(){
	return height2(root);
}

	int height2(Node* curr){
//base case
	if(!curr){return 0;}

//create two parameters for l and r
	int lh = height2(curr->l);
	int rh = height2(curr->r);

//compare the levels from left and right subtree and use larger one
	if(lh>rh){return (lh+1);}
		else {return (rh+1);}
	}
};


	int main(){
//create a tree
	BST b1;

//insert in tree and checking with display
b1.insert(3);
b1.insert(6);
b1.insert(2);
b1.insert(5);
b1.insert(4);
b1.insert(1);
b1.insert(9);
b1.insert(7);
b1.insert(8);
b1.display();

Node* find = b1.search(2);
if (find!=NULL){cout << find->data << endl;}
else{cout << "The number is not there in the tree" << endl;} 

Node* p = b1.fmin(6);
cout << p-> data << endl;

int r = b1.Count();
cout << "No of nodes = " << r << endl;
b1.display();

b1.Delete(3);
b1.display();

cout << "Now comes range search."<<endl;
cout << "Give the ranges."<<endl;
int x,y;
cin >> x >> y;
cout << "Items in between the range:-"<<endl;
b1.printrange(x,y);
cout << endl <<"Number of items in the range = " << b1.rangecount(x,y) <<endl;
cout << "range search over" << endl;

cout << "The height of tree = " << b1.height() << endl;

return 0;
}


