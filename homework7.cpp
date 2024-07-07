#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

void removeUnacceptableWords(const string& inputFilePath, const string& wordsFilePath, const string& outputFilePath) {
    ifstream inputFile(inputFilePath);
    ifstream wordsFile(wordsFilePath);
    ofstream outputFile(outputFilePath);

    if (!inputFile || !wordsFile || !outputFile) {
        cerr << "Error opening one of the files." << endl;
        return;
    }

    unordered_set<string> unacceptableWords;
    string word;
    while (wordsFile >> word) {
        unacceptableWords.insert(word);
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string word;
        bool firstWord = true;
        while (iss >> word) {
            if (unacceptableWords.find(word) == unacceptableWords.end()) {
                if (!firstWord) {
                    outputFile << " ";
                }
                outputFile << word;
                firstWord = false;
            }
        }
        outputFile << "\n";
    }

    inputFile.close();
    wordsFile.close();
    outputFile.close();
}

int main() {
    string inputFilePath = "input.txt";
    string wordsFilePath = "unacceptable_words.txt";
    string outputFilePath = "output.txt";

    removeUnacceptableWords(inputFilePath, wordsFilePath, outputFilePath);

    return 0;
}


//если честно, вот эту таблицу транслита я сделал с чатом гпт, так как банально лень было б писать это все(именно таблицу транслита)
unordered_map<char, string> createTranslitMap() {
    unordered_map<char, string> translitMap = {
        {'А', "A"}, {'а', "a"}, {'Б', "B"}, {'б', "b"},
        {'В', "V"}, {'в', "v"}, {'Г', "H"}, {'г', "h"},
        {'Ґ', "G"}, {'ґ', "g"}, {'Д', "D"}, {'д', "d"},
        {'Е', "E"}, {'е', "e"}, {'Є', "Ye"}, {'є', "ie"},
        {'Ж', "Zh"}, {'ж', "zh"}, {'З', "Z"}, {'з', "z"},
        {'И', "Y"}, {'и', "y"}, {'І', "I"}, {'і', "i"},
        {'Ї', "Yi"}, {'ї', "i"}, {'Й', "Y"}, {'й', "i"},
        {'К', "K"}, {'к', "k"}, {'Л', "L"}, {'л', "l"},
        {'М', "M"}, {'м', "m"}, {'Н', "N"}, {'н', "n"},
        {'О', "O"}, {'о', "o"}, {'П', "P"}, {'п', "p"},
        {'Р', "R"}, {'р', "r"}, {'С', "S"}, {'с', "s"},
        {'Т', "T"}, {'т', "t"}, {'У', "U"}, {'у', "u"},
        {'Ф', "F"}, {'ф', "f"}, {'Х', "Kh"}, {'х', "kh"},
        {'Ц', "Ts"}, {'ц', "ts"}, {'Ч', "Ch"}, {'ч', "ch"},
        {'Ш', "Sh"}, {'ш', "sh"}, {'Щ', "Shch"}, {'щ', "shch"},
        {'Ю', "Yu"}, {'ю', "iu"}, {'Я', "Ya"}, {'я', "ia"},
        {'Ь', ""}, {'ь', ""}, {'\'', ""}
    };
    return translitMap;
}

void transliterate(const string& inputFilePath, const string& outputFilePath) {
    unordered_map<char, string> translitMap = createTranslitMap();

    ifstream inputFile(inputFilePath);
    ofstream outputFile(outputFilePath);

    if (!inputFile || !outputFile) {
        cerr << "Error opening one of the files." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        string transliteratedLine;
        for (char ch : line) {
            if (translitMap.find(ch) != translitMap.end()) {
                transliteratedLine += translitMap[ch];
            }
            else {
                transliteratedLine += ch;
            }
        }
        outputFile << transliteratedLine << "\n";
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    string inputFilePath = "ukrainian_text.txt";
    string outputFilePath = "transliterated_text.txt";

    transliterate(inputFilePath, outputFilePath);

    return 0;
}