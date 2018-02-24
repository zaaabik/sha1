#include "Sha1.h" 
#include<iostream>
#include<fstream>
#include<cstring>

uint32_t cycleShiftInt32(uint32_t x, uint32_t pos) {
	return (x << pos) | (x >> (32 - pos));
}

uint8_t* Sha1::getHash(const uint8_t* input,const size_t len) {
	union {
		uint32_t longData[80];
		uint8_t data[1];
	};
	auto size = len;



	union {
		uint8_t H[0];
		uint32_t H32[5];
	};

	auto a = H32[0] = h0;
	auto b = H32[1] = h1;
	auto c = H32[2] = h2;
	auto d = H32[3] = h3;
	auto e = H32[4] = h4;
	auto countOfBlocks = ((size) * 8) / 512;
	for (auto i = 0; i < countOfBlocks + 1; ++i) {
		a = H32[0];
		b = H32[1];
		c = H32[2];
		d = H32[3];
		e = H32[4];
		auto defaultSize = 64;
		for (int j = 0; j < defaultSize; ++j) {
			data[j ^ 3] = input[j + (64 * i)];
		}
		if (i == (countOfBlocks)) {			
			defaultSize = len % 64;
			data[defaultSize++ ^ 3] = 0x80;
			while (defaultSize != 56) {
				data[defaultSize++ ^ 3] = 0x0;
			}
			uint64_t bitSize = len * 8;
			uint8_t* totalSize = ((uint8_t*)&(bitSize));
			for (auto n = 8; n;)
				data[defaultSize++ ^ 3] = (totalSize)[--n];
		}
		for (auto j = 16; j < 80; ++j) {
			auto tmp = (longData[j - 3] ^ longData[j - 8] ^ longData[j - 14] ^ longData[j - 16]);
			longData[j] = cycleShiftInt32(tmp, 1);
		}

		for (auto j = 0; j < 80; ++j) {
			uint32_t f, k;
			switch (j / 20) {
			case 0: f = (c^d)&b^d;   k = 0x5a827999; break;
			case 1:	f = b ^ c^d;       k = 0x6ed9eba1; break;
			case 2: f = b & c | d & (b | c); k = 0x8f1bbcdc; break;
			case 3: f = b ^ c^d;       k = 0xca62c1d6; break;
			}
			f += cycleShiftInt32(a, 5) + e + longData[j] + k;
			e = d, d = c, c = cycleShiftInt32(b, 30), b = a, a = f;
		}

		H32[0] += a;
		H32[1] += b;
		H32[2] += c;
		H32[3] += d;
		H32[4] += e;
	}
	
	uint8_t* result = new uint8_t[20];
	for (int n = 0; n < 20; n++) result[n] = H[n ^ 3];
	return result;
}

uint8_t* Sha1::getHash(const string path) {
	std::ifstream inputFile(path, std::ios::binary | std::ios::in);
	if (!inputFile.is_open()) {
		throw std::exception("file doesnt exist!");
	}
	inputFile.seekg(0, ifstream::end);
	size_t size = inputFile.tellg();
	inputFile.seekg(0, ifstream::beg);

	auto byteArray = new uint8_t[size];
	auto res = new uint32_t[size];
	inputFile.read((char*)byteArray, size);
	for (int i = 0; i < size; ++i) {
		res[i ^ 3] = byteArray[i];
	}
	inputFile.close();
	return getHash(byteArray, size);
}