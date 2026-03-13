// revision 0
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

 //The base version of divdiff, ends recursion
 template<typename F, typename T>
 T divdiff(F f, T t0, T t1) {
     return (f(t0) - f(t1)) / (t0 - t1);
 }

 // This divdiff overload takes a tuple and an index sequence
 // The index sequence specifies which elements from the tuple will
 // be unpacked as arguments for a divdiff call
// template <typename F, typename T, std::size_t... Is>
 // auto divdiff(F f, T arg_tuple, std::index_sequence<Is...>) {
//      return divdiff(f, kumi::get<Is>(arg_tuple)...);
//  }

 template<typename F, typename T, typename ...Ts>
 T divdiff(F f, T t0, Ts ...right_args)
{
  using r_t =  eve::common_value_t<T, Ts...>;
  constexpr auto siz = sizeof...(Ts);
  if constexpr(siz == 0) return eve::zero(eve::as<r_t>());
  else if constexpr(siz == 1)
  {
    auto t1 =  kumi::get<0>(right_args...);
    return  (f(t0) - f(t1)) / (t0 - t1);
  }
  else
  {
    // pack all arguments into a tuple
    auto arg_tuple = kumi::make_tuple(t0, right_args...);
    auto inner = [&f, &arg_tuple]<std::size_t... Is>( std::index_sequence<Is...>){
      return divdiff(f, kumi::get<Is>(arg_tuple)...);
    };
    // make an index sequence whose size is one less than the
    // current recursion's argument count
    using next_index_sequence = std::make_index_sequence<sizeof...(Ts)>;
    // get the value of the final argument in tn
    auto tn = kumi::get<sizeof...(Ts)>(arg_tuple);
    // Call divdiff, first using the tuple/sequence overload for the left
    // side arguments.
    // Then call it with the easily-obtained right side arguments.
    return (inner(next_index_sequence{}) - divdiff(f, right_args...)) / (t0 - tn);
  }
}

 int main() {
   double r = divdiff([](double x) { return eve::pow(x, 6); }, 1.0, 2.0, 3.0, 4.0);
     std::cout << r << '\n';
 }

// int main()
// {
//   std::cout << " -> divdiff(f, xx)       = " << eve::divdiff([](double x) { return x * x * x; }, 1.0, 2.0, 3.0);

//   // std::cout << " -> divdiff(f, xx)       = " << eve::divdiff(f, 1.5000, 2.2500, 3.3750, 5.0625, 7.5938, 11.3906, 17.0859, 25.6289) << std::endl;

// //   kumi::tuple yy{1.5000, 2.2500, 3.3750, 5.0625, 7.5938, 11.3906, 17.0859, 25.6289};
// //   auto f = [](double t){return eve::pow(1.5, t); };
// // //    auto yy =  kumi::generate<8>([](double t){return eve::pow(1.5, t); });
// // //     auto xx =  kumi::generate<8>([](double t){return t*0.5;} );
// // //     std::cout << " < - xx                                               = " << xx << std::endl;
// //   std::cout << " < - yy                                               = " << yy << std::endl;
// //   std::cout << " -> divdiff(f, xx)       = " << eve::divdiff(f, 1.5000, 2.2500, 3.3750, 5.0625, 7.5938, 11.3906, 17.0859, 25.6289) << std::endl;
// // //  //    std::cout << " -> divdiff(index_t<0>, tt)       = " << eve::divdiff(kumi::index_t<0>{}, tt) << std::endl;
// // // //     std::cout << " -> divdiff(index_t<1>, tt)       = " << eve::divdiff(kumi::index_t<1>{}, tt) << std::endl;
// // // //     std::cout << " -> divdiff(index_t<2>, tt)       = " << eve::divdiff(kumi::index_t<2>{}, tt) << std::endl;
// // // //     std::cout << " -> divdiff(index_t<7>, tt)       = " << eve::divdiff(kumi::index_t<7>{}, tt) << std::endl;
// // // //     std::cout << " -> divdiff(index_t<_>, tt)       = " << eve::divdiff(kumi::index_t<8>{}, tt) << std::endl;
// // //   }

// }
