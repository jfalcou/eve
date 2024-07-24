// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> expx2(wf)                = " << eve::expx2(wf) << "\n";
   std::cout << "-> expx2[ignore_last(2)](wf)= " << eve::expx2[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> expx2[wf != -2.0f](wf)   = " << eve::expx2[wf != -2.0f](wf) << "\n";
}
