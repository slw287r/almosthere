#include "almosthere.h"
#include "almosthere_time.h"
#include "almosthere_widget.h"
#include <stdlib.h>

/* Minimum different in seconds considered safe for computing speed. */
static const int MINIMUM_DELTA = 0.01;

struct almosthere {
  int64_t volume;
  double consumed;
  double speed;
  struct timespec delta_start;
  double consumed_start;
  struct almosthere_widget_bar *widget;
  thrd_t thr;
};

int almosthere_thread_start(void *args) {
  // struct cline *line = (struct cline *)args;
  //
  // long sleeping_delta = 1000 * 1000 * 10;
  //
  // cline_update(line, 0);
  // while (line->drawn < line->length) {
  //   thrd_sleep(&(struct timespec){.tv_nsec = sleeping_delta}, NULL);
  //   cline_update_speed(line);
  //   cline_update(line, sleeping_delta);
  // }

  return 0;
}

struct almosthere *almosthere_create(int64_t volume) {

  struct almosthere *at = malloc(sizeof(struct almosthere));

  at->volume = volume;
  at->consumed = 0;
  at->speed = 0;
  timespec_get(&at->delta_start, 0);
  at->consumed_start = 0;

  almosthere_widget_create(&at->widget);

  thrd_create(&at->thr, almosthere_thread_start, at);

  return at;
}

void almosthere_update_speed(struct almosthere *at) {
  // TODO: NEED TO BE ATOMIC!!
  struct timespec curr, diff;

  timespec_get(&curr, 0);
  timespec_diff(&at->delta_start, &curr, &diff);

  double dlt = timespec_seconds(diff);

  if (dlt >= MINIMUM_DELTA) {
    at->speed = at->consumed_start / dlt;
    at->delta_start = curr;
    at->consumed_start = at->consumed;
  }
}

void almosthere_consume(struct almosthere *at, int64_t consume) {
  // TODO: NEED TO BE ATOMIC!!
  at->consumed += consume;
  if (at->consumed > at->volume)
    at->consumed = at->volume;
}

struct almosthere *almosthere_finish(struct almosthere *at) {

  pthread_join(at->thr, NULL);
  almosthere_widget_create(at->widget);
  free(at);
}

// void almosthere_draw(struct almosthere *at) { (at->widget)() }
