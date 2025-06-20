// revision 1
#include <eve/module/special/detail/cotderiv.hpp>
#include <iostream>

int main()
{
  auto println = [](auto v){
    std::cout << "{";
    for (std::size_t i = 0; i < v.size()-1; ++i){
      std::cout << std::hexfloat << v[i] << ", ";
      if ((i+1)%10 == 0) std::cout << "\n        ";
    }
    std::cout << v[v.size()-1] << "}\n";
  };

  for(std::size_t i=0; i < 101; ++i)
 {
   std::cout << "/* " << i << " -> */";
  println(eve::detail::cotderiv(i));
 }
}
