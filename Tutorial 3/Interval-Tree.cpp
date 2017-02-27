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

Node * successor(Node * n)
{
	Node * t = n;
	while (t->left != NULL)
		t = t->left;
	return t;
}

//Function to update Max value after deletion
Node * Max_update (Node * n)
{
	if(n== NULL) return n;
	Max_update(n->left);
	Max_update(n->right);

	if (n->right != NULL)
	{
		if (n->left != NULL )
			n->Max = max(n->left->Max, n->right->Max , n->i.UB);
		else n->Max = max(n->right->Max , n->i.UB);
	}
	else
	{
		if (n->left != NULL )
			n->Max = max(n->left->Max , n->i.UB);
		else n->Max = n->i.UB;
	}
	return n;
}

Node * delete_node (Node * n,interval x)
{
	Node * temp;

	if(n == NULL)
	{
		return n;
	}

	if (x.LB < n->i.LB) 
	{
		n->left = delete_node(n->left,x);
		//If low of current node is higher node to be
		// deleted is in left subtree
	}
	else if (x.LB > n->i.LB)
	{
		n->right = delete_node(n->right,x);
		//If low of current node is lower node to be
		// deleted is in right subtree
	}

	//Node to be deleted has been found
	else
	{
		//If the node has only left child
		if(n->left == NULL && n->right != NULL)
		{
			temp = n->right;
			n = NULL;
			return temp;
		}

		//If the node has only right child
		else if(n->right == NULL)
		{
			temp = n-> left;
			n = NULL;
			return temp;
		}

		//If the node has both children
		//we find it's successor in inorder traversal and replace it
		temp = successor(n->right);
		n->i =temp->i;
		n->right = delete_node(n->right,temp->i);

		n = Max_update (n);
		return n;
	}

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
    interval ints[] = {{15, 20}, {10, 30}, {17, 19}, {5, 20}, {12, 15}, {30, 40} };
    int n = sizeof(ints)/sizeof(ints[0]);
    Node *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert_node(root, ints[i]);
 
    cout << "Inorder traversal of Interval Tree is\n";
    traverse(root);
      
 	interval   x = make_interval(14, 16);
 
    cout << "\nSearch for interval [" << x.LB << "," << x.UB << "]";
    interval res = search(root, x);
    if (res == Z)
        cout << "\nNo Overlapping Interval";
    else
        cout << "\nOverlaps with [" << res.LB << ", " << res.UB << "]";
    x = make_interval(21, 23);
 
    cout << "\nSearch for interval [" << x.LB << "," << x.UB << "]";
    res = search(root, x);
    if (res == Z)
        cout << "\nNo Overlapping Interval";
    else
        cout << "\nOverlaps with [" << res.LB << ", " << res.UB << "]";
   	 x = make_interval(10,30);
    Node * ptr = delete_node(root,x);
    delete ptr;
    traverse(root);
    
    x = make_interval(30,40);
    ptr = delete_node(root,x);
    delete ptr;
    traverse(root);
    return 0;
}