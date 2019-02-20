.. _function-is_greater:

is_greater
============

**Required header** ``#include <eve/function/is_greater.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_greater( Value lhs, Value rhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its first parameter is greater than the second.


Infix notation can be used with operator '>'.

.. seealso::  :ref:`is_greater_equal <function-is_greater_equal>`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare of the same type

Return value
------------

The logical values ``lhs`` greater than ``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_greater.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_greater.txt
  :literal:

