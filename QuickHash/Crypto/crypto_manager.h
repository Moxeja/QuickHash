#pragma once
#include <string>

namespace crypto
{
	std::string calculate_md5(const std::string* filepath);
	std::string calculate_sha1(const std::string* filepath);
	std::string calculate_sha256(const std::string* filepath);
}
