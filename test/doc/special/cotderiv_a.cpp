// revision 1
#include <eve/module/special/detail/cotderiv.hpp>
#include <iostream>

int main()
{
//   auto println = [](auto v, auto k){
//     for (std::size_t i = 0; i < v.size(); ++i, ++k){
//       std::cout << std::hexfloat << v[i] << ", ";
//       if ((k+1)%10 == 0) std::cout << "\n ";
//     }
//     return k;
//   };


  auto println = [](auto v){
//    std::cout << "{";
    for (std::size_t i = 0; i < v.size(); ++i){
      std::cout << std::hexfloat << v[i] << ", ";
    }
    std::cout << std::endl;
  };

  for(std::size_t i=0; i < 101; ++i)
  {
    println(eve::detail::cotderiv(i));
  }
};
