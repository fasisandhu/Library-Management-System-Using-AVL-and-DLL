#include <iostream>
#include <string>
using namespace std;

class record;
class index;

/////////////////////////////AVL/////////////////////////////////////////////
template <class t>
class avl {
	friend class record;
	friend class index;
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

	node* search(t key, node* r)
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

	t searchret(t key, node* r)
	{

		if (r == NULL)
		{
			return key;
		}
		else if (r->data == key)
		{
			key = r->data;
			return key;
		}
		else if (r->data > key)
		{
			return searchret(key, r->left);
		}
		else if (r->data < key)
		{
			return searchret(key, r->right);
		}

	}



	t successor(node* r,t key,t& max)
	{
		if (r)
		{
			if (r->data == key)
			{
				max = r->data;
			}
			else if (r->data < key)
			{
				return successor(r->right, key, max);
			}
			else if (r->data > key)
			{
				max = r->data;
				return successor(r->left, key, max);
			}
		}
		else
			return max;
	}


public:
	t successor(t key,t&max)
	{
		max = successor(root, key, max);
		return max;
	}

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
	t searchret(t key)
	{

		return searchret(key, root);

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
				r = r->right;
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
	friend class record;
	friend class index;
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
	friend class record;
	friend class index;
	friend struct DLLNode<T>;
public:
	DLLNode<T>* head, * tail; 
public:
	DLList()
	{
		head = tail = NULL;
	}

	DLList(const DLList& obj)
	{
		if (obj.head == NULL)
			head = tail =NULL;
		else
		{
			head = tail = new DLLNode<T>(obj.head->data);
			DLLNode<T>* n = obj.head->next;
			DLLNode<T>* h = head;
			while (n)
			{
				h->next = new DLLNode<T>(n->data, h);
				h = h->next;
				n = n->next;
			}
			tail = h;
		}
	}
	const DLList& operator=(const DLList& obj)
	{
		if (obj.head == NULL)
			head = NULL;
		else
		{
			head = tail = new DLLNode<T>(obj.head->data);
			DLLNode<T>* n = obj.head->next;
			DLLNode<T>* h = head;
			while (n)
			{
				h->next = new DLLNode<T>(n->data, h);
				h = h->next;
				n = n->next;
			}
			tail = h;
		}
		return *this;
	}
	void clearit()
	{
		if (head != NULL)
		{
			while (head)
			{
				DLLNode<T>* p = head->next;
				delete head;
				head = p;
			}
		}
	}
	DLLNode<T>* insertafter(DLLNode<T>* obj,T el)
	{
		if (!obj)//insert at tail
		{
			insertatEnd(el);
			return tail;
		}
		else if (obj == head)
		{
			insetatHead(el);
			return head;
		}
		else
		{
			obj = obj->prev;
			DLLNode<T>* temp = obj->next;
			obj->next = new DLLNode<T>(el, obj, temp);
			temp->prev = obj->next;
			return obj->next;
		}
	}
	void deletebynode(DLLNode<T>* n)
	{
		if (n == head)
		{
			deleteatStart();
		}
		else if (n == tail)
		{
			deleteatTail();
		}
		else
		{
			//DLLNode<T>* pre = n->prev;
			//DLLNode<T>* nex = n->nex;
			n->prev->next = n->next;
			//pre->next = n->next;
			n->next->prev = n->prev;
			delete n;
		}
	}
	void insetatHead(T el)
	{
		if (head == NULL)
		{
			head = new DLLNode<T>(el, 0, 0);
			tail = head;
		}
		else
		{
			head = new DLLNode<T>(el, 0, head);
			head->next->prev = head;
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
			tail->next = new DLLNode<T>(el, tail, 0);
			tail=tail->next;
		}
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
		if (head != NULL)
		{
			while (head)
			{
				DLLNode<T>* p = head->next;
				delete head;
				head = p;
			}
		}
	}

};

class record {
	int issn;
	string title;
	DLList<string> authors;
	int no_of_refer;
	int no_of_copies;
public:
	record()
	{
		issn = 0; title = " ";
		no_of_copies = no_of_refer = 0;
	}
	//record(int i,string t,DLList<string>a,int r,int c )
	//{
	//	issn = i; title = t;
	//	no_of_refer = r;
	//	no_of_copies = c; 
	//	authors = a;
	//}
	record(int i, string t,int r, int c)
	{
		issn = i; title = t;
		no_of_refer = r;
		no_of_copies = c;
	}
	void addauthor(string t)
	{
		//authors.insetatHead(t);
		authors.insertatEnd(t);
	}
	~record()
	{
		//nothing dynamic
	}
	void setissn(int i)
	{
		issn = i;
	}
	void settitle(string t)
	{
		title = t;
	}
	void setcopies(int c)
	{
		no_of_copies = c;
	}
	void setrefer(int r)
	{
		no_of_refer = r;
	}
	void setauthors(DLList<string>a)
	{
		if (authors.head == 0)//empty
			authors = a;
		else
		{
			authors.clearit();
			authors = a;
		}

	}
	int getissn()
	{
		return issn;
	}
	int getcopies()
	{
		return no_of_copies;
	}
	int getrefer()
	{
		return no_of_refer;
	}
	string gettile()
	{
		return title;
	}
	DLList<string> getauthors()
	{
		return authors;
	}
	bool operator ==(record& obj)
	{
		return issn == obj.issn;
	}

	friend ostream& operator<<(ostream& out, record& obj);
};
ostream& operator<<(ostream& out, record& obj)
{
	out << "ISSN::" << obj.issn<<endl;
	out << "Title::" << obj.title << endl;
	out << "No of copies::" << obj.no_of_copies << endl;
	out << "No of reference books::" << obj.no_of_refer << endl;
	out << "--List of Authors--" << endl;
	DLLNode<string>* n; n = obj.authors.head;
	while (n)
	{
		out << n->data << endl;
		n = n->next;
	}
	return out;
}

class index {

	int issn;
	DLLNode<record>* ptr;
public:
	friend class avl<index>;
	friend class DLList<record>;
	index()
	{
		issn = 0; ptr = NULL;
	}
	index(int i, DLLNode<record>* p)
	{
		issn = i;
		ptr = p;
	}
	~index()
	{
		
	}
	const index& operator=(const index& obj)
	{
		issn = obj.issn;
		ptr = obj.ptr;
		return *this;
	}
	void setissn(int i)
	{
		issn = i;
	}
	int getissn()
	{
		return issn;
	}
	void setdllnode(DLLNode<record>* p)
	{
		ptr = p;
	}
	
	DLLNode<record>* getdllnode()
	{
		return ptr;
	}

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
	friend ostream& operator<<(ostream& out, index& obj);

};
ostream& operator<<(ostream& out, index& obj)
{
	out << obj.issn << endl;
	//out << obj.ptr->data;
	return out;
}


class lms {
	avl<index> indexes;
	DLList<record> records;
	int noofrecords;
public:
	lms(int n = 0)
	{
		noofrecords = n;
	}
	~lms()
	{
		//nothing dynamic
	}

	///////////////////Create Book Record////////////////////////////////////////////
	void createbkrc()
	{
		int i, c, r;string t; int count;
		cout << "Enter ISSN:" << endl;
		cin >> i; cin.ignore();
		cout << "Enter Title:" << endl;
		getline(cin, t);
		cin.ignore();
		cout << "Enter No of COPIES:" << endl;
		cin >> c;
		cout << "Enter No of Reference Books:" << endl;
		cin >> r;
		cout << "Enter NO of authors:" << endl;
		cin >> count;
		index justacheck(i, NULL);
		justacheck=indexes.searchret(justacheck);
		if (justacheck.getdllnode())//already exists
		{
			cout << "Exists Already" << endl;
			return;
		}
		record objofrecod(i, t, r, c);
		for (int i = 0; i < count; i++)
		{
			//string name;
			cin.ignore();
			cout << "Enter author's name" << endl;
			getline(cin,t);
			//cin.ignore();
			cin.clear();
			objofrecod.addauthor(t);
		}
		if (noofrecords == 0)//1st record
		{
			records.insetatHead(objofrecod);
			index objofind(i, records.head);
			indexes.insert(objofind);
			noofrecords++;
		}
		else
		{
			DLLNode<record>* tobeinsertedafter=NULL;
			index temp1(i, NULL);
			index temp(i,NULL);
			//using mid 2 logic
			temp = indexes.successor(temp1,temp);
			tobeinsertedafter = temp.getdllnode();
			index objofind;
			objofind.setdllnode(records.insertafter(tobeinsertedafter, objofrecod));
			objofind.setissn(i);
			indexes.insert(objofind);
			noofrecords++;
		}
	}

	///////////////////Review Book Record/////////////////////////////////////////////
	void reviewbkrc()
	{
		int issn;
		cout << "Enter ISSN:" << endl;
		cin >> issn;
		index temp(issn, NULL);
		temp = indexes.searchret(temp);
		DLLNode<record>* node = temp.getdllnode();
		if (node)
		{
			cout << node->data;
		}
		else
			cout << "Not found" << endl;
	}

	///////////////////Update Book Record/////////////////////////////////////////////
	void updatebkrc()
	{
		int issn;
		cout << "Enter ISSN:" << endl;
		cin >> issn;
		index temp(issn, NULL);
		temp = indexes.searchret(temp);
		DLLNode<record>* node = temp.getdllnode();
	
		if (node)
		{
			int c, r; string t; int count;
			cin.ignore();
			cout << "Enter Title:" << endl;
			getline(cin, t);
			cin.ignore();
			cout << "Enter No of COPIES:" << endl;
			cin >> c;
			cout << "Enter No of Reference Books:" << endl;
			cin >> r;
			cout << "Enter NO of authors:" << endl;
			cin >> count;
			node->data.settitle(t);
			node->data.setcopies(c);
			node->data.setrefer(r);
			DLList<string> names;
			for (int i = 0; i < count; i++)
			{
				//string name;
				cin.ignore();
				cout << "Enter author's name" << endl;
				getline(cin, t);
				//cin.ignore();
				cin.clear();
				names.insertatEnd(t);
			}
			node->data.setauthors(names);
		}
		else
			cout << "Not Found"<<endl;
	}

	///////////////////Delete Book Record/////////////////////////////////////////////
	void deletebkrc()
	{
		int issn;
		cout << "Enter ISSN:" << endl;
		cin >> issn;
		index temp(issn, NULL);
		temp = indexes.searchret(temp);
		DLLNode<record>* node = temp.getdllnode();
		if (node)
		{
			records.deletebynode(node);
			indexes.deletenode(temp);
			cout << "Deleted" << endl;
			noofrecords--;
		}
		else
			cout << "Not Found" << endl;
	}

	void menu()
	{
		int choice=-1;
		while (1)
		{
			cout << "---------LMS-------" << endl;
			cout << "1:Create Record" << endl;
			cout << "2:Review Record" << endl;
			cout << "3:Update Record" << endl;
			cout << "4:Delete Record" << endl;
			cout << "5:Print Record(DLL)" << endl;
			cout << "6:Print Index(AVL)" << endl;
			cout << "7:Exit" << endl;
			cout << "Enter choice:" << endl;
			cin >> choice;
			while (!(choice >= 1 && choice <= 7))
			{
				cout << "Enter choice:" << endl;
				cin >> choice;
			}
			if (choice == 1)
			{
				createbkrc();
			}
			else if (choice == 2)
			{
				reviewbkrc();
			}
			else if (choice == 3)
			{
				updatebkrc();
			}
			else if (choice == 4)
			{
				deletebkrc();
			}
			else if (choice == 5)
			{
				records.print();
			}
			else if (choice == 6)
			{
				indexes.print();
			}
			else if (choice == 7)
			{
				break;
			}
			system("pause");
			system("cls");
		}
	}
};

int main()
{
	lms obj;
	obj.menu();
	//avl<index> obj;
	//DLList<record> obj1;
	//record o;
	//o.issn = 1234;
	//o.no_of_copies = 12;
	//o.no_of_refer = 21;
	//o.title = "test book";
	//o.authors.insetatHead("test author");
	//o.authors.insetatHead("test author1");
	//obj1.insetatHead(o);
	//index ind; ind.issn = o.issn;
	//ind.ptr = obj1.returnnode(o);
	////obj1.head;
	////obj1.print();
	////obj1.returnnode(o);
	////obj1.returnnode()
	////obj.insert(ind);
	////ind.ptr = obj1.head;
	//obj.insert(ind);
	//obj.createbkrc();
	//obj.reviewbkrc();
	////obj.reviewbkrc();
	////obj.updatebkrc();
	////obj.reviewbkrc();
	//obj.deletebkrc();
	//obj.reviewbkrc();
	//obj.printdll();

	system("pause");

	return 0;
}