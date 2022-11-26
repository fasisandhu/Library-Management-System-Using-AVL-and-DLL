#include <iostream>
using namespace std;

template <class t>
class avl {
	struct node {
		node()
		{
			left = right = NULL;
		}
		node(t x, node* left1 = NULL, node* right1 = NULL)
		{
			data = x;
			height = 0;
			left = left1;
			right = right1;
		}

		node(t x, int h, node* left1 = NULL, node* right1 = NULL)
		{
			data = x;
			height = h;
			left = left1;
			right = right1;
		}

		t data;
		int height;
		node* left, * right;
	};
	node* root;

	///////////////////////////////////////////////////////////

	node* search(int key, node* r)
	{

		if (r == NULL)
		{
			return NULL;
		}
		else if (r->data == key)
		{
			return r;
		}
		else if (r->data > key)
		{
			return search(key, r->left);
		}
		else if (r->data < key)
		{
			return search(key, r->right);
		}

	}


public:
	avl()
	{
		root = NULL;
	}
	///////////////////////////////////////////////////////////

	avl(const avl& obj)
	{
		node* r = obj.root;
		duplicate(root, r);
	}
	///////////////////////////////////////////////////////////

	~avl()
	{
		destory(root);
	}
	void destory(node*& r)
	{
		if (r)
		{
			destory(r->left);
			destory(r->right);
			delete r;
		}
	}
	void duplicate(node* r, node*& obj)
	{
		if (r)
		{
			obj = new node(r->data, r->height);
			duplicate(r->left, obj->left);
			duplicate(r->right, obj->right);
		}
	}
	///////////////////////////////////////////////////////////


	int getheight(node* r)
	{

		if (r == NULL)
		{
			return -1;
		}
		else
		{
			int l = getheight(r->left);
			int ri = getheight(r->right);
			return 1 + max(l, ri);
		}
	}

	void insert(t d)
	{
		insert(root, d);
	}

	void insert(node*& r, t d)
	{
		if (r == NULL)
		{
			r = new node(d);
		}
		else if (r->data == d)
		{
			insert(r->right, d);
		}
		else if (r->data > d)
		{
			insert(r->left, d);
		}
		else if (r->data < d)
		{
			insert(r->right, d);
		}
		balance(r);
	}

	int balancingfactor(node* r)
	{
		return getheight(r->right) - getheight(r->left);
	}
	void rightrotate(node*& r)
	{
		node* o = r->left->right;
		node* y = r->left;
		y->right = r;
		r->left = o;
		y->height = getheight(y);
		r->height = getheight(r);
		r = y;
	}
	void leftrotate(node*& r)
	{
		node* o = r->right->left;
		node* y = r->right;
		y->left = r;
		r->right = o;
		y->height = getheight(y);
		r->height = getheight(r);
		r = y;
	}
	void dbleftrightrotate(node*& r)
	{
		leftrotate(r->left);
		rightrotate(r);
	}
	void dbrightleftrotate(node*& r)
	{
		rightrotate(r->right);
		leftrotate(r);
	}
	void balance(node*& r)
	{
		if (!r)
			return;
		if (balancingfactor(r) < -1)//left
		{
			if (getheight(r->left->left) >= getheight(r->left->right))//leftleft
			{
				rightrotate(r);
			}
			else
				dbleftrightrotate(r);
		}
		else if (balancingfactor(r) > 1)
		{
			if (getheight(r->right->right) >= getheight(r->right->left))
			{
				leftrotate(r);
			}
			else
				dbrightleftrotate(r);
		}
		r->height = getheight(r);
	}

	///////////////////////////////////////////////////////////

	bool search(t key)
	{
		if (search(key, root))
		{
			return true;
		}
		else
			return false;
	}

	///////////////////////////////////////////////////////////

	void print()
	{
		cout << "in-order" << endl;
		inorder(root); cout << endl;

		cout << "pre-order" << endl;
		preorder(root); cout << endl;

		cout << "post-order" << endl;
		postorder(root); cout << endl;
	}
	void inorder(node* r)
	{
		if (r)
		{
			inorder(r->left);
			cout << r->data << " ";
			inorder(r->right);
		}
	}

	void preorder(node* r)
	{
		if (r)
		{
			cout << r->data << " ";
			preorder(r->left);
			preorder(r->right);
		}
	}

	void postorder(node* r)
	{
		if (r)
		{
			postorder(r->left);
			postorder(r->right);
			cout << r->data << " ";
		}
	}

	void printwithheight()
	{
		printheight(root);
		cout << endl;
	}
	void printheight(node* r)
	{
		if (r)
		{
			cout << r->data << "-" << r->height << "  ";
			printheight(r->left);
			printheight(r->right);
		}
	}
	///////////////////////////////////////////////////////////

	void deletenode(node*& r, t& el)
	{
		if (!r)
			return;
		if (r->data > el)
		{
			deletenode(r->left, el);
		}
		else if (r->data < el)
		{
			deletenode(r->right, el);
		}
		else if (r->right != NULL && r->left != NULL)
		{
			r->data = prede(r->left);
			deletenode(r->left, r->data);
		}
		else
		{
			node* p = r;
			if (r->right == NULL)
				r = r->left;
			else
				r = r->left;
			delete p;
		}

		balance(r);


	}
	void deletenode(t d)
	{
		deletenode(root, d);
	}

	t prede(node* r)
	{
		while (r->right)
		{
			r = r->right;
		}
		return r->data;
	}

	///////////////////////////////////////////////////////////

	bool isavl(avl tree)
	{
		return chkforavl(tree.root);
	}

	bool chkforavl(node* r)
	{
		if (r)
		{
			int n = balancingfactor(r);
			if (!(n <= 1 && n >= -1))
				return false;
			chkforavl(r->left);
			chkforavl(r->right);
		}
		return true;
	}

	///////////////////////////////////////////////////////////

	t min()
	{
		return min(root);
	}
	t min(node* r)
	{
		if (r)
		{
			if (r->left == NULL)
			{
				return r->data;
			}
			else
				return min(r->left);
		}
	}

	t min2nd()
	{
		return min2nd(root);
	}
	t min2nd(node* r)
	{
		if (r)
		{
			if (r->left->left == NULL)
			{
				return r->data;
			}
			else
				return min2nd(r->left);
		}
	}

	t min3rd()
	{
		return min3rd(root);
	}
	t min3rd(node* r)
	{
		if (r)
		{
			if (r->left->left->left == NULL)
			{
				return r->data;
			}
			else
				return min3rd(r->left);
		}
	}

	///////////////////////////////////////////////////////////
	int numofnodes()
	{
		int c = 0;
		numofnodes(root, c);
		return c;
	}
	void numofnodes(node* r, int& c)
	{
		if (r)
		{
			c++;
			numofnodes(r->left, c);
			numofnodes(r->right, c);
		}
	}



	void itprint()
	{
		cout << "Iterative PreOrder" << endl;
		node** arr = new node * [numofnodes()];
		int c = -1; c++;
		arr[c] = root;
		while (c != -1)
		{
			node* n = arr[c]; c--;
			cout << n->data << " ";
			if (n->right)
			{
				c++;
				arr[c] = n->right;
			}
			if (n->left)
			{
				c++;
				arr[c] = n->left;
			}
		}cout << endl;
	}


};

///////////////////////DOUBLYLINKEDLIST///////////////////////////////////////

template <class T>
struct DLLNode {
	DLLNode()
	{
		next = prev = NULL;
	}
	DLLNode(T& el, DLLNode* p = NULL, DLLNode* n = NULL)
	{
		next = n; prev = p; data = el;
	}
	T data;
	DLLNode* next;
	DLLNode* prev;

};


template <class T>
class DLList
{
	friend struct DLLNode<T>;
public:
	DLLNode<T>* head, * tail;
public:
	DLList()
	{
		head = tail = NULL;
	}
	void insetatHead(T el)
	{
		if (head == 0)
		{
			head = new DLLNode<T>(el, 0, 0);
			tail = head;
		}
		else
		{
			DLLNode<T>* temp = head;
			head = new DLLNode<T>(el, 0, head);
			temp->prev = head;
		}
	}
	void insertatEnd(T el)
	{
		if (head == 0)
		{
			head = new DLLNode<T>(el, 0, 0);
			tail = head;
		}
		else
		{
			DLLNode<T>* temp = tail;
			tail = new DLLNode<T>(el, tail, 0);
			temp->next = tail;
		}
	}
	void returnnode(T d)
	{
		//if (head->data == d)
		{
			//h = head;
			//return head;
			//return h;
		}
		//return head;

	}
	void print()
	{
		DLLNode<T>* temp;
		for (temp = head; temp != 0; temp = temp->next)
		{
			cout << temp->data << " ";
		}
		cout << endl;
	}
	void deleteatStart()
	{
		if (head == tail)
		{
			delete head; head = tail = 0;
		}
		else if (head == 0)
		{
			//do nothing
		}
		else
		{
			DLLNode<T>* temp = head->next;
			temp->prev = 0;
			delete head;
			head = temp;
		}
	}
	void deleteatTail()
	{
		if (head == tail)
		{
			delete head; head = tail = 0;
		}
		else if (head == 0)
		{
			//do nothing
		}
		else
		{
			DLLNode<T>* temp = tail->prev;
			temp->next = 0;
			delete tail;
			tail = temp;
		}
	}
	~DLList()
	{
		if (head != 0)
		{
			while (head)
			{
				DLLNode<T>* p = head->next;
				delete head;
				head = p;
			}
		}
	}
	//qs 2
	void insertsorted(T el)
	{
		if (head == 0)
		{
			insetatHead(el);
		}
		else
		{
			//find the req postion
			DLLNode<T>* temp;
			for (temp = head; !(temp->data > el); temp = temp->next)
			{
			}
			temp = temp->prev;
			DLLNode<T>* nodenew = new DLLNode<T>(el, temp, temp->next);
			temp->next = nodenew;
			nodenew->next->prev = nodenew;

		}
	}

	void deleteduplicates()
	{
		DLLNode* temp = head;
		while (temp->next != 0)//no need to go tail should stop one step before tail
		{
			if (temp->data == temp->next->data)
			{
				if (temp == head)
				{
					deleteatStart();
					temp = head;
				}
				else
				{
					DLLNode<T>* temp2 = temp;
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
					temp = temp->next;
					delete temp2;
				}
			}
			else
			{
				temp = temp->next;
			}
		}
	}

	void swapNodes(int n)
	{
		DLLNode<T>* start, * end;
		DLLNode<T>* temp = head;
		for (int i = 1; i < n; i++)
		{
			temp = temp->next;
		}
		start = temp;
		temp = tail;
		for (int i = 1; i < n; i++)
		{
			temp = temp->prev;
		}
		end = temp;
		DLLNode<T>* tt, * tt1, * tt2;
		tt1 = start->prev;
		tt2 = end->prev;
		tt = new DLLNode;
		tt->data = start->data;
		tt->next = start->next;
		tt->prev = start->prev;
		start->next = end->next;
		start->prev = end->prev;
		start->data = end->data;
		end->next = tt->next;
		end->prev = tt->prev;
		end->data = tt->data;
		tt1->next = end;
		tt2->next = start;
	}

	void unionlist(DLList l2, DLList Uni)
	{
		DLLNode<T>* temp;
		for (temp = head; temp != 0; temp = temp->next)
		{
			Uni.insertatEnd(temp->data);
		}
		for (temp = l2.head; temp != 0; temp = temp->next)
		{
			Uni.insertatEnd(temp->data);
		}
		Uni.print();

	}

};

class record {
public:
	int issn;
	string title;
	DLList<string> authors;
	int no_of_refer;
	int no_of_copies;

	bool operator ==(record& obj)
	{
		return issn == obj.issn;
	}
};

class index {
public:
	int issn;
	DLLNode<record>* ptr;
	bool operator <(index& obj)
	{
		return issn < obj.issn;
	}

	bool operator >(index& obj)
	{
		return issn > obj.issn;
	}

	bool operator ==(index& obj)
	{
		return issn == obj.issn;
	}
};

int main()
{
	avl<index> obj;
	DLList<record> obj1;
	record o;
	o.issn = 1234;
	o.no_of_copies = 12;
	o.no_of_refer = 21;
	o.title = "test book";
	o.authors.insetatHead("test author");
	o.authors.insetatHead("test author1");
	obj1.insetatHead(o);
	index ind; ind.issn = o.issn;
	//obj1.head;
	//obj1.print();
	//obj1.returnnode(o);
	//obj1.returnnode()
	//obj.insert(ind);
	ind.ptr = obj1.head;
	obj.insert(ind);




	system("pause");

	return 0;
}