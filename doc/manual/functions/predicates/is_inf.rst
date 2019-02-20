.. _function-is_inf:

is_inf
============

**Required header** ``#include <eve/function/is_inf.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_inf( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if the parameter is infinite

.. seealso::  :ref:`Inf <constant-inf>`, :ref:`Minf <constant-minf>`

Parameters
----------

  - ``lhs``  : values to test.

Return value
------------

Semantically equivalent to `is_equal(abs(lhs), Inf(as(lhs)))`

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_inf.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_inf.txt
  :literal:

