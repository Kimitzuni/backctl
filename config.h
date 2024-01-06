#ifndef __INCLUDE_CONFIG_H__
#define __INCLUDE_CONFIG_H__

/* 
 * Set this to 1 to set the backlight value as a raw value between 0 and 255 
 * 
 * If set to 0, then a lot of mathematics will be used to calculate the value
 * as the raw value, where 100 = 255 and 0 = 0
 */
#define RAW_BACKLIGHT 0

/*
 * This value specifies the maximum brightness value that a backlight can be.
 */
#define MAX_BRIGHTNESS 255
#endif /* include/config.h */
