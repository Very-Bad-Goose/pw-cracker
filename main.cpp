#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <openssl/md5.h>

using namespace std;

void print_hex(unsigned char* hash, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    unsigned char md5_hash[MD5_DIGEST_LENGTH];
    char input[1024];
    string hash_str;

    // Ask user to enter a password to hash or a hash string to crack
    if (argc == 1) {
        cout << "Enter a password to hash: ";
        cin.getline(input, sizeof(input));
        MD5((unsigned char*) input, strlen(input), md5_hash);
        cout << "Hash: ";
        print_hex(md5_hash, MD5_DIGEST_LENGTH);
    } else if (argc == 2) {
        hash_str = argv[1];
        if (hash_str.length() != MD5_DIGEST_LENGTH * 2) {
            cerr << "Invalid hash string" << endl;
            return 1;
        }
        for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
            sscanf(hash_str.substr(i * 2, 2).c_str(), "%02x", &md5_hash[i]);
        }
    } else {
        cerr << "Usage: " << argv[0] << " [hash_string]" << endl;
        return 1;
    }

    // Read the dictionary file
    ifstream dictionary("dictionary.txt");
    if (!dictionary.is_open()) {
        cerr << "Error: dictionary.txt not found" << endl;
        return 1;
    }

    // Crack the hash
    string word;
    while (getline(dictionary, word)) {
        MD5((unsigned char*) word.c_str(), word.length(), md5_hash);
        if (memcmp(md5_hash, md5_hash, MD5_DIGEST_LENGTH) == 0) {
            cout << "Password: " << word << endl;
            break;
        }
    }

    return 0;
}
