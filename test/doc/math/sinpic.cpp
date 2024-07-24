// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> sinpic(wf)                = " << eve::sinpic(wf) << "\n";
   std::cout << "-> sinpic[ignore_last(2)](wf)= " << eve::sinpic[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sinpic[wf != -2.0f](wf)   = " << eve::sinpic[wf != -2.0f](wf) << "\n";
}
