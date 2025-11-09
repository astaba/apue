# Advanced Programming in UNIX Environment (3rd)

## `restrict` vs `volatile`

The confusion between `volatile` and `restrict` is extremely common because
they both deal with how the compiler treats pointers and memory access,
yet they serve **diametrically opposite goals.**

The APUE quote correctly identifies `restrict` as a tool for **optimization**.

Here is a clear breakdown of `restrict`, why it exists, and how it differs
completely from `volatile`.

-----

### The `restrict` Keyword: The Promise of Uniqueness

The `restrict` keyword (introduced in C99) is a **contract** or a **promise**
you make to the compiler about how pointers are used within a function.

#### The Goal: Enable Aggressive Optimization

The primary purpose of `restrict` is to solve the problem of
**aliasing**. Aliasing occurs when two different pointers refer to the
*same memory location*. When the compiler sees aliased pointers, it must be
conservative and reload data from memory constantly, just in case the memory
was changed by the other pointer.

#### The Promise

When you use `restrict` on a pointer argument, you are telling the compiler:

> **"For the entire duration of this function, the memory pointed to by this
restricted pointer will only be accessed through this pointer—or pointers
derived from it. No other pointer outside this function signature will touch
this memory."**

#### How It Works

Because the compiler knows the memory pointed to by a restricted pointer is
unique, it can assume that changes made via one restricted pointer cannot
affect the value of another restricted pointer. This allows the compiler to:

1.  **Cache values in CPU Registers:** It can keep the value in a fast CPU
register for longer, avoiding expensive reloads from memory.
2.  **Reorder Operations:** It can reorder reads and writes more aggressively
because it doesn't have to worry about interdependencies created by hidden
aliasing.

#### Example

Consider a function that copies `n` elements:

```c
void copy(int *restrict dest, const int *restrict src, size_t n);
```

By adding `restrict`, you tell the compiler: "The memory area pointed to by
`dest` **does not overlap** with the memory area pointed to by `src`." This
allows the compiler to generate much faster, optimized assembly code for
the copy loop. If you break this promise (i.e., you call `copy(A, A, 10)`),
the program might behave unpredictably.

-----

### `restrict` vs. `volatile`: Opposite Goals

While both keywords affect compiler optimization, they force the compiler
to act in completely different ways:

#### `volatile`: Disable Optimization

| Aspect | `volatile` |
| :--- | :--- |
| **Purpose** | **Safety/Correctness.** Tells the compiler to **NOT** optimize access to this variable. |
| **Mechanism**| Forces the compiler to load the variable from memory (or a memory-mapped device register) *every single time* it is accessed, and write back *every single time* it is modified. |
| **Use Case** | Multi-threaded programming (shared variables), hardware registers (memory-mapped I/O), or signal handlers. |
| **Goal** | Ensures the code reflects the literal sequence of reads and writes in the source, protecting against memory changes that the compiler cannot detect (like those from a separate thread or external hardware). |

#### `restrict`: Enable Optimization

| Aspect | `restrict` |
| :--- | :--- |
| **Purpose** | **Performance.** Gives the compiler permission to aggressively optimize. |
| **Mechanism**| Makes a promise to the compiler that the pointer is unique (non-aliased), allowing the compiler to cache values in registers and reorder operations. |
| **Use Case** | Standard library functions (like `memcpy`, `strcpy`), and high-performance computation functions. |
| **Goal** | Improves the speed of the code by exploiting the knowledge that pointers do not overlap. |

In short:

  * **`volatile` says:** **"The memory might change outside the compiler's
  view. Read it every time\!"** (Optimization Off).
  * **`restrict` says:** **"Trust me, this pointer is unique. It's safe to
  cache the data in a register."** (Optimization On).

