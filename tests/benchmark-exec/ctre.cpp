#include <cstdio>
#include <iostream>
#include <fstream> 
#include <regex>
#include "ctre.hpp"
#include <re2/re2.h>
#include <boost/regex.hpp>

extern "C" {

#define PCRE2_CODE_UNIT_WIDTH 8
#define PCRE2_STATIC
#include <pcre2.h>

}

int main (int argc, char ** argv)
{
	using namespace ctre::literals;
	[[maybe_unused]] constexpr auto re = "[0-9a-fA-F]{8,16}?"_ctre;

	auto grep = [&](auto && stream) {
		std::string line;
		while (std::getline(stream, line)) {
			if (bool(re.search(line))) {
				std::cout << line << '\n';
			}
		}
	}; 
	
	if (argc == 1) {
		grep(std::cin);
	} else for (int i = 1; i < argc; ++i) {
		std::string fname{std::string(argv[i])};
		grep(std::ifstream(fname, std::ifstream::in));
	}
}

