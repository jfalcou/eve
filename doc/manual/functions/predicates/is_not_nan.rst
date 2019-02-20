.. _function-is_not_nan:

is_not_nan
============

**Required header** ``#include <eve/function/is_not_nan.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_not_nan( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if the parameter is not_nan

.. seealso::  :ref:`Smallestposval <constant-Smallestposval>`, :ref:`abs <constant-abs>`

Parameters
----------

  - ``lhs``  : values to test.

Return value
------------

Semantically equivalent to `is_equal(lhs, lhs)`

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_not_nan.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_not_nan.txt
  :literal:

