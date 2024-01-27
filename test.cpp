//
// Created by zql on 2022/12/30.
//
#include <iostream>
#include <string>
#include <complex>
#include <stdexcept>
#include <fstream>
#include "src/FiltFilt.h"
#include "src/coeff-butter.h"

//Source Files
#include "src/FiltFilt.cpp"
#include "src/Filter.cpp"
#include "src/MathUtilities.cpp"

using namespace std;
typedef std::vector<double> vectord;



std::vector<double> splitCsv(const std::string& p_path,char delim =',')
{
    std::ifstream fs;
    std::vector<double> vec;
    vec.reserve(256);
    fs.open(p_path,std::ios_base::in);
    if(fs.is_open())
    {
        char c;
        std::string cache;
        cache.reserve(20);
        bool exit{false};
        while(fs.get(c)&&!exit){
            if(c=='\n')
            {
                vec.push_back(std::stod(cache));
                exit=true;
            }
            if(c!=delim)
            {
                cache.push_back(c);
            }else{
                vec.push_back(std::stod(cache));
                cache.clear();
                cache.reserve(20);
            }
        }
        fs.close();
    }
    return vec;
}



void signal2file(std::vector<double> signal, std::string filename)
{
    std::ofstream output_file(filename);
    for (const auto &s : signal)
        output_file << s << "\n";
}


int main()
{

    std::vector<double> input_signal = splitCsv("origin.csv");
    std::cout << "input_signal: " << input_signal.size() << std::endl;
    vector <double> y_filtfilt_out1;
    vector<double> output(input_signal.size());

    vectord iir_a = a_4_001;
    vectord iir_b = b_4_001;
    vector<double> coeff_a(iir_a);
    vector<double> coeff_b(iir_b);

    FiltFilt f({ coeff_a, coeff_b });
    f.process(input_signal.data(), input_signal.size(), output);
    signal2file(output, "origin_test.txt");
    std::cout << "output_signal: " << output.size() << std::endl;
    std::cout << "success"<< std::endl;


}

