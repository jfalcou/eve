.. _function-is_equal_with_equal_nans:

is_equal_with_equal_nans
========================

**Required header** ``#include <eve/function/is_equal_with_equal_nans.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_equal_with_equal_nans( Value lhs, Value rhs ) noexcept
   }

This function returns :ref:`True <constant-true_>` if and only if
its parameters  :ref:`Values <concept-value>` are equal or both :ref:`Nans <constant-nan>`.

 
Infix notation can be used with operator '=='.

.. seealso::  :ref:`is_equal <function-is_equal>`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare of the same type

Return value
------------

The logical  equal of ``lhs`` and ``rhs`` for every elements of each parameter (considering :ref:`Nans <constant-nan>` are equal).

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_equal_with_equal_nans.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_equal_with_equal_nans.txt
  :literal:

