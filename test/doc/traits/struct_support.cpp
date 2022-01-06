#include <eve/product_type.hpp>
#include <eve/wide.hpp>
#include <iostream>

// vec3 is a product type made of 3 floats
struct vec3 : eve::struct_support<vec3, float, float, float>
{
  // To simplify member access, we can wrap access to the product type
  // elements via a named friend accessor.
  friend decltype(auto) x(eve::like<vec3> auto&& self)
  {
    return get<0>(std::forward<decltype(self)>(self));
  }

  friend decltype(auto) y(eve::like<vec3> auto&& self)
  {
    return get<1>(std::forward<decltype(self)>(self));
  }

  friend decltype(auto) z(eve::like<vec3> auto&& self)
  {
    return get<2>(std::forward<decltype(self)>(self));
  }

  // Defines += over vec3 to automatically generates +
  friend auto& operator+= ( eve::like<vec3> auto& self
                          , eve::like<vec3> auto const& other
                          )
  {
    x(self) += x(other);
    y(self) += y(other);
    z(self) += z(other);
    return self;
  }

  // Defines -= over vec3 to automatically generates -
  friend auto& operator-= ( eve::like<vec3> auto& self
                          , eve::like<vec3> auto const& other
                          )
  {
    x(self) -= x(other);
    y(self) -= y(other);
    z(self) -= z(other);
    return self;
  }

  // Defines stream insertion
  friend std::ostream& operator<<( std::ostream& os, eve::like<vec3> auto const& self )
  {
    return os << "{" << x(self) << ", " << y(self) << ", " << z(self) << "}";
  }
};

int main()
{
  eve::wide<vec3> p ( [](auto i, auto )
                          {
                            return vec3{1.f+i,4.f-i,1.f/(1+i)};
                          }
                        );
  std::cout << p << "\n";

  p = p + p;
  std::cout << p << "\n";

  p -= vec3{1,1,1};
  std::cout << p << "\n";
}
