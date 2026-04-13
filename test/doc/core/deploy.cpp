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
  std::cout << kumi::cat(eve::deploy(wf), eve::deploy(wf2), eve::deploy(wf3)) << std::endl;
  std::cout << eve::deploy(wf, wf2, wf3) << std::endl;
  std::cout << eve::deploy[eve::widen](wf, wf2, wf3) << std::endl;
  std::cout << eve::deploy[eve::widen](wf, wf2, 1.0f)<< std::endl;
  std::cout << eve::deploy(wf, 1.0f, 2.0f) << std::endl;
  eve::wide<std::int32_t> wi(fill);
  std::cout << eve::deploy(wi, 1, 2) << std::endl;
};
