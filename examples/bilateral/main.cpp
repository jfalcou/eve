//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
// Standalone benchmark for the 1D bilateral filter. Build it against an installed EVE and run it
// as is - the defaults are deliberately small so this stays cheap under emulation. For a figure
// that means something on your machine, ask for more work:
//
//   ./bilateral --size 50000 --iterations 2000 --csv
//
//==================================================================================================
#include "bilateral.hpp"

#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

namespace
{
  // Reads one sample back so the optimiser cannot discard a filter pass nobody looks at.
  float keep(std::vector<float> const& data)
  {
    static volatile float sink;
    sink = data[data.size() / 2];
    return sink;
  }

  template<typename Func>
  std::vector<double> run(std::string const& name, int iterations, Func&& func)
  {
    std::vector<double> times(iterations);

    for(int i = 0; i < iterations; ++i)
    {
      auto start = std::chrono::high_resolution_clock::now();
      func();
      auto stop = std::chrono::high_resolution_clock::now();

      times[i] = std::chrono::duration<double, std::milli>(stop - start).count();
    }

    double average = std::accumulate(times.begin(), times.end(), 0.0) / iterations;
    std::cout << "[" << std::left << std::setw(12) << name << "] Average time: " << average << " ms";

    return times;
  }

  double average_of(std::vector<double> const& times)
  {
    return std::accumulate(times.begin(), times.end(), 0.0) / times.size();
  }

  int value_of(int argc, char** argv, std::string const& option, int fallback)
  {
    for(int i = 1; i + 1 < argc; ++i)
      if(option == argv[i]) return std::stoi(argv[i + 1]);

    return fallback;
  }
}

int main(int argc, char** argv)
{
  int  size       = value_of(argc, argv, "--size"      , 4096);
  int  iterations = value_of(argc, argv, "--iterations",   20);
  bool csv        = false;

  for(int i = 1; i < argc; ++i) csv = csv || (std::string("--csv") == argv[i]);

  std::cout << "========================================\n"
            << "1D Bilateral Filter Benchmark\n"
            << "Elements   : " << size       << "\n"
            << "Iterations : " << iterations << "\n"
            << "Export CSV : " << (csv ? "Yes" : "No") << "\n"
            << "========================================\n\n";

  std::vector<float> input(size);
  std::vector<float> out_scalar(size, 0.0f);
  std::vector<float> out_eve(size, 0.0f);
  std::vector<float> out_raw(size, 0.0f);

  std::mt19937                          gen(42);
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  for(float& f : input) f = dist(gen);

  std::cout << std::fixed << std::setprecision(3);

  auto times_scalar = run("Scalar", iterations, [&]
  {
    bilateral::filter_scalar(input, out_scalar, [](float x) { return std::exp(x); });
    keep(out_scalar);
  });
  std::cout << "\n";

  auto times_eve = run("EVE Standard", iterations, [&]
  {
    bilateral::filter_simd(input, out_eve, eve::exp);
    keep(out_eve);
  });
  std::cout << " \t(Speedup: " << average_of(times_scalar) / average_of(times_eve) << "x)\n";

  auto times_raw = run("EVE Raw", iterations, [&]
  {
    bilateral::filter_simd(input, out_raw, eve::exp[eve::raw]);
    keep(out_raw);
  });
  std::cout << " \t(Speedup: " << average_of(times_scalar) / average_of(times_raw) << "x)\n";

  if(csv)
  {
    std::ofstream file("data.csv");

    if(!file.is_open())
    {
      std::cerr << "\n[Error] Unable to open data.csv for writing.\n";
      return 1;
    }

    file << "std,eve,eve_raw\n";
    for(int i = 0; i < iterations; ++i)
      file << times_scalar[i] << "," << times_eve[i] << "," << times_raw[i] << "\n";

    std::cout << "\n[Info] Raw iterations data exported to data.csv\n";
  }
}
