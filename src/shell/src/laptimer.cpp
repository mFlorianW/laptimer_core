#include <SDL2/SDL.h>
#include <lvgl.h>
#include <monitor.h>
#include <mouse.h>
#include <unistd.h>

[[noreturn]] static int tick_thread(void *data)
{
    (void)data;

    while (true)
    {
        SDL_Delay(5); /*Sleep for 5 millisecond*/
        lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
    }
}

static void memory_monitor(lv_task_t *param)
{
    (void)param; /*Unused*/
    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
}

static void hal_init()
{
    /* Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
    monitor_init();

    /*Create a display buffer*/
    static lv_disp_buf_t disp_buf1;
    static lv_color_t buf1_1[LV_HOR_RES_MAX * 120];
    lv_disp_buf_init(&disp_buf1, buf1_1, nullptr, LV_HOR_RES_MAX * 120);

    /*Create a display*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/
    disp_drv.buffer = &disp_buf1;
    disp_drv.flush_cb = monitor_flush;
    lv_disp_drv_register(&disp_drv);

    /* Add the mouse as input device
     * Use the 'mouse' driver which reads the PC's mouse*/
    mouse_init();
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;

    /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev_drv.read_cb = mouse_read;
    lv_indev_drv_register(&indev_drv);

    /* Tick init.
     * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL about
     * how much time were elapsed Create an SDL thread to do this*/
    SDL_CreateThread(tick_thread, "tick", nullptr);

    /* Optional:
     * Create a memory monitor task which prints the memory usage in
     * periodically.*/
    lv_task_create(memory_monitor, 5000, LV_TASK_PRIO_MID, nullptr);
}

int main(int argc, char *argv[])
{
    (void)argc; /*Unused*/
    (void)argv; /*Unused*/

    /*Initialize LVGL*/
    lv_init();

    /*Initialize the HAL (display, input devices, tick) for LVGL*/
    hal_init();

    // lv_demo_widgets();
    // lv_demo_printer();

    while (true)
    {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(5 * 1000);
    }
}
