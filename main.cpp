#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <algorithm>

bool password_cracker(const std::string& password, const std::string& hash)
{
    // simulate cracking the password hash
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return password == hash;
}

int main()
{
    std::string hash = "5f4dcc3b5aa765d61d8327deb882cf99"; // md5 hash of "password"

    std::vector<std::string> passwords = {"password", "123456", "qwerty", "letmein", "monkey",
                                          "football", "starwars", "iloveyou", "admin", "welcome",
                                          "hello", "charlie", "123123", "dragon", "baseball"};

    std::vector<std::thread> threads;
    bool found = false;

    // create and start threads to crack passwords
    for (const auto& password : passwords)
    {
        threads.emplace_back([&found, &password, &hash]() {
            if (password_cracker(password, hash))
            {
                std::cout << "Password found: " << password << std::endl;
                found = true;
            }
        });
    }

    // wait for all threads to finish
    std::for_each(threads.begin(), threads.end(), [](std::thread& t) { t.join(); });

    if (!found)
    {
        std::cout << "Password not found" << std::endl;
    }

    return 0;
}
