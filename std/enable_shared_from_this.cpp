#include <iostream>
#include <memory>
#include <format> //c++20 

/*
  A brief explanation what std::enable_shared_from_this<> does;
    let us have a class with a method inside which is called "GetSharedPtr";
  the purpose of that is merely giving a pointer to the instance of the class, thats it;
    but if we will return from the function std::make_shared<myClass>() -> we will get another;
    instance of the class, which is inconvinient and maybe u dont want it actually;

    but with the feature std::enable_shared_from_this<> we can just use the one instance of the class;
    and the ref_count will be 2 instead of 1, because we have 2 pointers are pointing on the same block of memory;
*/

// variant 1:
class myClass
{
public:
    std::shared_ptr<myClass> getSharedPtr()
    {
        return std::make_shared<myClass>();
    }
};

// variant 2
class myClass2 : public std::enable_shared_from_this<myClass2>
{
public:
    std::shared_ptr<myClass2> getSharedPtr()
    {
        return shared_from_this();
    }
};

int main()
{
    // variant 1:
    std::shared_ptr<myClass> ptr1 = std::make_shared<myClass>();
    std::cout << std::format("Ref count: {}\n", ptr1.use_count()); // Output: Ref count: 1  
    std::shared_ptr<myClass> ptr2 = ptr1->getSharedPtr();
    std::cout << std::format("Ref count: {}\n", ptr2.use_count()); // Output: Ref count: 1
    // variant 2:
    std::shared_ptr<myClass2> ptr3 = std::make_shared<myClass2>();
    std::cout << std::format("Ref count: {}\n", ptr3.use_count());
    std::shared_ptr<myClass2> ptr4 = ptr3->getSharedPtr();
    std::cout << std::format("Ref count ptr3: {}\n", ptr3.use_count());
    std::cout << std::format("Ref count ptr4: {}\n", ptr4.use_count());

}