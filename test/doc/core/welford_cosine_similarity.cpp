// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <tts/tts.hpp>

int main()
{
  std::cout << eve::welford_cosine_similarity(1.0f, 2.0f, -3.0f, 4.0f, 5.0f,
                                              6.0f, 7.0f, 48.0f, 9.0f, 10.0f) << std::endl;
  std::cout << eve::welford_cosine_similarity(1.0f, 2.0f, -3.0f, 4.0f, 5.0f,
                                              1.0f, 2.0f, -3.0f, 4.0f, 5.0f) << std::endl;

  auto a(kumi::generate<11>([](auto p){return float(p); }));
  auto b(kumi::generate<11>([](auto p){return float(p)+5; }));;
  std::cout << "<- a           = " << a << "\n";
  std::cout << "<- b           = " << b << "\n";
  std::cout << "-> welford_cosine_similarity(a, b)        = " << eve::welford_cosine_similarity(a, b) << "\n";
  std::cout << "-> welford_cosine_similarity(a, a)        = " << eve::welford_cosine_similarity(a, a) << "\n";
  auto c(kumi::generate<11>([](auto p){return p > 5  ? float(p) : 0.f; }));
  auto d(kumi::generate<11>([](auto p){return p > 5 ? 0.f :float(p)+5; }));;
  std::cout << "<- c           = " << c << "\n";
  std::cout << "<- d           = " << d << "\n";
  std::cout << "-> welford_cosine_similarity(c, d)        = " << eve::welford_cosine_similarity(c, d) << "\n";
}
