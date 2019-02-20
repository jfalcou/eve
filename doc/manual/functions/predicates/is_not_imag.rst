.. _function-is_not_imag:

is_not_imag
============

**Required header** ``#include <eve/function/is_not_imag.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_not_imag( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if the parameter is not zero.
This is the restriction to real inputs of the complex function.



Parameters
----------

  - ``lhs``  : values to test.

Return value
------------

Semantically equivalent to `is_nez(lhs)`

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_not_imag.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_not_imag.txt
  :literal:

