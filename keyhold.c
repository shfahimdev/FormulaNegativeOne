#include "keyhold.h"
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <linux/input.h>
#include <stdio.h>

#define DEVICE "/dev/input/event6"

static volatile int holding = 0;
static volatile int current_key = -1;
static struct timeval press_time;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void *event_thread(void *arg) {
    int fd = open(DEVICE, O_RDONLY);
    if (fd < 0) { perror("open (try sudo)"); return NULL; }

    struct input_event ev;
    while (1) {
        read(fd, &ev, sizeof(ev));
        if (ev.type != EV_KEY) continue;

        pthread_mutex_lock(&lock);
        if (ev.value == 1) {
            // any new press immediately takes over
            holding = 1;
            current_key = ev.code;
            press_time = ev.time;
        } else if (ev.value == 0 && ev.code == current_key) {
            // only stop if the *current* key was released
            holding = 0;
            current_key = -1;
        }
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void keyhold_start() {
    pthread_t tid;
    pthread_create(&tid, NULL, event_thread, NULL);
    pthread_detach(tid);
}

KeyState keyhold_get() {
    KeyState state = { -1, 0.0 };

    pthread_mutex_lock(&lock);
    if (holding) {
        struct timeval now;
        gettimeofday(&now, NULL);
        long usec = (now.tv_sec - press_time.tv_sec) * 1000000L
                  + (now.tv_usec - press_time.tv_usec);
        state.key = current_key;
        state.held = usec / 1000000.0;
    }
    pthread_mutex_unlock(&lock);

    return state;
}
