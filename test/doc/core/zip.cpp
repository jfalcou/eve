// revision 1
#include <eve/module/core.hpp>
#include <iostream>

int main()
{

                                                       
 std::cout << "-> zip(wf0,wi,wd)                       = " << eve::zip(wf0,wi,wd)  << std::endl;
 std::cout << "-> zip(eve::as<data_block>(),wf,wi,wd)) = " << eve::zip(eve::as<data_block>(),wf,wi,wd)  << std::endl;
 std::cout << "-> zip(wf,wi,wd)                        = " << eve::zip(wf,wi,wd)  << std::endl;
 std::cout << "-> zip(eve::as<data_block>(),wf,wi,wd)) = " << eve::zip(eve::as<data_block>(),wf,wi,wd)  << std::endl;
}
