#include"chessglobal.h"
#include"test_chess_UI.h"
#include"chessAI.h"
#include"init_chess.h"
#include<time.h>

int main()
{
    HANDLE handleIn,handleOut;
    DWORD a;
    handleIn = GetStdHandle(STD_INPUT_HANDLE);
    handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    draw_Chess_Line(handleOut, a);
    memset(board,0,sizeof(board));
    init_Chess_6_Type();
    while(1)
    {
        if(judgeChessBoardStatus(board))
        {
            break;
        }
        load_UI_Tips(handleOut,"µ¥»÷Êó±ê×ó¼üÂä×Ó",16);
        player(handleIn,handleOut,board);
        load_UI_Tips(handleOut,"                ",16);
        if(judgeChessBoardStatus(board))
        {
            break;
        }
        double a1,a2;
        a1 = clock();
        AI(board,handleOut);
        a2 = clock();
        //printf("%.2lf\n",(a2 - a1) / CLOCKS_PER_SEC);
        printf("%d %d\n",AIStep.x,AIStep.y);
    }
}
