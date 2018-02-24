#include<vector>
#include<iostream>
#include"Sha1.h"
#include<map>
using namespace std;


int main(int argc, char* argv[]) {
	const string pathKey = "-i";
	string path = "";

	std::vector< string> args;
	for (int i = 1; i < argc; ++i) {
		args.push_back(argv[i]);
	}

	if (args.empty()) {
		printf("arguments are required\n");
		return 0;
	}

	for (int i = 0; i < args.size(); ++i) {
		if (args[i] == pathKey) {
			if (i >= args.size()) {
				printf("path is empty\n");
				return 0;
			} else {
				path = args[i + 1];
			}
		}
	}
	if (path == "") {
		printf("path key is required\n");
		return 0;
	}
	try {
		auto hash = Sha1::getHash(path);
		for (int i = 0; i < 20; ++i) {
			printf("%02hhx", hash[i]);
		}
	} catch (exception e) {
		printf(e.what());
	}
    return 0;
}

