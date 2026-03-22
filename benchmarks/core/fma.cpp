#include <benchmark.hpp>
#include <eve/eve.hpp>
#include <random>

auto scalar_fma = [](auto x, auto y, auto z) { return x*y+z;};

TTS_CASE_TPL("Benchmark FMA", float, double)
<typename T>(tts::type<T>)
{
  std::mt19937 rng(::tts::random_seed());
  std::uniform_real_distribution<T> dist(-100.0f, 100.0f);
  auto rnd = [&]() { return dist(rng); };

  eve::bench::benchmark runner(rnd,rnd,rnd);

  std::cout << "# Benchmarking for T = " << ::tts::typename_<T> << std::endl;

  runner.template run("STD FMA (SCAL)"              , scalar_fma)
        .template run("EVE FMA (SCAL)"              ,   eve::fma)
        .template run<eve::wide<T>>("EVE FMA (SIMD)",   eve::fma);

  TTS_PASS("Benchmarks - SUCCESS");
};