#include <iostream>

using namespace std;

class String
{
	char* m_string;
	static int m_count;

public:	
	String()
		: String(80)
	{
	}

	String(int size)
		: String(size, ' ')
	{
	}

	String(const char* strHuman)
		: String(strlen(strHuman), ' ')
	{
		int length = strlen(strHuman);
		m_string = new char[length + 1];

		for (int i = 0; i < length; ++i)
		{
			m_string[i] = strHuman[i];
		}
		m_string[length] = '\0';
	}

	String(int size, char ch)
		: m_string(new char[size + 1]())
	{
		for (int i = 0; i < size; ++i)
		{
			m_string[i] = ch;
		}
		m_string[size] = '\0';
		m_count++;
	}

	~String()
	{
		m_count--;
		delete[] m_string;
	}

	void Row()
	{
		cout << "Pls row: "; 

		char temp[100];
		cin.getline(temp, 100);

		delete[] m_string;

		int length = 0;
		while (temp[length] != '\0') length++;
		m_string = new char[length + 1];

		for (int i = 0; i < length; ++i)
		{
			m_string[i] = temp[i];
		}
		m_string[length] = '\0';
	}

	void printRow()
	{
		cout << "Row: " << m_string << endl;
	}

	static int getCount() 
	{
		return m_count;
	}

};

int String::m_count = 0;

int main()
{
	String s1;
	String s2(80);
	String s3("Kchau");

	s1.Row();
	s1.printRow();

	cout << "Object String: " << String::getCount() << endl;
}