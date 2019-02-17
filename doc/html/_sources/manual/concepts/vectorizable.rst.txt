.. _concept-vectorizable:

Vectorizable
============

A :ref:`concept-vectorizable` type is usable as the template parameter of other components like
``eve::wide`` to produce a :ref:`concept-vectorized` type.

Requirements
------------

  A type ``T`` satisfies :ref:`concept-vectorizable` if it refines Logical or if:

    - ``sizeof(T) <= sizeof(double)`` and
    - ``std::is_arithmetic_v<T>`` evaluates to ``true`` and
    - ``std::is_same_v<T, bool>`` evaluates to ``false``.

Example
-------

  - ``float``
  - ``double``
  - ``int``
  - ``char``
  - ``std::uint16_t``
  - ``eve::logical<short>``
