# Ch 1. UNIX System Overview

## Exercise 1.3

> In Section 1.7, the argument to `perror` is defined with the ISO C attribute
`const,` whereas the integer argument to `strerror` isn’t defined with this
attribute. Why?

That is a very sharp question that gets into the core difference between
**pure functions** and functions that rely on or modify internal state—a
key concept in writing robust C code!

The difference in the use of the `const` attribute for the arguments of
`perror` and `strerror` is due to **data integrity and the contract of the
function itself.**

### 1. Why `perror`'s Argument is `const`

#### Signature: `void perror(const char *msg);`

The `perror` function performs this job:
1.  It takes your custom message (`msg`).
2.  It writes your message to standard error (`stderr`).
3.  It then appends a colon, space and the system error string (obtained
internally via `strerror(errno)`) then tails with newline.

**The Rule:** Since `perror` only needs to **read** the string pointed to by
`msg` and has no business changing it, the argument is declared `const`.

* **Contract:** By making the argument `const`, the compiler guarantees that
the function will not modify the memory where your message is stored. This
prevents accidental data corruption in the caller's program.

### 2. Why `strerror`'s Argument is NOT `const`

#### Signature: `char *strerror(int errnum);`

The `strerror` function's job is to take an error number (`errnum`) and
return a pointer to the corresponding human-readable error string.

**The Rule:** The argument is an integer (`int errnum`), which is passed
by value (a copy of the number). Since it's a copy of a primitive type,
**there is no pointer involved, and therefore `const` is irrelevant.**

* `const` can only be applied to a pointer or the data it points to.
* The function cannot modify the original integer variable in the calling
scope, making the use of `const` on `int errnum` nonsensical and unnecessary.

If the signature had been: `char *strerror(const int *errnum_ptr);` (meaning
it took a pointer to the error number), then the `const` keyword would
be appropriate to prevent the function from modifying the integer pointed
to. But since it takes the integer directly, `const` doesn't apply.

### Summary of the Difference

| Function | Argument Type | `const` Usage | Reason |
| :--- | :--- | :--- | :--- |
| **`perror`** | Pointer to character data (`char *`) | **Used** (`const char *`) | Prevents the function from modifying the user's string buffer. |
| **`strerror`**| Primitive integer (`int`) | **Not Used** (N/A) | The value is passed by copy. `const` has no meaning when applied to a value parameter of a primitive type. |

This subtle difference demonstrates how C uses the `const` keyword
meticulously to maintain memory safety and clearly define the "read-only"
contracts for pointers
