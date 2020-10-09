#include <iostream>
#include <iomanip>

using namespace std;

class Stack  //���������� ������
{
private:
	struct List  // ��������� �����
	{
		int digit;
		List* next, * prev;
	};
	List* begin, * end;  // ��������� �� ������� � ����� �����
public:
	Stack() // ����������� ������
	{
		this->end = this->begin = NULL;
	}

	void addElement(int k1, int info) {  // ���������� �������� � ����(� ����� ��� � ������)
		if (this->begin == NULL) {  // ���� ������ ���
			this->begin = this->end = new List;
			this->begin->digit = this->end->digit = info;

			this->begin->next = this->begin->prev = this->end->next = this->end->prev = NULL;

			cout << "������� ��� ������� ��������!" << endl << endl;
			
			return;
		}

		List* temp = new List;   // ���� � ������ ��� ���� ��������
		temp->digit = info;
		if (k1 == 1) {
			temp->prev = NULL;
			temp->next = this->begin;
			this->begin->prev = temp;
			this->begin = temp;
		}
		else {
			temp->next = NULL;
			temp->prev = this->end;
			this->end->next = temp;
			this->end = temp;
		}

		cout << "������� ��� ������� ��������!" << endl << endl;
	}

	void showList() {  // ����� ������ � ������ � � �����
		List* temp;
		temp = this->begin;

		if (temp == NULL) {
			cout << "������ ����!" << endl << endl;
			return;
		}

		cout << "������ � ������: ";
		while (temp != NULL) {
			cout << temp->digit << setw(2);
			temp = temp->next;
		}
		cout << endl;
		temp = this->end;
		cout << "������ � �����: ";
		while (temp != NULL) {
			cout << temp->digit << setw(2);
			temp = temp->prev;
		}

		cout << endl << endl;
	}

	void deleteAll() {  // �������� ����� ������
		List* temp;

		while (this->begin != NULL) {
			temp = this->begin;
			this->begin = this->begin->next;
			delete temp;
		}
		cout << "������ ��� �����!" << endl << endl;
	}

	void deleteElement(int number) {  // �������� ��������
		List* temp;
		int counter = 1;

		if (this->begin == NULL) {  // �������� �� ��, ���� �� ������
			return;
		}

		for (temp = this->begin; counter != number; counter++, temp = temp->next) {  // ���������� �������� ��� ��������
			if (temp == NULL) {
				cout << "�������� � ����� ������� �� ����������!" << endl << endl;
				return;
			}
		}

		if (temp == NULL) {
			cout << "�������� � ����� ������� �� ����������!" << endl << endl;
			return;
		}

		if (temp == this->begin && temp == this->end) {  // ������ ������ �������� �������� ������
			this->begin = this->end = NULL;
			delete temp;
		}
		else if (temp == this->begin) {
			this->begin->next->prev = NULL;
			this->begin = this->begin->next;
			delete temp;
		}
		else if (temp == this->end) {
			this->end->prev->next = NULL;
			this->end = this->end->prev;
			delete temp;
		}
		else {
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			delete temp;
		}

		cout << "������� ������� �����" << endl << endl;
	}

	~Stack()  // ���������� ������
	{
		List* temp;

		while (begin != NULL) {
			temp = this->begin;
			this->begin = this->begin->next;
			delete temp;
		}

		delete begin;
	}

};

bool isNumberNumeric();
int inputRangeNumber(int rangeA, int rangeB);
int menu();
void fulfillActions();

int main()
{
	setlocale(LC_ALL, "rus");

	fulfillActions();

	system("pause");
}

bool isNumberNumeric() {
	if (cin.get() == '\n') return true;
	else {
		cin.clear();
		cin.ignore(256, '\n');
		return false;
	}
}

int inputRangeNumber(int rangeA, int rangeB)
{
	int number;

	do 
	{
		cin >> number;

		if (!isNumberNumeric())
		{
			cout << "������ �����(������������ ������), ���������� �����: ";
		}
		else if (number < rangeA || number > rangeB) {
			cout << "������ �����(������������ ��������), ���������� �����: ";
		}
		else {
			return number;
		}

	} while (true);
}

int menu() {
	int selection = 0;

	cout << "1. �������� ����� ������.\n2. ����������� �������� ������.\n3. ������� ������� ������.\n4. ������� ������\n5. �������� �������\n6. �����" << endl;
	cout << "�� �����: ";
	selection = inputRangeNumber(1, 6);

	return selection;
}

void fulfillActions() {
	Stack MyList;
	int start_end;
	int info;
	int number;

	do {
		switch (menu())
		{
		case 1:
			cout << "1 - �������� ������� � ������ ������; 2 - �������� ������� � ����� ������." << endl;
			start_end = inputRangeNumber(1, 2);

			do {
				cout << "������� ������� ��� ����������: ";
				cin >> info;
			} while (!isNumberNumeric());

			MyList.addElement(start_end, info);
			break;
		case 2:
			MyList.showList();
			break;
		case 3:

			MyList.showList();
			cout << "������� ����� ��������, ������� ������ �������: ";
			do {
				cout << "������� ������� ��� ����������: ";
				cin >> number;
			} while (!isNumberNumeric());

			MyList.deleteElement(number);
			break;
		case 4:
			MyList.deleteAll();
			break;
		case 5:
			system("cls");
			break;
		case 6: return;
		default:
			break;
		}
	} while (true);
}