#include "cp-notebook/data-structures/dsu.h"

string testDsu(string& s) {
    istringstream iss(s);
    ostringstream oss;
    int n, q, c;
    build();
    iss >> n >> q;
    for (int i = 0, a, b; i < q; i++) {
        iss >> c >> a >> b;
        if (c)
            unite(a, b);
        else
            oss << (find(a) == find(b)) << endl;
    }
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
            testResult = normalizeLineEndings(testResult);
            expectedOutput = normalizeLineEndings(expectedOutput);
            testResult = trim(testResult);
            expectedOutput = trim(expectedOutput);
            assert(testResult == expectedOutput && "Test failed!");

            cout << "Test passed for: " << inputFile << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    string testsDir = string(TEST_DATA_DIR) + "/local_tests/data-structures";
    string dsuDir = testsDir + "/dsu";
    test(dsuDir, testDsu);
    cout << "All test cases passed\n";
    return 0;
}
