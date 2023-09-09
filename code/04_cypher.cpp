// A program to practice string manipulation and working with key-value pairs by implementing a simple half-reversed alphabet cypher.

#include <map>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

std::string transform (const std::string& s)
{

    // Set up key-value pairs
    std::map<char, char> m;
    m['A'] = 'N';
    m['B'] = 'O';
    m['C'] = 'P';
    m['D'] = 'Q';
    m['E'] = 'R';
    m['F'] = 'S';
    m['G'] = 'T';
    m['H'] = 'U';
    m['I'] = 'V';
    m['J'] = 'W';
    m['K'] = 'X';
    m['L'] = 'Y';
    m['M'] = 'Z';
    m['N'] = 'A';
    m['O'] = 'B';
    m['P'] = 'C';
    m['Q'] = 'D';
    m['R'] = 'E';
    m['S'] = 'F';
    m['T'] = 'G';
    m['U'] = 'H';
    m['V'] = 'I';
    m['W'] = 'J';
    m['X'] = 'K';
    m['Y'] = 'L';
    m['Z'] = 'M';

    std::string result = "";
    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];
        if (std::isalpha(c)) {
            char upperC = std::toupper(c); // Convert to uppercase
            result += std::isupper(c) ? m[upperC] : std::tolower(m[upperC]);
        } else {
            result += c;
        }
    }
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Define a test function to check if the result matches the expected value
void testTransform(const std::string& input, const std::string& expected) {
    std::string result = transform(input);
    if (result == expected) {
        std::cout << "Test Passed: " << input << " -> " << result << std::endl;
    } else {
        std::cerr << "Test Failed: " << input << " -> " << result << " (Expected: " << expected << ")" << std::endl;
    }
}

int main() {
    std::cout << "Running tests: " << std::endl;
    testTransform("APPLE", "NCCYR");
    testTransform("ZBBA", "MOON");
    testTransform("Apple", "NCCYR");
    testTransform("APPLE ZBBA 123", "NCCYR MOON 123");
    testTransform("Hello World", "URYYB JBEYQ");

    std::cout << std::endl;
    std::cout << "Type a single character, word or sentence: " << std::endl;
    std::string inputString = "";
    std::getline(std::cin, inputString);

    std::string result = transform(inputString);
    std::cout << std::endl;
    std::cout << "Transformed input is: " << std::endl;
    std::cout << result << std::endl;
}