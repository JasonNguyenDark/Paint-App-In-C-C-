#include <iostream>
#include <string>
#include <fstream>
#include <stack>
using namespace std;

int Number_change(char a)
{
	if (a == '0') return 0;
	if (a == '1') return 1;
	if (a == '2') return 2;
	if (a == '3') return 3;
	if (a == '4') return 4;
	if (a == '5') return 5;
	if (a == '6') return 6;
	if (a == '7') return 7;
	if (a == '8') return 8;
	if (a == '9') return 9;
}
char Char_change(int a)
{
	if (a == 0) return '0';
	if (a == 1) return '1';
	if (a == 2) return '2';
	if (a == 3) return '3';
	if (a == 4) return '4';
	if (a == 5) return '5';
	if (a == 6) return '6';
	if (a == 7) return '7';
	if (a == 8) return '8';
	if (a == 9) return '9';
	if (a == 10) return '10';
}

struct Node
{
	char data;
	Node *next;
	string data_string;
};
class List
{
private:
	Node *head;
public:
	List() // Build the list
	{
		head = NULL;
	}

	void InsertHead(char x) // Insert value to head
	{
		if (head == NULL)
		{
			head = new Node;
			head->data = x;
			head->next = NULL;
		}
		else
		{
			Node *p = new Node;
			p->data = x;
			p->next = head;
			head = p;
		}
	}
	void Print() // Print the List
	{
		if (head == NULL)
		{
			cout << "No data!" << endl;
		}
		else
		{
			Node *cur = head;
			while (cur != NULL)
			{
				cout << cur->data << " ";
				cur = cur->next;
			}
		}
	}
	void InsertLast(char x) // Insert value to the tail
	{
		if (head == NULL)
		{
			head = new Node;
			head->data = x;
			head->next = NULL;
		}
		else
		{
			Node *cur = head;
			while (cur->next != NULL)
				cur = cur->next;
			Node *p = new Node;
			p->data = x;
			p->next = NULL;
			cur->next = p;
		}
	}
	void InsertLast_string(string x) // Insert value to the tail
	{
		if (head == NULL)
		{
			head = new Node;
			head->data_string = x;
			head->next = NULL;
		}
		else
		{
			Node *cur = head;
			while (cur->next != NULL)
				cur = cur->next;
			Node *p = new Node;
			p->data_string = x;
			p->next = NULL;
			cur->next = p;
		}
	}

	~List() // Delete the list
	{
		Node *tmp;
		while (head != NULL)
		{
			tmp = head;
			head = head->next;
			delete tmp;
		}
	}

	void DeleteLast() // Delete the last Node
	{
		if (head == NULL)
		{
			return;
		}
		if (head->next == NULL)
		{
			delete head;
			head = NULL;
		}
		else
		{
			Node *cur = head;
			while (cur != NULL)
			{
				if (cur->next->next == NULL)
				{
					Node *tmp = cur->next;
					delete tmp;
					cur->next = NULL;
					break;
				}
				cur = cur->next;
			}
		}
	}
	void Change_info(char k, char k1)
	{
		Node *cur = head;
		while (cur != NULL)
		{
			if (cur->data == k)
				cur->data = k1;
			cur = cur->next;
		}
	}
	void Change_info2(char k, char &k1)
	{
		Node *cur = head;
		while (cur != NULL)
		{
			if (cur->data == k)
				k1 = cur->data;
			cur = cur->next;
		}
	}
	void Copy_List(List &listA)
	{
		char c;
		Node *cur = head;
		while (cur != NULL)
		{
			c = cur->data;
			listA.InsertLast(c);
			cur = cur->next;
		}
		//DeleteList(l);
	}

	void Dem_dau(int &dem)
	{
		Node *cur = head;
		while (cur != NULL)
		{
			if (cur->data == '+' ||
				cur->data == '-' ||
				cur->data == '*' ||
				cur->data == '/' ||
				cur->data == '%')
				dem++;
			cur = cur->next;
		}
	}
	void Tinh_gia_tri_Bieu_thuc(int &result, stack<int> &s)
	{
		int a, b;
		bool flag = false;
		Node *cur = head;
		while (cur != NULL)
		{
			if (cur->data == '0' ||
				cur->data == '1' ||
				cur->data == '2' ||
				cur->data == '3' ||
				cur->data == '4' ||
				cur->data == '5' ||
				cur->data == '6' ||
				cur->data == '7' ||
				cur->data == '8' ||
				cur->data == '9')
			{
				int temp = Number_change(cur->data);
				s.push(temp);
			}
			else flag = true;
			if (flag == true)
			{
				a = s.top(); s.pop();
				b = s.top(); s.pop();

				if (cur->data == '+')
				{
					result = b + a;
				}
				if (cur->data == '-')
				{
					result = b - a;
				}
				if (cur->data == '*')
				{
					result = b*a;
				}
				if (cur->data == '/')
				{
					result = b / a;
				}
				s.push(result);
			}
			flag = false;
			cur = cur->next;
		}
	}
};

class Bieu_Thuc
{
private:
	List PostFix;
	string InFix;
	stack<char> ss; // stack phụ để xử lí Infix sang Postfix
	stack<int> s; // stack phụ để tính biểu thức Postfix
	int result;
public:	
	Bieu_Thuc() {};
	~Bieu_Thuc() {};
	void Read_file_txt()
	{
		ifstream FileIn;
		FileIn.open("D:\Input.txt", ios_base::in);
		if (!FileIn)
		{
			cout << endl << " Not found txt file";
			system("pause");
			return;
		}
		getline(FileIn, InFix);
		FileIn.close();
		cout << "Read file successful!" << endl;
		cout << "Infix= " << InFix << endl;
	}
	void Transfer_Infix_to_Postfix()
	{
		int result;
		char string2;
		
		int dau = 0;
		int i = 0;

		while( i < InFix.length())
		{
			if (InFix[i] == '+' ||
				InFix[i] == '-' ||
				InFix[i] == '*' ||
				InFix[i] == '/' ||
				InFix[i] == '%')
				dau++;
			if (InFix[i] == '0' || InFix[i] == '1' ||
				InFix[i] == '2' || InFix[i] == '3' ||
				InFix[i] == '4' || InFix[i] == '5' ||
				InFix[i] == '5' || InFix[i] == '6' ||
				InFix[i] == '7' || InFix[i] == '8' ||
				InFix[i] == '9')
			{
				if (InFix[i] == '0') {
					PostFix.InsertLast(InFix[i]);
					//i++;
				}
				if (InFix[i] == '1') {
					PostFix.InsertLast(InFix[i]);
					//i++;
				}
				if (InFix[i] == '2') {
					PostFix.InsertLast(InFix[i]);
					//i++;
				}
				if (InFix[i] == '3') {
					PostFix.InsertLast(InFix[i]);
					//i++;
				}
				if (InFix[i] == '4') {
					PostFix.InsertLast(InFix[i]);
					//i++;
				}
				if (InFix[i] == '5') {
					PostFix.InsertLast(InFix[i]);
					//i++;
				}
				if (InFix[i] == '6') {
					PostFix.InsertLast(InFix[i]);
					//i++;
				}
				if (InFix[i] == '7') {
					PostFix.InsertLast(InFix[i]);
					//i++;
				}
				if (InFix[i] == '8') {
					PostFix.InsertLast(InFix[i]);
					//i++;
				}
				if (InFix[i] == '9') {
					PostFix.InsertLast(InFix[i]);
					//i++;
				}
			}

			if (InFix[i] == '*' || InFix[i] == '/' || InFix[i] == '%' || InFix[i] == '(') {

				if (InFix[i] == '(') {
					ss.push(InFix[i]);
					//i++;
				}
				else {
					if ( (InFix[i + 2] == '+' || InFix[i + 2] == '-') && (InFix[i - 2] == '+' || InFix[i - 2] == '-')) {
						PostFix.InsertLast(InFix[i + 1]);
						PostFix.InsertLast(InFix[i]);
						if (InFix[i] == '*' || InFix[i] == '/' || InFix[i] == '%')
						{
							while (ss.top() == '+' || ss.top() == '-')
							{
								char temp = ss.top();
								PostFix.InsertLast(temp);
								ss.pop();
								if (ss.size() == 0) break;
							}
						}
						i++;
					} else ss.push(InFix[i]);
				}
			}

			if (InFix[i] == '+' || InFix[i] == '-')
			{
				if (ss.size() == 0) {
					ss.push(InFix[i]);
				}
				if (ss.top() != '*' && ss.top() != '/' && ss.top() != '%') {
					ss.push(InFix[i]);
				}
				else
				{
					while (ss.top() == '*' || ss.top() == '/' || ss.top() == '%')
					{
						char temp = ss.top();
						PostFix.InsertLast(temp);
						ss.pop();
						if (ss.size() == 0) break;
					}
					ss.push(InFix[i]);
				}
				//i++;
			}
			if (InFix[i] == ')') {
				while (ss.top() != '(')
				{
					char temp = ss.top();
					PostFix.InsertLast(temp);
					ss.pop();
				}
				ss.pop(); 
				//i++;
			}
			i++;
		}

		////////////////
		if (ss.size() != 0)
		{
			while (ss.size() != 0)
			{
				char temp = ss.top();
				PostFix.InsertLast(temp);
				ss.pop();
			}
		}
		int dem = 0;
		PostFix.Dem_dau(dem);
		if (dem > dau) PostFix.DeleteLast();
		cout << "Postfix" << endl;
		PostFix.Print();
		cout << endl;
	}
	void Tinh_Bieu_thuc()
	{
		PostFix.Tinh_gia_tri_Bieu_thuc(result,s);
		cout << result << endl;
	}
	int Gia_tri_Bieu_thuc()
	{
		Read_file_txt();
		Transfer_Infix_to_Postfix();
		Tinh_Bieu_thuc();
		return result;
	}
};