#include <iostream>
#include <map>
#include "CustomVector.hpp"
#include "CustomAllocator.hpp"

int factorial(int n) noexcept
{
	return (n == 1 || n == 0) ? 1 : n * factorial(n - 1);
}

int main() noexcept
{
	std::map<int, int> map_default_alloc;
	for (int i = 0; i < 10; ++i)
	{
		map_default_alloc[i] = factorial(i);
	}

	std::cout << "std::map with default allocator:\n";
	for (const auto& it : map_default_alloc)
	{
		std::cout << it.first << " " << it.second << std::endl;
	}
	std::cout << std::endl;

	//-------------------------------------------------------------------------
	std::map<int, int, std::less<>, CustomAllocator<std::pair<const int, int>, 10>> map_custom_alloc;
	for (int i = 0; i < 10; ++i)
	{
		map_custom_alloc[i] = factorial(i);
	}

	std::cout << "std::map with custom allocator:\n";
	for (const auto& it : map_custom_alloc)
	{
		std::cout << it.first << " " << it.second << std::endl;
	}
	std::cout << std::endl;

	//-------------------------------------
	CustomVector<int> vector_default_alloc;
	for (int i = 0; i < 10; ++i)
	{
		vector_default_alloc.push_back(i);
	}

	std::cout << "custom vector with default allocator:\n";
	for (const auto& it : vector_default_alloc)
	{
		std::cout << it << std::endl;
	}
	std::cout << std::endl;

	//--------------------------------------------------------------
	CustomVector<int, CustomAllocator<int, 16>> vector_custom_alloc;
	for (int i = 0; i < 10; ++i)
	{
		vector_custom_alloc.push_back(i);
	}

	std::cout << "custom vector with custom allocator:\n";
	for (const auto& it : vector_custom_alloc)
	{
		std::cout << it << std::endl;
	}
	std::cout << std::endl;

	return 0;
}