#include <fstream>
#include <string>

#include "crypto_manager.h"
#include "md5.h"
#include "sha1.h"
#include "sha256.h"

namespace crypto
{
	constexpr int MD5_BUFFER_LEN = 16;
	constexpr int MD5_STRING_LEN = MD5_BUFFER_LEN * 2;

	constexpr int SHA1_BUFFER_LEN = 20;
	constexpr int SHA1_STRING_LEN = SHA1_BUFFER_LEN * 2;

	constexpr int SHA256_BUFFER_LEN = 32;
	constexpr int SHA256_STRING_LEN = SHA256_BUFFER_LEN * 2;

	constexpr int CHUNK_SIZE = 4096;

	std::string buffer_to_string(size_t str_len,
		const unsigned char* buffer, size_t buf_len)
	{
		std::string hash_string(str_len, 0);
		for (unsigned int i = 0; i < buf_len; i++)
		{
			constexpr auto hex_val = "0123456789ABCDEF";
			hash_string[i * 2] = hex_val[buffer[i] >> 4];
			hash_string[(i * 2) + 1] = hex_val[buffer[i] & 15];
		}

		return hash_string;
	}

#pragma warning(push)
#pragma warning(disable: 4244)
	std::string calculate_md5(std::string* filepath)
	{
		unsigned char hash_result[MD5_BUFFER_LEN];
		mbedtls_md5_context ctx;
		mbedtls_md5_init(&ctx);
		mbedtls_md5_starts_ret(&ctx);

		std::ifstream file(*filepath, std::ifstream::binary);
		char buffer[CHUNK_SIZE] = { 0 };
		while (!file.eof())
		{
			file.read(buffer, CHUNK_SIZE);
			unsigned int bytes_read = file.gcount();
			mbedtls_md5_update_ret(&ctx, (unsigned char*)buffer, bytes_read);
		}
		file.close();
		mbedtls_md5_finish_ret(&ctx, hash_result);

		return buffer_to_string(MD5_STRING_LEN, hash_result, MD5_BUFFER_LEN);
	}

	std::string calculate_sha1(std::string* filepath)
	{
		unsigned char hash_result[SHA1_BUFFER_LEN];
		sha1_context ctx;
		sha1_starts(&ctx);

		std::ifstream file(*filepath, std::ifstream::binary);
		char buffer[CHUNK_SIZE] = { 0 };
		while (!file.eof())
		{
			file.read(buffer, CHUNK_SIZE);
			unsigned int bytes_read = file.gcount();
			sha1_update(&ctx, (unsigned char*)buffer, bytes_read);
		}
		file.close();
		sha1_finish(&ctx, hash_result);

		return buffer_to_string(SHA1_STRING_LEN, hash_result, SHA1_BUFFER_LEN);
	}

	std::string calculate_sha256(std::string* filepath)
	{
		unsigned char hash_result[SHA256_BUFFER_LEN];
		mbedtls_sha256_context ctx;
		mbedtls_sha256_init(&ctx);
		mbedtls_sha256_starts_ret(&ctx, 0);

		std::ifstream file(*filepath, std::ifstream::binary);
		char buffer[CHUNK_SIZE] = { 0 };
		while (!file.eof())
		{
			file.read(buffer, CHUNK_SIZE);
			unsigned int bytes_read = file.gcount();
			mbedtls_sha256_update_ret(&ctx, (unsigned char*)buffer, bytes_read);
		}
		file.close();
		mbedtls_sha256_finish_ret(&ctx, hash_result);

		return buffer_to_string(SHA256_STRING_LEN, hash_result, SHA256_BUFFER_LEN);
	}
#pragma warning(pop)
}
