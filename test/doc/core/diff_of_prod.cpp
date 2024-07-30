// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{

                                                                    
  std::cout << "-> diff_of_prod(wf0, wf1, wf2, wf3)                 = " << eve::diff_of_prod(wf0, wf1, wf2, wf3) << "\n";
  std::cout << "-> diff_of_prod[ignore_last(2)](wf0, wf1, wf2, wf3) = " << eve::diff_of_prod[eve::ignore_last(2)](wf0, wf1, wf2, wf3) << "\n";
  std::cout << "-> diff_of_prod[raw](wf0, wf1, wf2, wf3)            = " << eve::diff_of_prod[eve::raw](wf0, wf1, wf2, wf3) << "\n";
  std::cout << "-> diff_of_prod[pedantic](wf0, wf1, wf2, wf3)       = " << eve::diff_of_prod[eve::pedantic](wf0, wf1, wf2, wf3) << "\n";
}
