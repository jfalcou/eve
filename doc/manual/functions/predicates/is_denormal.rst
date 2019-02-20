.. _function-is_denormal:

is_denormal
============

**Required header** ``#include <eve/function/is_denormal.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_denormal( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if the parameter is denormal

.. seealso::  :ref:`Smallestposval <constant-Smallestposval>`, :ref:`abs <function-abs>`

Parameters
----------

  - ``lhs``  : values to test.

Return value
------------

Semantically equivalent to `is_less(abs(lhs), Smallestposval(as(lhs))) && is_nez(lhs)`

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_denormal.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_denormal.txt
  :literal:

