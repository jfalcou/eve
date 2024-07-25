// revision 1
#include <eve/module/combinatorial.hpp>
#include <iostream>

eve::wide<float> wf0([](auto i, auto c)->float{ return (i-c/2);});
eve::wide<float> wf1([](auto i, auto )->float{ return 10*i; });
eve::wide n{93, 25, 32, 368,  216,  43, 18, 25};
eve::wide p{42, 30, 27, 1024, 36, 12, 51, 44};

int main(){
   std::cout << "<- wf0 = " << wf0 << "\n";
   std::cout << "<- wf1 = " << wf1 << "\n";
   std::cout << "<- n   = " << n   << "\n";
   std::cout << "<- p   = " << p   << "\n";

   std::cout << "-> gcd(wf0, wf1)                = " << eve::gcd(wf0, wf1) << "\n";
   std::cout << "-> gcd[ignore_last(2)](wf0, wf1)= " << eve::gcd[eve::ignore_last(2)](wf0, wf1) << "\n";
   std::cout << "-> gcd[wf0 != -2.0f](wf0, wf1)  = " << eve::gcd[wf0 != -2.0f](wf0, wf1) << "\n";
   std::cout << "-> gcd(p, n)                    = " << eve::gcd(p, n) << "\n";
}
