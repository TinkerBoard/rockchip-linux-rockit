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
 *     author: <rimon.xu@rock-chips.com> and <martin.cheng@rock-chips.com>
 *       date: 2020-04-03
 *     module: RTTaskGraph
 */

#ifndef SRC_RT_TASK_APP_GRAPH_RTTASKGRAPH_H_
#define SRC_RT_TASK_APP_GRAPH_RTTASKGRAPH_H_

#include <vector>
#include <memory>
#include <map>
#include <functional>

#include "rt_header.h"
#include "rt_metadata.h"

typedef enum ExecutorMode {
    EXECUTOR_THREAD_POOL,
    EXECUTOR_THREAD_LOCAL,
} RTExecutorMode;

typedef enum GraphCmd {
    GRAPH_CMD_PREPARE = 100,
    GRAPH_CMD_START,
    GRAPH_CMD_PAUSE,
    GRAPH_CMD_RESUME,
    GRAPH_CMD_STOP,
    GRAPH_CMD_FLUSH,
    // for graph private command
    GRAPH_CMD_PRIVATE_CMD,
    // for task node command
    GRAPH_CMD_TASK_NODE_PRIVATE_CMD,
    GRAPH_CMD_MAX,
} RTGraphCmd;

class RTInputStreamManager;
class RTOutputStreamManager;
class RTTaskNode;
class RTGraphOutputStream;
class RTExecutor;
class RTScheduler;
class RTMediaBuffer;
class RTNodeParser;

class RTTaskGraph {
 public:
    explicit RTTaskGraph(const char* tagName);
    virtual ~RTTaskGraph();

    RT_RET autoBuild(const char* configFile);
    RT_RET prepareForRun(RtMetaData *options);
    RT_RET cleanupAfterRun();
    RT_RET invoke(INT32 cmd, RtMetaData *params);
    RT_RET dump();
    RT_RET startRun();
    RT_RET finishRun();
    RT_RET waitUntilDone();
    RT_RET waitForObservedOutput();

    void sendInterrupt(std::string reason);
    void updateThrottledNodes(RTInputStreamManager* stream, bool *streamWasFull);
    RT_RET observeOutputStream(const std::string& streamName,
            INT32 streamId,
            std::function<RT_RET(RTMediaBuffer *)> streamCallback);

    RT_RET addSubGraph(const char *graphConfig);
    RT_RET removeSubGraph(const char *graphConfig);

 private:
    RT_RET prepare();
    RT_RET autoLinkSource();
    RT_RET autoUnlinkSource(INT32 nodeId);
    RT_RET prepareNodeForRun(RTTaskNode *node, RtMetaData *options);
    RT_RET buildTaskNode(INT32 pipeId, INT32 nodeId, RTNodeParser* nodeParser);

 protected:
    std::string     mTagName;
    RT_BOOL         mHasError;
    RtMutex         mFullInputStreamsMutex;
    RtMutex         mErrorMutex;
    RTScheduler    *mScheduler;

    std::vector<RTExecutor *>                             mExecutors;
    std::map<INT32/* node id */, RTTaskNode *>            mNodes;
    std::map<INT32, RTInputStreamManager *>               mFullInputStreams;
    std::map<INT32/* node id */, RTInputStreamManager *>  mInputManagers;
    std::map<INT32/* node id */, RTOutputStreamManager *> mOutputManagers;
    // The graph output streams.
    std::map<INT32, RTGraphOutputStream *>                mGraphOutputStreams;
};

#endif  // SRC_RT_TASK_APP_GRAPH_RTTASKGRAPH_H_
