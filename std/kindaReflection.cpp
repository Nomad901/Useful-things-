template<typename first, typename second>
struct pair
{
	static constexpr std::array<std::string_view, 2> names
	{
		"first",
		"second"
	};
	first mFirst;
	second mSecond;
};

template<typename Object>
void visit(auto pVisitor, Object&& pObject)
{
	if constexpr (pObject.names.size() == 0)
	{}
	else if constexpr (pObject.names.size() == 1)
	{
		auto&& [m0] = std::forward<Object>(pObject);
		pVisitor(pObject.names[0], std::forward<decltype(m0)>(m0));
	}
	else if constexpr (pObject.names.size() == 2)
	{
		auto&& [m0, m1] = std::forward<Object>(pObject);
		pVisitor(pObject.names[0], std::forward<decltype(m0)>(m0));
		pVisitor(pObject.names[1], std::forward<decltype(m1)>(m1));
	}
	else if constexpr (pObject.names.size() == 3)
	{
		auto&& [m0, m1, m2] = std::forward<Object>(pObject);
		pVisitor(pObject.names[0], std::forward<decltype(m0)>(m0));
		pVisitor(pObject.names[1], std::forward<decltype(m1)>(m1));
		pVisitor(pObject.names[2], std::forward<decltype(m2)>(m2));
	}
}

struct myData
{
	static constexpr std::array<std::string_view, 3> names{ "i", "str", "f" };
	int32_t i;
	std::string str;
	float f;
};

int main()
{
	pair<int32_t, float> myPair;
	const auto visitor = [](std::string_view pName, const auto& pValue)
		{
			std::cout << std::format("Name: {}, Value: {}\n", pName, pValue);
		};
	visit(visitor, myPair);
	visit(visitor, myData{ 42, "hello", 32.0f });
}
