#include <sys/mman.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include "font_define.h"

extern int mid_flag;
extern void  mice_doing(int);
extern char *pic_pool[];
extern int position_id[];
int m_x, m_y;
int whitch_pic = 0;
int *status_p = NULL;
int *mp3_num = NULL;
int *play_flag = NULL;
int slid_flag = 0;
int *song_disp_flag = NULL;
mouse_event_t mevent = {0};
fb_info fb_inf;
pthread_mutex_t mice_lock = PTHREAD_MUTEX_INITIALIZER;
//typedef int fun_t(char *, fb_info);//lingjia

void *we_slide_do(void *p)
{
    while(*status_p == 4)
    {
        display_box("jack.jpg", fb_inf, fb_inf);
        display_v_up("dong.jpg", fb_inf, fb_inf);
        display_zig("zhenshan.jpg", fb_inf, fb_inf);
    }
    return 0;
}

void * slide_do(void *p)
{
    //int pictures[12];//lingjia
    //fun_t *funs[16];//lingjia
    //int fun_num[16];
    //fun_t *fp;
    //int pic_tmp, fun_tmp;
    //bzero(fun_num, 16*sizeof(int));
    //bzero(pictures, 12*sizeof(int));//lingjia
    //srand(time(0));//lingjia

    
    //while(*status_p == 2)
    //{
        //while(1)
        //{
            //fun_tmp = rand()%16;
            //if(fun_num[fun_tmp] == 1)
            //continue;
            //else
            //{
                //fun_num[fun_tmp] = 1;
                //break;
            //}
        //}
        //while(1)
        //{
            //pic_tmp = rand()%12;
            //if(pictures[pic_tmp] == 1)
            //continue;
            //else
            //{
                //pictures[pic_tmp] = 1;
                //break;
            //}
        //}
        //fp = funs[fun_tmp];
        //fp(pic_pool[pic_tmp], fb_inf);
    //}/*
    while(*status_p == 2)
    {
        display_jpegkaiji(pic_pool[0], fb_inf);
        fb_line2(pic_pool[1], fb_inf);
        display_xie1(pic_pool[2], fb_inf);
        display_four(pic_pool[3], fb_inf);
        display_jpeg(pic_pool[4], fb_inf);
        fb_line4(pic_pool[5], fb_inf);
        display_jpeg_1(pic_pool[6],fb_inf);
        display_midtoside(pic_pool[7], fb_inf);
        display_flash1(pic_pool[8],fb_inf); 
        display_jpeg2(pic_pool[9], fb_inf);
        display_scale(pic_pool[10], fb_inf);
        display_jpeg12(pic_pool[11], fb_inf);
        display_jpeg13(pic_pool[3], fb_inf); 
        fb_line1(pic_pool[4], fb_inf);
        display_flash2(pic_pool[5],fb_inf); 
        display_baiye1(pic_pool[6], fb_inf );
    }

    return 0;
}

int store = -1 ;
void * scan_do(void *arg)
{
    store = -1 ;
    //usleep(180000);
    while(1)
    {
        if(store != whitch_pic)
        {
            disp_four_pic(whitch_pic);
            store = whitch_pic;
        }
        if(*status_p != 1)
            break;
    }

    return NULL;
}

int main(int argc, char *argv[]) 
{

    pid_t pid1 = 0, pid2 = 0, pid3 = 0;
    int song_flag1 = 0,song_flag3 = 0, song_flag4 = 0;

    if (init_fb(&fb_inf) < 0) {
        fprintf(stderr, "Error initial framebuffer\n");
        return 1;
    }
    display_jpeg111("HomePage.jpg", fb_inf);
    if (init_ft("STLITI.TTF", 30) != 0) 
    {
        fprintf(stderr, "Error initial font\n")	;
        return -1;
    }
    display_string("浏览", 82, 296, fb_inf, COLOR);

    display_string("幻灯", 235, 339, fb_inf, COLOR);

    display_string("音乐", 368, 296, fb_inf, COLOR);

    display_string("我们", 533, 295, fb_inf, COLOR);

    display_string("退出", 658, 215, fb_inf, COLOR);

    status_p = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    mp3_num = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    play_flag = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    song_disp_flag = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    *status_p = 0;
    *mp3_num = 0;
    *play_flag = 1;
    *song_disp_flag = 0;

    u8_t buf[8];
    int n, mfd;
    static int tmp;

    mouse_open(NULL, &mfd);

    m_x = fb_inf.w / 2;
    m_y = fb_inf.h / 2;

    pthread_t tid1, tid2, tid4;
    fb_drawcursor(fb_inf, m_x, m_y);

    set_dsp();
    while(1) 
    {

        pthread_mutex_lock(&mice_lock);
        n = read(mfd, buf, 8);
        pthread_mutex_unlock(&mice_lock);
        if (n != -1)
        {
            mouse_parse(buf,&mevent);

            if(*status_p != 2&&*status_p!=4)
            {
                fb_restorecursor(fb_inf, m_x, m_y);
                m_x += mevent.x;
                m_y += mevent.y;
                m_x = (m_x > 0? m_x:1);
                m_y = (m_y > 0? m_y:1);
                m_x = (m_x < fb_inf.w-11? m_x:fb_inf.w-12);
                m_y = (m_y < fb_inf.h-18? m_y:fb_inf.h-19);
                fb_drawcursor(fb_inf, m_x, m_y);
            }
            tmp = chang_color(m_x, m_y, PRE_COLOR);
            if(mevent.button == 1) 
            {
                switch(*status_p)
                {
                    case 0:
                        {
                            switch(tmp)
                            {
                                case 1: *status_p = 1;
                                        {
                                            pthread_create(&tid2, 0, scan_do, 0);
                                            mid_flag = 0;
                                            break;
                                        }

                                        break;
                                case 2:
                                        {
                                            *status_p = 2;
                                            fb_restorecursor(fb_inf, m_x, m_y);
                                            pthread_create(&tid1, 0, slide_do, 0);
                                            break;
                                        }
                                case 3:           
                                        *status_p = 3;
                                        break;
                                case 4:*status_p = 4;
                                       pthread_create(&tid4, 0, we_slide_do, 0);

                                       break;
                                case 5: goto all_exit;
                            }
                            break;
                        }
                    case 1: 
                        {
                            switch(tmp) 
                            {
                                case 1:
                                    {
                                        if(whitch_pic > 0)
                                            whitch_pic -= 4;
                                        else whitch_pic = 8;

                                        break;
                                    }
                                case 2:
                                    {
                                        if(whitch_pic < 8)
                                            whitch_pic += 4;
                                        else whitch_pic = 0;
                                        break;
                                    }
                                case 3:
                                    {
                                        pthread_cancel(tid2);
                                        *status_p = 0;
                                        pthread_join(tid2, NULL);
                                        whitch_pic = 0;
                                        break;
                                    }
                                case 40:
                                    {
                                        display_mid_jpeg(pic_pool[position_id[0]], fb_inf, 140, 68);
                                        if(m_x>140&&m_x<407+267&&m_y>68&&m_y<228+160)
                                            fb_savecursor (fb_inf,m_x,m_y);
                                        mid_flag = 1;
                                        break;
                                    }
                                case 41:
                                    {
                                        display_mid_jpeg(pic_pool[position_id[1]], fb_inf, 140, 68);
                                        if(m_x>140&&m_x<407+267&&m_y>68&&m_y<228+160)
                                            fb_savecursor (fb_inf,m_x,m_y);
                                        mid_flag = 1;
                                        break;
                                    }
                                case 42:
                                    {
                                        display_mid_jpeg(pic_pool[position_id[2]], fb_inf, 140, 68);
                                        if(m_x>140&&m_x<407+267&&m_y>68&&m_y<228+160)
                                            fb_savecursor (fb_inf,m_x,m_y);
                                        mid_flag = 1;
                                        break;
                                    }
                                case 43:
                                    {
                                        display_mid_jpeg(pic_pool[position_id[3]], fb_inf, 140, 68);
                                        if(m_x>140&&m_x<407+267&&m_y>68&&m_y<228+160)
                                            fb_savecursor (fb_inf,m_x,m_y);
                                        mid_flag = 1;
                                        break;
                                    }
                            }
                            break;
                        }
                    case 2: break;
                    case 3:
                        {
                            switch(tmp)
                            {
                                case 1:
                                    if(pid1 != 0)
                                    {
                                        kill(pid1,SIGINT);
                                        pid1 = 0;
                                    }
                                    if(pid3 != 0)
                                    {
                                        kill(pid3,SIGINT);
                                        pid3 = 0;
                                    }
                                    if(pid2 != 0)
                                    {
                                        kill(pid2,SIGINT);
                                        pid2 = 0;
                                    }
                                    pid2 = fork();
                                    if(pid2 == -1)
                                    {
                                        perror("fork pid2");
                                        exit(1);
                                    }
                                    if(pid2 == 0)
                                    {
                                        if(*mp3_num == 0)
                                            *mp3_num = 2;
                                        else
                                            *mp3_num=*mp3_num - 1;
                                        if(song_flag1 == 1) 
                                        {
                                            display_song(mp3_num);
                                        }
                                        play(mp3_num);
                                        *play_flag = 1;
                                        exit(0);
                                    }
                                    break;
                                case 2:
                                    if(pid1 != 0)
                                    {
                                        kill(pid1,SIGINT);
                                        pid1 = 0;
                                    }
                                    if(pid2 != 0)
                                    {
                                        kill(pid2,SIGINT);
                                        pid2 = 0;
                                    }
                                    if(pid3 != 0)
                                    {
                                        kill(pid3,SIGINT);
                                        pid3 = 0;
                                    }
                                    pid3 = fork();
                                    if(pid3 == -1)
                                    {
                                        perror("fork pid2");
                                        exit(1);
                                    }
                                    if(pid3 == 0)
                                    {
                                        if(*mp3_num == 2)
                                            *mp3_num = 0;
                                        else
                                            *mp3_num+=1;
                                        if(song_flag1 == 1) 
                                        {
                                            display_song(mp3_num);
                                        }
                                        play(mp3_num);
                                        *play_flag = 1;
                                    }
                                    break;
                                case 3:*status_p = 0;
                                       break;
                                case 4:
                                       if(song_flag4 == 0)
                                       {
                                           pid1 = fork();
                                           if(pid1 == -1)
                                           {
                                               perror("fork pid1");
                                               exit(1);
                                           }
                                           if(pid1 == 0)
                                           {

                                               *play_flag = 0;
                                               play(mp3_num);
                                               *play_flag = 1;
                                               exit(1);
                                           }
                                           else
                                           {
                                               song_flag3 = 1;
                                               song_flag4 = 1;
                                           }

                                       }
                                       else 
                                       {
                                           if(song_flag3 == 1)
                                           {
                                               *play_flag = 1;
                                               song_flag3 = 0;
                                           }
                                           else
                                           {
                                               *play_flag = 0;
                                               song_flag3 = 1;
                                           }
                                       }
                                       break;
                                case 5:
                                       if(song_flag1 == 0)
                                       {
                                           restoresong(fb_inf, 62, 50);
                                           display_song(mp3_num);
                                           song_flag1 = 1;
                                           *song_disp_flag = 1;
                                       }
                                       else
                                       {
                                           disappear(fb_inf, 62, 50);
                                           song_flag1 = 0;
                                           *song_disp_flag = 0;
                                       }
                                       break;
                            }
                            break;
                        }
                    case 4:
                        break;
                }
            }
            else if(mevent.button ==2)
            {
                if(*status_p == 2)
                {
                    *status_p = 0;
                    pthread_cancel(tid1);
                    pthread_join(tid1, NULL);
                }
                if(*status_p == 4)
                {
                    *status_p = 0;
                    pthread_cancel(tid4);
                    pthread_join(tid4, NULL);
                }
                if (*status_p == 1) 
                {
                    mid_flag = 0;
                    store = -1;
                }
            }
        }
    }

 all_exit:
            display_jpeg14("EndPage.jpg",fb_inf); 
         if (init_ft("STLITI.TTF", 60) != 0) 
         {
             fprintf(stderr, "Error initial font\n");
             return -1;
         }

         display_string("谢谢使用!", 50, 250, fb_inf, 0xbf3eff);
         sleep(1);
         display_jpeg_dj("EndPage.jpg", fb_inf); 
         display_string("再见!", 50, 250, fb_inf, 0xbf3eff);
         sleep(1);
         memset(fb_inf.fbmem, 0, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);
         munmap(fb_inf.fbmem, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);
         kill(pid1, SIGINT);
         kill(pid2, SIGINT);
         kill(pid3, SIGINT);

         return 0;
}


