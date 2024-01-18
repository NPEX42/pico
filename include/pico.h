#pragma once
#include <stdbool.h>
#include "pico/common.h"
#include "pico/app.h"
#include "pico/engine.h"
#include "pico/maths.h"
#include "pico/renderer.h"
#include "pico/image.h"


#define PICO_MAJOR 0
#define PICO_MINOR 1

bool pico_init(void);
void pico_start(PicoApp* app);

void pico_set_icon(PicoEngine* engine, PicoImage* icon);