.. _function-is_equal:

is_equal
============

**Required header** ``#include <eve/function/is_equal.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_equal( Value lhs, Value rhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
  according its parameters  :ref:`Values <concept-value>` are equal or not.


Infix notation can be used with operator '=='.

.. seealso::  :ref:`is_equal_with_equal_nans <function-is_equal_with_equal_nans>`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare of the same type

Return value
------------

The logical  equal of ``lhs`` and ``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_equal.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_equal.txt
  :literal:

