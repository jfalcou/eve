// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  constexpr auto S = eve::cardinal_v<eve::wide<float>>;
  auto fill = [](auto i,  auto){return i;};
  auto fill2 = [](auto i,  auto){return (i+S);};
  auto fill3 = [](auto i,  auto){return (i+2*S);};
  eve::wide<float> wf(fill);
  eve::wide<float> wf2(fill2);
  eve::wide<float> wf3(fill3);
  std::cout << kumi::cat(eve::unfold(wf), eve::unfold(wf2), eve::unfold(wf3)) << std::endl;
  std::cout << eve::unfold(wf, wf2, wf3) << std::endl;
  std::cout << eve::unfold[eve::widen](wf, wf2, wf3) << std::endl;
  std::cout << eve::unfold[eve::widen](wf, wf2, 1.0f)<< std::endl;
  std::cout << eve::unfold(wf, 1.0f, 2.0f) << std::endl;
  eve::wide<std::int32_t> wi(fill);
  std::cout << eve::unfold(wi, 1, 2) << std::endl;
  auto t = kumi::make_tuple(wi);
  std::cout << t << std::endl;
  std::cout << eve::unfold(t) << std::endl;

};
