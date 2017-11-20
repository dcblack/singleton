// Multi-thread example that uses a singleton class

#include <string>

const size_t PER_JOB_RANDOM_DELAY_COUNT = 1'000;
const size_t PER_JOB_INCREMENT_COUNT = 1'000;
const size_t NUMBER_OF_THREADS = 500;

////////////////////////////////////////////////////////////////////////////////
#include "singleton.h"
#include <deque>
std::mutex finish_mutex;
std::deque<size_t> finished;

#include <mutex>
#include <condition_variable>
std::mutex              go_mutex;
std::condition_variable go_condition;
bool                    go_ready = false;

#include <random>

// Function to launch as multiple threads
void do_work( size_t id )
{
  // Wait for `go' signal
  std::unique_lock<std::mutex> lck( go_mutex );
  while ( !go_ready ) {
    go_condition.wait( lck );
  }

  // Random delay
  std::uniform_int_distribution<size_t> dist{1, 10};
  std::random_device gen;
  volatile double x = 0.0;
  for ( size_t i = PER_JOB_RANDOM_DELAY_COUNT*dist(gen); i>0; --i ) {
    ++x;
  }

  // Increment shared data
  Singleton& s{Singleton::instance()};
    for ( size_t i=PER_JOB_INCREMENT_COUNT; i > 0; --i ) {
    s.increment();
  }

  // Record order of completion
  {
    std::lock_guard<std::mutex> lock( finish_mutex );
    finished.push_back( id );
  }
}

void go()
{
  std::unique_lock<std::mutex> lck( go_mutex );
  go_ready = true;
  go_condition.notify_all();
}

////////////////////////////////////////////////////////////////////////////////
#include <deque>
#include <thread>
#include <iostream>
#include <iomanip>
int main( void )
{
  // Create threads
  std::deque<std::thread> threads;
  for ( size_t i=NUMBER_OF_THREADS; i>0; --i ) {
    threads.push_back(std::thread(do_work, i));
  }
  std::cout << threads.size() << " threads ready to race" << std::endl;

  // Start threads
  go();

  // Wait for finish
  for ( auto& t: threads ) {
    t.join();
  }

  // Report results
  std::cout << "Finishing order:\n" << std::flush;
  size_t n = 0;
  for( auto v: finished ) {
    std::cout << " " << std::setw(4) << v;
    if( (++n % 20) == 0 ) std::cout << std::endl;
  }
  std::cout << "Got reference to singleton " << Singleton::get_refs() << " times." << std::endl;
  std::cout << "Final count is " << Singleton::instance().get_count() << std::endl;
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Copyright 2017 Doulos Inc.
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////
