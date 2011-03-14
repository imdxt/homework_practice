#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"
#include "font_define.h"
extern int *status_p;
extern fb_info fb_inf;
extern int *status_p;

int change_color_preview(mouse_event_t mevent, int x, int y, unsigned int color)
{
    if(x>PREVIEW_X1 && y>PREVIEW_Y1 && x<PREVIEW_X2 && y<PREVIEW_Y2)
        display_string("浏览", 103, 475, fb_inf, PRE_COLOR);
    else
        display_string("浏览", 103, 475, fb_inf, COLOR);

    return 0;
}

int change_color_slide(mouse_event_t mevent, int x, int y, unsigned int color)
{
    if(x>SLIDE_X1 && y>SLIDE_Y1 && x<SLIDE_X2 && y<SLIDE_Y2)
        display_string("幻灯", 296, 543, fb_inf, PRE_COLOR);
    else
        display_string("幻灯", 296, 543, fb_inf, COLOR);
    return 0;
}

int change_color_music(mouse_event_t mevent, int x, int y, unsigned int color)
{
    if((x>MUSIC_X1) && (y>MUSIC_Y1) && (x<MUSIC_X2) && (y<MUSIC_Y2))
        display_string("音乐", 470, 473, fb_inf, PRE_COLOR);
    else
        display_string("音乐", 470, 473, fb_inf, COLOR);

    return 0;
}

int change_color_us(mouse_event_t mevent, int x, int y, unsigned int color)
{
    if((x>US_X1) && (y>US_Y1) && (x<US_X2) && (y<US_Y2))
        display_string("我们", 682, 470, fb_inf, PRE_COLOR);
    else
        display_string("我们", 682, 470, fb_inf, COLOR);
    return 0;
}
int change_color_exit(mouse_event_t mevent, int x, int y, unsigned int color)
{
    if((x>EXIT_X1) && (y>EXIT_Y1) && (x<EXIT_X2) && (y<EXIT_Y2))
        display_string("退出", 843, 343, fb_inf, PRE_COLOR);
    else
        display_string("退出", 843, 343, fb_inf, COLOR);


    return 0;
}

int change_color_up(mouse_event_t mevent, int x, int y, unsigned int color)
{
    if((x>JPG_UP_X1) && (y>JPG_UP_Y1) && (x<JPG_UP_X2) && (y<JPG_UP_Y2))
        display_string("上一首", 183, 606, fb_inf, PRE_COLOR);
    else
        display_string("上一首", 183, 606, fb_inf, COLOR);

    return 0;
}
int change_color_down(mouse_event_t mevent, int x, int y, unsigned int color)
{
    if((x>JPG_DOWN_X1) && (y>JPG_DOWN_Y1) && (x<JPG_DOWN_X2) && (y<JPG_DOWN_Y2))
        display_string("下一首", 363, 616, fb_inf, PRE_COLOR);
    else
        display_string("下一首", 363, 616, fb_inf, COLOR);

    return 0;
}

int change_color_return(mouse_event_t mevent, int x, int y, unsigned int color)
{
    if((x>PREVIEWEXIT_X1) && (y>PREVIEWEXIT_Y1) && (x<PREVIEWEXIT_X2) && (y<PREVIEWEXIT_Y2))
        display_string("返回", 885, 695, fb_inf, PRE_COLOR);
    else
        display_string("返回", 885, 695, fb_inf, COLOR);

    return 0;
}
int change_color_play(mouse_event_t mevent, int x, int y, unsigned int color)
{
    if((x>PREVIEWPLAY_X1) && (y>PREVIEWPLAY_Y1) && (x<PREVIEWPLAY_X2) && (y<PREVIEWPLAY_Y2))
        display_string("播放", 228, 707, fb_inf, PRE_COLOR);
    else
        display_string("播放", 228, 707, fb_inf, COLOR);

    return 0;
}
int change_color_tab(mouse_event_t mevent, int x, int y, unsigned int color)
{
    if((x>PREVIEWTAB_X1) && (y>PREVIEWTAB_Y1) && (x<PREVIEWTAB_X2) && (y<PREVIEWTAB_Y2))
        display_string("列表", 355, 530, fb_inf, PRE_COLOR);
    else
        display_string("列表", 355, 530, fb_inf, COLOR);

    return 0;
}
