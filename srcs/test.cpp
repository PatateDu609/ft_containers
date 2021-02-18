#include <typeinfo>
#include <iterator>
#include <iostream>

int main()
{
	std::cout << typeid(std::input_iterator_tag).name() << std::endl;
	std::cout << typeid(std::output_iterator_tag).name() << std::endl;
	std::cout << typeid(std::forward_iterator_tag).name() << std::endl;
	std::cout << typeid(std::bidirectional_iterator_tag).name() << std::endl;
	std::cout << typeid(std::random_access_iterator_tag).name() << std::endl;

	return (0);
}
