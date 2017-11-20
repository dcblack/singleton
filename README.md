# singleton

C++ Multi-threaded Singleton Design Pattern Example

## ABOUT

This is an example of using a singleton class with threads.
Note that C++11 guarantees the thread safety of the static
construction.

## Building and running


```bash
${CXX} -std=c++14 -o singleton.x singleton.cpp main.cpp && ./singleton.x
```

## Summary of technique

```c++
  struct Singleton {
     static Singleton& instance( void ) {
       static Singleton instance{}; //< the single instance
       return instance;
     }
     // Other public methods ...
 
  private: //deletes don't need to be private, but it's of no interest publically either
      Singleton( const Singleton& rhs ) = delete;  // copy constructor
      const Singleton& operator=( const Singleton& rhs ) = delete;  // copy assignment
      Singleton( const Singleton&& rhs ) = delete;  // move constructor
      const Singleton& operator=( const Singleton&& rhs ) = delete;  // move assignment
      Singleton( void ); // Default constructor
      ~Singleton( void ); // Destructor
      // attributes ...
  };
```
