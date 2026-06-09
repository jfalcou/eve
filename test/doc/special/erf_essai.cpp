// revision 1
#include <eve/module/special.hpp>
#include <iostream>
#include <iomanip>


int main()
{


 for(float i=0.0f; i < 2.; i+= 0.01)
 {
   float a = i;
   auto ref = eve::erf(a);
   std::cout << std::setprecision(15) << "a =  " << a << " val " << ref
             << " difr "<< eve::abs(ref-eve::erf[eve::raw](a))
             << " diff "<< eve::abs(ref-eve::erf[eve::fast](a))
             << std::endl;
 }


}
