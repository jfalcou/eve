// revision 1 TODO investigate last result
#include <eve/module/core.hpp>
#include <iostream>

int main()
{

                                                     
 std::cout << "-> clamp(wf0, mi, ma)                 = " << eve::clamp(wf0, mi, ma)  << "\n";
 std::cout << "-> clamp[ignore_last(2)](wf0, mi, ma) = " << eve::clamp[eve::ignore_last(2)](wf0, mi, ma)  << "\n";
 std::cout << "-> clamp[wf0 != -4.0f](wf0, mi, ma)   = " << eve::clamp[wf0 != -2.0f](wf0, mi, ma)  << "\n";
}
