//This is an example of using a singleton class usable with threads.

#include "singleton.h"

std::mutex cout_mutex;

std::atomic<size_t> Singleton::s_refs{0U};

// This is the key method that returns the singleton reference
Singleton& Singleton::instance( void )
{
  ++s_refs;
  static Singleton instance{};
  return instance;
}

Singleton::Singleton( void ) // Default constructor
{
  std::cout << "Constructing Singleton" << std::endl;
}

Singleton::~Singleton( void ) // Destructor
{
  std::cout << "Destroying Singleton" << std::endl;
}

void Singleton::whoami( void )
{
  std::lock_guard<std::mutex> lock( cout_mutex );
  printf( "Singleton at @%p\n", this );
}

void Singleton::increment( void ) {
  ++m_count;
}

//EOF
