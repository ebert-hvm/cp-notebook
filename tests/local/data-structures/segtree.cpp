#include "cp-notebook/data-structures/segtree.h"

string testSegtree(string& s) {
    istringstream iss(s);
    ostringstream oss;
    int n, q, a, b, t;
    iss >> n >> q;
    for (int i = 0, x; i < n; i++) {
        iss >> x;
        add(i + 1, x);
    }
    while (q--) {
        iss >> t >> a >> b;
        if (t == 1)
            add(a, b - sum(a) + sum(a - 1));
        else
            oss << sum(b) - sum(a - 1) << "\n";
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
    string segtreeDir = testsDir + "/segtree";
    test(segtreeDir, testSegtree);
    cout << "All test cases passed\n";
    return 0;
}
