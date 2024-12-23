#include "cp-notebook/data-structures/sparse.h"
namespace sparse {
string testSparse(string& s) {
    istringstream iss(s);
    ostringstream oss;
    int q, a, b;
    iss >> n >> q;
    for (int i = 0; i < n; i++) {
        iss >> v[i];
    }
    build();
    while (q--) {
        iss >> a >> b;
        a--, b--;
        oss << query(a, b) << "\n";
    }
    return oss.str();
}
}  // namespace sparse

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
    string sparseDir = testsDir + "/sparse";
    test(sparseDir, sparse::testSparse);
    cout << "All test cases passed\n";
    return 0;
}
