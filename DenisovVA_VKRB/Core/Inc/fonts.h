#ifndef __FONTS_H__
#define __FONTS_H__

#include <stdint.h>

// Шрифт: Font11x18
// Высота: 18 пикселей
// Ширина: 11 пикселей на символ
// Доступные символы: ASCII 32..126 (печатаемые)

#define FONT11X18_WIDTH 11
#define FONT11X18_HEIGHT 18

extern const uint16_t Font11x18[95][11];

#endif // __FONTS_H__
