#pragma once
#include <string>
#include <vector>

namespace fs
{
	std::string get_filename(const std::string* filepath);
}

namespace args
{
	typedef struct {
		bool valid = false;
		bool help = false;
		bool version = false;
		std::string input_file = "0";
		std::string output_file = "0";
		std::string hash = "0";
	} command_options;

	void parse_args(command_options* options, const std::vector<std::string>* args);
}
