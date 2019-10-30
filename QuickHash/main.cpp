#include "Crypto/crypto_manager.h"

#include <vector>
#include <iostream>
#include <fstream>

constexpr const char* VERSION = "0.1";

typedef struct {
	bool valid = false;
	bool help = false;
	bool version = false;
	std::string input_file = "0";
	std::string output_file = "0";
	std::string hash = "0";
} command_options;

void parse_args(command_options* options, const std::vector<std::string>* args)
{
	for (unsigned int i = 0; i < args->size(); i++)
	{
		const std::string temp = args->at(i);
		if (temp == "?")
		{
			options->valid = true;
			options->help = true;
		}
		else if (temp == "-v" || temp == "--version")
		{
			options->valid = true;
			options->version = true;
		}
		else if (temp == "-h" || temp == "--hash")
		{
			i++;
			if (i < args->size())
			{
				options->hash = args->at(i);
			}
			else
			{
				options->valid = false;
				return;
			}
		}
		else if (temp == "-i" || temp == "--input")
		{
			i++;
			if (i < args->size())
			{
				options->input_file = args->at(i);
				options->valid = true;
			}
			else
			{
				options->valid = false;
				return;
			}
		}
		else if (temp == "-o" || temp == "--output")
		{
			i++;
			if (i < args->size())
			{
				options->output_file = args->at(i);
			}
			else
			{
				options->valid = false;
				return;
			}
		}
	}
}

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

std::string get_filename(const std::string filepath)
{
	size_t last_index = filepath.find_last_of("\\/")+1;
	std::string filename = filepath.substr(last_index, std::string::npos);
	return filename;
}

void compute_hash(const command_options* options)
{
	// Check if file exists
	std::ifstream file(options->input_file.c_str());
	if (!file.good())
	{
		std::printf("Could not read file!\n");
		return;
	}
	file.close();

	// Calculate and print hash result
	std::string hash_string("null");
	std::string filepath = options->input_file;
	if (options->hash == "sha1")
	{
		hash_string = crypto::calculate_sha1(&filepath);
		std::printf("\nSHA1: %s\n", hash_string.c_str());
	}
	else if (options->hash == "sha256")
	{
		hash_string = crypto::calculate_sha256(&filepath);
		std::printf("\nSHA256: %s\n", hash_string.c_str());
	}
	else if (options->hash == "md5" || options->hash == "0")
	{
		hash_string = crypto::calculate_md5(&filepath);
		std::printf("\nMD5: %s\n", hash_string.c_str());
	}
	else
	{
		std::printf("No suitable hash selected!\n");
		return;
	}

	// Output to file if requested
	if (options->output_file != "0")
	{
		std::ofstream file(options->output_file, std::ofstream::trunc);
		file.write(hash_string.c_str(), hash_string.size());
		file.write("   ", 3);

		std::string filename = get_filename(options->input_file);
		filename.append("\n");

		file.write(filename.c_str(), filename.size());
		file.close();
	}
}

int main(int argc, char* argv[])
{
	// Current max no. of arguments is 7
	if (argc > 1 && argc <= 7)
	{
		std::vector<std::string> allArgs(argv, argv + argc);
		command_options options;
		parse_args(&options, &allArgs);

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

		compute_hash(&options);
		return 0;
	}
	else
	{
		print_usage();
		return 1;
	}
	
	return 0;
}
