#include <iostream>
#include <string>
#include <cstring>
#include <chrono>
#include <cmath>

using namespace std;

// Function to generate all possible combinations of characters of a given length
void generate_combinations(string characters, string prefix, int length)
{
    // If the prefix has the desired length, print it
    if (prefix.length() == length) {
        cout << prefix << endl;
        return;
    }
    // Recursively generate combinations with each character of the given set
    for (int i = 0; i < characters.length(); i++) {
        string new_prefix = prefix + characters[i];
        generate_combinations(characters, new_prefix, length);
    }
}

// Function to check if a given password matches the target password
bool check_password(string password, string target)
{
    if (password == target) {
        return true;
    }
    else {
        return false;
    }
}

int main()
{
    // Prompt user to enter the target password
    string target_password;
    cout << "Enter the target password: ";
    cin >> target_password;

    // Define the set of characters that can be used in the password
    string character_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+-=[]{}\\|;':\",./<>?`~";

    // Define the maximum length of the password to be cracked
    int max_password_length = 10;

    // Brute-force the password by trying all possible combinations of characters
    bool password_found = false;
    auto start_time = chrono::high_resolution_clock::now();
    for (int length = 1; length <= max_password_length; length++) {
        generate_combinations(character_set, "", length);
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time).count();

    cout << "Password cracked in " << duration << " seconds." << endl;

    return 0;
}
