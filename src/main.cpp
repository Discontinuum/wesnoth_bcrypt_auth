#include <string>
#include <iostream>

#include "hash.hpp"

//prog salt pass
int main (int argc, char* argv[]) {
	if (argc != 3) {
		return 1;
	}
	const std::string salt(argv[1]);
	std::string password(argv[2]);
	auto bcrypt_salt = utils::bcrypt::from_salted_salt(salt);
	auto hash = utils::bcrypt::hash_pw(password, bcrypt_salt);

	const std::string outer_salt = salt.substr(bcrypt_salt.iteration_count_delim_pos + 23);
	if(outer_salt.size() != 32) {
		return 1;
	}

	std::cout << (utils::md5(hash.base64_digest(), outer_salt).base64_digest());
	return 0;
}
