#include <eve/function/sub.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/literals.hpp>
#include <eve/wide.hpp>

int main()
{
  using namespace eve::literal;
  eve::wide<float> w( [](int i, int) { return 1.f+i; } );
  eve::wide<float> v( [](int i, int) { return 1.f-i; } ); 

  std::cout << "sub(3.f, 5.5f) = " << eve::sub(3.f,5.5f) << '\n';
  std::cout << "sub({3,3,3,3}, {1,2,3,4}) = " << eve::sub(3._wf, w ) << '\n';
  std::cout << "sub[3 > 4](2, 5)" << eve::sub[3 > 4](2, 5) << std::endl; 
  std::cout << "w " << w << std::endl;
  std::cout << "v " << v << std::endl;   
  std::cout << "sub[w > 3.0f](w, v)" << eve::sub[w > 3.0f](w, v) << std::endl;  
}
