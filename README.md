This program tests the data race that happens when you modify bitfield data members in a C struct.

In all the cases where the two printed numbers are not equal, and are not equal to 1, at least one data race has
happened.

In the case of TSAN executables you will see an error printed as well.

*Example output*
```
❯ make
gcc/test
1 0
1 0
14 1

gcc/test-tsan
==================
WARNING: ThreadSanitizer: data race (pid=235870)
  Read of size 1 at 0x7fffffffa634 by thread T2:
    #0 inc_b(S&) test.cpp:28 (test-tsan+0x4015e8)
    #1 void std::__invoke_impl<void, void (*)(S&), std::reference_wrapper<S> >(std::__invoke_other, void (*&&)(S&), std::reference_wrapper<S>&&) invoke.h:61 (test-tsan+0x40169e)
    #2 std::__invoke_result<void (*)(S&), std::reference_wrapper<S> >::type std::__invoke<void (*)(S&), std::reference_wrapper<S> >(void (*&&)(S&), std::reference_wrapper<S>&&) invoke.h:96 (test-tsan+0x40169e)
    #3 void std::thread::_Invoker<std::tuple<void (*)(S&), std::reference_wrapper<S> > >::_M_invoke<0ul, 1ul>(std::_Index_tuple<0ul, 1ul>) std_thread.h:292 (test-tsan+0x40169e)
    #4 std::thread::_Invoker<std::tuple<void (*)(S&), std::reference_wrapper<S> > >::operator()() std_thread.h:299 (test-tsan+0x40169e)
    #5 std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)(S&), std::reference_wrapper<S> > > >::_M_run() std_thread.h:244 (test-tsan+0x40169e)
    #6 execute_native_thread_routine ..thread.cc:104 (libstdc++.so.6+0xe8763)

  Previous write of size 1 at 0x7fffffffa634 by thread T1:
    #0 inc_a(S&) test.cpp:18 (test-tsan+0x401557)
    #1 void std::__invoke_impl<void, void (*)(S&), std::reference_wrapper<S> >(std::__invoke_other, void (*&&)(S&), std::reference_wrapper<S>&&) invoke.h:61 (test-tsan+0x40169e)
    #2 std::__invoke_result<void (*)(S&), std::reference_wrapper<S> >::type std::__invoke<void (*)(S&), std::reference_wrapper<S> >(void (*&&)(S&), std::reference_wrapper<S>&&) invoke.h:96 (test-tsan+0x40169e)
    #3 void std::thread::_Invoker<std::tuple<void (*)(S&), std::reference_wrapper<S> > >::_M_invoke<0ul, 1ul>(std::_Index_tuple<0ul, 1ul>) std_thread.h:292 (test-tsan+0x40169e)
    #4 std::thread::_Invoker<std::tuple<void (*)(S&), std::reference_wrapper<S> > >::operator()() std_thread.h:299 (test-tsan+0x40169e)
    #5 std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)(S&), std::reference_wrapper<S> > > >::_M_run() std_thread.h:244 (test-tsan+0x40169e)
    #6 execute_native_thread_routine ..thread.cc:104 (libstdc++.so.6+0xe8763)

  Location is stack of main thread.

  Location is global '<null>' at 0x000000000000 ([stack]+0x20634)

  Thread T2 (tid=235873, running) created by main thread at:
    #0 pthread_create ..tsan_interceptors_posix.cpp:1022 (libtsan.so.2+0x5b6a6)
    #1 std::thread::_M_start_thread(std::unique_ptr<std::thread::_State, std::default_delete<std::thread::_State> >, void (*)()) gthr-default.h:676 (libstdc++.so.6+0xe884c)

  Thread T1 (tid=235872, running) created by main thread at:
    #0 pthread_create ..tsan_interceptors_posix.cpp:1022 (libtsan.so.2+0x5b6a6)
    #1 std::thread::_M_start_thread(std::unique_ptr<std::thread::_State, std::default_delete<std::thread::_State> >, void (*)()) gthr-default.h:676 (libstdc++.so.6+0xe884c)

SUMMARY: ThreadSanitizer: data race test.cpp:28 in inc_b(S&)
==================
...
1 1
1 1
1 1
ThreadSanitizer: reported 4 warnings

clang/test
11 1
13 3
12 4

clang/test-tsan
llvm-symbolizer: error: '[stack]': No such file or directory
==================
WARNING: ThreadSanitizer: data race (pid=235897)
  Write of size 1 at 0x7fffffffa644 by thread T2:
    #0 inc_b(S&) race/test.cpp:28:7 (test-tsan+0x10579f)
    #1 void std::__invoke_impl<void, void (*)(S&), std::reference_wrapper<S>>(std::__invoke_other, void (*&&)(S&), std::reference_wrapper<S>&&) invoke.h:61:14 (test-tsan+0x105b51)
    #2 std::__invoke_result<void (*)(S&), std::reference_wrapper<S>>::type std::__invoke<void (*)(S&), std::reference_wrapper<S>>(void (*&&)(S&), std::reference_wrapper<S>&&) invoke.h:96:14 (test-tsan+0x105b51)
    #3 void std::thread::_Invoker<std::tuple<void (*)(S&), std::reference_wrapper<S>>>::_M_invoke<0ul, 1ul>(std::_Index_tuple<0ul, 1ul>) std_thread.h:292:13 (test-tsan+0x105b51)
    #4 std::thread::_Invoker<std::tuple<void (*)(S&), std::reference_wrapper<S>>>::operator()() std_thread.h:299:11 (test-tsan+0x105b51)
    #5 std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)(S&), std::reference_wrapper<S>>>>::_M_run() std_thread.h:244:13 (test-tsan+0x105b51)
    #6 execute_native_thread_routine thread.cc:104:18 (libstdc++.so.6+0xe8763)

  Previous write of size 1 at 0x7fffffffa644 by thread T1:
    #0 inc_a(S&) test.cpp:18:7 (test-tsan+0x1056e9)
    #1 void std::__invoke_impl<void, void (*)(S&), std::reference_wrapper<S>>(std::__invoke_other, void (*&&)(S&), std::reference_wrapper<S>&&) invoke.h:61:14 (test-tsan+0x105b51)
    #2 std::__invoke_result<void (*)(S&), std::reference_wrapper<S>>::type std::__invoke<void (*)(S&), std::reference_wrapper<S>>(void (*&&)(S&), std::reference_wrapper<S>&&) invoke.h:96:14 (test-tsan+0x105b51)
    #3 void std::thread::_Invoker<std::tuple<void (*)(S&), std::reference_wrapper<S>>>::_M_invoke<0ul, 1ul>(std::_Index_tuple<0ul, 1ul>) std_thread.h:292:13 (test-tsan+0x105b51)
    #4 std::thread::_Invoker<std::tuple<void (*)(S&), std::reference_wrapper<S>>>::operator()() std_thread.h:299:11 (test-tsan+0x105b51)
    #5 std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)(S&), std::reference_wrapper<S>>>>::_M_run() std_thread.h:244:13 (test-tsan+0x105b51)
    #6 execute_native_thread_routine thread.cc:104:18 (libstdc++.so.6+0xe8763)

  Location is stack of main thread.

  Location is global '??' at 0x7ffffffda000 ([stack]+0x20644)

  Thread T2 (tid=235900, running) created by main thread at:
    #0 pthread_create tsan_interceptors_posix.cpp:1023:3 (test-tsan+0x43967)
    #1 __gthread_create gthr-default.h:676:35 (libstdc++.so.6+0xe884c)
    #2 std::thread::_M_start_thread(std::unique_ptr<std::thread::_State, std::default_delete<std::thread::_State>>, void (*)()) thread.cc:172:37 (libstdc++.so.6+0xe884c)

  Thread T1 (tid=235899, running) created by main thread at:
    #0 pthread_create tsan_interceptors_posix.cpp:1023:3 (test-tsan+0x43967)
    #1 __gthread_create gthr-default.h:676:35 (libstdc++.so.6+0xe884c)
    #2 std::thread::_M_start_thread(std::unique_ptr<std::thread::_State, std::default_delete<std::thread::_State>>, void (*)()) thread.cc:172:37 (libstdc++.so.6+0xe884c)

SUMMARY: ThreadSanitizer: data race test.cpp:28:7 in inc_b(S&)
==================
...
5 1
14 9
8 9
ThreadSanitizer: reported 8 warnings
make: [Makefile:19: clang/test-tsan] Error 66 (ignored)
```
