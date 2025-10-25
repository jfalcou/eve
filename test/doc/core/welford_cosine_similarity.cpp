// revision 0
// revision 0
#include <eve/module/core.hpp>
#include "../../vec3.hpp"
#include <iostream>
#include <iomanip>
#include <tts/tts.hpp>

int main()
{
  // scalar welford_cosine_similarity vec3<float>
  vec3<float> a(1.0, 2.0, 3.0);
  vec3<float> b(-3.0, -4.0, -6.0);
  std::cout <<  "a " << a << std::endl;
  std::cout <<  "b " << b << std::endl;
  std::cout << "eve::welford_cosine_similarity[eve::unbiased](a, b) = "<< eve::welford_cosine_similarity(a, b) << std::endl;
  std::cout << "eve::welford_cosine_similarity(a, a) = " << eve::welford_cosine_similarity(a, a) << std::endl;
  std::cout << "eve::welford_cosine_similarity(b, a) = " << eve::welford_cosine_similarity(b, a) << std::endl;
  std::cout << "eve::welford_cosine_similarity(b, b) = " << eve::welford_cosine_similarity(b, b) << std::endl;

  // simd welford_cosine_similarity eve::wide<vec3<float>, eve::fixed<4>>;
  using wv3_t = eve::wide<vec3<float>, eve::fixed<4>>;
  auto wa = wv3_t(a, a, b, b);
  auto wb = wv3_t(b, a, a, b);
   std::cout << "wa " << wa << std::endl;
   std::cout << "wb " << wb << std::endl;
   std::cout << "eve::welford_cosine_similarity[eve::widen](wa, wb) = "<< eve::welford_cosine_similarity[eve::widen](wa, wb) << std::endl;


  kumi::tuple x{4.0f, 3.0f, 2.0f, 1.0f};
  kumi::tuple y{1.0f, 2.0f, 3.0f, 4.0f};
  std::cout << eve::welford_cosine_similarity(x, x) <<  std::endl;
  std::cout << eve::welford_cosine_similarity(x, y) <<  std::endl;
  std::cout << eve::welford_cosine_similarity(y, x) <<  std::endl;

 {
    // incremental computation versus global computation
    auto constexpr N = 11;
    std::array<v_t, N> aa, bb;

    for(int i=0; i < N; ++i)
    {
      aa[i] = cos(i+1);
      bb[i] = cos(i+1)+1/v_t(i+1);
    }
    auto cc = eve::welford_cosine_similarity(aa[0], bb[0]);
    for(int i=1; i < N; ++i)
    {
      cc = eve::welford_cosine_similarity(cc, eve::welford_cosine_similarity(aa[i], bb[i]));
    }
    TTS_ULP_EQUAL(cc, eve::welford_cosine_similarity(aa, bb);, 0.5);
  }
}
