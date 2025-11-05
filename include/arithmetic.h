// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#ifndef _ARITHMETIC_H_
#define _ARITHMETIC_H_

#include <string>
#include <vector>
#include <map>
#include "lexemus.h" // лексема не определ€ет свой тип, но если она - оператор, определ€ет приоритет
class Arithmetic {
private:
	std::string input;
	std::string polish;
	double res;
	std::vector<Lexemus> lex;
	std::vector<Lexemus> lexpol;
	std::map<std::string, double> variables;
public:
	Arithmetic();
	Arithmetic(std::string s);
	Arithmetic(std::vector<Lexemus> v);
	~Arithmetic();
	
	void parce();
	std::string check();
	void calculate();
	void turn_to_postfix();
	void set_variables();
	

	std::vector<Lexemus> get_lex();
	std::vector<Lexemus> get_lexpol();
	std::map<std::string, double> get_map();
	double get_res();
	
	bool operator==(Arithmetic& a);
	
};
#endif