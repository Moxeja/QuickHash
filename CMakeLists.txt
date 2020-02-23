cmake_minimum_required(VERSION 3.8)

project(QuickHasher)

set(SRC	QuickHash/utils.h
		QuickHash/Crypto/crypto_manager.h
		QuickHash/Crypto/md5.h
		QuickHash/Crypto/sha1.h
		QuickHash/Crypto/sha256.h
		QuickHash/Crypto/sha512.h

		QuickHash/main.cpp
		QuickHash/utils.cpp
		QuickHash/Crypto/crypto_manager.cpp
		QuickHash/Crypto/md5.c
		QuickHash/Crypto/sha1.c
		QuickHash/Crypto/sha256.c
		QuickHash/Crypto/sha512.c)

add_executable(quickhasher ${SRC})
