#ifndef __LEXEMUS_H__
#define __LEXEMUS_H__
#include <string>
#include <iostream>

class Lexemus {
private:
	std::string val;
	int type;				// 0 - number, 1 - operator, 2 - variable, 3 - ?
	int priority; 
public:
	Lexemus()																//конструкторы и деструктор
	{
		val = std::string();
		type = -1;
		priority = -1;
	}
	Lexemus(char c, int t, int p) 
	{
		val = std::string(&c, 1);
		type = t;
		priority = p;
	}
	Lexemus(char c, int t)
	{
		val = std::string(&c, 1);
		type = t;
		priority = -1;
	}
	Lexemus(std::string s, int t)
	{
		val = s;
		type = t;
		priority = -1;
	}
	Lexemus(std::string s, int t, int p)
	{
		val = s;
		type = t;
		priority = p;
	}
	~Lexemus() {}
	void set_priority()															//сеттеры и обнулитель
	{
		if (type == 1)
		{
			if ((val == "(") || (val == ")")) priority = 0;
			else if ((val == "+") || (val == "-")) priority = 1;
			else if ((val == "*") || (val == "/")) priority = 2;
		}
		else priority = -1;
	}
	void nullify()													
	{
		val = std::string();
		type = -1;
		priority = -1;
	}
	void append(char c)
	{
		val.push_back(c);
	}
	void set_type(int t) noexcept
	{
		type = t;
	}
	Lexemus& operator=(const std::string s)							//перегрузка операторов
	{
		val = s;
		type = -1;
		priority = -1;
	}
	Lexemus& operator=(const char c)
	{
		val = std::string();
		val.push_back(c);;
	}
	bool operator==(Lexemus& l) 
	{
		return (val == l.val) && (l.type == type) && (priority == l.priority);
	}
	bool operator==(const Lexemus& l) const
	{
		return (val == l.val) && (l.type == type) && (priority == l.priority);
	}
	std::string get_val()											//геттеры
	{										
		return val;
	}
	int get_type() {
		return type;
	}
	int get_prio() {
		return priority;
	}
	double get_double()
	{
		char* res = new char[val.size()];
		for (int i = 0; i < val.size(); ++i)
		{
			res[i] = val[i];
		}
		double number = 0.0;
		number = atof(res);
		return number;
	}

	friend std::ostream& operator<<(std::ostream& s, const Lexemus& l) {
		s << l.val << " ";
		return s;
	}
};
#endif