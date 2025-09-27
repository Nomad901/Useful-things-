class benchmark
{
public:
	benchmark()
	{
		point1 = std::chrono::high_resolution_clock::now();
	}
	int getResult()
	{
		point2 = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(point2 - point1).count();
	}
	~benchmark()
	{
		point2 = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(point2 - point1).count() << '\n';
	}
	std::chrono::steady_clock::time_point point1;
	std::chrono::steady_clock::time_point point2;
};

void Program::initModels()
{
	// museum
	{
		benchmark bench; 
		mModelProperties.mModel.push_back(std::make_unique<Model>(glm::vec3(2.0f),
																  mProgramProperties.mResourcePath + "Models/museum.obj", typeModels::OBJ,
																  mModelProperties.mTextures[0], std::make_pair(0, 0)));
		std::cout << std::format("Time OBJ loader: {}\n", bench.getResult() * 0.0001); //Time OBJ loader: 2245.8174
																					   // 22458316
	}
	{
		benchmark bench;
		mModelProperties.mModel.push_back(std::make_unique<Model>(glm::vec3(2.0f),
																  mProgramProperties.mResourcePath + "Models/museum.obj", typeModels::ANY,
																  mModelProperties.mTextures[0], std::make_pair(0, 0)));
		std::cout << std::format("Time Assimp loader: {}\n", bench.getResult() * 0.0001); //Time OBJ loader: 4789.3732
																					      // 47893838
	}
