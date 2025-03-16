#include <iostream>
#include <string>
#include <cctype>
#include <random>
#include <cstdlib>

const int gridwidth = 10, gridheight = 10;
const char characters[gridwidth] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

bool enemyused = 0, ship3done = 0;
int gamestate = 0, usergrid[gridheight][gridwidth], enemygrid[gridheight][gridwidth], usercursor[2] = {1, 1}, userdirection = 2,  usership = 5, enemycursor[2], enemydirection, enemysizes[5] = {5, 4, 3, 3, 2};
/* 
GRID VALUES:
0 - EMPTY;
1 - SHIP;
2 - HIT;
3 - MISS;
4 - PLACING;

USER CURSOR DIRECTIONS:
0 - W;
1 - A;
2 - S;
3 - D;
*/

void n()
{
    std::cout << '\n';
}

void nullifygrids() {
    for (int i = 0; i < gridheight; i++)
    {
        for (int j = 0; j < gridwidth; j++)
        {
            usergrid[i][j] = 0;
            enemygrid[i][j] = 0;
        }
    }
    usergrid[0][0] = 4;
    usergrid[1][0] = 4;
    usergrid[2][0] = 4;
    usergrid[3][0] = 4;
    usergrid[4][0] = 4;
}

void buildheaders()
{
    std::cout << "                             YOU                                                   ENEMY                     " << '\n';
}

void buildcolumns()
{
    std::cout << "     ";
    for (char character : characters)
    {
        std::cout << "   " << character << " ";
    }
}

void buildwall()
{
    std::cout << "     ";
    for (int i = 1; i <= gridwidth; i++)
    {
        std::cout << "_____";
    }
    std::cout << "_";
}

void builduser(int rownum)
{
    if (rownum >= 10) 
    {
        std::cout << "  ";
    } 
    else 
    {
        std::cout << "   ";
    }
    std::cout << rownum << ' ';
    for (int colnum = 1; colnum <= gridwidth; colnum++)
    {
        int cell = usergrid[rownum - 1][colnum - 1];
        switch (cell)
        {
        case 0:
            std::cout << "|    ";
            break;
        
        case 1:
            std::cout << "|  # ";
            break;
        
        case 2:
            std::cout << "|  X ";
            break;

        case 3:
            std::cout << "|  O ";
            break;

        case 4:
            std::cout << "|  * ";
            break;
        
        default:
            break;
        }
    }
    std::cout << '|';
}
void buildenemy(int rownum)
{
    if (rownum >= 10) 
    {
        std::cout << "  ";
    } 
    else 
    {
        std::cout << "   ";
    }
    std::cout << rownum << ' ';
    for (int colnum = 1; colnum <= gridwidth; colnum++)
    {
        int cell = enemygrid[rownum - 1][colnum - 1];
        switch (cell)
        {
        case 0:
            std::cout << "|    ";
            break;
        
        case 1:
            std::cout << "|  # ";
            break;
        
        case 2:
            std::cout << "|  X ";
            break;

        case 3:
            std::cout << "|  O ";
            break;

        case 4:
            std::cout << "|  * ";
            break;
        
        default:
            break;
        }
    }
    std::cout << '|';
}

void render()
{
    buildheaders();
    n();
    buildcolumns();
    buildcolumns();
    n();
    buildwall();
    buildwall();
    n();
    for (int i = 1; i <= gridheight; i++)
    {
        builduser(i);
        buildenemy(i);
        n();
        buildwall();
        buildwall();
        n();
    }
}

void handleinput0()
{
    char input = getchar();
    input = tolower(input);
    int usercursor1[2] = {usercursor[0], usercursor[1]};
    int userdirection1 = userdirection;

    switch (input)
    {
    case 'q':
        if (userdirection != 3) {
            userdirection++;
        }
        else if (userdirection == 3)
        {
            userdirection = 0;
        }
        break;
    
    case 'e':
        if (userdirection != 0) {
            userdirection--;
        }
        else if (userdirection == 0)
        {
            userdirection = 3;
        }
        break;

    case 'w':
        usercursor[1]--;
        break;

    case 'a':
        usercursor[0]--;
        break;

    case 's':
        usercursor[1]++;
        break;

    case 'd':
        usercursor[0]++;
        break;
    
    case 'f':
        for (int i = 0; i < gridheight; i++)
        {
            for (int j = 0; j < gridwidth; j++)
            {
                if (usergrid[i][j] == 4) {
                    usergrid[i][j] = 1;
                }
            }
        }
        switch (usership)
        {
        case 5:
            usership = 4;
            break;

        case 4:
            usership = 3;
            break;

        case 3:
            if (ship3done) {
                usership = 2;
            }
            else
            {
                ship3done = 1;
            }
            break;

        case 2:
            gamestate = 1;
            break;
        
        default:
            break;
        }
        break;
        
    default:
        break;
    }

    for (int i = 0; i < usership; i++) {
        switch (userdirection)
        {
        case 0:
            if (usergrid[usercursor[1] - i - 1][usercursor[0] - 1] == 1) {
                usercursor[0] = usercursor1[0];
                usercursor[1] = usercursor1[1];
                userdirection = userdirection1;
            }
            break;
        case 1:
            if (usergrid[usercursor[1] - 1][usercursor[0] - i - 1] == 1) {
                usercursor[0] = usercursor1[0];
                usercursor[1] = usercursor1[1];
                userdirection = userdirection1;
            }
            break;
        case 2:
            if (usergrid[usercursor[1] + i - 1][usercursor[0] - 1] == 1) {
                usercursor[0] = usercursor1[0];
                usercursor[1] = usercursor1[1];
                userdirection = userdirection1;
            }
            break;
        case 3:
            if (usergrid[usercursor[1] - 1][usercursor[0] + i - 1] == 1) {
                usercursor[0] = usercursor1[0];
                usercursor[1] = usercursor1[1];
                userdirection = userdirection1;
            }
            break;
        default:
            break;
        }
    }

    switch (userdirection)
    {
    case 0:
        if ((usercursor[1] < usership)) {
            usercursor[0] = usercursor1[0];
            usercursor[1] = usercursor1[1];
            userdirection = userdirection1;
        }  else if ((usercursor[0] == 0) || (usercursor[1] == 0) || (usercursor[0] == 11) || (usercursor[1] == 11)) {
            usercursor[0] = usercursor1[0];
            usercursor[1] = usercursor1[1];
            userdirection = userdirection1;
        }
        break;

    case 1:
        if ((usercursor[0] < usership)) {
            usercursor[0] = usercursor1[0];
            usercursor[1] = usercursor1[1];
            userdirection = userdirection1;
        }  else if ((usercursor[0] == 0) || (usercursor[1] == 0) || (usercursor[0] == 11) || (usercursor[1] == 11)) {
            usercursor[0] = usercursor1[0];
            usercursor[1] = usercursor1[1];
            userdirection = userdirection1;
        }
        break;

    case 2:
        if ((usercursor[1] + usership > gridheight + 1)) {
            usercursor[0] = usercursor1[0];
            usercursor[1] = usercursor1[1];
            userdirection = userdirection1;
        } else if ((usercursor[0] == 0) || (usercursor[1] == 0) || (usercursor[0] == 11) || (usercursor[1] == 11)) {
            usercursor[0] = usercursor1[0];
            usercursor[1] = usercursor1[1];
            userdirection = userdirection1;
        }
        break;

    case 3:
        if ((usercursor[0] + usership > gridwidth + 1)) {
            usercursor[0] = usercursor1[0];
            usercursor[1] = usercursor1[1];
            userdirection = userdirection1;
        } else if ((usercursor[0] == 0) || (usercursor[1] == 0) || (usercursor[0] == 11) || (usercursor[1] == 11)) {
            usercursor[0] = usercursor1[0];
            usercursor[1] = usercursor1[1];
            userdirection = userdirection1;
        }
        break;
    
    default:
        break;
    }
}

void applyinput0()
{
    bool is4 = 1;
    for (int i = 0; i < gridheight; i++)
    {
        for (int j = 0; j < gridwidth; j++)
        {
            if (usergrid[i][j] == 4) {
                is4 = 0;
            }
        }
    }
    if (!is4) {
    for (int i = 0; i < gridheight; i++)
    {
        for (int j = 0; j < gridwidth; j++)
        {
            if (usergrid[i][j] == 4) {
                usergrid[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < usership; i++) {
        switch (userdirection)
        {
        case 0:
            usergrid[usercursor[1] - i - 1][usercursor[0] - 1] = 4;
            break;
        case 1:
            usergrid[usercursor[1] - 1][usercursor[0] - i - 1] = 4;
            break;
        case 2:
            usergrid[usercursor[1] + i - 1][usercursor[0] - 1] = 4;
            break;
        case 3:
            usergrid[usercursor[1] - 1][usercursor[0] + i - 1] = 4;
            break;
        default:
            break;
        }
    }
    } else {
    for (int j = 0; j < gridwidth; j++)
    {
        for (int i = 0; i < gridheight; i++)
        {
            if (!((usergrid[i][j] == 1) && (usergrid[i + 1][j] == 1) && (usergrid[i + 2][j] == 1) && (usergrid[i + 3][j] == 1))) {
                    usergrid[i][j] = 4;
                    usergrid[i + 1][j] = 4;
                    usergrid[i + 2][j] = 4;
                    usergrid[i + 3][j] = 4;
                    usercursor[0] = j + 1;
                    usercursor[1] = i + 1;
                    userdirection = 2;
                    j = gridwidth;
                    i = gridheight;
            }
        }
    }
    }
}

void randomenemy() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distxy(1, 10);
    std::uniform_int_distribution<std::mt19937::result_type> distrot(0, 4);

    for (int enemyship : enemysizes) {

    redo:
	
    enemycursor[0] = distxy(rng);
    enemycursor[1] = distxy(rng);
    enemydirection = distrot(rng);

    for (int i = 0; i < enemyship; i++) {
        switch (enemydirection)
        {
        case 0:
            if (enemygrid[enemycursor[1] - i - 1][enemycursor[0] - 1] == 1) {
                goto redo;
            }
            break;
        case 1:
            if (enemygrid[enemycursor[1] - 1][enemycursor[0] - i - 1] == 1) {
                goto redo;
            }
            break;
        case 2:
            if (enemygrid[enemycursor[1] + i - 1][enemycursor[0] - 1] == 1) {
                goto redo;
            }
            break;
        case 3:
            if (enemygrid[enemycursor[1] - 1][enemycursor[0] + i - 1] == 1) {
                goto redo;
            }
            break;
        default:
	    goto redo;
            break;
        }
    }

    switch (enemydirection)
    {
    case 0:
        if ((enemycursor[1] < enemyship)) {
            goto redo;
        }  else if ((enemycursor[0] == 0) || (enemycursor[1] == 0) || (enemycursor[0] == 11) || (enemycursor[1] == 11)) {
            goto redo;
        }
        break;

    case 1:
        if ((enemycursor[0] < enemyship)) {
            goto redo;
        }  else if ((enemycursor[0] == 0) || (enemycursor[1] == 0) || (enemycursor[0] == 11) || (enemycursor[1] == 11)) {
            goto redo;
        }
        break;

    case 2:
        if ((enemycursor[1] + enemyship > gridheight + 1)) {
            goto redo;
        }
        break;

    case 3:
        if ((enemycursor[0] + enemyship > gridwidth + 1)) {
            goto redo;
        } else if ((enemycursor[0] == 0) || (enemycursor[1] == 0) || (enemycursor[0] == 11) || (enemycursor[1] == 11)) {
            goto redo;
        }
        break;
    
    default:
	goto redo;
        break;
    }

    for (int i = 0; i < enemyship; i++) {
        switch (enemydirection)
        {
        case 0:
            enemygrid[enemycursor[1] - i - 1][enemycursor[0] - 1] = 1;
            break;
        case 1:
            enemygrid[enemycursor[1] - 1][enemycursor[0] - i - 1] = 1;
            break;
        case 2:
            enemygrid[enemycursor[1] + i - 1][enemycursor[0] - 1] = 1;
            break;
        case 3:
            enemygrid[enemycursor[1] - 1][enemycursor[0] + i - 1] = 1;
            break;
        default:
	    goto redo;
            break;
        }
    }
    }
    gamestate = 2;
}

int main()
{
    nullifygrids();
    while (true)
    {
        if (gamestate == 0)
        {
            render();
            handleinput0();
            if (gamestate == 1) {
                goto state1;
            }
            applyinput0();
	    }
        else if (gamestate == 1)
        {
            state1:
            render();
            randomenemy();
        }
        else
        {
            render();
            getchar();
        }
    }
}
