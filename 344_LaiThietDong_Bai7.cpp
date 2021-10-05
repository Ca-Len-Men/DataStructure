#include<iostream>
#include<conio.h>
//#include<string.h>

#define _CRT_SECURE_NO_WARNINGS
//==================================================
template <class _data> class node;
template <class _data> class stack;

void standard(char* str);					//Chuan hoa ve chuoi tieu chuan
bool toPostfix(stack<char>& listchar, stack<int>& listint, char* str);		//Chuyen ve hau to
void show(stack<char>& listchar, stack<int>& listint);

int strtoint(char* str, int& idx);			//Chuyen chuoi thanh so
int priority(char ch);						//Do uu tien
void count(stack<char>& listchar, stack<int>& listint);

bool isNumber(char ch);						//True neu la ky tu so
bool check(char* str);						//Kiem tra dong mo ngoac : ( )
//==================================================
template <class _data>
class node {
public:
	_data info;
	node* next;

	//Khoi tao
	node(_data element = 0);
};

template <class _data>
node<_data>::node(_data element)
{
	info = element;
	next = NULL;
}
//==================================================
template <class _data>
class stack {
public:
	node<_data>* head;

	//Khoi tao
	stack();

	//Ham
	void push(_data element = 0);	//Them vao dinh stack
	void del();						//Giai phong stack
	void show();					//Xuat ra stack
	void delnode(node<_data>* p);	//Xoa node p

	bool isEmpty();					//True neu stack rong

	_data pop();					//Lay ra dinh stack
	_data get();					//Lay gia tri dinh stack
};

template <class _data>
void stack<_data>::delnode(node<_data>* p)
{
	if (head == NULL || p == NULL)
		return;

	if (head->next == NULL)	//Chi co 1 node
	{
		delete head;
		head = NULL;
		return;
	}

	node<_data>* i;
	if (p->next)	//Phia sau co node
	{
		i = p->next;		//Giu node sau p
		p->info = i->info;	//Copy gia tri node sau p
		p->next = i->next;	//Bo node sau p
		delete i;			//Giai phong node sau p
		return;		//Ket thuc
	}

	//p->next == NULL
	for (i = head; i->next; i = i->next)
		if (i->next == p)
		{
			i->next = NULL;
			delete p;
			break;
		}
}

template <class _data>
void stack<_data>::show()
{
	node<_data>* p = head;
	for (; p; p = p->next)
		std::cout << p->info << " ";
	std::cout << "NULL\n";
}

template <class _data>
void stack<_data>::del()
{
	node<_data>* p = head;

	for (; head; p = head)
	{
		head = head->next;
		delete p;
	}
}

template <class _data>
bool stack<_data>::isEmpty()
{
	return head == NULL;
}

template <class _data>
_data stack<_data>::get()
{
	if (head == NULL)
		return 0;
	return head->info;
}

template <class _data>
_data stack<_data>::pop()
{
	if (head == NULL)
		return 0;

	node<_data>* p = head;			//Giu dia chi dinh stack
	head = head->next;		//Lay ra dinh stack

	_data value = p->info;	//Luu lai gia tri dinh stack truoc do
	delete p;				//Giai phong dinh stack truoc do
	return value;				//Tra ve gia tri dinh stack truoc do
}

template <class _data>
void stack<_data>::push(_data element)
{
	node<_data>* p = new node<_data>(element);
	p->next = head;
	head = p;
}

template <class _data>
stack<_data>::stack()
{
	head = NULL;
}
//==================================================
void main()
{
	char s[100];
	stack<char> listchar;
	stack<int> listint;

	do {
		printf("Nhap bieu thuc : ");
		fgets(s, 100, stdin);

		if (!toPostfix(listchar, listint, s))
		{
			printf("Nhap sai cu phap !");
			getch();
			system("cls");
			continue;
		}
		
		printf("Chuan hoa chuoi : %s\n", s);

		show(listchar, listint);

		count(listchar, listint);
		printf("Gia tri : %d", listint.head->info);

		listchar.del();
		listint.del();

		getch();
		system("cls");
	} while (true);
}
//==================================================
void show(stack<char>& listchar, stack<int>& listint)
{
	stack<char> tempchar;
	stack<int> tempint;

	while (!listchar.isEmpty())
	{
		tempchar.push(listchar.pop());
		tempint.push(listint.pop());
	}

	node<char>* p = tempchar.head;
	node<int>* q = tempint.head;

	for (; p; p = p->next, q = q->next)
	{
		if (p->info == '0')	//La so
			std::cout << q->info << " ";
		else
			std::cout << p->info << " ";
	}

	std::cout << '\n';

	while (!tempchar.isEmpty())
	{
		listchar.push(tempchar.pop());
		listint.push(tempint.pop());
	}
}

void count(stack<char>& listchar, stack<int>& listint)
{
	int dem = 0;
	node<char>* p;
	node<int>* q;
	while (listchar.head->next)
	{
		dem++;
		if (dem == 200)
		{
			printf("Loi input : + - * / %\n");
			break;
		}
		p = listchar.head;
		q = listint.head;

		while (p->next && p->next->next)
		{
			if (p->info != '0' && p->next->info == '0' && p->next->next->info == '0')
			{
				switch (p->info)	//Operator
				{
					case '+':
						q->info = q->next->next->info + q->next->info;
						break;
					case '-':
						q->info = q->next->next->info - q->next->info;
						break;
					case '*':
						q->info = q->next->next->info * q->next->info;
						break;
					case '/':
						q->info = q->next->next->info / q->next->info;
						break;
					case '%':
						q->info = q->next->next->info % q->next->info;
						break;
				}
				p->info = '0';

				for (int i = 0; i < 2; i++)	//Xoa 2 node sau p, q
				{
					listchar.delnode(p->next);
					listint.delnode(q->next);
				}
				break;
			}

			p = p->next;
			q = q->next;
		}
	}
}

bool toPostfix(stack<char>& listchar, stack<int>& listint, char* str)
{
	if (!check(str))
		return false;
	standard(str);
	//printf("%s\n", str);
	//getch();

	char ch;
	stack<char> temp;		//Operator

	for (int i = 0; str[i]; i++)	//Duyet chuoi
	{
		switch (str[i])
		{
			case '(':	//Ngoac mo
				temp.push(str[i]);
				break;

			case ')':	//Ngoac dong
				while (!temp.isEmpty())
				{
					ch = temp.pop();
					if (ch == '(')
						break;
					listchar.push(ch);
					listint.push();
				}
				break;

			default:
				if (isNumber(str[i]))		//Neu la so
				{
					listchar.push('0');
					listint.push(strtoint(str, i));
					i--;
					break;
				}

				//Operator : + - * / %
				while (!temp.isEmpty() && temp.get() != '(' && priority(temp.get()) >= priority(str[i]))
				{
					listchar.push(temp.pop());		//Lay ra temp them vao postfix
					listint.push();
				}

				temp.push(str[i]);
		}
	}

	while (!temp.isEmpty())
	{
		listchar.push(temp.pop());		//Lay ra temp them vao postfix
		listint.push();
	}
}

bool check(char* str)
{
    stack<char> list;
    char ch, temp = '(';
    
    for (int i = 0; str[i]; i++)
        switch (str[i])
        {
            case '(':// case '{': case '[':
                list.push(str[i]);
                break;

            case ')':// case '}': case ']':
                if (list.isEmpty()) //Stack rong
                    return false;

                /*switch (str[i])
                {
                    case '}': temp = '{';   break;
                    case ')': temp = '(';   break;
                    case ']': temp = '[';   break;
                }*/
				
                ch = list.pop();      //Lay ra stack

                if (temp != ch)    //Sai
                {
                    list.del();     //Giai phong
                    return false;
                }
                break;
        }

    if (!list.isEmpty()) //Stack khong rong
    {
        list.del();
        return false;
    }

    return true;    //Stack rong
}

void standard(char* str)
{
	char s[100];
	int len = 0;

	for (int i = 0; str[i]; i++)
		switch (str[i])
		{
			case '+': case '-':
			case '*': case '/': case '%':
			case '(': case ')':
				s[len++] = str[i];
				break;

			default:
				if(isNumber(str[i]))
					s[len++] = str[i];
		}
	s[len] = '\0';
	strcpy(str, s);
}

int strtoint(char* str, int& idx)
{
	int value = 0;
	for (; isNumber(str[idx]); idx++)
		value = value * 10 + str[idx] - '0';
	return value;
}

bool isNumber(char ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	return false;
}

int priority(char ch)
{
	if (ch == '*' || ch == '/' || ch == '%')
		return 2;
	if (ch == '+' || ch == '-')
		return 1;
	if (ch == '(')
		return 0;
	return -1;
}