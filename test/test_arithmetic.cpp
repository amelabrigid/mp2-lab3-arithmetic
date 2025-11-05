// тесты для вычисления арифметических выражений

#include <gtest.h>
#include <iostream>
#include "arithmetic.h"

TEST(gtest, test_of_tests)
{
	EXPECT_EQ(1, 1);
}

TEST(arithmetic_parser, can_parce_short_variables_and_numbers)
{
	std::string s = "(5 + 6) * a";
	Arithmetic a(s);
	a.parce();
	std::vector<Lexemus> vex;
	vex.push_back(Lexemus('(', 1, 0));
	vex.push_back(Lexemus('5', 0));
	vex.push_back(Lexemus('+', 1, 1));
	vex.push_back(Lexemus('6', 0));
	vex.push_back(Lexemus(')', 1, 0));
	vex.push_back(Lexemus('*', 1, 2));
	vex.push_back(Lexemus('a', 2));

	EXPECT_EQ(vex, a.get_lex());
}

TEST(arithmetic_parser, can_parse_long_numbers)
{
	std::string s = "(56 + 675) * a";
	Arithmetic a(s);
	a.parce();
	std::vector<Lexemus> vex;
	vex.push_back(Lexemus('(', 1, 0));
	vex.push_back(Lexemus("56", 0));
	vex.push_back(Lexemus('+', 1, 1));
	vex.push_back(Lexemus("675", 0));
	vex.push_back(Lexemus(')', 1, 0));
	vex.push_back(Lexemus('*', 1, 2));
	vex.push_back(Lexemus('a', 2));

	EXPECT_EQ(vex, a.get_lex());
}

TEST(arithmetic_parser, can_parse_doubles)
{
	std::string s = "(56 + 67.5) * a";
	Arithmetic a(s);
	a.parce();
	std::vector<Lexemus> vex;
	vex.push_back(Lexemus('(', 1, 0));
	vex.push_back(Lexemus("56", 0));
	vex.push_back(Lexemus('+', 1, 1));
	vex.push_back(Lexemus("67.5", 0));
	vex.push_back(Lexemus(')', 1, 0));
	vex.push_back(Lexemus('*', 1, 2));
	vex.push_back(Lexemus('a', 2));

	EXPECT_EQ(vex, a.get_lex());
}

TEST(arithmetic_parser, can_parse_long_variables)
{
	std::string s = "(56 + 675) * abc";
	Arithmetic a(s);
	a.parce();
	std::vector<Lexemus> vex;
	vex.push_back(Lexemus('(', 1, 0));
	vex.push_back(Lexemus("56", 0));
	vex.push_back(Lexemus('+', 1, 1));
	vex.push_back(Lexemus("675", 0));
	vex.push_back(Lexemus(')', 1, 0));
	vex.push_back(Lexemus('*', 1, 2));
	vex.push_back(Lexemus("abc", 2));

	EXPECT_EQ(vex, a.get_lex());
}

TEST(arithmetic_parser, can_parse_consecutive_braces)
{
	std::string s = "((56 + 67.5) * a + b) / 7.76";
	Arithmetic a(s);
	a.parce();
	std::vector<Lexemus> vex;
	vex.push_back(Lexemus('(', 1, 0));
	vex.push_back(Lexemus('(', 1, 0));
	vex.push_back(Lexemus("56", 0));
	vex.push_back(Lexemus('+', 1, 1));
	vex.push_back(Lexemus("67.5", 0));
	vex.push_back(Lexemus(')', 1, 0));
	vex.push_back(Lexemus('*', 1, 2));
	vex.push_back(Lexemus('a', 2));
	vex.push_back(Lexemus('+', 1, 1));
	vex.push_back(Lexemus('b', 2));
	vex.push_back(Lexemus(')', 1, 0));
	vex.push_back(Lexemus('/', 1, 2));
	vex.push_back(Lexemus("7.76", 0));

	EXPECT_EQ(vex, a.get_lex());
}

TEST(arithmetic_parser, can_set_prio)
{
	std::string s = "5 + 6 * 7";
	Arithmetic a(s);
	a.parce();
	EXPECT_EQ(2, a.get_lex()[3].get_prio());
}

TEST(arithmetic_parser, can_set_prio2)
{
	std::string s = "5 + 6 * 7";
	Arithmetic a(s);
	a.parce();
	EXPECT_EQ(1, a.get_lex()[1].get_prio());
}

TEST(arithmetic_check, correct_is_correct)
{
	std::string s = "((56 + 67.5) * a + b) / 7.76";
	Arithmetic a(s);
	a.parce();
	std::string result = a.check();
	EXPECT_EQ("all good", result);
}

TEST(arithmetic_check, catches_consecutive_operators)
{
	std::string s = "56 +* 7";
	Arithmetic a(s);
	a.parce();
	std::string result = a.check();
	EXPECT_EQ("consecutive operators", result);
}

TEST(arithmetic_check, catches_compromised_braces)
{
	std::string s = "(5.5 + a))";
	Arithmetic a(s);
	a.parce();
	std::string result = a.check();
	EXPECT_EQ("compromised braces", result);
}

TEST(arithmetic_check, catches_multiple_points)
{
	std::string s = "(5.5.5 + a)";
	Arithmetic a(s);
	a.parce();
	std::string result = a.check();
	EXPECT_EQ("multiple points", result);
}

TEST(arithmetic_check, catches_missing_operators)
{
	std::string s = "(5 5.5 + a)";
	Arithmetic a(s);
	a.parce();
	std::string result = a.check();
	EXPECT_EQ("missing operator", result);
}


TEST(arithmetic_turn_to_postfix, can_turn_small1)
{
	std::string s = "5 + 6 * 7";
	Arithmetic a(s);
	a.parce();
	a.turn_to_postfix();
	std::vector<Lexemus> pol;
	pol.push_back(Lexemus('5', 0));
	pol.push_back(Lexemus('6', 0));
	pol.push_back(Lexemus('7', 0));
	pol.push_back(Lexemus('*', 1, 2));
	pol.push_back(Lexemus('+', 1, 1));
	EXPECT_EQ(pol, a.get_lexpol());
}

TEST(arithmetic_turn_to_postfix, can_turn_small)
{
	std::string s = "(5 + 6) * a";
	Arithmetic a(s);
	a.parce();
	a.turn_to_postfix();
	std::vector<Lexemus> pol;
	pol.push_back(Lexemus("5", 0));
	pol.push_back(Lexemus("6", 0));
	pol.push_back(Lexemus("+", 1, 1));
	pol.push_back(Lexemus("a", 2));
	pol.push_back(Lexemus("*", 1, 2));
	EXPECT_EQ(pol, a.get_lexpol());
}

TEST(arithmetic_turn_to_postfix, can_turn_large)
{
	std::string s = "(5.67 - 86) * (17 / a - 45.6)";
	Arithmetic a(s);
	a.parce();
	a.turn_to_postfix();
	std::vector<Lexemus> pol;
	pol.push_back(Lexemus("5.67", 0));
	pol.push_back(Lexemus("86", 0));
	pol.push_back(Lexemus("-", 1, 1));
	pol.push_back(Lexemus("17", 0));
	pol.push_back(Lexemus("a", 2));
	pol.push_back(Lexemus("/", 1, 2));
	pol.push_back(Lexemus("45.6", 0));
	pol.push_back(Lexemus("-", 1, 1));
	pol.push_back(Lexemus("*", 1, 2));
	EXPECT_EQ(pol, a.get_lexpol());
}

TEST(lexemus, can_set_priority)
{
	Lexemus l("+", 1);
	l.set_priority();
	EXPECT_EQ(1, l.get_prio());
}

TEST(lexemus, can_set_priority2)
{
	Lexemus l("*", 1);
	l.set_priority();
	EXPECT_EQ(2, l.get_prio());
}

TEST(lexemus, can_set_priority3)
{
	Lexemus l("(", 1);
	l.set_priority();
	EXPECT_EQ(0, l.get_prio());
}

TEST(lexemus, can_get_double)
{
	Lexemus l("56.7", 0);
	double res = l.get_double();
	EXPECT_EQ(56.7, res);
}

TEST(arithmetic_variables, can_set_one)
{
	std::string s = "(5.67 - 86) * (17 / a - 45.6)";
	Arithmetic a(s);
	a.parce();
	a.turn_to_postfix();
	a.set_variables();
	std::map<std::string, double> ex{
		std::pair<std::string, double> {"a", 30.0}
	};
	EXPECT_EQ(ex, a.get_map());
}

TEST(arithmetic_variables, can_set_two)
{
	std::string s = "(5.67 - b) * (17 / a - 45.6)";
	Arithmetic a(s);
	a.parce();
	a.turn_to_postfix();
	a.set_variables();
	std::map<std::string, double> ex{
		std::pair<std::string, double> {"a", 30.0}, {"b", 40.0}
	};
	std::cout << a.get_map()["a"];
	EXPECT_EQ(ex, a.get_map());
}

TEST(arithmetic_calculate, can_calculate)
{
	std::string s = "5 + 6 * 7";
	Arithmetic a(s);
	a.parce();
	a.turn_to_postfix();
	a.calculate();
	EXPECT_EQ(47.0, a.get_res());
}

TEST(arithmetic_calculate, can_calculate_variable)
{
	std::string s = "(5 + 6) * 7 - a";
	Arithmetic a(s);
	a.parce();
	a.turn_to_postfix(); //только в таком порядке
	a.set_variables();
	a.calculate();
	EXPECT_EQ(70.0, a.get_res());
}

TEST(arithmetic_calculate, can_calculate_multiple_times)
{
	std::string s = "(5 + 6) * 7 - a";
	Arithmetic a(s);
	a.parce();
	a.turn_to_postfix(); //только в таком порядке
	a.set_variables();
	a.calculate();
	EXPECT_EQ(70.0, a.get_res());
	a.set_variables();
	a.calculate();
	EXPECT_EQ(67.0, a.get_res());
}