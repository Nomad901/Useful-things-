#include <iostream>
#include <vector>

// example 1 ------
template<typename T, template<typename> typename Container>
class myClass
{
private:
	Container<T> mContainer;
	// without the nested templates it would be
	// unnecessary to instantiate the container with a type T twice 
};
// ----------------

// example 2 ------
template<typename T>
class weapon
{
public:
	virtual void printWeapon() = 0;
};

template<typename T>
class pistol : public weapon<int32_t>
{
public:
	void printWeapon() override
	{
		std::cout << "im a pistol!\n";
	}
};

template<typename T>
class rifle : public weapon<int32_t>
{
public:
	void printWeapon() override
	{
		std::cout << "im a rifle!\n";
	}
};

template<typename T, template<typename> typename Weapon>
class weaponManager
{
public:
	void writeSmth()
	{
		mWeapon.printWeapon();
	}
private:
	Weapon<T> mWeapon;
};
// ---------

int main()
{
	// example 1 
	myClass<int32_t, std::vector> f;
	// example 2 
	weaponManager<int32_t, pistol> weapon;
	weapon.writeSmth();
}
