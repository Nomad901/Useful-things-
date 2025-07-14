#include <iostream>

// 
// Example with factory pattern
//

class Enemy
{
public:
	virtual ~Enemy() = default;
	
	virtual void attack() = 0;
	virtual void reload() = 0;
	virtual int32_t getHp()  = 0;
};

class Ork : public Enemy
{
public:

	void attack() override
	{
		std::cout << "Ork attack!\n";
	}
	void reload() override
	{
		std::cout << "Ork reload!\n";
	}
	int32_t getHp() override
	{
		std::cout << "Ork is giving his HP!!!\n";
		return mHp;
	}

private:
	int32_t mHp{};
	int32_t mDamage{};
};

class Goblin : public Enemy
{
public:

	void attack() override
	{
		std::cout << "Goblin attack!\n";
	}
	void reload() override
	{
		std::cout << "Goblin reload!\n";
	}
	int32_t getHp() override
	{
		std::cout << "Goblin is giving his HP!!!\n";
		return mHp;
	}

private:
	int32_t mHp{};
	int32_t mDamage{};
};

//
// usage:
//

//int main()
//{
//	std::unique_ptr<Enemy> enemy;
//
//	// Ork case
//	enemy = std::make_unique<Ork>();
//	enemy->attack();
//	enemy->reload();
//	enemy->getHp();
//
//	std::cout << '\n';
//
//	// Goblin case
//	enemy = std::make_unique<Goblin>();
//	enemy->attack();
//	enemy->reload();
//	enemy->getHp();
//}

//
//
//



//
// Example with std::function
//

template<typename>
class function;

template<typename Ret, typename... Args>
class function<Ret(Args...)>
{
public:
	function()
		:ptr(nullptr)
	{}
	function(Ret(*pPtr)(Args...))
	{
		ptr = pPtr;
	}

	function(const function& pOther)
	{
		ptr = pOther.ptr;
	}
	function operator=(const function& pOther)
	{
		if (&pOther == this)
			return *this;
		ptr = pOther.ptr;
		return *this;
	}
	function(function&& pOther)
	{
		ptr = std::move(pOther.ptr);
	}
	function operator=(function&& pOther)
	{
		if (&pOther == this)
			return *this;
		ptr = std::move(pOther.ptr);
		return *this;
	}
	
	function operator()(Args&&... pArgs)
	{
		ptr(std::forward<Args>(pArgs)...);
		return *this;
	}

private:
	Ret(*ptr)(Args...) {};
};

//
// usage:
//

void foo()
{
	std::cout << "im a function!\n";
}

int main()
{
	function<void(void)> f = foo;
	f();
}

//
//
//