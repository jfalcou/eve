.. _function-is_not_denormal:

is_not_denormal
============

**Required header** ``#include <eve/function/is_not_denormal.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_not_denormal( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if the parameter is not_denormal

.. seealso::  :ref:`Smallestposval <constant-Smallestposval>`, :ref:`abs <function-abs>`

Parameters
----------

  - ``lhs``  : values to test.

Return value
------------

Semantically equivalent to ``is_greater_equal(abs(lhs), Smallestposval(as(lhs)))``

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_not_denormal.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_not_denormal.txt
  :literal:

