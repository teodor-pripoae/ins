// Copyright (c) 2015, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Author: yanshiguang02@baidu.com

#ifndef  COMMON_THIS_THREAD_H_
#define  COMMON_THIS_THREAD_H_

#include <pthread.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#ifdef __APPLE__
#include <mach/mach.h>
#include <sys/resource.h>
#else
#include <syscall.h>
#endif

namespace ins_common {

class ThisThread {
public:
    /// Sleep in ms
    static void Sleep(int64_t time_ms) {
        if (time_ms > 0) {
            timespec ts = {time_ms / 1000, (time_ms % 1000) * 1000000 };
            nanosleep(&ts, &ts);
        }
    }
    /// Get thread id
    static int GetId() {
        static __thread int s_thread_id = 0;
        if (s_thread_id == 0) {
            #if defined(__APPLE__)
            s_thread_id = mach_thread_self();
            #else
            s_thread_id = syscall(__NR_gettid);
            #endif
        }
        return s_thread_id;
    }
    /// Yield cpu
    static void Yield() {
        sched_yield();
    }

};

} // namespace common

using ins_common::ThisThread;

#endif  // COMMON_THIS_THREAD_H_
