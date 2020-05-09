//#include"chessglobal.h"
void copychess(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int (&sameBoard)[CHESS_HEIGHT][CHESS_LENGTH])
{
    for(int i = 0;i < CHESS_HEIGHT;i++)
    {
        for(int j = 0;j < CHESS_LENGTH;j++)
        {
            sameBoard[i][j] = board[i][j];
        }
    }
}

void revBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int (&reverseBoard)[CHESS_HEIGHT][CHESS_LENGTH])
{
    for(int i = 0;i < CHESS_HEIGHT;i++)
    {
        for(int j = 0;j < CHESS_LENGTH;j++)
        {
            if(board[i][j] == C_BLACK)
            {
                reverseBoard[i][j] = C_WHITE;
            }
            else if(board[i][j] == C_WHITE)
            {
                reverseBoard[i][j] = C_BLACK;
            }
            else
            {
                reverseBoard[i][j] = board[i][j];
            }
        }
    }
}

// boardStatus evaluateBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH])
// {
//     boardStatus evalutation;
//     int score = 0, status = 0;

//     for(int k = 0;k < 4;k++)
//     {
//         for(int i = 0;i < CHESS_HEIGHT;i++)
//         {
//             for(int j = 0;j < CHESS_LENGTH;j++)
//             {
//                 int max_x = i + dir[k][0] * 5,max_y = j + dir[k][1] * 5, pre = score;
//                 if(max_x < 0 || max_x >= CHESS_HEIGHT || max_y < 0 || max_y >= CHESS_LENGTH) continue;

//                 score += chess_6_type[board[i][j]][board[i + dir[k][0]][j + dir[k][1]]][board[i + dir[k][0] * 2][j + dir[k][1] * 2]][board[i + dir[k][0] * 3][j + dir[k][1] * 3]][board[i + dir[k][0] * 4][j + dir[k][1] * 4]][board[i + dir[k][0] * 5][j + dir[k][1] * 5]];
//                 if(score - pre == WIN)
//                 {
//                     status = 1;
//                 }
//                 else if(score - pre == LOSE)
//                 {
//                     status = 2;
//                 }
//             }
//         }
//     }
//     evalutation.score = score;
//     evalutation.status = status;
//     return evalutation;
// }


boardStatus evaluateBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH])//
{
    boardStatus evaluation;
    ll score = 0,status = 0;
    bool flag = false;

    for(int i = 1;i <= R;i++)
    {
        int x = q[i].x, y = q[i].y;
        for(int k = 0;k < 4;k++)
        {
            for(int t = 0;t <= 5;t++)
            {
                int min_x = x - dir[k][0] * t,min_y = y - dir[k][1] * t;
                int max_x = x - dir[k][0] * (t - 5), max_y = y - dir[k][1] * (t - 5);
                int pre = score;
                if((!judgePoints(min_x,min_y)) || (!judgePoints(max_x,max_y))) continue;
                score += chess_6_type[board[x - dir[k][0] * t][y - dir[k][1] * t]][board[x - dir[k][0] * (t - 1)][y - dir[k][1] * (t - 1)]][board[x - dir[k][0] * (t - 2)][y - dir[k][1] * (t - 2)]][board[x - dir[k][0] * (t - 3)][y - dir[k][1] * (t - 3)]][board[x - dir[k][0] * (t - 4)][y - dir[k][1] * (t - 4)]][board[x - dir[k][0] * (t - 5)][y - dir[k][1] * (t - 5)]];
                if(score - pre == WIN)
                {
                    status = 1;
                    flag = true;
                }
                else if(score - pre == LOSE)
                {
                    status = 2;
                    flag = true;
                }
                if(flag)
                {
                	score += (score - pre) * 5;
                    evaluation.score = score;
			 		evaluation.status = status;
					return evaluation;
				}
            }
        }
    }
    evaluation.score = score;
    evaluation.status = status;
	return evaluation;
}



bool judgePoints(int x,int y)
{
    if(x <= 0 || x >= CHESS_HEIGHT - 1 || y <= 0 || y >= CHESS_LENGTH - 1)
    {
        return false;
    }
    return true;
}


Points queue[CHESS_HEIGHT * CHESS_LENGTH];
ll value_queue[CHESS_HEIGHT * CHESS_LENGTH];
bool inque[CHESS_HEIGHT][CHESS_LENGTH];



decision findPoints(int (&board)[CHESS_HEIGHT][CHESS_LENGTH])
{
    //bool placepiece[CHESS_HEIGHT][CHESS_LENGTH];
    decision P;
    int r = 0;
//    memset(queue,0,sizeof(queue));
//    memset(value,0,sizeof(value));
//    memset(placepiece,0,sizeof(placepiece));
//    for(int i = 1;i < CHESS_HEIGHT - 1;i++)
//    {
//        for(int j = 1;j < CHESS_LENGTH - 1;j++)
//        {
//            if(board[i][j] == C_NONE || board[i][j] == C_BOUND) continue;
//            for(int k = 1;k <= STEPS;k++)
//            {
//                for(int d = 0;d < 8;d++)
//                {
//                    if(judgePoints(i + dir[d][0] * k,j + dir[d][1] * k) 
//                    && board[i + dir[d][0] * k][j + dir[d][1] * k] == 0)
//                    {
//                        Points pos;
//                        pos.x = i + dir[d][0] * k;
//                        pos.y = j + dir[d][1] * k;
//                        queue[++r] = pos;
//                    }
//                }
//            }
//        }
//    }
	for(int t = 1;t <= R;t++)
	{
		int i = q[t].x, j = q[t].y;
		for(int k = 1;k <= STEPS;k++)
            {
                for(int d = 0;d < 8;d++)
                {
                    if(judgePoints(i + dir[d][0] * k,j + dir[d][1] * k) 
                    && board[i + dir[d][0] * k][j + dir[d][1] * k] == C_NONE 
					&& (!inque[i + dir[d][0] * k][j + dir[d][1] * k]))
                    {
                        Points pos;
                        pos.x = i + dir[d][0] * k;
                        pos.y = j + dir[d][1] * k;
                        queue[++r] = pos;
                        inque[i + dir[d][0] * k][j + dir[d][1] * k] = true;
                    }
                }
            }
  }  
    
    
    //int valueBoard[CHESS_HEIGHT][CHESS_LENGTH];
//    for(int i = 1;i < CHESS_HEIGHT - 1;i++)
//    {
//        for(int j = 1;j < CHESS_LENGTH - 1;j++)
//        {
//            if(placepiece[i][j])
//            {
//                board[i][j] = C_WHITE;
//                valueBoard[i][j] = evaluateBoard(board).score;
//                board[i][j] = C_NONE;
//            }
//            else
//            {
//                valueBoard[i][j] = -INT_MAX;
//            }
//            
//        }
//    }
    
    for(int t = 1;t <= r;t++)
    {
    	int i = queue[t].x,j = queue[t].y;
    	board[i][j] = C_WHITE;
    	Points pos;
    	pos.x = i;
    	pos.y = j;
    	q[++R] = pos;
        value_queue[t] = evaluateBoard(board).score;
        board[i][j] = C_NONE;
        R--;
	}
    
//    for(int k = 0;k < MAX_CHOICE;k++)
//    {
//        int maxvalue = -INT_MAX;
//        bool flag = false;
//        for(int i = 1;i < CHESS_HEIGHT - 1;i++)
//        {
//            for(int j = 1;j < CHESS_LENGTH - 1;j++)
//            {
//                if(maxvalue < valueBoard[i][j])
//                {
//                    maxvalue = valueBoard[i][j];
//                    P.pos[k].x = i;
//                    P.pos[k].y = j;
//                    P.score[k] = maxvalue;
//                    flag = true;
//                }
//            }
//        }
//        if(flag)
//        {
//            valueBoard[P.pos[k].x][P.pos[k].y] = -INT_MAX;
//        }
//    }
    
    for(int k = 0;k < MAX_CHOICE;k++)
    {
    	ll maxvalue = -LLONG_MAX;
    	bool flag = false;
    	int pos = -1;
    	for(int t = 1;t <= r;t++)
    	{
    		int i = queue[t].x,j = queue[t].y;
    		if(maxvalue < value_queue[t])
    		{
    			maxvalue = value_queue[t];
    			P.pos[k] = queue[t];
    			P.score[k] = value_queue[t];
    			flag = true;
    			pos = t;
			}
			inque[i][j] = false;
		}
		if(flag)
		{
			value_queue[pos] = -LLONG_MAX;
		}
	}
    return P;
}


ll alphaBetaSearch(int (&board)[CHESS_HEIGHT][CHESS_LENGTH], int depth, ll alpha, ll beta)
{
    boardStatus result = evaluateBoard(board);
    if(depth == 0 || result.status != 0)
    {
        if(depth == 0)
        {
            decision P;
            P = findPoints(board);
            return P.score[0];
        }
        else 
        {
        	if(result.status == 1)
        	{
        		return LLONG_MAX;
			}
			else
			{
				return -LLONG_MAX;
			}
		}
    }
    else if(depth % 2 == 0)
    {
        int sameBoard[CHESS_HEIGHT][CHESS_LENGTH];
        copychess(board,sameBoard);
        decision P = findPoints(sameBoard);

        for(int i = 0;i < MAX_CHOICE;i++)
        {
        	if(!judgePoints(P.pos[i].x,P.pos[i].y)) continue;
            sameBoard[P.pos[i].x][P.pos[i].y] = C_WHITE;
            q[++R] = P.pos[i];
            ll score = alphaBetaSearch(sameBoard, depth - 1,alpha,beta);
            sameBoard[P.pos[i].x][P.pos[i].y] = C_NONE;
            R--;
            if(score > alpha)
            {
                alpha = score;
                if(depth == depth_MAX)
                {
                    AIStep = P.pos[i];
                }
            }
            if(alpha >= beta) break;
        }
        return alpha;
    }
    else
    {
        int reverseBoard[CHESS_HEIGHT][CHESS_LENGTH];
        revBoard(board,reverseBoard);
        decision P = findPoints(reverseBoard);

        int sameBoard[CHESS_HEIGHT][CHESS_LENGTH];
        copychess(board,sameBoard);

        for(int i = 0;i < MAX_CHOICE;i++)
        {
        	if(!judgePoints(P.pos[i].x,P.pos[i].y)) continue;
            sameBoard[P.pos[i].x][P.pos[i].y] = C_BLACK;
            q[++R] = P.pos[i];
            ll score = alphaBetaSearch(sameBoard,depth - 1,alpha,beta);
            sameBoard[P.pos[i].x][P.pos[i].y] = C_NONE;
            R--;
            if(score < beta)
            {
                beta = score;
            }
            if(alpha >= beta) break;
        }
        return beta;
    }
}

bool judgeChessBoardStatus(int (&board)[CHESS_HEIGHT][CHESS_LENGTH])
{
    boardStatus chess_Board = evaluateBoard(board);
    if(chess_Board.status == 0)
    {
        return false;
    }
    if(chess_Board.status == 1)
    {
        printf("You Lose");
        
    }
    else if(chess_Board.status == 2)
    {
        printf("You win");
    }
    system("pause");
    return true;
}
//void writeChessPiece(int x,int y,HANDLE handleOut,const char* s);///??????
void AI(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],HANDLE handleOut)
{
    alphaBetaSearch(board,depth_MAX,-INT_MAX,INT_MAX);
    writeChessPiece(AIStep.x,AIStep.y,handleOut,"��");
    board[AIStep.x][AIStep.y] = C_WHITE;
    q[++R] = AIStep;//
}
