#ifndef __TSTACK_H__
#define __TSTACK_H__
#include <vector>

template <typename T>
class TStack
{
private:
	std::vector<T> pMem;
	size_t size;
public:
	TStack() : size(0) {
		pMem = std::vector<T>();
	}
	~TStack(){}
	TStack(const TStack& t)
	{
		size = t.size;
		pMem = std::vector<T>(size);
		std::copy(t.pMem, t.pMem + size, pMem);
	}
	TStack& operator=(const TStack& v)
	{
		size = v.size;
		std::copy(v.pMem, v.pMem + size, pMem);
		return *this;
	}
	bool IsEmpty()
	{
		if (size) return 0;
		else return 1;
	}
	void push(const T elem)
	{
		pMem.push_back(elem);
		size++;
	}
	void pop()
	{
		if (!(this->IsEmpty()))
		{
			pMem.pop_back();
			size--;
		}
	}
	T& top()
	{
		return (pMem[size - 1]);
	}
};
#endif