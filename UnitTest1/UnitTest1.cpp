#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <string>
#include <cmath>
#include "../Lab12.1c++/lab12.1.cpp"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestCreateBIN)
        {
            char fname[] = "test_input.bin";


            std::istringstream input("1.5\ny\n2.5\ny\n-3.5\nn\n");
            std::streambuf* cinBackup = std::cin.rdbuf();
            std::cin.rdbuf(input.rdbuf());


            CreateBIN(fname);


            std::cin.rdbuf(cinBackup);


            std::ifstream fin(fname, std::ios::binary);
            Assert::IsTrue(fin.is_open(), L"Input file was not created.");


            double expectedNumbers[] = { 1.5, 2.5, -3.5 };
            double readNumber;
            for (double expected : expectedNumbers) {
                fin.read((char*)&readNumber, sizeof(readNumber));
                Assert::AreEqual(expected, readNumber, 0.01);
            }


            fin.read((char*)&readNumber, sizeof(readNumber));
            Assert::IsTrue(fin.eof(), L"File contains unexpected data.");
            fin.close();
        }


        TEST_METHOD(TestProcessBIN)
        {

            char inputFile[] = "test_input.bin";
            char outputFile[] = "test_output.txt";


            std::ofstream fout(inputFile, std::ios::binary);
            double numbers[] = { 1.5, 2.5, -3.5, 4.5 };
            for (double num : numbers) {
                fout.write((char*)&num, sizeof(num));
            }
            fout.close();


            ProcessBIN(inputFile, outputFile);


            std::ifstream fin(outputFile);
            Assert::IsTrue(fin.is_open(), L"Output file was not created.");


            std::string line;
            std::getline(fin, line);
            Assert::AreEqual(std::string("Average of max and min: 0.50"), line);

            std::getline(fin, line);
            Assert::AreEqual(std::string("Average of all numbers: 1.25"), line);

            fin.close();
        }

        TEST_METHOD(TestPrintBIN)
        {

            char fname[] = "test_input.bin";


            std::ofstream fout(fname, std::ios::binary);
            double numbers[] = { 10.0, -5.0, 0.0, 3.3 };
            for (double num : numbers) {
                fout.write((char*)&num, sizeof(num));
            }
            fout.close();


            PrintBIN(fname);


            Logger::WriteMessage("PrintBIN executed successfully.");
        }
    };
}