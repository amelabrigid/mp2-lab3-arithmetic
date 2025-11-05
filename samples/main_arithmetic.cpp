// реализация пользовательского приложения


#include "arithmetic.h"


int main()
{
	std::cout << "Enter your expression:" << std::endl;
	std::string expression;
	std::getline(std::cin, expression);
	Arithmetic a(expression);
	a.parce();
	a.turn_to_postfix();
	char confirm = 'y';
	while (confirm == 'y')
	{
		std::cout << "Enter the variables:" << std::endl;
		a.set_variables();
		a.calculate();
		std::cout << "The result is " << a.get_res() << std::endl << "Calculate again? (y/n): ";
		std::cin >> confirm;
	}
}
