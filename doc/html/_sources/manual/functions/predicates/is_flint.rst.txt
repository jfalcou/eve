.. _function-is_flint:

is_flint
============

**Required header** ``#include <eve/function/is_flint.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_flint( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if the parameter is a floating point representing an integral value

.. seealso::  :ref:`is_eqz <function-is_eqz>`

Parameters
----------

  - ``lhs``  : values to test.

Return value
------------

Semantically equivalent to ``is_eqz(lhs%1)``

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_flint.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_flint.txt
  :literal:

