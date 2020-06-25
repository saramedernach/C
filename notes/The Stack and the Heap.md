# The Stack and the Heap

This code is dangerous!  Why?

```cpp
int* allocate_four_ints() {
  // Allocate four ints; set them all to zero:
  int storage[4] = {0};

  // Return a pointer to the new memory:
  return storage;
}
```


## The Stack

The **stack** is an area of memory that your program uses to store all the local
variables of  all the functions  that are currently running.  A  **stack frame**
(storage space for a single function's locals) is pushed onto the stack whenever
a function is called, and is popped off the stack when that function returns.

Consider this program:

```cpp
#include <iostream>

void print_double(int number) {
  int dbl = number + number;
  std::cout << dbl << '\n';
}

void say_goodbye() {
  std::cout << "Goodbye.\n";
}

int main() {
  int number = 17;
  print_double(number);
  say_goodbye();
  return 0;
}

```

As the program runs, the stack looks like this (stack frames are pushed onto and
popped off of the right side):

```
[main]
[main] [print_double]
[main] [print_double] [<<]
[main] [print_double]
[main] [print_double] [<<]
[main] [print_double]
[main]
[main] [say_goodbye]
[main] [say_goodbye] [<<]
[main] [say_goodbye]
[main]
```

The stack frame for `main()` contains storage space for the variable `number` as
well as any  temporary variables  the compiler needed to create  (in this simple
example, probably none).

Similarly, the stack frame for  `print_double()`  contains storage space for the
local `dbl`.  It does _not_ have any storage space for  its `number` parameter -
depending on you architecture, parameters are either passed on the stack between
stack frames (`x86_32`) or in registers inside the CPU itself (`x86_64`).

The  `say_goodbye()`  function doesn't have any local variables, but it gets its
own stack frame simply because it's a function call.

Finally, the  `<<`  operator is  actually a function call  (defined via operator
overloading  somewhere in the  standard  library).  It gets its own  stack frame
whenever you use it, holding whatever local variables it needs.


## Pointers to Local Variables

As you can see from the stack diagram, if `f()` calls `g()`, `f()`'s stack frame
is "alive" the entire time that `g()` is running.  This means that it's safe for
`f()`  to pass a pointer to  one of its local variables  to `g()` - that pointer
will always be valid inside `g()`.

_Note that this is not the case if `g()` stores that pointer anywhere that might
outlive `f()`'s stack frame._

You can also see how  `return`ing  a pointer to a local variable  isn't going to
work.  As soon as a function returns, its stack frame gets popped off the stack,
and any pointers into that frame are now invalid.  But what does that mean?

Well, the memory the pointer points to is still there, and you can acces it.  It
even still contains the data you expect it to - at least for a little while. The
problem is that the stack considers that memory to be available,  and if another
function  needs that stack space,  the new function's locals  will get copied on
top of your data,  and your data is now corrupt.  Furthermore, if you then write
to that pointer, you've trashed an innocent function's stack frame.  Either case
could cause any number of strange bugs, and they will not be easy to find.


## The Heap

So how  do you  return memory from a  function?  You can do it,  but that memory
shouldn't come from the stack.  It needs to live somewhere else.  That somewhere
else is known as the **heap**, and it's designed for exactly this purpose.

You can think of the heap as a big bag of memory. You can use the `new` operator
to tell C++ that you'd like some memory,  and then that memory is reserved until
you use the `delete` operator to say that you're done with it.

The `new` operator does three things. First it allocates memory, like `malloc()`
from C. Then it calls the appropriate constructor(s) to make sure that memory is
initialized.  Finaly it returns  a pointer  to your new object(s).  The `delete`
operator does the reverse: it calls destructors and then behaves like `free()`.

There are two forms of both `new` and `delete`. The first form is for allocating
and destroying single objects:

```cpp
std::string* mystring = new std::string;
delete mystring;
```

The second is for arrays, and involves square brackets:

```cpp
std::string* mystrings = new std::string[42];
delete [] mystrings;
```

We can now fix the broken function from the beginning by using the heap:

```cpp
int* allocate_four_ints() {
  // Allocate four ints; set them all to zero.
  // Without the () the memory will not be zeroed.
  // This is a C++ quirk with built-in types.
  int* storage = new int[4]();

  // Return a pointer to the new memory:
  return storage;
}
```


## Problems

Our  `allocate_four_ints()`  function is safe now,  but with a caveat.  Since we
used `new` to allocate storage,  whoever uses that storage  needs to remember to
use `delete`  when they're done with it.  If they forget,  that's a memory leak,
one of  several  things that can go wrong when you let programmers manage memory
directly:

- A **memory leak** is when you don't `delete` memory  when you're done with it.
  This won't  crash your program  (unless you use up all your memory),  but it's
  wasteful and considered bad hygiene, especially in long-running programs.

- A **use after free** is when you access a pointer  after using `delete` on it.
  This causes  essentially the same problems  as returning a pointer  to a local
  variable: your data can be overwritten at any time, and writes to that pointer
  can corrupt other objects, or even the heap itself.

- A **double free** is when you `delete` the same pointer  more than once.  This
  is usually caught by your heap implementation,  which will report an error and
  crash your program.  If it isn't caught,  it can result in  different calls to
  `new` returning the same memory, leading to data corruption.


## Encapsulation

One way to make manual memory management easier to work with is to let C++ do as
much of the work as it can.  Since objects' constructos are called automatically
when they're created,  and their destructors are  called automatically when they
go out of scope,  any memory that belongs to the object can be dealt with there.
This makes your objects easier to use by hiding the implementation details.

If you write such a class, though, be careful.  The default behavior of some C++
class functions is to copy pointers - _not_ the values they point to.  So you'll
probably need to implement or delete the move/copy constructor and the move/copy
assignment operators of any class you use like this.

```cpp
class Wrapper {
  Thing* data;
public:
  // Constructor
  Wrapper() {
    data = new Thing;
  }

  // Move Constructor
  Wrapper(Wrapper&& other) {
    data = nullptr;
    *this = other;
  }

  // Copy Constructor
  Wrapper(const Wrapper& other) {
    data = nullptr;
    *this = other;
  }

  // Destructor
  ~Wrapper() {
    delete data;
  }

  // Move Assignment
  Wrapper& operator = (Wrapper&& other) {
    if(this != &other) {
      std::swap(data, other->data);
    }

    return *this;
  }

  // Copy Assignment
  Wrapper& operator = (const Wrapper& other) {
    if(this != &other) {
      Thing* temp = data;
      data = new Thing(*other->data);
      delete temp;
    }

    return *this;
  }
};
```
