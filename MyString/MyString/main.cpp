#include<iostream>
using namespace std;

class MyString
{
public:
	MyString() //конструктор по умолчанию
	{

	}

	MyString(const char* str)
	{
		int len = strlen(str);
 		this->string = new char[len + 1];

		for (int i = 0; i < len; i++)
		{
			this->string[i] = str[i];
		}

		this->string[len] = '\0'; //в конец присваиваем терминирующий ноль
	}

	MyString(const MyString& other)
	{
		int len = strlen(other.string);
		this->string = new char[len + 1];

		for (int i = 0; i < len; i++)
		{
			this->string[i] = other.string[i];
		}

		this->string[len] = '\0';
	}

	~MyString()
	{
		delete[] this->string;
	}

	MyString& operator = (const MyString& other)
	{
		if (this->string != nullptr) //если указатель не Null, то надо его очистить
		{
			delete[] this->string;
		}

		int len = strlen(other.string);
		this->string = new char[len + 1];

		for (int i = 0; i < len; i++)
		{
			this->string[i] = other.string[i];
		}

		this->string[len] = '\0';

		return *this;
	}

	//перегрузка оператора +
	MyString operator + (const MyString& other)
	{
		MyString newStr;

		int thisLens = strlen(this->string);
		int otherLens = strlen(other.string);

		newStr.string = new char[thisLens + otherLens + 1];

		int i = 0;
		for (; i < thisLens; i++)
		{
			newStr.string[i] = this->string[i];
		}

		for (int j = 0; j < otherLens; j++, i++)
		{
			newStr.string[i] = other.string[j];
		}

		newStr.string[thisLens + otherLens] = '\0';

		return newStr;
	}

	void Print()
	{
		cout << string;
	}

private:
	char* string;
};

int main()
{
	setlocale(LC_ALL, "RU");

	MyString str("test");
	MyString str1("Hellp World");
	MyString result = str + str1;

	//str = str1;

	result.Print();

	return 0;
}