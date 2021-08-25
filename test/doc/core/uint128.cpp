#include <eve/uint128.hpp>
#include <eve/int128.hpp>
#include <eve/constant/valmax.hpp>
#include <iostream>
#include <iomanip>



int main()
{
  eve::uint128 n1(1, 0);
  eve::uint128 n2(eve::valmax(eve::as< uint64_t>()));
  eve::uint128 n3(eve::valmax(eve::as< uint64_t>()), 0);
  std::cout << std::oct << "n1   =  " << n1 << std::endl;
  std::cout << "n2   =  " << n2 << std::endl;
   std::cout << "n3   =  " << n3 << std::endl;
 std::cout << "++n2 =  " << ++n2<< std::endl;
  std::cout << "n1+n2=  " << n1+n2<< std::endl;
//  std::cout << "n1*n2=  " << n1*n2<< std::endl;
//  eve::int128 m(1, 1);
//   std::cout << "m =  " << m << std::endl;
  return 0;
}
