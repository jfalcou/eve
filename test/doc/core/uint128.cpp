#include <eve/uint128.hpp>
#include <eve/int128.hpp>
#include <eve/constant/valmax.hpp>
#include <iostream>
#include <iomanip>



int main()
{
  using eve::uint128;
  uint128 n1(1, 0);
  uint128 n2(0, eve::valmax(eve::as< uint64_t>()));
  uint128 n3(eve::valmax(eve::as< uint64_t>()), 0);
  uint128 n4(eve::valmax(eve::as< uint64_t>()), eve::valmax(eve::as< uint64_t>()));


  std::cout << std::oct << "n1   =   0" << n1 << std::endl;
  std::cout << std::hex << "n1   =  0x" << n1 << std::endl;
  std::cout << std::dec << "n1   =    " << n1 << std::endl;
  std::cout << std::dec << "n1   =    " << eve::hl(n1) << std::endl;

  std::cout << std::oct << "n2   =   0" << n2 << std::endl;
  std::cout << std::hex << "n2   =  0x" << n2 << std::endl;
  std::cout << std::dec << "n2   =    " << n2 << std::endl;
  std::cout << std::hex << "n2   =    " << eve::hl(n2) << std::endl;

  std::cout << std::oct << "n3   =   0" << n3 << std::endl;
  std::cout << std::hex << "n3   =  0x" << n3 << std::endl;
  std::cout << std::dec << "n3   =    " << n3 << std::endl;
  std::cout << std::oct << "n3   =   " << eve::hl(n3) << std::endl;

  std::cout << std::oct << "n4   =   0" << n4 << std::endl;
  std::cout << std::hex << "n4   =  0x" << n4 << std::endl;
  std::cout << std::dec << "n4   =    " << n4 << std::endl;
  std::cout << std::oct << "n4   =   " << eve::hl(n4) << std::endl;

  uint128 a(0xffffeeeeddddcccc, 0xbbbbaaaa99998888);
  uint128 b(0x7777666655554444, 0x3333222211110000);
  uint128 c = a * b;
  uint128 d(0x530EDA741C71D4C3, 0xBF25975319080000);
  std::cout << std::hex << "a   =  0x" << a << std::endl;
  std::cout << std::hex << "b   =  0x" << b << std::endl;
  std::cout << std::hex << "c   =  0x" << c << std::endl;
  std::cout << std::hex << "d   =  0x" << d << std::endl;
  std::cout << (c == d) << std::endl<< std::endl;
//    std::cout << "++n2 =  " << ++n2<< std::endl;
//   std::cout << "n1+n2=  " << n1+n2<< std::endl;
// //  std::cout << "n1*n2=  " << n1*n2<< std::endl;
// //  eve::int128 m(1, 1);
// //   std::cout << "m =  " << m << std::endl;
//   std::cout << std::oct << eve::valmax(eve::as< uint64_t>()) << std::endl;
//   std::cout << std::hex << eve::valmax(eve::as< uint64_t>()) << std::endl;
//   std::cout << std::dec << eve::valmax(eve::as< uint64_t>()) << std::endl;


//   uint128 m1(0, eve::valmax(eve::as<std::uint64_t>()));
//   uint128 m2(2u*n1);
//   std::cout << std::oct << "m1   =   0" << m1 << std::endl;
//   std::cout << std::hex << "m1   =  0x" << m1 << std::endl;
//   std::cout << std::dec << "m1   =    " << m1 << std::endl;
//   std::cout << std::dec << "m1   =    " << eve::hl(m1) << std::endl;

//   std::cout << std::oct << "m2   =   0" << m2 << std::endl;
//   std::cout << std::hex << "m2   =  0x" << m2 << std::endl;
//   std::cout << std::dec << "m2   =    " << m2 << std::endl;
//   std::cout << std::dec << "m2   =    " << eve::hl(m2) << std::endl;
//   std::cout << (m2-m1 == m1)<< std::endl;
//   std::cout << uint128(2u) << std::endl;
//   std::cout << std::hex << eve::hl(uint128(2u)) << std::endl;
//   std::cout << eve::hl(uint128(1, 0))<< std::endl;
//   std::cout << eve::hl(2u*uint128(1, 0))<< std::endl;



  uint128 aaa = eve::valmax(eve::as< uint64_t>());
  uint128 bbb = 2;
  std::cout << "aaa " << aaa << std::endl;
  std::cout << "bbb " << bbb << std::endl;
  std::cout << aaa*bbb << std::endl;
  std::cout << eve::hl(aaa*bbb) << std::endl;
  std::cout << (aaa*bbb-aaa == aaa) <<  std::endl;
  std::cout << spy::supports::int128_ << std::endl;
  std::cout << std::dec << __SIZEOF_INT128__ <<  std::endl;

  return 0;
}
