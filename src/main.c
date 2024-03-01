#include <curses.h>
#include <libssh/libssh.h>
#include "arc/ssh/ssh.h"
#include "arc/ncurses/ncurses.h"

// static ARC_Ssh *ssh;

// ARC_Ssh_ExecStrInNewSession(ssh, "export DISPLAY=:0 ; volume --inc");
// ARC_Ssh_ExecStrInNewSession(ssh, "export DISPLAY=:0 ; volume --dec");
// ARC_Ssh_ExecStrInNewSession(ssh, "sudo ydotool key 105:1 105:0");
// ARC_Ssh_ExecStrInNewSession(ssh, "sudo ydotool key 106:1 106:0");
// ARC_Ssh_ExecStrInNewSession(ssh, "sudo ydotool key 57:1 57:0");

/*
alias pspace='ydotool key 57:1 57:0'
alias pright='ydotool key 106:1 106:0'
alias pleft='ydotool key 105:1 105:0'
alias pdesktop1='ydotool key 125:1 2:1 2:0 125:0'
alias pdesktop2='ydotool key 125:1 3:1 3:0 125:0'
alias pdesktop3='ydotool key 125:1 4:1 4:0 125:0'
alias pdesktop4='ydotool key 125:1 5:1 5:0 125:0'
alias pclose='ydotool key 125:1 46:1 46:0 125:0'
*/
#include <ncurses.h>

typedef struct _win_border_struct {
    chtype ls, rs, ts, bs, tl, tr, bl, br;
} WIN_BORDER;

typedef struct _WIN_struct {
    int startx, starty;
    int height, width;
    WIN_BORDER border;
} WIN;

void init_win_params(WIN *p_win);
void print_win_params(WIN *p_win);
void create_box(WIN *win, bool flag);

int main(int argc, char *argv[]){
    // ARC_Ssh_Create(&ssh);
    ARC_NCurses *mainNCurses;
    ARC_NCurses_Create(&mainNCurses, NULL);
    ARC_NCurses_SetBorder(mainNCurses, ARC_NCURSES_BORDER_DEFAULT);

    getch();

    ARC_NCurses_Destroy(mainNCurses);

//    WIN win;
//    int ch;
//
//    noecho();
//    init_pair(1, COLOR_CYAN, COLOR_BLACK);
//
//    /* Initialize the window parameters */
//    init_win_params(&win);
//    print_win_params(&win);
//
//    attron(COLOR_PAIR(1));
//    printw("Press F1 to exit");
//    refresh();
//    attroff(COLOR_PAIR(1));
//
//    create_box(&win, TRUE);
//    while((ch = getch()) != KEY_F(1)){
//        switch(ch){
//            case KEY_LEFT:
//                create_box(&win, FALSE);
//                --win.startx;
//                create_box(&win, TRUE);
//                break;
//            case KEY_RIGHT:
//                create_box(&win, FALSE);
//                ++win.startx;
//                create_box(&win, TRUE);
//                break;
//            case KEY_UP:
//                create_box(&win, FALSE);
//                --win.starty;
//                create_box(&win, TRUE);
//                break;
//            case KEY_DOWN:
//                create_box(&win, FALSE);
//                ++win.starty;
//                create_box(&win, TRUE);
//                break;
//        }
//    }
//    endwin();           /* End curses mode      */

    // ARC_Ssh_Destroy(ssh);
    return 0;
}

void init_win_params(WIN *p_win){
    p_win->height = 3;
    p_win->width = 10;
    p_win->starty = (LINES - p_win->height)/2;	
    p_win->startx = (COLS - p_win->width)/2;

    p_win->border.ls = '|';
    p_win->border.rs = '|';
    p_win->border.ts = '-';
    p_win->border.bs = '-';
    p_win->border.tl = '+';
    p_win->border.tr = '+';
    p_win->border.bl = '+';
    p_win->border.br = '+';
}

void print_win_params(WIN *p_win){
#ifdef _DEBUG
    mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty, p_win->width, p_win->height);
    refresh();
#endif
}

void create_box(WIN *p_win, bool flag){
    int i, j;
    int x, y, w, h;

    x = p_win->startx;
    y = p_win->starty;
    w = p_win->width;
    h = p_win->height;

    if(flag == TRUE){
        mvaddch(y, x, p_win->border.tl);
        mvaddch(y, x + w, p_win->border.tr);
        mvaddch(y + h, x, p_win->border.bl);
        mvaddch(y + h, x + w, p_win->border.br);
        mvhline(y, x + 1, p_win->border.ts, w - 1);
        mvhline(y + h, x + 1, p_win->border.bs, w - 1);
        mvvline(y + 1, x, p_win->border.ls, h - 1);
        mvvline(y + 1, x + w, p_win->border.rs, h - 1);
        refresh();
        return;
    }

    for(j = y; j <= y + h; ++j){
        for(i = x; i <= x + w; ++i){
                mvaddch(j, i, ' ');
        }
    }
}
