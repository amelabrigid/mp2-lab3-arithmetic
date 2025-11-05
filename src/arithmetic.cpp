// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"
#include "stack.h"
#include <iostream>

Arithmetic::Arithmetic() {
	input = std::string();
	lex = std::vector<Lexemus>();
	lexpol = std::vector<Lexemus>();
}
Arithmetic::Arithmetic(std::string s) {
	input = s;
	lex = std::vector<Lexemus>();
	lexpol = std::vector<Lexemus>();
}
Arithmetic::~Arithmetic() {
}
Arithmetic::Arithmetic(std::vector<Lexemus> v)
{
	input = std::string();
	lex = v;
	lexpol = std::vector<Lexemus>();
}
std::vector<Lexemus> Arithmetic::get_lex() {
	return lex;
}
double Arithmetic::get_res() {
	return res;
}
std::vector<Lexemus> Arithmetic::get_lexpol() {
	return lexpol;
}
std::map<std::string, double> Arithmetic::get_map() {
	return variables;
}
//bool operator==(Arithmetic& a) {
	//return input == a.input;
//}
void Arithmetic::parce() {
	size_t size = input.length();
	Lexemus lexema;
	for (int i = 0; i < size; ++i)
	{
		if (input[i] != ' ') {
			lexema.nullify();
			int k = 0;							// k - счётчик, чтобы записать в лексему всё число
			if ((i + k < size) && ((input[i + k] >= 48) && (input[i + k] <= 57) || (input[i + k] == '.')))
			{
				while ((i + k < size) && ((input[i + k] >= 48) && (input[i + k] <= 57) || (input[i + k] == '.'))) // пока элемент строки - число и мы не вышли за пределы
				{
					lexema.set_type(0);        // тип лексемы - число
					lexema.append(input[i + k]);
					k++;
				}  // случай цифры и точки, даблы записываются только с одной точкой
				i += k - 1;
				lex.push_back(lexema);
				continue;
			}
			if ((input[i] == '+') || (input[i] == '-') || (input[i] == '*') || (input[i] == '/') || (input[i] == '(') || (input[i] == ')'))
			{
				lexema.append(input[i]);
				lexema.set_type(1);
				lexema.set_priority();
				lex.push_back(lexema);
				continue;
			} // случай переменной
			k = 0;
			// isalpha()
			if ((i + k < size) && (input[i + k] >= 97) && (input[i + k] <= 122)) {
				while ((input[i + k] >= 97) && (input[i + k] <= 122) && (i + k < size)) // пока элемент строки - строчная буква и мы не вышли за пределы
				{
					lexema.set_type(2);        // тип лексемы - переменная
					lexema.append(input[i + k]);
					k++;
				}
				i += k - 1;
			}
			lex.push_back(lexema);
		}
	}
}

std::string Arithmetic::check() {
	TStack<Lexemus> braces;
	int point_flag = 0;
	for (int i = 0; i < lex.size(); ++i)
	{
		point_flag = 0;
		if ((lex[i].get_type() == 1) && (lex[i].get_prio() != 0) && (i < (lex.size() - 1)))            //если лексема - оператор, но не скобка
		{
			if ((lex[i + 1].get_type() == 1) && ((lex[i + 1].get_prio() != 0) || (lex[i].get_val() == ")")))
			{
				return std::string("consecutive operators");
			}
		}
		if ((lex[i].get_val() == "(") && (i < lex.size() - 1))            //если лексема - скобка, а дальше - оператор
		{
			if ((lex[i + 1].get_type() == 1) && ((lex[i + 1].get_prio() != 0) || (lex[i].get_val() == ")")))
			{
				return std::string("consecutive operators");
			}
		}
		if (lex[i].get_val() == "(")
		{
			braces.push(lex[i]);
		}
		if ((lex[i].get_val() == ")") && (braces.IsEmpty()))
		{
			return std::string("compromised braces");
		}
		if (lex[i].get_val() == ")")
		{
			braces.pop();
		}
		
		if (lex[i].get_type() == 0) {
			for (int j = 0; j < lex[i].get_val().size(); ++j)
			{
				if (lex[i].get_val()[j] == '.')
				{
					if (point_flag++) return std::string("multiple points");
				}
			}
		}
		// уже ne вызывает выход за границы
		if (lex[i].get_type() == 0) {
			if ((i < (lex.size() - 1)) && (lex[i + 1].get_type() == 0))
			{
				return std::string("missing operator");
			}
		}
	}
	if(!braces.IsEmpty()) { return std::string("compromised braces"); }
	return std::string("all good");
}

void Arithmetic::turn_to_postfix()
{
	TStack<Lexemus> operators;
	for (int i = 0; i < lex.size(); ++i)
	{
		if (lex[i].get_val() == "(")
		{
			operators.push(lex[i]);
			continue;
		}
		if (lex[i].get_val() == ")")
		{
			while (!(operators.top().get_val() == "("))
			{
				lexpol.push_back(operators.top());
				operators.pop();
			}
			operators.pop();
			continue;
		}
		if ((lex[i].get_type() == 0) || (lex[i].get_type() == 2))
		{
			lexpol.push_back(lex[i]);
			continue;
		}
		if (lex[i].get_type() == 1) {
			if (operators.IsEmpty())
			{
				operators.push(lex[i]);
			}
			else {
				if (lex[i].get_prio() > operators.top().get_prio())
				{
					operators.push(lex[i]);
				}
				else {
					while ((!(operators.IsEmpty())) && (lex[i].get_prio() <= operators.top().get_prio()))
					{
						lexpol.push_back(operators.top());
						operators.pop();
					}
					operators.push(lex[i]);
				}
			}
		}
	}
	while (!(operators.IsEmpty()))
	{
		lexpol.push_back(operators.top());
		operators.pop();
	}
}

void Arithmetic::set_variables() 
{
	double value = 0.0;

	for (int i = 0; i < lexpol.size(); ++i)
	{
		if (lexpol[i].get_type() == 2)
		{
			std::cout << lexpol[i].get_val() << ": " << std::endl;
			std::cin >> value;
			variables[lexpol[i].get_val()] = double(value);
		}
	}
}

void Arithmetic::calculate() {
	TStack<double> numbers;
	double result = 0.0;
	double op1 = 0.0;
	double op2 = 0.0;
	for (int i = 0; i < lexpol.size(); ++i)
	{
		if (lexpol[i].get_type() == 0)
		{
			numbers.push(lexpol[i].get_double());
		}
		if (lexpol[i].get_type() == 1)
		{
			if (lexpol[i].get_val() == "+")
			{
				op2 = numbers.top();
				numbers.pop();
				op1 = numbers.top();
				numbers.pop();
				result = op1 + op2;
				numbers.push(result);
			}
			if (lexpol[i].get_val() == "-")
			{
				op2 = numbers.top();
				numbers.pop();
				op1 = numbers.top();
				numbers.pop();
				result = op1 - op2;
				numbers.push(result);
			}
			if (lexpol[i].get_val() == "*")
			{
				op2 = numbers.top();
				numbers.pop();
				op1 = numbers.top();
				numbers.pop();
				result = op1 * op2;
				numbers.push(result);
			}
			if (lexpol[i].get_val() == "/")
			{
				op2 = numbers.top();
				numbers.pop();
				op1 = numbers.top();
				numbers.pop();
				result = op1 / op2;
				numbers.push(result);
			}
		}
		if (lexpol[i].get_type() == 2)
		{
			result = double(variables[lexpol[i].get_val()]);
			numbers.push(result);
		}
	}
	res = numbers.top();
}