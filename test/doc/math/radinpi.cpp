// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> radinpi(wf)                = " << eve::radinpi(wf) << "\n";
   std::cout << "-> radinpi[ignore_last(2)](wf)= " << eve::radinpi[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> radinpi[wf != -2.0f](wf)   = " << eve::radinpi[wf != -2.0f](wf) << "\n";
}
