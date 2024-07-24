// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> nthroot(wf, 2*wf)                = " << eve::nthroot(wf, 2*wf) << "\n";
   std::cout << "-> nthroot(wf, 2*wi)                = " << eve::nthroot(wf, 2*wi) << "\n";
   std::cout << "-> nthroot(wf, 2*wu)                = " << eve::nthroot(wf, 2*wu) << "\n";
   std::cout << "-> nthroot[ignore_last(2)](wf, 2*wf)= " << eve::nthroot[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> nthroot[wf != -2.0f](wf, 2*wf)   = " << eve::nthroot[wf != -2.0f](wf, 2*wf) << "\n";
   std::cout << "-> nthroot[raw](wf, 2*wf)           = " << eve::nthroot[eve::raw](wf, 2*wf) << "\n";
}
