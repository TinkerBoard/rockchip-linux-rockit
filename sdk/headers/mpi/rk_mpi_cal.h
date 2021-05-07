/*
 * Copyright 2021 Rockchip Electronics Co. LTD
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
 */

#ifndef INCLUDE_RT_MPI_RK_MPI_BUFFER_H_
#define INCLUDE_RT_MPI_RK_MPI_BUFFER_H_

#include "rk_type.h"
#include "rk_common.h"
#include "rk_comm_video.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

RK_S32 RK_MPI_CAL_COMM_GetPicBufferSize(const PIC_BUF_ATTR_S *pstBufAttr, MB_PIC_CAL_S *pstPicCal);
RK_S32 RK_MPI_CAL_TDE_GetPicBufferSize(const PIC_BUF_ATTR_S *pstBufAttr, MB_PIC_CAL_S *pstPicCal);
RK_S32 RK_MPI_CAL_VGS_GetPicBufferSize(const PIC_BUF_ATTR_S *pstBufAttr, MB_PIC_CAL_S *pstPicCal);
RK_S32 RK_MPI_CAL_VDEC_GetPicBufferSize(const VDEC_PIC_BUF_ATTR_S *pstBufAttr, MB_PIC_CAL_S *pstPicCal);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  // INCLUDE_RT_MPI_RK_MPI_BUFFER_H_

