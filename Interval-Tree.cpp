#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> interval;
#define make_interval make_pair
#define UB second //Upper Bound of Interval
#define LB first  //Lower Bound of Interval

//Interval Tree Node with interval i, maximum of range Max and pointers to left and right subtree
struct Node  
{
	interval i;
	int Max;
	Node *left,*right;
};

//Makes a new node with interval x
Node * make_node (interval x)
{
	Node *temp = new Node;
    temp->i = x;
    temp->Max = x.UB;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

// Function to insert a node with interval x in the tree rooted at root
Node * insert_node (Node *root, interval x)
{
	if(root == NULL)
		return make_node(x);
	//If the tree/subtree is empty then the inserted node becomes the root node

	int l,r;
	l=root->i.LB;
	r=root->i.UB;

    if (l > x.LB)
        root->left = insert_node (root->left, x);
    //If Lower Bound of root is greater than lower bound of 
    //inserted interval then the new node is inserted in
    //the left subtree
 
    else
        root->right = insert_node(root->right, x);
 	//Otherwise the new node will be inserted in the
 	//right subtree

    if (x.UB > root->Max)
        root->Max = x.UB;
 	//If Upper Bound of inserted interval is greater 
 	//than Max of root then Max is updated

    return root;
    //Updated root node is returned
}

//Function to check if two intervals overlap
bool isOverlap (interval i1, interval i2)
{
	if(i2.LB > i1.UB || i2.UB < i1.LB) 
		return false;
	return true;
}

interval Z;

//Search function to return the first interval which overlaps 
// with the query interval
interval search (Node *n,interval x)
{
	if(n == NULL)
	{
		return Z; 
		//Z is a dummy interval when search interval is not found.
	}
	if(isOverlap(n->i,x)) //If overlap occurs return the node
	{
		return n->i;
	}
	if(n->left != NULL)		
	// If left tree is non-empty and within range check left subtree
	{
		if(n->left->Max >= x.LB)
		{
			return search(n->left,x);
		}
	}
	else
	{
		return search(n->right,x);
		//Otherwise check right subtree
	}
}


void delete_node (interval i)
{

} 

void print_node (Node * root)
{
	cout<<" [ " << root->i.LB << ", " << root->i.UB << " ] , Max = <" << root->Max << ">\n";
}
void traverse(Node *root)
{
	if(root == NULL)
	{
		return;
	}

	traverse(root->left);
	print_node(root);
	traverse(root->right);
}


int main()
{
    Z = make_interval(0,-1);   
}