// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{

                                                    
  std::cout << "-> ldexp(wf0, 2*wi)                 = " << eve::ldexp(wf0, 2*wi) << "\n";
  std::cout << "-> ldexp[ignore_last(2)](wf0, 2*wi) = " << eve::ldexp[eve::ignore_last(2)](wf0, 2*wi) << "\n";
  std::cout << "-> ldexp[wf0 != 0](wf0, 2*wi)       = " << eve::ldexp[wf0 != 0](wf0, 2*wi) << "\n";
  std::cout << "-> ldexp(wf, wi1)                   = " << eve::ldexp(wf, wi1) << "\n";
  std::cout << "-> ldexp[ignore_last(2)](wf, wi1)   = " << eve::ldexp[eve::ignore_last(2)](wf, wi1) << "\n";
  std::cout << "-> ldexp[wf != 0](wf, wi1)          = " << eve::ldexp[wf != 0](wf, wi1) << "\n";
}
