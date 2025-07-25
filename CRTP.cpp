#include <iostream>

template<typename T>
class Singleton
{
public:
	static void init()
	{
		shutDown();
		mInstance = new T();
	}
	static T* getInstance()
	{
		return mInstance;
	}
	static void shutDown()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	Singleton(const Singleton&) = delete;
	Singleton operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton operator=(Singleton&&) = delete;
protected:
	Singleton() = default;
	~Singleton() = default;
private:
	static T* mInstance;
};
template<typename T>
T* Singleton<T>::mInstance = nullptr;

class Assets : public Singleton<Assets>
{
public:
	void printSmth()
	{
		std::cout << "Im printing smth!\n";
	}
	
	friend class Singleton<Assets>;
};

int main()
{
	Assets::init();
	Assets::getInstance()->printSmth();
	Assets::shutDown();
}
