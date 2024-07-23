// revision 1
#include <eve/module/special.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> lfactorial(wf)= " << eve::lfactorial(wf) << "\n";
   std::cout << "-> lfactorial(wi)= " << eve::lfactorial(wi) << "\n";
   std::cout << "-> lfactorial(wu)= " << eve::lfactorial(wu) << "\n";
}
