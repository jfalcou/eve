.. _function-is_odd:

is_odd
============

**Required header** ``#include <eve/function/is_odd.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_odd( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if the parameter is odd


Parameters
----------

  - ``lhs``  : values to test.

Return value
------------

Semantically equivalent to `is_even(lhs+lhs)`

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_odd.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_odd.txt
  :literal:

