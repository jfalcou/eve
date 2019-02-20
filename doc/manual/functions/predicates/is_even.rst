.. _function-is_even:

is_even
============

**Required header** ``#include <eve/function/is_even.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_even( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if the parameter is even


Parameters
----------

  - ``lhs``  : values to test.

Return value
------------

Semantically equivalent to ``is_eqz(lhs%2 )``

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_even.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_even.txt
  :literal:

