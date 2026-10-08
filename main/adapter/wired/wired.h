/*
 * Copyright (c) 2021-2022, Jacques Gagnon
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _WIRED_H_
#define _WIRED_H_
#include "adapter/adapter.h"

int32_t wired_meta_init(struct wired_ctrl *ctrl_data);
void wired_init_buffer(int32_t dev_mode, struct wired_data *wired_data);
void wired_from_generic(int32_t dev_mode, struct wired_ctrl *ctrl_data, struct wired_data *wired_data);
void wired_fb_to_generic(int32_t dev_mode, struct raw_fb *raw_fb_data, struct generic_fb *fb_data);
void wired_gen_turbo_mask_axes8(struct wired_data *wired_data, uint8_t *axes, uint32_t axes_cnt,
                                const uint8_t axes_idx[6], const struct ctrl_meta *axes_meta);

#endif /* _WIRED_H_ */

