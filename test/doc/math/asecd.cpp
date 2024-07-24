// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> asecd(wf)                = " << eve::asecd(wf) << "\n";
   std::cout << "-> asecd[raw](wf)           = " << eve::asecd[eve::raw](wf) << "\n";
   std::cout << "-> asecd[ignore_last(2)](wf)= " << eve::asecd[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> asecd[wf != -2.0f](wf)   = " << eve::asecd[wf != -2.0f](wf) << "\n";
}
