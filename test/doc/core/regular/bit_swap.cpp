#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint64_t, eve::fixed<8>>;

int main()
{
//  wide_it pi = {1, 4, 8, 16, 32, 64, 128, 256};
//   wide_it pi = {1, 3, 7, 15, 31, 63, 127, 255};

//   std::cout << "---- simd" << '\n'
//             << "<- pi              = " << pi << '\n'
//             << "-> bit_swap<1>(pi) = " << eve::bit_swap(pi, std::integral_constant<size_t, 1>{} ) << '\n'
//             << "-> bit_swap<2>(pi) = " << eve::bit_swap(pi, std::integral_constant<size_t, 2>{} ) << '\n'
//             << "-> bit_swap<4>(pi) = " << eve::bit_swap(pi, std::integral_constant<size_t, 4>{} ) << '\n'
//             << "-> bit_swap<8>(pi) = " << eve::bit_swap(pi, std::integral_constant<size_t, 8>{} ) << '\n';


  //////// ok
//  for(size_t i=0; i < 16 ; ++i)
//  {
//    uint8_t a =  1 << i;
//    if(!a) break;
//    std::cout << " <-             a   = " << std::bitset<8>(a) << '\n'
//              << "-> bit_swap<1>(a)   = " << std::bitset<8>(eve::bit_swap(a, std::integral_constant<size_t, 1>{} )) << '\n'
//              << "-> bit_swap<2>(a)   = " << std::bitset<8>(eve::bit_swap(a, std::integral_constant<size_t, 2>{} )) << '\n'
//              << "-> bit_swap<4>(a)   = " << std::bitset<8>(eve::bit_swap(a, std::integral_constant<size_t, 4>{} )) << '\n'
//              << "-> bit_swap<8>(a)   = " << std::bitset<8>(eve::bit_swap(a, std::integral_constant<size_t, 8>{} )) << '\n'
//              << "-> bit_swap<16>(a)  = " << std::bitset<8>(eve::bit_swap(a, std::integral_constant<size_t, 16>{} )) << '\n'
//              << "-> bit_swap<32>(a)  = " << std::bitset<8>(eve::bit_swap(a, std::integral_constant<size_t, 32>{} )) << '\n';
// }

  //////// ok
//  for(size_t i=0; i < 16 ; ++i)
//  {
//    uint16_t a =  1 << i;
//    if(!a) break;
//    std::cout << " <-             a   = " << std::bitset<16>(a) << '\n'
//              << "-> bit_swap<1>(a)   = " << std::bitset<16>(eve::bit_swap(a, std::integral_constant<size_t, 1>{} )) << '\n'
//              << "-> bit_swap<2>(a)   = " << std::bitset<16>(eve::bit_swap(a, std::integral_constant<size_t, 2>{} )) << '\n'
//              << "-> bit_swap<4>(a)   = " << std::bitset<16>(eve::bit_swap(a, std::integral_constant<size_t, 4>{} )) << '\n'
//              << "-> bit_swap<8>(a)   = " << std::bitset<16>(eve::bit_swap(a, std::integral_constant<size_t, 8>{} )) << '\n'
//              << "-> bit_swap<16>(a)  = " << std::bitset<16>(eve::bit_swap(a, std::integral_constant<size_t, 16>{} )) << '\n'
//              << "-> bit_swap<32>(a)  = " << std::bitset<16>(eve::bit_swap(a, std::integral_constant<size_t, 32>{} )) << '\n';
//  }

//  for(size_t i=0; i < 16 ; ++i)
//  {
//    uint32_t a =  1 << i;
//    if(!a) break;
//    std::cout << " <-             a   = " << std::bitset<32>(a) << '\n'
//              << "-> bit_swap<1>(a)   = " << std::bitset<32>(eve::bit_swap(a, std::integral_constant<size_t, 1>{} )) << '\n'
//              << "-> bit_swap<2>(a)   = " << std::bitset<32>(eve::bit_swap(a, std::integral_constant<size_t, 2>{} )) << '\n'
//              << "-> bit_swap<4>(a)   = " << std::bitset<32>(eve::bit_swap(a, std::integral_constant<size_t, 4>{} )) << '\n'
//              << "-> bit_swap<8>(a)   = " << std::bitset<32>(eve::bit_swap(a, std::integral_constant<size_t, 8>{} )) << '\n'
//              << "-> bit_swap<16>(a)  = " << std::bitset<32>(eve::bit_swap(a, std::integral_constant<size_t, 16>{} )) << '\n'
//              << "-> bit_swap<32>(a)  = " << std::bitset<32>(eve::bit_swap(a, std::integral_constant<size_t, 32>{} )) << '\n'
// ; }

 for(uint64_t i=0; i < 63 ; ++i)
 {
   uint64_t a =  1ULL << i;
   if(!a) break;
   std::cout << " <-             a   = " << std::bitset<64>(a) << '\n'
             << "-> bit_swap<1>(a)   = " << std::bitset<64>(eve::bit_swap(a, std::integral_constant<size_t, 1>{} )) << '\n'
             << "-> bit_swap<2>(a)   = " << std::bitset<64>(eve::bit_swap(a, std::integral_constant<size_t, 2>{} )) << '\n'
             << "-> bit_swap<4>(a)   = " << std::bitset<64>(eve::bit_swap(a, std::integral_constant<size_t, 4>{} )) << '\n'
             << "-> bit_swap<8>(a)   = " << std::bitset<64>(eve::bit_swap(a, std::integral_constant<size_t, 8>{} )) << '\n'
             << "-> bit_swap<16>(a)  = " << std::bitset<64>(eve::bit_swap(a, std::integral_constant<size_t, 16>{} )) << '\n'
             << "-> bit_swap<32>(a)  = " << std::bitset<64>(eve::bit_swap(a, std::integral_constant<size_t, 32>{} )) << '\n'
 ; }

//   std::uint8_t xf = 48;

//   std::cout << "---- scalar" << '\n'
//             << "<- xf              = " << +xf << '\n'
//             << "-> bit_swap<2>(xf) = " << +eve::bit_swap<2>(xf) << '\n';
  return 0;
}
