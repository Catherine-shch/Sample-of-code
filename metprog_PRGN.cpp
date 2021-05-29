#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

std::vector<size_t> metod_square(size_t n, size_t min_, size_t max_, size_t seed)
{
    std::vector<size_t> sample = {};
    std::string size_string = std::to_string(seed);
    size_t new_number = seed;
    for (int i = 0; i < n; ++i) {
        new_number *= new_number;
        std::string number = std::to_string(new_number);
        if (number.size() != 2*size_string.size()) number = '0' + number;
        std:: string newnumber = "";
        for (size_t j = 2*size_string.size()/ 4 + 1 - 1; j <= 2 * 3 * size_string.size() / 4 - 1; ++j) {
            newnumber += number[j - 1];
        }
        int new_n = std::stoi(newnumber);
        new_number = static_cast<size_t> (new_n);
        sample.push_back(new_number);
    }
    return sample;
}

std::vector<size_t> linear_cong(size_t n, size_t min_, size_t max_, size_t seed)
{
    std::vector<size_t> sample = {};
    size_t a = 22695477;
    size_t m = pow(2, 16);
    size_t c = 1;
    for (int i = 0; i < n; ++i) {
        seed = (a * seed + c) % m + 17;
        sample.push_back(seed);
    }
    return sample;
}

double middle(std::vector<size_t> PRNG) {
    double sum = 0;
    for (auto a : PRNG) sum += a;
    sum /= PRNG.size();
    return sum;
}

double moment2(std::vector<size_t> PRNG) {
    double sum = 0;
    for (auto a : PRNG) sum += a * a;
    sum /= PRNG.size();
    return sum;
}

double standart_deviation(std::vector<size_t> PRNG) {
    return std::sqrt(moment2(PRNG) - middle(PRNG) * middle(PRNG));
}

double coef_of_variation(std::vector<size_t> PRNG) {
    return standart_deviation(PRNG) / middle(PRNG) * 100;
}

double xi_square(std::vector<size_t> PRNG) {
    size_t count_of_group = 1 + std::log2(PRNG.size());
    std::sort(PRNG.begin(), PRNG.end());
    size_t min_ = PRNG[0];
    size_t max_ = PRNG[PRNG.size() - 1];
    size_t difference = max_ - min_;
    size_t size_of_group = difference / count_of_group;
    std::vector <size_t> group = {};
    for (int i = 0; i < count_of_group; ++i) group.push_back(0);
    for (int i = 0; i < PRNG.size(); ++i) {
        for (int j = 0; j < count_of_group; ++j) {
            if (PRNG[i] < (j + 1) * size_of_group) { ++group[j]; break;}
        }
    }
    double probability = static_cast<double>(1)/count_of_group;
    double xi = 0;
    for (int i = 0; i < count_of_group; ++i) {
        xi += (group[i] - probability * PRNG.size()) * (group[i] - probability * PRNG.size()) / (probability * PRNG.size());
    }
    std::cout << count_of_group << " " << size_of_group <<" " << difference << "\n";
    return xi;
}




int main()
{
    auto t1 = std::chrono::steady_clock::now();
    std::vector<size_t> a = metod_square(1000000, 0, 0, 56123);
    auto t2 = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration<double>(t2 - t1).count() << "\n";
     //for (auto c : a) std::cout << c << "\n";
    t1 = std::chrono::steady_clock::now();
    std::vector<size_t> b = linear_cong(1000000, 0, 0, 19);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration<double>(t2 - t1).count() << "\n";
    //for (auto c : b) std::cout << c << "\n";
    //std::cout << "Xi: " << xi_square(a) << "\n";
    //std::cout << coef_of_variation(a) << "\n";
    //std::cout << standart_deviation(a) << "\n";
    //std::cout << middle(a) << "\n";
    // t1 = std::chrono::high_resolution_clock::now();
    t1 = std::chrono::steady_clock::now();
    std::random_device rd;
    std::mt19937 prng{ rd() };
    std::uniform_int_distribution <> dist(0, 60000);
    for (int i = 0; i < 1000000; ++i) {
        int random_selection = dist(prng);
    }
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration<double>(t2 - t1).count() << "\n";
}
