/*
 * Copyright (c) 2021-2024, Jacques Gagnon
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include "zephyr/types.h"
#include "tools/util.h"
#include "ps.h"
#include "wired.h"

static from_generic_t from_generic_func[WIRED_MAX] = {
    [PSX] = ps_from_generic,
    [PS2] = ps_from_generic,
};

static fb_to_generic_t fb_to_generic_func[WIRED_MAX] = {
    [PSX] = ps_fb_to_generic,
    [PS2] = ps_fb_to_generic,
};

static meta_init_t meta_init_func[WIRED_MAX] = {
    [PSX] = ps_meta_init,
    [PS2] = ps_meta_init,
};

static DRAM_ATTR buffer_init_t buffer_init_func[WIRED_MAX] = {
    [PSX] = ps_init_buffer,
    [PS2] = ps_init_buffer,
};

int32_t wired_meta_init(struct wired_ctrl *ctrl_data) {
    if (meta_init_func[wired_adapter.system_id]) {
        meta_init_func[wired_adapter.system_id](ctrl_data);
        return 0;
    }
    return -1;
}

void IRAM_ATTR wired_init_buffer(int32_t dev_mode, struct wired_data *wired_data) {
    if (buffer_init_func[wired_adapter.system_id]) {
        buffer_init_func[wired_adapter.system_id](dev_mode, wired_data);
    }
}

void wired_from_generic(int32_t dev_mode, struct wired_ctrl *ctrl_data, struct wired_data *wired_data) {
    if (from_generic_func[wired_adapter.system_id]) {
        from_generic_func[wired_adapter.system_id](dev_mode, ctrl_data, wired_data);
    }
}

void wired_fb_to_generic(int32_t dev_mode, struct raw_fb *raw_fb_data, struct generic_fb *fb_data) {
    if (fb_to_generic_func[wired_adapter.system_id]) {
        fb_to_generic_func[wired_adapter.system_id](dev_mode, raw_fb_data, fb_data);
    }
}

void IRAM_ATTR wired_gen_turbo_mask_axes8(struct wired_data *wired_data, uint8_t *axes, uint32_t axes_cnt,
                                            const uint8_t axes_idx[6], const struct ctrl_meta *axes_meta) {
    for (uint32_t i = 0; i < axes_cnt; i++) {
        uint8_t btn_id = axis_to_btn_id(i);
        uint8_t mask = wired_data->cnt_mask[btn_id] >> 1;
        if (mask) {
            if (wired_data->cnt_mask[btn_id] & 1) {
                if (!(mask & wired_data->frame_cnt)) {
                    axes[axes_idx[i]] = axes_meta[i].neutral;
                }
            }
            else {
                if (!((mask & wired_data->frame_cnt) == mask)) {
                    axes[axes_idx[i]] = axes_meta[i].neutral;
                }
            }
        }
    }
}

