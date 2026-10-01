#ifndef ZV_SCRIPT_H
#define ZV_SCRIPT_H

/*
 * A text script of Canvas 2D commands, one per line, run on a canvas. The
 * same text renders in a browser through tools/ref_render.js, which is how
 * zen_vector is tested, and it is a compact way for tools and remote
 * clients to describe a drawing:
 *
 *   fillStyle #3366cc
 *   beginPath
 *   arc 32 32 20 0 6.2831853
 *   fill
 *
 * Commands: fillStyle, strokeStyle, lineWidth, lineCap, lineJoin, miterLimit,
 * setLineDash, lineDashOffset, globalAlpha, globalCompositeOperation,
 * imageSmoothingEnabled, shadowColor, shadowBlur, shadowOffsetX, shadowOffsetY,
 * translate, rotate, scale, transform, setTransform, resetTransform, save,
 * restore, fillRect, strokeRect, clearRect, beginPath, closePath, moveTo,
 * lineTo, quadraticCurveTo, bezierCurveTo, rect, roundRect, arc, arcTo,
 * ellipse, fill [nonzero|evenodd], stroke, clip, gradientLinear,
 * gradientRadial, gradientStop, fillGradient, strokeGradient, patternImage,
 * fillPattern, patternTransform, drawImage, font SIZE, textAlign,
 * textBaseline, fillText X Y TEXT..., strokeText X Y TEXT... Colours are
 * #rrggbb or #rrggbbaa. Lines starting with # are comments. An unknown
 * command is an error and nothing after it runs.
 */

#include "zv_canvas.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* A TrueType font for the text commands; NULL makes them fail. */
    typedef struct
    {
        const uint8_t *data;
        size_t size;
    } ZvScriptFont;

    /* Runs the script on canvas, drawing with its current state. A size
       command is an error here. Returns false with a message naming the
       line in err. */
    bool zv_script_run(ZvCanvas *canvas, const char *text, const ZvScriptFont *font, char *err, size_t errcap);

    /* Runs a script that starts with "size W H" into a new surface, which
       the caller releases. */
    bool zv_script_render(const char *text, const ZvScriptFont *font, ZvSurface *out, char *err, size_t errcap);

#ifdef __cplusplus
}
#endif

#endif /* ZV_SCRIPT_H */
