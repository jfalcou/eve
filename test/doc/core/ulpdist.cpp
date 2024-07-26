// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> ulpdist(wf, 2*wf)                = " << eve::ulpdist(wf, 2*wf) << "\n";
   std::cout << "-> ulpdist[ignore_last(2)](wf, 2*wf)= " << eve::ulpdist[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> ulpdist[wf != -2.0f](wf, 2*wf)   = " << eve::ulpdist[wf != -2.0f](wf, 2*wf) << "\n";
}
