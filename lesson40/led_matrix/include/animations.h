/*
 * animations.h
 * 动画效果接口
 */

#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "led_matrix.h"

/* 动画名称枚举 */
typedef enum {
    ANIM_SMILE,       // 笑脸图案（静态展示）
    ANIM_BLINK,       // 眨眼动画（笑脸的眼睛闪烁）
    ANIM_MARQUEE,     // 跑马灯（一条垂直线从左向右移动）
    ANIM_BOUNCE,      // 弹跳球（一个点上下左右弹跳）
} AnimType;

/* 播放指定动画 */
void animation_play(AnimType type, int frames, int frame_delay_ms);

#endif