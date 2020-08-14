/*
 * Copyright 2020 Rockchip Electronics Co. LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * src author: <mediapipe-team@google.com>
 * new author: modified by <rimon.xu@rock-chips.com> and <martin.cheng@rock-chips.com>
 *       date: 2020-03-19
 *  reference: https://github.com/google/mediapipe
 */


#ifndef SRC_RT_TASK_TASK_GRAPH_RTEXECUTOR_H_
#define SRC_RT_TASK_TASK_GRAPH_RTEXECUTOR_H_

#include "rt_header.h"
#include "RTThreadOptions.h"
#include "RTThreadPool.h"

// Abstract base class for the task queue.
// NOTE: The task queue orders the ready tasks by their priorities. This
// enables the executor to run ready tasks in priority order.
class RTTaskQueue {
 public:
    virtual ~RTTaskQueue();

    // Runs the next ready task in the current thread. Should be invoked by the
    // executor. This method should be called exactly as many times as AddTask
    // was called on the executor.
    virtual void runNextTask() = 0;
};

// Abstract base class for the RTExecutor.
class RTExecutor {
 public:
    virtual ~RTExecutor();

    // A registered RTExecutor subclass must implement the static factory method
    // Create.  The RTExecutor subclass cannot be registered without it.
    //
    // static ::mediapipe::StatusOr<RTExecutor*> Create(
    //     const MediaPipeOptions& extendable_options);
    //
    // Create validates extendable_options, then calls the constructor, and
    // returns the newly allocated RTExecutor object.

    // The scheduler queue calls this method to tell the executor that it has
    // a new task to run. The executor should use its execution mechanism to
    // invoke taskQueue->runNextTask.
    virtual void addTask(RTTaskQueue* taskQueue) {
        schedule([taskQueue] { taskQueue->runNextTask(); });
    }

    // schedule the specified "task" for execution in this executor.
    virtual void schedule(std::function<void()> task) = 0;
};

// A multithreaded executor based on a thread pool.
class RTThreadPoolExecutor : public RTExecutor {
 public:
    static RTExecutor* create(void *extendOptions, int numThreads = 4);

    explicit RTThreadPoolExecutor(int numThreads);
    ~RTThreadPoolExecutor() override;

 public:
    void schedule(std::function<void()> task) override;

    // For testing.
    int getNumThreads() const { return mThreadPool.getNumThreads(); }
    // Returns the thread stack size (in bytes).
    size_t getStackSize() const { return mStackSize; }

 private:
    RTThreadPoolExecutor(const RTThreadOptions& threadOptions, INT32 numThreads);

    // Saves the value of the stack size option and starts the thread pool.
    void start();

    RTThreadPool mThreadPool;

    // Records the stack size in RTThreadOptions right before we call
    // mThreadPool.startWorkers().
    //
    // The actual stack size passed to pthread_attr_setstacksize() for the
    // worker threads differs from the stack size we specified. It includes the
    // guard size and space for thread-local storage. (See Thread::start() in
    // thread/thread.cc.) So the unit tests check the stack size in
    // RTThreadOptions, in addition to trying to recover the specified stack
    // size from the stack size returned by pthread_getattr_np(),
    // pthread_attr_getstacksize(), and pthread_attr_getguardsize().
    size_t mStackSize = 0;
};

class RTSingleExecutor : public RTExecutor {
 public:
    static RTExecutor* create(void *extendOptions);

    explicit RTSingleExecutor(const RTThreadOptions& threadOptions);
    ~RTSingleExecutor() override;
    void schedule(std::function<void()> task) override;

 private:
    RTThreadPool mThreadPool;
};

#endif  // SRC_RT_TASK_TASK_GRAPH_RTEXECUTOR_H_
