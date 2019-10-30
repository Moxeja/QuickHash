#include "Crypto/crypto_manager.h"
#include "utils.h"

#include <vector>
#include <iostream>

constexpr const char* VERSION = "0.1";

void print_usage()
{
	std::printf("Usage: QuickHasher [options]\n"
		"Options:\n"
		"\t?			Print this help\n"
		"\t-v | --version		Print application version\n"
		"\t-h | --hash [hashes]	Choose hash to use. Default is MD5\n"
		"\t-i | --input		Input file\n"
		"\t-o | --output		Ouput file\n"
		"Hashes:\n"
		"\tmd5\n"
		"\tsha1\n"
		"\tsha256\n");
}

int main(int argc, char* argv[])
{
	// Current max no. of arguments is 7
	if (argc > 1 && argc <= 7)
	{
		std::vector<std::string> allArgs(argv, argv + argc);
		args::command_options options;
		args::parse_args(&options, &allArgs);

		if (!options.valid)
		{
			std::printf("Options are not valid!\n");
			return 2;
		}

		if (options.help)
		{
			print_usage();
			return 0;
		}

		if (options.version)
		{
			std::printf("Program version: %s\n", VERSION);
			return 0;
		}

		crypto::compute_hash(&options);
		return 0;
	}
	else
	{
		print_usage();
		return 1;
	}
	
	return 0;
}
