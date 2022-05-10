#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <list>
#include <vector>


int main()
{
  std::vector<float> u {1,  2, -3, 0, 4};
  std::vector<float> v {3, 2, 1};
  eve::polynom<float> pu(u, eve::upward);
  eve::polynom<float> pv(v, eve::upward);
  eve::polynom<float> pw{1, 1};

// float x = 2.0;

  auto [rem, quo] = remquo(pv, pw);
 std::cout  << "-> pv            = " << pv << '\n'
            << "-> pw            = " << pw << '\n'
            <<  "-> rem            = " << rem << '\n'
            << "-> quo            = " << quo << '\n' << '\n';

   std::cout << "---- simd" << '\n'
//             << "<- l and v contain  {1, 2, -3, 0, 4} "<< '\n'
//             << "-> pu            = " << pu << '\n'
//             << "-> pv            = " << pv << '\n'
//             << "-> pw            = " << pw << '\n'
//             << "-> pu.derivative() = " << pu.derivative()  << '\n'
//             << "-> pu.derivative(2)= " << pu.derivative(2) << '\n'
//             << "-> pu.derivative(3)= " << pu.derivative(3) << '\n'
//             << "-> pu.derivative(4)= " << pu.derivative(4) << '\n'
//             << "-> pu.derivative(5)= " << pu.derivative(5) << '\n'
//             << "-> pu.primitive()  = " << pu.primitive()    << '\n'
//             << "-> pu.primitive(1) = " << pu.primitive(1)    << '\n'
//             << "-> pu.primitive(2) = " << pu.primitive(2)    << '\n'
//             << "-> derivative(pv)= " << pv.derivative()  << '\n'
//             << "-> degree(pu)    = " << degree(pu)<< '\n'
//             << "-> degree(pv)    = " << degree(pv)<< '\n'
//             << "-> valuation(pu) = " << valuation(pu)<< '\n'
//             << "-> valuation(pv) = " << valuation(pv)<< '\n'
//             << "-> pu(x)         = " << pu(x)        << '\n'
//             << "-> pv(x)         = " << pv(x)        << '\n'
//             << "-> pu+pv            = " << pu+pv  << '\n'
//             << "-> pv+pu            = " << pv+pu  << '\n'
//             << "-> pu-pv            = " << pu-pv  << '\n'
//             << "-> pv-pu            = " << pv-pu  << '\n'
             << "-> pv*pu            = " << pv*pu  << '\n'
             << "-> pv*pw            = " << pv*pw  << '\n'
             << "-> from_roots(v) = " << eve::from_roots(v)<< '\n'
     ;


  return 0;
}


// #include <eve/module/core.hpp>
// #include <eve/algo/for_each.hpp>
// #include <eve/algo/transform.hpp>
// #include <eve/views/zip.hpp>
// #include <iostream>
// #include <eve/algo/as_range.hpp>
// #include <eve/algo/copy.hpp>

// #include <vector>


// std::vector<int>& read_plus_read_modify(std::vector<int> const & read,
//                            std::vector<int>       & readWrite) {
//     eve::algo::transform_to(eve::views::zip(read, readWrite), readWrite, [](auto x_y) {
//         auto [x, y] = x_y;
//         return x + y;
//                             });
//     return readWrite;
// }

// int main()
// {
//   std::vector < int> v{1, 2, 3};
//   std::vector < int> w{1, 2, 3, 4, 5};
//   std::vector < int> r(5);
//   std::copy(v.begin(), v.end(), r.begin()+5-3);
//   eve::algo::copy(v, eve::algo::as_range(r.begin()+5-3, r.end()));
// //  w = read_plus_read_modify(v, w);

//   for(int i=0; i <5 ; ++i) std::cout << r[i] << std::endl;
// }
