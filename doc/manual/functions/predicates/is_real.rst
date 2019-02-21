.. _function-is_real:

is_real
============

**Required header** ``#include <eve/function/is_real.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_real( Value lhs ) noexcept
   }


This function always returns :ref:`True <constant-true_>` 
This is the restriction to real inputs of the complex function.


Parameters
----------

  - ``lhs``  : values to test.

Return value
------------

Semantically equivalent to ``True(as(lhs)))``

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_real.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_real.txt
  :literal:

