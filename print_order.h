#pragma once

#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <functional>
#include <atomic>

namespace print_order
{
  class FooCondVar {
  public:

      void first() {
          
          // printFirst() outputs "first". Do not change or remove this line.
          std::cout << "First";
          _firstDone = true;
          _cv.notify_all();
      }

      void second() {
          std::unique_lock<std::mutex> lck(_mtx);
          while (!_firstDone) _cv.wait(lck);
          // printSecond() outputs "second". Do not change or remove this line.
          std::cout << "Second";
          _secondDone = true;
          _cv.notify_all();
      }

      void third() {
          std::unique_lock<std::mutex> lck(_mtx);
          while (!_secondDone) _cv.wait(lck);
          // printThird() outputs "third". Do not change or remove this line.
          std::cout << "Third";
      }
      
  private:
      std::mutex _mtx;
      std::condition_variable _cv;
      std::atomic<bool> _firstDone{false};
      std::atomic<bool> _secondDone{false};
  };

  class Foo {
  public:

      Foo() {
        std::lock(_mtx1, _mtx2);
      }

      void first() {
          
          // printFirst() outputs "first". Do not change or remove this line.
          std::cout << "First";
          _mtx1.unlock();
      }

      void second() {
          _mtx1.lock();
          // printSecond() outputs "second". Do not change or remove this line.
          std::cout << "Second";
          _mtx2.unlock();
      }

      void third() {
          _mtx2.lock();
          // printThird() outputs "third". Do not change or remove this line.
          std::cout << "Third";
      }
      
  private:
      std::mutex _mtx1;
      std::mutex _mtx2;
  };

  void run()
  {
      Foo foo;

      std::thread t1([&foo](){ foo.third(); });
      std::thread t2([&foo](){ foo.first(); });
      std::thread t3([&foo](){ foo.second(); });
      t1.join();
      t2.join();
      t3.join();
  }
}