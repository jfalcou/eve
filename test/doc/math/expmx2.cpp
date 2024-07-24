// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> expmx2(wf)                = " << eve::expmx2(wf) << "\n";
   std::cout << "-> expmx2[ignore_last(2)](wf)= " << eve::expmx2[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> expmx2[wf != -2.0f](wf)   = " << eve::expmx2[wf != -2.0f](wf) << "\n";
}
