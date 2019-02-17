.. _concept-integervalue:

IntegerValue
============

An :ref:`concept-integervalue` type is a type which satisfies either :ref:`concept-vectorizable` or
``Vectorized`` and which underlying scalar type behaves like an integral value.

Requirements
------------

A type ``T`` satisfies :ref:`concept-integervalue` if:

  - ``T``  satisfies `:ref:`concept-vectorizable` or  ``Vectorized``
  - ``std::is_integral_v<eve::scalar_of_t<T>>`` evaluates to ``true``

Example
---------

  - ``int``
  - ``short``
  - ``eve::wide<std::int64_t>``
