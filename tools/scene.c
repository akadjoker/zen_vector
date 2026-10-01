#include "scene.h"
#include "zv_script.h"

#include <stdlib.h>
#include <string.h>

#ifndef ZV_SCENE_FONT
#define ZV_SCENE_FONT "fonts/DejaVuSans.ttf"
#endif

static const char *g_font_path = ZV_SCENE_FONT;

void zv_scene_set_font_path(const char *path)
{
    g_font_path = path ? path : ZV_SCENE_FONT;
}

static void message(char *err, size_t errcap, const char *text)
{
    if (err && errcap)
    {
        strncpy(err, text, errcap - 1);
        err[errcap - 1] = '\0';
    }
}

bool zv_scene_run(const char *text, ZvBitmap *out, char *err, size_t errcap)
{
    if (err && errcap)
        err[0] = '\0';
    if (!text || !out)
    {
        message(err, errcap, "line 0: no scene");
        return false;
    }
    size_t font_size = 0;
    uint8_t *font_data = zv_io_read(g_font_path, &font_size);
    ZvScriptFont font = {font_data, font_size};
    ZvSurface surface;
    bool ok = zv_script_render(text, font_data ? &font : NULL, &surface, err, errcap);
    if (ok)
    {
        if (!zv_bitmap_alloc(out, surface.width, surface.height))
        {
            message(err, errcap, "line 0: out of memory");
            ok = false;
        }
        else
            zv_surface_store_pixels(&surface, out->pixels, out->width, out->height, out->stride);
        zv_surface_release(&surface);
    }
    zv_io_free(font_data);
    return ok;
}
