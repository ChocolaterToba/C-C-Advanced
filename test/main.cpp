#include <gtest/gtest.h>

#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

extern "C" {
#include "make_histogram.h"
#include "nesting_free.h"
#include "processi.h"
#include "processo.h"
}

bool compareFiles(const std::string& p1, const std::string& p2) {
  std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
  std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

  if (f1.fail() || f2.fail()) {
    return false;  //  file problem
  }

  if (f1.tellg() != f2.tellg()) {
    return false;  //  size mismatch
  }

  //  seek back to beginning and use std::equal to compare contents
  f1.seekg(0, std::ifstream::beg);
  f2.seekg(0, std::ifstream::beg);
  return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(f2.rdbuf()));
}

const std::string TESTFILES_PATH = "../test/testfiles/";

TEST(InputTesting, test1) {
    FILE* infile = fopen((TESTFILES_PATH + "InputTest1.txt").c_str(), "r");

    size_t inputSize = 0;
    int testInput[10] = {1, 2, 3, 1, 6, 4, 3, 2, 1, 1};
    int* actualInput = NULL;

    EXPECT_EQ(Processi(infile, &actualInput, &inputSize), EXIT_SUCCESS) <<
    "Processi exited with failure";

    EXPECT_EQ(inputSize, 10) << "Input size should be 10";
    EXPECT_NE(actualInput, nullptr) << "Array actualInput was not created";

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(testInput[i], actualInput[i]) << "Input was read incorrectly";
    }

    free(actualInput);
    fclose(infile);
}

TEST(InputTesting, wrongInput) {
    FILE* infile = fopen((TESTFILES_PATH + "WrongInput1.txt").c_str(), "r");

    size_t inputSize = 0;
    int* actualInput = NULL;

    EXPECT_EQ(Processi(infile, &actualInput, &inputSize), EXIT_FAILURE) <<
    "Processi exited with success on file with no array size";

    fclose(infile);

    infile = fopen((TESTFILES_PATH + "WrongInput2.txt").c_str(), "r");

    EXPECT_EQ(Processi(infile, &actualInput, &inputSize), EXIT_FAILURE) <<
    "Processi exited with success on file with wrong array elements";

    fclose(infile);
}

TEST(HistogramTesting, test1) {
    int testInput[10] = {1, 2, 3, 1, 6, 4, 3, 2, 1, 1};
    int testOutput[2][5] = {{1, 2, 3, 6, 4}, {4, 2, 2, 1, 1}};
    int** actualOutput[2] = {NULL, NULL};
    size_t outputSize = 0;

    EXPECT_EQ(MakeHistogram(testInput, 10, actualOutput, &outputSize),
              EXIT_SUCCESS) << "MakeHistogram exited with failure";

    EXPECT_EQ(outputSize, 5) << "Wrong output size";

    for (size_t i = 0; i < outputSize; ++i) {
        EXPECT_EQ(testOutput[0][i], *actualOutput[0][i]) <<
        "Number is incorrect";
        EXPECT_EQ(testOutput[1][i], *actualOutput[1][i]) <<
        "Frequency is incorrect";
    }

    free(actualOutput[0]);
    NestingFree(actualOutput[1], outputSize);
}

TEST(HistogramTesting, test2) {
    int testInput[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int testOutput[2][10] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                            {1, 1, 1, 1, 1, 1, 1,  1, 1, 1}};
    int** actualOutput[2] = {NULL, NULL};
    size_t outputSize = 0;

    EXPECT_EQ(MakeHistogram(testInput, 10, actualOutput, &outputSize),
              EXIT_SUCCESS) << "MakeHistogram exited with failure";

    EXPECT_EQ(outputSize, 10) << "Wrong output size";

    for (size_t i = 0; i < outputSize; ++i) {
        EXPECT_EQ(testOutput[0][i], *actualOutput[0][i]) <<
        "Number is incorrect";
        EXPECT_EQ(testOutput[1][i], *actualOutput[1][i]) <<
        "Frequency is incorrect";
    }

    free(actualOutput[0]);
    NestingFree(actualOutput[1], outputSize);
}

TEST(HistogramTesting, wrongInput) {
    int testInput[10] = {1, 2, 3, 1, 6, 4, 3, 2, 1, 1};
    size_t outputSize = 0;
    int** actualOutput[2] = {NULL, NULL};

    ASSERT_EQ(MakeHistogram(testInput, 10, actualOutput, NULL),
              EXIT_FAILURE) <<
    "MakeHistogram did not exit with failure when passing NULLs";
    ASSERT_EQ(MakeHistogram(testInput, 10, NULL, &outputSize),
              EXIT_FAILURE) <<
    "MakeHistogram did not exit with failure when passing NULLs";
    ASSERT_EQ(MakeHistogram(NULL, 10, actualOutput, &outputSize),
              EXIT_FAILURE) <<
    "MakeHistogram did not exit with failure when passing NULLs";

    actualOutput[0] = new int*[5];
    EXPECT_EQ(MakeHistogram(testInput, 10, actualOutput, &outputSize),
              EXIT_FAILURE) <<
    "MakeHistogram din not exit with failure when passing not-NULLs in output";
    delete[] actualOutput[0];
    actualOutput[0] = NULL;

    actualOutput[1] = new int*[5];
    EXPECT_EQ(MakeHistogram(testInput, 10, actualOutput, &outputSize),
              EXIT_FAILURE) <<
    "MakeHistogram din not exit with failure when passing not-NULLs in output";
    delete[] actualOutput[1];
}

TEST(OutputTesting, test1) {
    int testOutput[2][4][1] = {{{1}, {2}, {3}, {4}},
                               {{5}, {99999}, {1}, {765}}};
    int** testOutputp[2];  //  testOutput converted to int***
    testOutputp[0] = new int* [4];
    testOutputp[1] = new int* [4];

    for (size_t i = 0; i < 4; ++i) {
      testOutputp[0][i] = testOutput[0][i];
      testOutputp[1][i] = testOutput[1][i];
    }

    FILE* outfile = fopen((TESTFILES_PATH + "OutputActual1.txt").c_str(), "w");

    EXPECT_EQ(Processo(outfile, testOutputp, 4), EXIT_SUCCESS) <<
    "Processio exited with failure";

    fclose(outfile);
    delete[] testOutputp[0];
    delete[] testOutputp[1];

    ASSERT_TRUE(compareFiles(TESTFILES_PATH + "OutputTest1.txt",
                             TESTFILES_PATH + "OutputActual1.txt")) <<
    "Output did not match expected one";
}

TEST(OutputTesting, wrongInput) {
    FILE* outfile = fopen((TESTFILES_PATH + "OutputActual1.txt").c_str(), "w");
    int** testOutputp[2] = {NULL, NULL};

    EXPECT_EQ(Processo(outfile, NULL, 0), EXIT_FAILURE) <<
    "Processio exited with success when getting NULL as outputArray";
    EXPECT_EQ(Processo(outfile, testOutputp, 0), EXIT_FAILURE) <<
    "Processio exited with success when getting NULL as outputArray[0]";
    testOutputp[0] = new int* [4];
    EXPECT_EQ(Processo(outfile, testOutputp, 0), EXIT_FAILURE) <<
    "Processio exited with success when getting NULL as outputArray[1]";

    EXPECT_EQ(Processo(NULL, testOutputp, 0), EXIT_FAILURE) <<
    "Processio exited with success when getting NULL as infile";

    fclose(outfile);
    delete[] testOutputp[0];
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
