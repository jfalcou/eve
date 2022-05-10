#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <list>
#include <vector>


int main()
{
  std::vector<float> v {3, 2, 1};
  std::cout << "---- simd" << '\n'
            << "-> v                            = {3, 2, 1}"  << '\n'
            << "-> from_roots(v)                = " << eve::from_roots(v) << '\n'
            << "-> from_roots(1.0f, 1.0f, 1.0f) = " << eve::from_roots(1.0f, 1.0f, 1.0f) << '\n'
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
