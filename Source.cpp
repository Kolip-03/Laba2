#include <iostream>
#include <iomanip>

using namespace std;

class Stack  //объявление класса
{
private:
	struct List  // структура стека
	{
		int digit;
		List* next, * prev;
	};
	List* begin, * end;  // указатель на вершину и конец стека
public:
	Stack() // конструктор класса
	{
		this->end = this->begin = NULL;
	}

	void addElement(int k1, int info) {  // добавление элемента в стек(в конец или в начало)
		if (this->begin == NULL) {  // Если списка нет
			this->begin = this->end = new List;
			this->begin->digit = this->end->digit = info;

			this->begin->next = this->begin->prev = this->end->next = this->end->prev = NULL;

			cout << "Элемент был успешно добавлен!" << endl << endl;
			
			return;
		}

		List* temp = new List;   // Если в списке уже есть элементы
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

		cout << "Элемент был успешно добавлен!" << endl << endl;
	}

	void showList() {  // вывод списка с начала и с конца
		List* temp;
		temp = this->begin;

		if (temp == NULL) {
			cout << "Список пуст!" << endl << endl;
			return;
		}

		cout << "Список с начала: ";
		while (temp != NULL) {
			cout << temp->digit << setw(2);
			temp = temp->next;
		}
		cout << endl;
		temp = this->end;
		cout << "Список с конца: ";
		while (temp != NULL) {
			cout << temp->digit << setw(2);
			temp = temp->prev;
		}

		cout << endl << endl;
	}

	void deleteAll() {  // удаление всего списка
		List* temp;

		while (this->begin != NULL) {
			temp = this->begin;
			this->begin = this->begin->next;
			delete temp;
		}
		cout << "Список был удалён!" << endl << endl;
	}

	void deleteElement(int number) {  // удаление элемента
		List* temp;
		int counter = 1;

		if (this->begin == NULL) {  // проверка на то, есть ли список
			return;
		}

		for (temp = this->begin; counter != number; counter++, temp = temp->next) {  // нахождение элемента для удаления
			if (temp == NULL) {
				cout << "Элемента с таким номером не существует!" << endl << endl;
				return;
			}
		}

		if (temp == NULL) {
			cout << "Элемента с таким номером не существует!" << endl << endl;
			return;
		}

		if (temp == this->begin && temp == this->end) {  // разные случаи удаления элемента списка
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

		cout << "Элемент успешно удалён" << endl << endl;
	}

	~Stack()  // деструктор класса
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
			cout << "Ошибка ввода(некорректный символ), попробуйте снова: ";
		}
		else if (number < rangeA || number > rangeB) {
			cout << "Ошибка ввода(недопустимое значение), попробуйте снова: ";
		}
		else {
			return number;
		}

	} while (true);
}

int menu() {
	int selection = 0;

	cout << "1. Добавить новый лемент.\n2. Просмотреть элементы списка.\n3. Удалить элемент списка.\n4. Удалить список\n5. Очистить консоль\n6. Выход" << endl;
	cout << "Вы ввели: ";
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
			cout << "1 - добавить элемент в начало списка; 2 - добавить элемент в конец списка." << endl;
			start_end = inputRangeNumber(1, 2);

			do {
				cout << "Введите элемент для добавления: ";
				cin >> info;
			} while (!isNumberNumeric());

			MyList.addElement(start_end, info);
			break;
		case 2:
			MyList.showList();
			break;
		case 3:

			MyList.showList();
			cout << "Введите номер элемента, который хотите удалить: ";
			do {
				cout << "Введите элемент для добавления: ";
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