#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::string readCode(const std::string& filename) {
    std::ifstream s(filename);
    std::stringstream buffer;
    buffer << s.rdbuf();
    return buffer.str();
}

void interpret(const std::string& code) {
    
    int codeIndex{ 0 };
    std::vector<char> tape(50000, 0);
    int tapeIndex{ 0 };
    std::vector<int> stack_loop_addr;

    while (codeIndex < code.length()) {
        char c = code[codeIndex];
        switch (c) {
        case '>':
            ++tapeIndex;
            ++codeIndex;
            break;
        case '<':
            --tapeIndex;
            ++codeIndex;
            break;
        case '+':
            ++tape[tapeIndex];
            ++codeIndex;
            break;
        case '-':
            --tape[tapeIndex];
            ++codeIndex;
            break;
        case '.':
            putchar(tape[tapeIndex]);
            ++codeIndex;
            break;
        case ',':
            tape[tapeIndex] = getchar();
            ++codeIndex;
            break;
        case '[':
            if (tape[tapeIndex] == 0) {
                int temp_depth = 1;
                while (true) {
                    ++codeIndex;
                    if (code[codeIndex] == '[') {
                        ++temp_depth;
                    }
                    else if (code[codeIndex] == ']') {
                        --temp_depth;
                    }
                    if (code[codeIndex] == ']' && temp_depth == 0) {
                        break;
                    }
                }
            }
            else {
                stack_loop_addr.push_back(codeIndex);
            }
            ++codeIndex;
            break;
        case ']':
            codeIndex = stack_loop_addr[stack_loop_addr.size() - 1];
            stack_loop_addr.pop_back();
            break;
        default:
            ++codeIndex;
            break;
        }
    }
}

int main(int argc, char **argv)
{
    std::cout << "Braindo v. 1.0\n";
    if (argc < 2) {
        std::cout << "Usage: braindo.exe filename\n";
        return 0;
    }

    std::string filename{ argv[1] };
    std::string code{ readCode(filename) };
    interpret(code);
}

