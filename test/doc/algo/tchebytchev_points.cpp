#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "detail/print.hpp"

int main()
{
  using eve::detail::print;
  using eve::views::tchebytchev_points;

 for(int i=0; i < 10 ; ++i)
 {
   print(tchebytchev_points(i, eve::as<float>()));
 }
  return 0;
}
