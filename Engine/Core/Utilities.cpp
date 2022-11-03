#include "Utilities.h" 
#include <algorithm> 

namespace Bear
{
	std::string ToLower(const std::string& str)
	{
		std::string lower = str;
		// convert string characters to lower case 
		std::transform(str.begin(), str.end(), lower.begin(),[](char c) { return std::tolower(c); });

		return lower;
	}

	std::string ToUpper(const std::string& str)
	{
		std::string upper = str;
		// convert string characters to upper case 
		std::transform(str.begin(), str.end(), upper.begin(),[](char c) { return std::toupper(c); });

		return upper;
	}

	bool CompareIgnoreCase(const std::string& str1, const std::string& str2)
	{
		// if string lengths don't match return false 
		if (str1.length() != str2.length()) return false;

		// returns false if string characters aren't equal 
		if (ToLower(str1) == ToLower(str2)) return true;
		else return false;
	}
}