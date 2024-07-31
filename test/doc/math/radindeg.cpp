// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
int main()
{ 
  
  eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
  
  std::cout << "<- wf = " << wf << "\n"; 
  
  std::cout << "-> radindeg(wf)                = " << eve::radindeg(wf) << "\n";
  std::cout << "-> radindeg[ignore_last(2)](wf)= " << eve::radindeg[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> radindeg[wf != -2.0f](wf)   = " << eve::radindeg[wf != -2.0f](wf) << "\n";
}
