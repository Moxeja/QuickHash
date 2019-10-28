#pragma once
#include <string>

namespace crypto
{
	std::string calculate_md5(std::string* filepath);
	std::string calculate_sha1(std::string* filepath);
	std::string calculate_sha256(std::string* filepath);
}
