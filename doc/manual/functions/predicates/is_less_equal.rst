.. _function-is_less_equal:

is_less_equal
============

**Required header** ``#include <eve/function/is_less_equal.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_less_equal( Value lhs, Value rhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
  according its first parameter is less or equal to the second.


Infix notation can be used with operator '<='.

.. seealso::  :ref:`is_less <function-is_less>`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare of the same type

Return value
------------

The logical values ``lhs`` less or equal to ``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_less_equal.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_less_equal.txt
  :literal:

