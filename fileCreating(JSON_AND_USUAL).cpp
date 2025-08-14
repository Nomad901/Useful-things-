int main()
{
  if (std::filesystem::exists(pPath))
  	mFstream.open(pPath, pOpenModes);
  else
  {
  	mFstream.open(pPath, std::ios::app);
  	mFstream.close();
  	mFstream.open(pPath, pOpenModes);
  }
  if (!mFstream.is_open())
  	std::cout << std::format("[PATH] {} [FILE] {} [LINE] {}\n", pPath.string() + " is not opened!", 
  															    __FILE__, __LINE__);
  mModes = pOpenModes;
  mPath = pPath;
  if (pIsJSONstream && (pOpenModes & std::ios::in))
  {
  	try
  	{
  		// setting the pointer of the file on the first value 
  		// then we are checking if the next element is an end or not
  		mFstream.seekg(0);
  		if (mFstream.peek() != std::ifstream::traits_type::eof())
  			mJSONstream = nlohmann::json::parse(mFstream);
  		else
  			mJSONstream = nlohmann::json::object();
  		mIsJSONfile = pIsJSONstream;
  	}
  	catch (...)
  	{
  		std::cerr << "Json file was not parsed!\n";
  		mIsJSONfile = false;
  	}
  }
}
