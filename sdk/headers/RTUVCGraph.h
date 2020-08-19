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
 *     module: RTUVCGraph
 */

#ifndef SRC_RT_TASK_APP_GRAPH_RTUVCGRAPH_H_
#define SRC_RT_TASK_APP_GRAPH_RTUVCGRAPH_H_

#include "rt_header.h"
#include "RTTaskGraph.h"

class RTUVCGraph : public RTTaskGraph {
 public:
    explicit RTUVCGraph(const char* tagName);
    ~RTUVCGraph();

    RT_RET prepare();
    RT_RET start();
    RT_RET stop();

    RT_RET observeUVCOutputStream(std::function<RT_RET(RTMediaBuffer *)> streamCallback);
    RT_RET updateCameraParams(RtMetaData *params);
    RT_RET updateEncoderParams(RtMetaData *params);
    RT_RET updateEPTZParams(RtMetaData *params);

    RT_RET enableEPTZ(RT_BOOL enableEPTZ);
    RT_RET setZoom(float val);

 private:
    RT_RET initialize(const char* tagName);
    RT_RET deinitialize();

 private:
    RT_BOOL mEnableEPTZ = RT_FALSE;
    float mZoom = 1.0f;
    INT32 mWidth;
    INT32 mHeight;
    INT32 mWStride;
    INT32 mHStride;
    std::function<RT_RET(RTMediaBuffer *)> mStreamCallback = NULL;
};

#endif  // SRC_RT_TASK_APP_GRAPH_RTUVCGRAPH_H_
