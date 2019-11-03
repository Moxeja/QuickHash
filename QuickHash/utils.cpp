#include "utils.h"

std::string fs::get_filename(const std::string* filepath)
{
	size_t last_index = filepath->find_last_of("\\/") + 1;
	std::string filename = filepath->substr(last_index, std::string::npos);
	return filename;
}

void args::parse_args(command_options* options, const std::vector<std::string>* args)
{
	for (int i = 0; i < args->size(); i++)
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
