add
===

**Required header** ``#include <eve/function/add.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value add( Value arg0, Value arg1 ) noexcept
   }

Computes the sum of two Value of the same type.

Parameters
----------

   - ``arg0``,``arg1`` :

Return value
------------

The value of  ``arg0 + arg1`` for every element f each parameters.

Options
-------


Example
-------

.. code-block:: c++

   #include <iostream>
   #include <cstdlib>
   #include <climits>

   int main()
   {
       std::cout << "abs(+3) = " << std::abs(3) << '\n'
                 << "abs(-3) = " << std::abs(-3) << '\n';

   //  std::cout << std::abs(INT_MIN); // undefined behavior on 2's complement systems
   }


See also
--------
