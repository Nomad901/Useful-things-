#include <iostream>
#include <format>
#include <string>
#include <filesystem>
#include <fstream>
#include <exception>
#include <unordered_map>
#include <type_traits>
#include <variant>
#include <optional>

// i wanted to use VariantType struct for determining a return type of a variable in std::variant
// it works well, but in order to invoke this, we need to write this huge block of code:
//      tng::JSONValue instance(120);
//      std::cout << std::format("Value: {}\n", instance.getValue<tng::JSONValue::typeVariant::INT>());
// tbh - this is horrendous...

template<typename T>
concept isString = std::is_same_v<std::string, T> ||
				   std::is_same_v<const char*, T>;

template<typename T>
concept isDescreteNumber = std::is_same_v<int32_t, T>  ||
						   std::is_same_v<int64_t, T>  ||
						   std::is_same_v<int16_t, T>  ||
						   std::is_same_v<uint32_t, T> ||
						   std::is_same_v<uint64_t, T> ||
						   std::is_same_v<uint16_t, T>;

template<typename T>
concept isRealNumber = std::is_same_v<float, T>  ||
					   std::is_same_v<double, T> ||
					   std::is_same_v<long double, T>;

template<typename T>
concept ProperValue = isString<T> || isDescreteNumber<T> || isRealNumber<T>;

class JSONValue
{
public:
	enum class typeVariant
	{
		INT = 0,
		FLOAT = 1,
		STRING = 2,
		VECTOR = 3
	};
private:
	template<typeVariant TV>
	struct VariantType;

	template<>
	struct VariantType<typeVariant::INT> { using type = int32_t; };
	template<>
	struct VariantType<typeVariant::FLOAT> { using type = float; };
	template<>
	struct VariantType<typeVariant::STRING> { using type = std::string; };
	template<>
	struct VariantType<typeVariant::VECTOR> { using type = std::vector<JSONValue>; };

	template<typeVariant TV>
	using VariantType_t = typename VariantType<TV>::type;

public:
	JSONValue() = default;
	template<typename T>
	requires ProperValue<T>
	JSONValue(T&& pValue);
	explicit JSONValue(const std::initializer_list<JSONValue>& pArray);
	
	auto at(size_t pIndex) -> JSONValue&;

	template<typename setType>
	requires ProperValue<setType>
	auto setValue(setType&& pValue) -> void;
	auto setArray(const std::initializer_list<JSONValue>& pArray) -> void;
	template<typeVariant TV>
	auto getValue() -> VariantType_t<TV>&;

	auto valueIsString() -> bool;
	auto valueIsReal() -> bool;
	auto valueIsDescrete() -> bool;
	auto valueIsVector() -> bool;
	
private:
	std::variant<int32_t, float, std::string,
				 std::vector<JSONValue>> mValue{ 0 };
	typeVariant mTypeVariant{ typeVariant::INT };
};
