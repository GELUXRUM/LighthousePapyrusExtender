#pragma once

namespace Papyrus::String
{
	inline int HexToInt(IVM& a_vm, VMStackID a_stackID, std::monostate,
		std::string a_hexString)
	{
		// Check that the input string is not empty
		if (a_hexString.empty()) {
			a_vm.PostError("String is empty", a_stackID, Severity::kError);
			return -1;
		}

		// Check in case the user inputs invalid characters
		const std::regex hexRegex("[0-9a-fA-F]+");

		if (!std::regex_match(a_hexString, hexRegex)) {
			a_vm.PostError("Invalid string", a_stackID, Severity::kError);
			return -1;
		}

		// Convert the hexadecimal string to an unsigned integer
		uint32_t result = 0;
		try {
			result = std::stoul(a_hexString, nullptr, 16);
		} catch (std::exception&) {
			a_vm.PostError("Invalid string", a_stackID, Severity::kError);
			return 0;
		}

		return result;
	}

	inline std::string IntToBin(std::monostate,
		int a_numToConvert,
		int a_binWidth,
		bool a_addPrefix)
	{
		std::string outputString{ std::bitset<32>(a_numToConvert).to_string() };

		while (a_binWidth < outputString.length()) {
			if (outputString.front() == '0') {
				outputString.erase(0, 1);
			} else {
				break;
			}
		}

		if (a_addPrefix == 1) {
			outputString.insert(0, "0b");
		}

		return outputString;
	}

	inline std::string IntToHex(std::monostate,
		int a_numToConvert,
		int a_hexWidth,
		bool a_addPrefix)
	{
		std::stringstream tempStringStream{ "" };

		tempStringStream << std::hex << a_numToConvert;

		std::string outputString = tempStringStream.str();

		if (a_hexWidth > 0 && a_hexWidth > outputString.length()) {
			if (a_hexWidth > 8) {
				a_hexWidth = 8;
			}
			while (a_hexWidth > outputString.length()) {
				outputString.insert(0, "0");
			}
		}
		if (a_addPrefix == 1) {
			outputString.insert(0, "0x");
		}

		return outputString;
	}

	inline int StringToInt(std::monostate,
		std::string a_intString)
	{
		int outputInt{ 0 };

		outputInt = std::stoi(a_intString);

		return outputInt;
	}

	std::string ToLower(std::monostate,
		const std::string a_str)
	{
		std::string lowercaseStr;

		size_t length = std::strlen(a_str.c_str());

		for (size_t i = 0; i < length; ++i) {
			lowercaseStr += static_cast<char>(std::tolower(static_cast<unsigned char>(a_str.c_str()[i])));
		}

		return lowercaseStr;
	}

	std::string ToUpper(std::monostate,
		const std::string a_str)
	{
		std::string uppercaseStr;

		size_t length = std::strlen(a_str.c_str());

		for (size_t i = 0; i < length; ++i) {
			uppercaseStr += static_cast<char>(std::toupper(static_cast<unsigned char>(a_str.c_str()[i])));
		}

		return uppercaseStr;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "HexToInt", HexToInt, true);
		a_vm.BindNativeMethod("Lighthouse", "IntToBin", IntToBin, true);
		a_vm.BindNativeMethod("Lighthouse", "IntToHex", IntToHex, true);
		a_vm.BindNativeMethod("Lighthouse", "StringToInt", StringToInt, true);
		a_vm.BindNativeMethod("Lighthouse", "ToLower", ToLower, true);
		a_vm.BindNativeMethod("Lighthouse", "ToUpper", ToUpper, true);

		logger::info("String functions registered.");
	}
}
