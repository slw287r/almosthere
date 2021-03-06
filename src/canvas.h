#ifndef ATHR_CANVAS_H
#define ATHR_CANVAS_H

struct canvas
{
    char* buff;
    int   length;
    int   min_length;
};

/**
 * Create a canvas.
 * It also sets the canvas length according to terminal width and
 * minimum length provided.
 * @param canvas Canvas object.
 * @param min_length Required minimum canvas length.
 */
void athr_canvas_create(struct canvas* canvas, int min_length);
/**
 * Assign ASCII character ' ' to every canvas character.
 * @param canvas Canvas object.
 */
void athr_canvas_draw(struct canvas* canvas);
void athr_canvas_clean(struct canvas* canvas);
/**
 * Resize canvas according to terminal width and minimum length.
 * @param canvas Canvas object.
 */
void athr_canvas_resize(struct canvas* canvas);
void athr_canvas_finish(struct canvas* canvas);

#endif
