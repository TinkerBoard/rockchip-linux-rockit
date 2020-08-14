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
 * new author: modified by <rimon.xu@rock-chips.com>
 *       date: 2020-03-23
 *  reference: https://github.com/google/mediapipe
 */

#ifndef SRC_RT_TASK_TASK_GRAPH_RTTASKNODECONTEXT_H_
#define SRC_RT_TASK_TASK_GRAPH_RTTASKNODECONTEXT_H_

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "rt_header.h"
#include "rt_metadata.h"
#include "RTStreamInfo.h"

class RTMediaBuffer;
class RTOutputStreamShared;
class RTTaskNodeContext {
 public:
    explicit RTTaskNodeContext(
            std::string nodeName,
            INT32 nodeId,
            const std::vector<RTStreamInfo *> &inputInfos,
            const std::vector<RTStreamInfo *> &outputInfos);
    ~RTTaskNodeContext();

    RTTaskNodeContext(const RTTaskNodeContext&) = delete;
    RTTaskNodeContext& operator=(const RTTaskNodeContext&) = delete;

    RT_RET prepareForRun(RtMetaData* options);
    RT_RET cleanupAfterRun();

    const std::string& nodeName() const { return mNodeName; }
    INT32 nodeId() const { return mNodeId; }

    void suspend() { mSuspend = true; }
    void resume() { mSuspend = false; }
    bool isSuspend() { return mSuspend; }

    std::vector<RTMediaBuffer *>& inputs(std::string streamType) { return mInputs[streamType]; }
    std::vector<RTMediaBuffer *>& inputs() { return mInputs.begin()->second; }
    RTStreamInfo *getInputInfo(std::string streamType);
    RTStreamInfo *getInputInfo() { return mInputInfos.front(); }
    RTStreamInfo *getOutputInfo(std::string streamName);
    RTStreamInfo *getOutputInfo() { return mOutputInfos.front(); }

    RTOutputStreamShared *outputs() { return mOutputs.begin()->second; }
    RTOutputStreamShared *outputs(std::string streamName) { return mOutputs[streamName]; }
    RtMetaData* options() { return mOptions; }

    void setMaxBatchPrcoessSize(INT32 maxBatchSize) {
        mMaxBatchProcessSize = maxBatchSize;
    }

    INT32 getMaxBatchPrcoessSize() { return mMaxBatchProcessSize; }

 private:
    std::map<std::string, std::vector<RTMediaBuffer *>> mInputs;
    std::map<std::string, RTOutputStreamShared *> mOutputs;
    RtMetaData           *mOptions;
    INT32 mNodeId;
    std::string mNodeName;
    bool mSuspend = false;
    INT32 mMaxBatchProcessSize = 4;
    std::vector<RTStreamInfo *> mInputInfos;
    std::vector<RTStreamInfo *> mOutputInfos;
};

#endif  // SRC_RT_TASK_TASK_GRAPH_RTTASKNODECONTEXT_H_

