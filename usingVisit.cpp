/*
  small use of std::visit() function on the lines 56-84. never used this before and looks so interesting, guess need to preserve for the future.
*/


  void JSONObject::addNumber(std::string& pKey, std::string_view pNumbers,
							   tng::JSONObject& pObject)
	{
		if (!std::isdigit(pNumbers[0]) ||
			!std::isdigit(pNumbers[1]))
			throw JSONException("Array does not contain any numbers!\n");
		enum class type
		{
			INT = 0,
			UINT = 1,
			FLOAT = 2
		} typeNumbers;

		std::variant<int32_t, uint32_t, float> storageChecker;
		if (pNumbers.find('.') != std::string::npos)
		{
			storageChecker = 1.0f;
			typeNumbers = type::FLOAT;
		}
		else if (pNumbers.find('-') != std::string::npos)
		{
			storageChecker = -1;
			typeNumbers = type::INT;
		}
		else
		{
			storageChecker = 1;
			typeNumbers = type::UINT;
		}

		struct Values
		{
			Values()
			{
				intVector.reserve(50);
				uintVector.reserve(50);
				floatVector.reserve(50);
			}

			std::vector<int32_t> intVector;
			std::vector<uint64_t> uintVector;
			std::vector<float> floatVector;

			bool isInt{ false };
			bool isUint{ false };
			bool isFloat{ false };
		} values;

		
		std::visit([&values](const auto& value)
			{
				using type = std::decay_t<decltype(value)>;

				if constexpr (std::is_same_v<type, int32_t>)
				{
					values.isInt = true;
					values.isUint = false;
					values.isFloat = false;
				}
				else if constexpr (std::is_same_v<type, uint64_t>)
				{
					values.isUint = true;
					values.isInt = false;
					values.isFloat = false;
				}
				else if constexpr (std::is_same_v<type, float>)
				{
					values.isFloat = true;
					values.isInt = false;
					values.isUint = false;
				}
				else
				{
					values.isInt = true;
					values.isUint = false;
					values.isFloat = false;
				}
			}, storageChecker);

		
		std::string tmpNumber;
		for (auto& i : pNumbers)
		{
			if (std::isdigit(i))
				tmpNumber.push_back(i);
			else
			{
				switch (typeNumbers)
				{
				case type::INT:
				{
					int32_t var = std::stoi(tmpNumber);
					values.intVector
				}
				break;
				case type::UINT:
				{
					uint64_t var = std::stoul(tmpNumber);
					storageNumbers.push_back(var);
				}
					break;
				case type::FLOAT:
				{
					float var = std::stof(tmpNumber);
					storageNumbers.push_back(var);
				}
					break;
				default:
					throw JSONException("Somehow we found a type which does not exist >:(\n");
				}
				tmpNumber.clear();
			}
		}
		if (!storageNumbers.empty())
		{
			std::vector<tng::JSONValue> values;
			for (auto& i : storageNumbers)
			{
				tng::JSONValue value;
				switch (typeNumbers)
				{
				case type::INT:
					value.setValue((int32_t)i);
					break;
				case type::UINT:
					value.setValue((uint32_t)i);
					break;
				case type::FLOAT:
					value.setValue((float)i);
					break;
				default:
					throw JSONException("Somehow we found a type which does not exist >:(\n");
				}
				values.push_back(value);
			}
			pObject.addObject(pKey, tng::JSONValue(values));
		}
	}
