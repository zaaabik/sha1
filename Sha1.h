#pragma once
#include<string>
#include<vector>
using namespace std;
static class Sha1 {
public:
	static uint8_t* getHash(const uint8_t* fileName,const size_t size);
	static uint8_t* getHash(const string path);
private:
	const static uint64_t maxSize = (2 << 64) - 1;
	const static uint32_t outputBitSize = 160;
	const static uint32_t h0 = 0x67452301;
	const static uint32_t h1 = 0xEFCDAB89;
	const static uint32_t h2 = 0x98BADCFE;
	const static uint32_t h3 = 0x10325476;
	const static uint32_t h4 = 0xC3D2E1F0;
};