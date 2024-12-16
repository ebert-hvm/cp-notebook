#include "cp-notebook/math/basic.h"

string test(string& s) {
    sieve();
    istringstream iss(s);
    ostringstream oss;
    int n;
    iss >> n;
    for (int i = 0; i <= n; i++)
        if (!comp[i]) oss << i << " ";
    return oss.str();
}

int main(int argc, char* argv[]) {
    string inputDir = string(TEST_DATA_DIR) + "/local_tests/basic/input";
    string outputDir = string(TEST_DATA_DIR) + "/local_tests/basic/output";

    for (const auto& entry : filesystem::directory_iterator(inputDir)) {
        if (entry.is_regular_file()) {
            string inputFile = entry.path().string();
            string outputFile = outputDir + "/" + entry.path().filename().string();

            ifstream inputStream(inputFile);
            if (!inputStream) {
                cerr << "Failed to open input file: " << inputFile << endl;
                continue;
            }
            stringstream buffer;
            buffer << inputStream.rdbuf();

            string inputContent = buffer.str();
            string testResult = test(inputContent);
            ifstream expectedStream(outputFile);

            if (!expectedStream) {
                cerr << "Failed to open output file: " << outputFile << endl;
                continue;
            }

            string expectedOutput((istreambuf_iterator<char>(expectedStream)),
                                  istreambuf_iterator<char>());
            testResult = trim(testResult);
            expectedOutput = trim(expectedOutput);
            cerr << testResult << endl;
            cerr << expectedOutput << endl;
            assert(testResult == expectedOutput && "Test failed!");

            cout << "Test passed for: " << inputFile << endl;
        }
    }
    cout << "All test cases passed.\n";
    return 0;
}
