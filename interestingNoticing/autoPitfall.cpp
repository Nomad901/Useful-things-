#include <iostream>
#include <vector>
#include <format> 

class myClass
{
public:
	std::vector<bool> getTheStorage()
	{
		return mStorage;
	}

private:
	std::vector<bool> mStorage{ true,false,false,true,true };

};


int main()
{
	myClass mc;

	bool var = mc.getTheStorage()[1];
	std::cout << std::format("Element type: {}\n", typeid(var).name()); // Element type : bool

	auto var2 = mc.getTheStorage()[1]; // UB!
	std::cout << std::format("Element type: {}\n", typeid(var2).name());
	// Element type : class std::_Vb_reference<struct std::_Wrap_alloc<class std::allocator<unsigned int> > >
}
