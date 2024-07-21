// revision 1
#include <eve/module/combinatorial.hpp>
#include <iostream>

eve::wide<float> wf0([](auto i, auto c)->float{ return 2*(i-c/2);});
eve::wide<float> wf1([](auto i, auto c)->float{ return 2*(i+c/2);});

int main(){
   std::cout << "<- wf0 = " << wf0 << "\n";
   std::cout << "<- wf1 = " << wf1 << "\n";

   std::cout << "-> fibonacci(n, wf0, wf1)= " << eve::fibonacci(n, wf0, wf1) << "\n";
   std::cout << "-> fibonacci
}
