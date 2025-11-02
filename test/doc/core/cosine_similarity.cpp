// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include "../../vec3.hpp"

int main()
{
  kumi::tuple wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  kumi::tuple wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, 3.0, -4.0};

  std::cout << "<- wf0           = " << wf0 << "\n";
  std::cout << "<- wf1           = " << wf1 << "\n";


  std::cout << "-> cosine_similarity(wf0, wf1) = " << eve::cosine_similarity(wf0, wf1) << "\n";
  std::cout << "-> cosine_similarity(wf0, wf0) = " << eve::cosine_similarity(wf0, wf0) << "\n";
  vec3<float> a(1.0, 2.0, 3.0);
  vec3<float> b(-3.0, -4.0, -6.0);
  std::cout <<  "a " << a << std::endl;
  std::cout <<  "b " << b << std::endl;
  std::cout << "eve::cosine_similarity(a, b) = "<< eve::cosine_similarity(a, b) << std::endl;
  std::cout << "eve::cosine_similarity(a, a) = " << eve::cosine_similarity(a, a) << std::endl;
  std::cout << "eve::cosine_similarity(b, a) = " << eve::cosine_similarity(b, a) << std::endl;
  std::cout << "eve::cosine_similarity(b, b) = " << eve::cosine_similarity(b, b) << std::endl;

  // simd cosine_similarity eve::wide<vec3<float>, eve::fixed<4>>;
  using wv3_t = eve::wide<vec3<float>, eve::fixed<4>>;
  auto wa = wv3_t(a, a, b, b);
  auto wb = wv3_t(b, a, a, b);
   std::cout << "wa " << wa << std::endl;
   std::cout << "wb " << wb << std::endl;
   std::cout << "eve::cosine_similarity[eve::widen](wa, wb) = "<< eve::cosine_similarity(wa, wb) << std::endl;


  kumi::tuple x{4.0f, 3.0f, 2.0f, 1.0f};
  kumi::tuple y{1.0f, 2.0f, 3.0f, 4.0f};
  std::cout << eve::cosine_similarity(x, x) <<  std::endl;
  std::cout << eve::cosine_similarity(x, y) <<  std::endl;
  std::cout << eve::cosine_similarity(y, x) <<  std::endl;

  using w_t = eve::wide<float, eve::fixed<4>>;
  auto wt1 = kumi::generate<11>([](auto p){return w_t([p](auto q, auto){return float(p+q); }); });
  auto wt2 = kumi::generate<11>([](auto p){return w_t([p](auto q, auto){return p*p/float((q+1)); }); });
  std::cout << wt1 << std::endl;
  std::cout << wt2 << std::endl;

}
