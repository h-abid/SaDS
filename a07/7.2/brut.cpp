
#include <iostream>
#include <inttypes.h>
#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

uint64_t pow_mod(uint64_t x){
	for (int i = 0; i < 1234567; i++){
		x *= x;
		x %= 9993201131;
	}
	return x;
}


uint64_t my_hash(unsigned long w){
	uint64_t h = 0;
	h = pow_mod(h + 2 + w); // input assumed to be 32 bits
	cout << w << " hashes to " << h << endl;
	return h;
}

int main (){
	unordered_map<uint64_t, unsigned long> my_map;
	uint64_t res = 0;
	unsigned long start = 0;
	for (unsigned long i = start; i < ULONG_MAX; i++) {
		if (i > start) {
			my_map[res] = i-1;
		}
		res = my_hash(i);
		if (my_map.find(res) != my_map.end()) {
			cout << "Collisions on " << my_map[res] << " and " << i << endl;
			break;
		}
	}
	return 0;
}

