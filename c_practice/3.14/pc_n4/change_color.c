#include "font_define.h"
#include <pthread.h>
#include "common.h"

#define song_w 313 
#define song_h 219

extern int *status_p;
extern fb_info fb_inf;
int mid_flag = 0;
extern int m_x;
extern int m_y;
extern pthread_mutex_t mice_lock;
extern int *song_disp_flag;
extern int *mp3_num;
extern int *play_flag;

char *pic_pool[12] = 
{
    "pic0.jpg", "pic1.jpg", "pic2.jpg", "pic3.jpg", "pic4.jpg","pic5.jpg",
    "pic6.jpg", "pic7.jpg", "pic8.jpg", "pic9.jpg", "pic10.jpg", "pic11.jpg"
};
int position_id[4] = {0, 1, 2, 3};
unsigned long save_song[song_w*song_h];


int chang_color(int x, int y, u32_t color)
{
    static int flag1 = 1;
    static int flag2 = 0;
    static int flag3 = 0;
    int tmp = 0;

    switch(*status_p)
    {
        case 0:
            {   
                if(flag1==0)
                {
                    display_jpeg111("HomePage.jpg", fb_inf);
                    fb_savecursor (fb_inf, m_x, m_y);
                    fb_restorecursor(fb_inf, m_x, m_y);
                    if (init_ft("STLITI.TTF", 43) != 0) 
                    {
                        fprintf(stderr, "Error initial font\n")	;
                        return -1;
                    }
                    flag1 = 1;
                    flag2 = 0;
                    flag3 = 0;
                }

                if(x>PREVIEW_X1 && y>PREVIEW_Y1 && x<PREVIEW_X2 && y<PREVIEW_Y2)
                {
                    display_string("浏览", 103, 475, fb_inf, PRE_COLOR);
                    tmp = 1;
                }
                else
                    display_string("浏览", 103, 475, fb_inf, COLOR);

                if(x>SLIDE_X1 && y>SLIDE_Y1 && x<SLIDE_X2 && y<SLIDE_Y2)
                {
                    display_string("幻灯", 296, 543, fb_inf, PRE_COLOR);
                    tmp = 2;
                }
                else
                    display_string("幻灯", 296, 543, fb_inf, COLOR);

                if((x>MUSIC_X1) && (y>MUSIC_Y1) && (x<MUSIC_X2) && (y<MUSIC_Y2))
                {
                    display_string("音乐", 470, 473, fb_inf, PRE_COLOR);
                    tmp = 3;
                }
                else
                    display_string("音乐", 470, 473, fb_inf, COLOR);

                if((x>US_X1) && (y>US_Y1) && (x<US_X2) && (y<US_Y2))
                {
                    display_string("我们", 682, 470, fb_inf, PRE_COLOR);
                    tmp = 4;
                }
                else
                    display_string("我们", 682, 470, fb_inf, COLOR);

                if((x>EXIT_X1) && (y>EXIT_Y1) && (x<EXIT_X2) && (y<EXIT_Y2))
                {  
                    display_string("退出", 843, 343, fb_inf, PRE_COLOR);
                    tmp = 5;
                }
                else
                    display_string("退出", 843, 343, fb_inf, COLOR);
            }
            return tmp;
        case 2:
            {
                flag1 = 0;
                flag2 = 0;
                flag3 = 0;
            }
            return 0;
            return 0;

        case 3:
            {
                if(flag2==0)
                {
                    //display_jpeg_dj("MusicPage.jpg", fb_inf);
                    display_jpeg111("MusicPage.jpg", fb_inf);
                    fb_savecursor (fb_inf, m_x, m_y);
                    fb_restorecursor(fb_inf, m_x, m_y);
                    if (init_ft("STLITI.TTF", 35) != 0)
                    {
                        fprintf(stderr, "Error initial font\n");
                        return -1;
                    }
                    flag2 = 1;
                    flag3 = 0;
                    flag1 = 0;
                }
                if(*song_disp_flag == 1)
                    display_song(mp3_num);
                if(*play_flag&&((x>JPG_UP_X1) && (y>JPG_UP_Y1) && (x<JPG_UP_X2) && (y<JPG_UP_Y2)))
                {
                    display_string("上一首", 183, 606, fb_inf, PRE_COLOR);
                    return 1;
                }
                else
                    display_string("上一首", 183, 606, fb_inf, COLOR);

                if(*play_flag&&((x>JPG_DOWN_X1) && (y>JPG_DOWN_Y1) && (x<JPG_DOWN_X2) && (y<JPG_DOWN_Y2)))
                {
                    display_string("下一首", 363, 616, fb_inf, PRE_COLOR);
                    return 2;
                }
                else
                    display_string("下一首", 363, 616, fb_inf, COLOR);

                if((x>PREVIEWEXIT_X1) && (y>PREVIEWEXIT_Y1) && (x<PREVIEWEXIT_X2) && (y<PREVIEWEXIT_Y2))
                {
                    display_string("返回", 885, 695, fb_inf, PRE_COLOR);
                    return 3;
                }
                else
                    display_string("返回", 885, 695, fb_inf, COLOR);

                if((x>PREVIEWPLAY_X1) && (y>PREVIEWPLAY_Y1) && (x<PREVIEWPLAY_X2) && (y<PREVIEWPLAY_Y2))
                {   display_string("播放", 228, 707, fb_inf, PRE_COLOR);
                    return 4;
                }
                if(*play_flag == 0) 
                    display_string("播放", 228, 707, fb_inf, PRE_COLOR);
                else
                    display_string("播放", 228, 707, fb_inf, COLOR);

                if((x>PREVIEWTAB_X1) && (y>PREVIEWTAB_Y1) && (x<PREVIEWTAB_X2) && (y<PREVIEWTAB_Y2))
                {
                    display_string("列表", 355, 530, fb_inf, PRE_COLOR);
                    return 5;
                }
                else
                    display_string("列表", 355, 530, fb_inf, COLOR);
            }
            return 0;
        case 1:
            {   
                if(flag3==0)
                {
                    display_jpeg_dj("ScanPage.jpg", fb_inf);
                    fb_savecursor (fb_inf, m_x, m_y);
                    fb_restorecursor(fb_inf, m_x, m_y);
                    //fb_drawcursor(fb_inf, m_x, m_y);
                    if (init_ft("STLITI.TTF", 33) != 0)
                    {
                        fprintf(stderr, "Error initial font\n")	;
                        return -1;
                    }
                    flag3 = 1;
                    flag2 = 0;
                    flag1 = 0;
                }
                if(mid_flag == 0)
                {

                    if(x>AREA_ONE_X1 && y>AREA_ONE_Y1 && x<AREA_ONE_X2 && y<AREA_ONE_Y2)
                    {
                        return 40;
                    }
                    if(x>AREA_TOW_X1 && y>AREA_TOW_Y1 && x<AREA_TOW_X2 && y<AREA_TOW_Y2)
                    {
                        return 41;
                    }
                    if(x>AREA_THREE_X1 && y>AREA_THREE_Y1 && x<AREA_THREE_X2 && y<AREA_THREE_Y2-17)
                    {
                        return 42;
                    }
                    if(x>AREA_FOUR_X1 && y>AREA_FOUR_Y1 && x<AREA_FOUR_X2 && y<AREA_FOUR_Y2-17)
                    {
                        return 43;
                    }

                    if(x>SCAN_UP_X1 && y>SCAN_UP_Y1 && x<SCAN_UP_X2 && y<SCAN_UP_Y2)
                    {
                        display_string("上一页", 300, 719, fb_inf, PRE_COLOR);
                        return 1;
                    }
                    else
                        display_string("上一页", 300, 719, fb_inf, COLOR);

                    if(x>SCAN_DOWN_X1 && y>SCAN_DOWN_Y1 && x<SCAN_DOWN_X2 && y<SCAN_DOWN_Y2)
                    {
                        display_string("下一页", 735, 718, fb_inf, PRE_COLOR);
                        return 2;
                    }
                    else
                        display_string("下一页", 735, 718, fb_inf, COLOR);

                }
                if((x>SCAN_EXIT_X1) && (y>SCAN_EXIT_Y1) && (x<SCAN_EXIT_X2) && (y<SCAN_EXIT_Y2))
                {
                    display_string("返回", 905, 73, fb_inf, PRE_COLOR);
                    return 3;
                }
                else
                    display_string("返回", 905, 73, fb_inf, COLOR);
            }

    }
    return 0;
}

int display_song(int *p)
{
    int num, i;

    num = *p;
    for(i=0; i<3; i++)
    {
        if(i == num)
        {
            display_string(mp3_name[num], 156+fb_inf.w*i, 125+i*37, fb_inf, PRE_COLOR);
        }
        else
            display_string(mp3_name[i], 156+fb_inf.w*i, 125+i*37, fb_inf, COLOR);
    }

    return 0;
}

int disappear(fb_info fb_inf, int x, int y)
{
    int i, j;
    u32_t color;
    for (j = 0;j<song_h;j++)
    {
        for (i = 0;i<song_w;i++)
        {
            color = save_song[i + j * song_w];
            fb_pixel(fb_inf,x+i,y+j,color);
        }
    }

    return 0;
}

int restoresong(fb_info fb_inf,int x,int y)
{
    int i,j;
    u32_t color;

    for (j=0; j<song_h;j++)
    {
        for (i=0; i<song_w;i++)
        {
            color = *(u32_t*)(fb_inf.fbmem + ((y + j) * fb_inf.w + x + i) * fb_inf.bpp/8);
            save_song[i + j * song_w] = color;
        }
    }

    return 0;
}
