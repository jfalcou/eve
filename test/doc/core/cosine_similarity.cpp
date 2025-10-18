// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};
  eve::wide wu1{7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};

  std::cout << "<- wf0           = " << wf0 << "\n";
  std::cout << "<- wf1           = " << wf1 << "\n";
  std::cout << "<- wi0           = " << wi0 << "\n";
  std::cout << "<- wi1           = " << wi1 << "\n";
  std::cout << "<- wu0           = " << wu0 << "\n";
  std::cout << "<- wu1           = " << wu1 << "\n";

  std::cout << "-> cosine_similarity(wf0, wf1) = " << eve::cosine_similarity(wf0, wf1) << "\n";
  std::cout << "-> cosine_similarity(wu0, wu1) = " << eve::cosine_similarity(wu0, wu1) << "\n";
  std::cout << "-> cosine_similarity(wi0, wi1)  = " << eve::cosine_similarity(wi0, wi1) << "\n";
  std::cout << "-> cosine_similarity(wf0, wf1, wf0, wf1) = "<< eve::cosine_similarity(wf0, wf1, wf0, wf1) << "\n";
  std::cout << "-> cosine_similarity[widen](wf0, wf1, wf0, wf1) = "<< eve::cosine_similarity[eve::widen](wf0, wf1, wf0, wf1) << "\n";

   auto vwf0= kumi::tuple{wf0, 2*wf0, 3*wf0};
   auto vwf1= kumi::tuple{wf1, 2*wf1, 3*wf1};
   std::cout << "-> cosine_similarity(vwf0, vwf1)        = " << eve::cosine_similarity(vwf0, vwf1) << "\n";
   std::cout << "-> cosine_similarity[widen](vwf0, vwf1) = " << eve::cosine_similarity[eve::widen](vwf0, vwf1) << "\n";

   auto a(kumi::generate<11>([](auto p){return float(p); }));
   auto b(kumi::generate<11>([](auto p){return float(p)+5; }));;
   std::cout << "<- a           = " << a << "\n";
   std::cout << "<- b           = " << b << "\n";
   std::cout << "-> cosine_similarity(a, b)        = " << eve::cosine_similarity(a, b) << "\n";
   std::cout << "-> cosine_similarity(a, a)        = " << eve::cosine_similarity(a, a) << "\n";
   auto c(kumi::generate<11>([](auto p){return p > 5  ? float(p) : 0.f; }));
   auto d(kumi::generate<11>([](auto p){return p > 5 ? 0.f :float(p)+5; }));;
   std::cout << "<- c           = " << c << "\n";
   std::cout << "<- d           = " << d << "\n";
   std::cout << "-> cosine_similarity(c, d)        = " << eve::cosine_similarity(c, d) << "\n";
}
