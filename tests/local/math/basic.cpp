#include "cp-notebook/math/basic.h"

string testSieve(string& s) {
    sieve();
    istringstream iss(s);
    ostringstream oss;
    int n;
    iss >> n;
    for (int i = 0; i <= n; i++)
        if (!comp[i]) oss << i << " ";
    return oss.str();
}

string testFexp(string& s) {
    istringstream iss(s);
    ostringstream oss;
    long long a, b, r, m;
    iss >> a >> b >> m;
    r = fexp(a, b, m);
    oss << r;
    return oss.str();
}

void test(string& path, string (*testCase)(string&)) {
    string inputDir = path + "/input";
    string outputDir = path + "/output";
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
            string testResult = testCase(inputContent);
            ifstream expectedStream(outputFile);

            if (!expectedStream) {
                cerr << "Failed to open output file: " << outputFile << endl;
                continue;
            }

            string expectedOutput((istreambuf_iterator<char>(expectedStream)),
                                  istreambuf_iterator<char>());
            testResult = trim(testResult);
            expectedOutput = trim(expectedOutput);
            assert(testResult == expectedOutput && "Test failed!");

            cout << "Test passed for: " << inputFile << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    string testsDir = string(TEST_DATA_DIR) + "/local_tests/basic";
    string sieveDir = testsDir + "/sieve";
    string fexpDir = testsDir + "/fexp";
    test(sieveDir, testSieve);
    test(fexpDir, testFexp);
    cout << "All test cases passed\n";
    return 0;
}
