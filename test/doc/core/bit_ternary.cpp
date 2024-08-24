// revision 0
#include <eve/module/core.hpp>
#include <iostream>

template < int a, int b, int c, int d, int e, int f , int g, int h>
constexpr auto makefrombits(){
  return std::integral_constant<int, (a << 7) + (b << 6) + (c << 5) + (d << 4) + (e << 3) + (f << 2) + (g << 1) + h>();
}

int main()
{
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};
  eve::wide wu1{7u, 3u, 5u, 4u, 3u, 2u, 1u, 0u};
  eve::wide wu2{6u, 5u, 4u, 3u, 2u, 1u, 0u, ~0u};
  std::integral_constant<int, 0xff> iff;
  std::integral_constant<int, 0x80> i80;
  std::integral_constant<int, 0xac> iac;

//   std::cout << "<- wf0                               = " << wf0 << "\n";
//   std::cout << "<- wf1                               = " << wf1 << "\n";
//   std::cout << "<- wi0                               = " << wi0 << "\n";
//   std::cout << "<- wi1                               = " << wi1 << "\n";
  std::cout << std::hex << std::endl;
  std::cout << "<- wu0                               = " << wu0 << "\n";
  std::cout << "<- wu1                               = " << wu1 << "\n";
  std::cout << "<- wu2                               = " << wu2 << "\n";

  constexpr auto myff = makefrombits<1, 1, 1, 1, 1, 1, 1, 1 >();
  constexpr auto my80 = makefrombits<1, 0, 0, 0, 0, 0, 0, 0 >();
  constexpr auto myac = makefrombits<1, 0, 1, 0, 1, 1, 0, 0 >();
  std::cout << "-> bit_ternary(myff, wu0, wu1, wu2)   = " << (eve::bit_ternary(myff, wu0, wu1, wu2)) << "\n";
  std::cout << "-> bit_ternary(iff, wu0, wu1, wu2)    = " << (eve::bit_ternary(iff, wu0, wu1, wu2)) << "\n";
  std::cout << "-> bit_ternary(i80, wu0, wu1, wu2)    = " << (eve::bit_ternary(i80, wu0, wu1, wu2)) << "\n";
  std::cout << "-> bit_ternary(my80, wu0, wu1, wu2)   = " << (eve::bit_ternary(my80, wu0, wu1, wu2)) << "\n";
  std::cout << "-> bit_ternary(iac, wu0, wu1, wu2)    = " << (eve::bit_ternary(iac, wu0, wu1, wu2)) << "\n";
  std::cout << "-> bit_ternary(myac, wu0, wu1, wu2)   = " << (eve::bit_ternary(myac, wu0, wu1, wu2)) << "\n";
  std::cout << "-> bit_select(wu0, wu2, wu1)          = " << (eve::bit_select(wu0, wu2, wu1))       << "\n";
}
