.. _function-bitwise_notor:

bitwise_notor
=============

**Required header** ``#include <eve/function/bitwise_notor.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value0 bitwise_notor( Value0 lhs, Value1 rhs ) noexcept
   }

Function object for performing bitwise notor over two :ref:`Values <concept-value>` of possibly different types
but of same bit size, (``~lhs | rhs``).

The result type is the one of the first operator.


Parameters
----------

  - ``lhs``, ``rhs`` : input values

Return value
------------

The bitwise or of  complement of ``lhs`` with  ``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/bitwise_notor.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/bitwise_notor.txt
  :literal:

