#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int wickets, overs, currover = 0, total_balls = 0;
int target;

struct player
{
    int playerno, ind_runs, ind_wickets;
    float average, economy, strike_rate;
    char player_type[15], player_name[20];
};
typedef struct player player;

struct score
{
    int team_score;
    int total_overs;
    int total_wickets;
} team, comp;
typedef struct score score; //Both team and score are the instances of the structure score

player *createPlayer()
{
    player *p = (player *)malloc(sizeof(struct player));
    p->ind_runs = p->ind_wickets = 0;
    return p;
}

struct node
{
    player *data;      //data part
    struct node *next; //Pointer to the next node
};

struct queue
{
    struct node *front;
    struct node *rear;
};

typedef struct node node;
typedef struct queue queue;
queue *batting_order;

node *createNode(player *p)
{
    node *newNode = (node *)malloc(sizeof(struct node));
    newNode->data = p;
    newNode->next = NULL;
    return newNode;
}

void createQueue()
{
    batting_order = (queue *)malloc(sizeof(struct queue));
    batting_order->rear = NULL;
    batting_order->front = NULL;
}

void lets_start();
void lets_start2();
void compbatting();
void userbattingChase();

int allOut() //isEmpty() func
{
    return batting_order->front == NULL;
}

void enqueueBatsman(player *p)
{
    node *newNode = createNode(p);
    if (allOut())
        batting_order->front = batting_order->rear = newNode;
    else
    {
        batting_order->rear->next = newNode;
        batting_order->rear = newNode;
    }
}

void dequeueBatsman(int total_balls)
{
    node *temp = batting_order->front;
    batting_order->front = batting_order->front->next;
    free(temp);
}

void makeEmpty()
{
    while (!allOut())
        dequeueBatsman(total_balls);
    target = team.team_score + 1;
    team.team_score = 0;
    comp.team_score = 0;
    comp.total_overs = 0;
    team.total_overs = 0;
    comp.total_wickets = 0;
    team.total_wickets = 0;
    currover = 0;
    total_balls = 0;
    batting_order->rear = NULL;
    batting_order->front = NULL;
}

void makeEmpty_2()
{
    while (!allOut())
        dequeueBatsman(total_balls);
    target = comp.team_score + 1;
    team.team_score = 0;
    comp.team_score = 0;
    comp.total_overs = 0;
    team.total_overs = 0;
    comp.total_wickets = 0;
    team.total_wickets = 0;
    currover = 0;
    total_balls = 0;
    batting_order->rear = NULL;
    batting_order->front = NULL;
}

void currentBatsman() //peek() func
{
    printf("\033[1;32m");
    printf("\nThe batsman on strike : %s\n\n", batting_order->front->data->player_name);
    printf("\033[0m");
}

void battingLineUp() //display() func of queue
{
    printf("\033[1;36m");
    if (allOut())
    {
        printf("\nALL OUT !!\n");
        return;
    }
    node *curr = batting_order->front;
    printf("\nNext to bat :\n");
    printf("----------------------------\n");
    printf("PLAYER ID\tBATSMAN NAME\n");
    printf("----------------------------\n");
    while (curr != batting_order->rear)
    {
        printf("%d\t\t%s\t\n", curr->data->playerno, curr->data->player_name);
        curr = curr->next;
    }
    printf("%d\t\t%s\t\n", curr->data->playerno, curr->data->player_name);
    printf("----------------------------\n");
    printf("\033[0m");
}

void acceptPlayerDetails(player *p, int num)
{
    printf("\033[1;34m");
    printf("\nEnter the details of PLAYER %d\n", num);
    printf("----------------------------------\n");
    printf("\033[1;32m");
    printf("Enter the player's name : ");
    scanf("%s",p->player_name);
    printf("Enter the player's role (batsman/bowler/all-rounder) : ");
    scanf("%s",p->player_type);
    p->playerno = num;
    printf("\n");
    printf("\033[0m");
}

void computerPlayerDetails(player *p, int num)
{
    char s1[8] = "Player";
    char c = 48 + num;
    strncat(s1, &c, 1);
    strcpy(p->player_name, s1);
    p->playerno = num;
}

int print_rules()
{
    printf("\033[1;32m");
    printf("\n--------------------------------------------------------------Rules Of The Game-------------------------------------------------------------");
    printf("\033[1;31m");
    printf("\n\n\n1.The User has to spin a coin during the toss,based on the outcome of the toss, the user will bat or field first!");
    printf("\n\n3.The User can choose the total number of overs and wickets for the respective match after the toss.");
    printf("\n\n4.The User can enter scores only between 0 to 6.");
    printf("\n\n5.If the User and computer land up on the same number while batting, the batsman is declared out.");
    printf("\n\n6.The team is considered ALL OUT after losing all the wickets during batting.");
    printf("\n\n7.If the batsman inputs a 0 and the computer generates any number other than 0,those runs will be added to the batsman's score.");
    printf("\n\n8.In case of a 0 by both the batsman and the computer, then the batsman is declared out.");
    printf("\n\n9.A batsman is considered to be out when he inputs the same number as that of the number generated by the opponent.");
    printf("\033[1;32m");
    printf("\n\n\n--------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\033[0;m");
    printf("\n\n");
}

void start()
{
    printf("\033[1;33m");
    printf("\nEnter the No of wickets(1-5) : ");
    scanf("%d", &wickets);
    while (wickets > 5 || wickets <= 0)
    {
        printf("\033[1;31m");
        printf("Please enter the No of wickets in the given range (1-5) : ");
        scanf("%d", &wickets);
        printf("\033[0m");
    }
    printf("\033[1;33m");
    printf("Enter the No of Overs(1-6) : ");
    scanf("%d", &overs);
    while (overs > 6 || overs <= 0)
    {
        printf("\033[1;31m");
        printf("Please enter the No of overs in the given range (1-6) : ");
        scanf("%d", &overs);
        printf("\033[0m");
    }
    printf("\033[0m");
}

int printRandoms(int lower, int upper)
{
    srand(time(0));
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

int choose()
{
    int a;
    printf("\033[1;32m");
    printf("Enter 0 to bat and 1 to bowl: ");
    scanf("%d", &a);
    if (a == 0)
    {
        printf("\nYou have decided to bat first\n");
        return 1;
    }
    else
    {
        printf("\nYou have decided to bowl first\n");
        return 0;
    }
    printf("\033[0m");
}

int syschoose()
{
    printf("\033[1;31m");
    int toss = 0;
    toss = rand() % 2;
    if (toss == 0)
    {
        printf("\nSystem has decided to bat first\n");
        return 1;
    }
    else
    {
        printf("\nSystem has decided to bowl first\n");
        return 0;
    }
    printf("\033[0m");
}

void toss()
{
    printf("\033[1;32m");
    int toss = 0, dec, s = 0, x, y;
    int call = 0;
    srand(time(NULL));
    toss = (rand() % (7));
    printf("\nToss Time!!!\n");
    printf("\nEnter 0 for even and 1 for odd: ");
    scanf("%d", &dec);
    while (dec > 1 || dec < 0)
    {
        printf("\033[1;31m");
        printf("Please enter either 0 for even or 1 for odd: ");
        scanf("%d", &dec);
        printf("\033[0m");
    }
    if (dec == 0 || dec == 1)
    {
        printf("Enter a number within 0 and 6: ");
        scanf("%d", &call);
        while (call < 0 || call > 6)
        {
            printf("\033[1;31m");
            printf("Please enter a number within 0 and 6: ");
            scanf("%d", &call);
            printf("\033[0m");
        }
        printf("\033[1;32m");
        if (call >= 0 && call <= 6)
        {
            s = toss + call;
            if (s % 2 == dec)
            {
                if (dec == 1)
                {
                    printf("Sum is %d and It's odd\n", s);
                }
                else
                {
                    printf("Sum is %d and It's even\n", s);
                }
                printf("\nYou have won the toss\n");
                x = choose();
                if (x == 1)
                {
                    lets_start();
                }
                else
                {
                    printf("\nYou have to bowl\n");
                    lets_start2();
                }
            }
            else
            {
                printf("\033[1;31m");
                if (dec == 1)
                {
                    printf("Sum is %d and It's even\n", s);
                }
                else
                {
                    printf("Sum is %d and It's odd\n", s);
                }
                printf("System has won the toss\n");
                y = syschoose();
                if (y == 1)
                {
                    printf("You have to bowl\n");
                    lets_start2();
                }
                else
                {
                    lets_start();
                }
            }
        }
    }
    printf("\033[0m");
}

void displayPlayerScore(int wickets, player *p[wickets])
{
    printf("\033[1;36m");
    printf("\n-------INDIVIDUAL SCORES IN THE MATCH-------\n");
    printf("\n------------------------------------------------\n");
    printf("PLAYER NO.\tPLAYER NAME\tRUNS SCORED");
    printf("\n------------------------------------------------\n");
    for (int i = 0; i < wickets; i++)
    {
        printf("%d\t\t%-20s%d\n", p[i]->playerno, p[i]->player_name, p[i]->ind_runs);
    }
    printf("------------------------------------------------\n\n");
    printf("\033[0m");
}

void total_balls_by_each_player()
{
    total_balls += 1;
}

void addBallsHuman() //Existing
{
    currover += 1;
    if (currover % 6 == 0)
    {
        currover = 0;
        team.total_overs += 1;
    }
}

void addBallsComputer()
{
    currover += 1;
    if (currover % 6 == 0)
    {
        currover = 0;
        comp.total_overs += 1;
    }
}

void addScoreHuman(int n)
{
    team.team_score += n;
    batting_order->front->data->ind_runs += n;
}

void addScoreComputer(int n)
{
    comp.team_score += n;
    batting_order->front->data->ind_runs += n;
}

void addWicketHuman()
{
    team.total_wickets += 1;
}

void addWicketComputer()
{
    comp.total_wickets += 1;
}

void batting() //users first batting innings(sets the target)
{
    printf("\033[1;34m");
    int n;
    printf("%.1fth ball\n\n", team.total_overs + (currover / 10.0 + 0.1));
    printf("Enter a number (0-6) : ");
    scanf("%d", &n);
    while (n >= 7 || n < 0)
    {
        printf("\033[1;31m");
        printf("Please enter a number in the range 0-6 : ");
        scanf("%d", &n);
        printf("\033[0m");
    }
    int computer_random = printRandoms(0, 6);
    printf("\033[1;32m");
    printf("Computer generated number : %d\n\n", computer_random);
    printf("\033[1;34m");
    if (n == computer_random)
    {
        total_balls_by_each_player();
        node *temp = batting_order->front;
        printf("\033[1;31m");
        printf("\n%s is OUT!!\n", temp->data->player_name);
        printf("Runs scored : %d\n", temp->data->ind_runs);
        temp->data->strike_rate = ((float)temp->data->ind_runs / total_balls) * 100;
        printf("Strike rate is %.2f\n\n", temp->data->strike_rate);
        printf("\033[1;34m");
        dequeueBatsman(total_balls);
        total_balls = 0;
        addBallsHuman();
        addWicketHuman();
        if (!allOut())
        {
            battingLineUp();
            currentBatsman();
        }
    }
    else if (n == 0)
    {
        addScoreHuman(computer_random);
        addBallsHuman();
        total_balls_by_each_player();
        printf("EXTRAS!! %d added to the Score! Score now is: %d/%d\n\n", computer_random, team.team_score, team.total_wickets);
        if (currover == 0)
            printf("OVER UP!!!\t %d overs finished\n\n", team.total_overs);
    }
    else
    {
        addScoreHuman(n);
        addBallsHuman();
        total_balls_by_each_player();
        printf("%d added to the Score! Score now is: %d/%d\n\n", n, team.team_score, team.total_wickets);
        if (currover == 0)
            printf("OVER UP!!!\t %d overs finished\n\n", team.total_overs);
    }
    printf("\033[0m");
}

void compbattingChase()
{
    printf("\033[1;35m");
    int n;
    printf("\n----Innings 2----\n");
    printf("%.1fth ball\n\n", comp.total_overs + (currover / 10.0 + 0.1));
    printf("Enter a number (0-6) : ");
    scanf("%d", &n);
    while (n >= 7 || n < 0)
    {
        printf("\033[1;31m");
        printf("Please enter a number in the range 0-6 : ");
        scanf("%d", &n);
        printf("\033[1;35m");
    }
    int computer_random = printRandoms(0, 6);
    printf("\033[1;32m");
    printf("Computer generated number : %d\n\n", computer_random);
    printf("\033[1;35m");
    if (n == computer_random)
    {
        total_balls_by_each_player();
        node *temp = batting_order->front;
        printf("\033[1;31m");
        printf("\n%s is OUT!!\n", temp->data->player_name);
        printf("Runs scored : %d\n", temp->data->ind_runs);
        temp->data->strike_rate = ((float)temp->data->ind_runs / total_balls) * 100;
        printf("Strike rate is %.2f\n\n", temp->data->strike_rate);
        printf("\033[1;35m");
        dequeueBatsman(total_balls);
        total_balls = 0;
        addBallsComputer();
        addWicketComputer();
        if (!allOut())
        {
            battingLineUp();
            currentBatsman();
        }
    }
    else if (computer_random == 0)
    {
        total_balls_by_each_player();
        addScoreComputer(n);
        addBallsComputer(comp);
        printf("EXTRAS!! %d added to the Score! Score now is: %d/%d\n\n", n, comp.team_score, comp.total_wickets);
        if (currover == 0)
            printf("OVER UP!!!\t %d overs finished\n\n", comp.total_overs);
    }
    else
    {
        total_balls_by_each_player();
        addScoreComputer(computer_random);
        addBallsComputer();
        printf("%d added to the Score! Score now is: %d/%d\n\n", computer_random, comp.team_score, comp.total_wickets);
        if (currover == 0)
            printf("OVER UP!!!\t %d overs finished\n\n", comp.total_overs);
    }
    printf("\033[0m");
}

void maxRuns(int wickets, player *p[wickets])
{

    char *tempName = (char *)malloc(sizeof(char) * 20);
    int maxRuns = p[0]->ind_runs;
    tempName = p[0]->player_name;
    for (int i = 0; i < wickets; i++)
    {
        if (p[i]->ind_runs > maxRuns)
        {
            maxRuns = p[i]->ind_runs;
            strcpy(tempName, p[i]->player_name);
        }
    }
    printf("\n");
    printf("\033[1;32m");
    printf("\nMaximum runs in the innings was scored by : %s\n", tempName);
    printf("Runs scored = %d\n\n", maxRuns);
    printf("\033[0m");
}

void lets_start()
{
    player *players[wickets];
    createQueue();
    for (int i = 0; i < wickets; i++)
    {
        players[i] = createPlayer();
        acceptPlayerDetails(players[i], i + 1);
        enqueueBatsman(players[i]);
    }
    printf("\033[1;34m");
    printf("Start Batting!!!\n");
    currentBatsman();
    printf("\033[1;34m");
    printf("%d/%d %.1f overs up\n", team.team_score, team.total_wickets, team.total_overs + (currover / 10.0));
    int f = 0;
    while (team.total_overs + (currover / 10.0) < overs)
    {
        batting();
        if (allOut())
        {
            printf("\033[1;31m");
            printf("\nALL OUT!!!\n");
            f++;
            break;
        }
    }
    printf("\033[1;34m");
    if (f == 0)
        printf("1st Innings finished!!!\n\n");
    printf("-------TEAM SCORE-------\n");
    printf("%d/%d   in   %.1f overs\n", team.team_score, team.total_wickets, team.total_overs + (currover / 10.0));
    displayPlayerScore(wickets, players);
    maxRuns(wickets, players);
    makeEmpty();
    printf("\033[1;32m");
    printf("\nTarget for the computer = %d\n", target);
    printf("\033[1;34m");
    for (int i = 0; i < wickets; i++)
    {
        players[i] = createPlayer();
        computerPlayerDetails(players[i], i + 1);
        enqueueBatsman(players[i]);
    }
    f = 0;
    while ((comp.total_overs + (currover / 10.0) < overs) && comp.team_score < target)
    {
        compbattingChase();
        if (allOut())
        {
             printf("\033[1;31m");
            printf("ALL OUT!!!\n");
            f++;
            break;
        }
    }
    printf("\033[1;34m");
    if (f == 0)
        printf("2nd Innings finished!!!\n\n");
    printf("-------TEAM SCORE-------\n");
    printf("%d/%d   in   %.1f overs\n", comp.team_score, comp.total_wickets, comp.total_overs + (currover / 10.0));
    displayPlayerScore(wickets, players);
    maxRuns(wickets, players);
    if (comp.team_score < target)
    {
         printf("\033[1;32m");
        printf("\nCongratulations!!You have won the game by %d runs\n", target - 1 - comp.team_score);
    }
    else
    {
        printf("\033[1;31m");
        printf("\nComputer has won by %d wickets\n", wickets - comp.total_wickets);
    }
    makeEmpty();
    printf("\033[0m");
}

void lets_start2() //computer first batting
{
    player *players[wickets];
    createQueue();
    for (int i = 0; i < wickets; i++)
    {
        players[i] = createPlayer();
        computerPlayerDetails(players[i], i + 1);
        enqueueBatsman(players[i]);
    }
    printf("Computer Batting!!!\n");
    currentBatsman();
    printf("\033[1;35m");
    printf("%d/%d %.1f overs up\n", comp.team_score, comp.total_wickets, comp.total_overs + (currover / 10.0));
    int f = 0;
    while (comp.total_overs + (currover / 10.0) < overs)
    {
        compbatting();
        if (allOut())
        {
            printf("\033[1;31m");
            printf("\nALL OUT!!!\n");
            f++;
            break;
        }
    }
    printf("\033[1;35m");
    if (f == 0)
        printf("1st Innings finished!!!\n\n");
    printf("-------TEAM SCORE-------\n");
    printf("%d/%d   in   %.1f overs\n", comp.team_score, comp.total_wickets, comp.total_overs + (currover / 10.0));
    displayPlayerScore(wickets, players);
    maxRuns(wickets, players);
    makeEmpty_2();
    printf("\033[1;32m");
    printf("\nTarget for the user = %d\n", target);
    printf("\033[1;35m");
    for (int i = 0; i < wickets; i++)
    {
        players[i] = createPlayer();
        acceptPlayerDetails(players[i], i + 1);
        enqueueBatsman(players[i]);
    }
    f = 0;
    while ((team.total_overs + (currover / 10.0) < overs) && team.team_score < target)
    {
        userbattingChase();
        if (allOut())
        {
            printf("\033[1;31m");
            printf("ALL OUT!!!\n");
            f++;
            break;
        }
    }
    printf("\033[1;35m");
    if (f == 0)
        printf("2nd Innings finished!!!\n\n");
    printf("-------TEAM SCORE-------\n");
    printf("%d/%d   in   %.1f overs\n", team.team_score, team.total_wickets, team.total_overs + (currover / 10.0));
    displayPlayerScore(wickets, players);
    maxRuns(wickets, players);
    if (team.team_score < target)
    {
        printf("\033[1;31m");
        printf("\nComputer has won by %d runs\n", target - 1 - team.team_score);
    }
    else
    {
        printf("\033[1;32m");
        printf("\nCongratulations!!You have won the game by %d wickets\n", wickets - team.total_wickets);
    }
    makeEmpty_2();
    printf("\033[0m");
}

void compbatting() //computer first batting innings(sets the target)
{
    printf("\033[1;35m");
    int n;
    printf("%.1fth ball\n\n", comp.total_overs + (currover / 10.0 + 0.1));
    printf("Enter a number (0-6) : ");
    scanf("%d", &n);
    while (n >= 7 || n < 0)
    {
        printf("\033[1;31m");
        printf("Please enter a number in the range 0-6 : ");
        scanf("%d", &n);
        printf("\033[1;35m");
    }
    int computer_random = printRandoms(0, 6);
    printf("\033[1;32m");
    printf("Computer generated number : %d\n\n", computer_random);
    printf("\033[1;35m");
    if (n == computer_random)
    {
        total_balls_by_each_player();
        node *temp = batting_order->front;
        printf("\033[1;31m");
        printf("\n%s is OUT!!\n", temp->data->player_name);
        printf("Runs scored : %d\n", temp->data->ind_runs);
        temp->data->strike_rate = ((float)temp->data->ind_runs / total_balls) * 100;
        printf("Strike rate is %.2f\n\n", temp->data->strike_rate);
        printf("\033[1;35m");
        dequeueBatsman(total_balls);
        total_balls = 0;
        addBallsComputer();
        addWicketComputer();
        if (!allOut())
        {
            battingLineUp();
            currentBatsman();
        }
    }
    else if (computer_random == 0)
    {
        total_balls_by_each_player();
        addScoreComputer(n);
        addBallsComputer();
        printf("EXTRAS!! %d added to the Score! Score now is: %d/%d\n\n", n, comp.team_score, comp.total_wickets);
        if (currover == 0)
            printf("OVER UP!!!\t %d overs finished\n\n", comp.total_overs);
    }
    else
    {
        total_balls_by_each_player();
        addScoreComputer(computer_random);
        addBallsComputer();
        printf("%d added to the Score! Score now is: %d/%d\n\n", computer_random, comp.team_score, comp.total_wickets);
        if (currover == 0)
            printf("OVER UP!!!\t %d overs finished\n\n", comp.total_overs);
    }
    printf("\033[0m");
}

void userbattingChase()
{
    printf("\033[1;34m");
    int n;
    printf("\n----Innings 2----\n");
    printf("%.1fth ball\n\n", team.total_overs + (currover / 10.0 + 0.1));
    printf("Enter a number (0-6) : ");
    scanf("%d", &n);
    while (n >= 7 || n < 0)
    {   printf("\033[1;31m");
        printf("Please enter a number in the range 0-6 : ");
        scanf("%d", &n);
        printf("\033[1;34m");
    }
    int computer_random = printRandoms(0, 6);
    printf("\033[1;32m");
    printf("Computer generated number : %d\n\n", computer_random);
    printf("\033[1;34m");
    if (n == computer_random)
    {
        total_balls_by_each_player();
        node *temp = batting_order->front;
        printf("\033[1;31m");
        printf("\n%s is OUT!!\n", temp->data->player_name);
        printf("Runs scored : %d\n", temp->data->ind_runs);
        temp->data->strike_rate = ((float)temp->data->ind_runs / total_balls) * 100;
        printf("Strike rate is %.2f\n\n", temp->data->strike_rate);
        printf("\033[1;34m");
        dequeueBatsman(total_balls);
        total_balls = 0;
        addBallsHuman();
        addWicketHuman();
        if (!allOut())
        {
            battingLineUp();
            currentBatsman();
        }
    }
    else if (n == 0)
    {
        addScoreHuman(computer_random);
        addBallsHuman();
        total_balls_by_each_player();
        printf("EXTRAS!! %d added to the Score! Score now is: %d/%d\n\n", computer_random, team.team_score, team.total_wickets);
        if (currover == 0)
            printf("OVER UP!!!\t %d overs finished\n\n", team.total_overs);
    }
    else
    {
        addScoreHuman(n);
        addBallsHuman();
        total_balls_by_each_player();
        printf("%d added to the Score! Score now is: %d/%d\n\n", n, team.team_score, team.total_wickets);
        if (currover == 0)
            printf("OVER UP!!!\t %d overs finished\n\n", team.total_overs);
    }
    printf("\033[0m");
}

void clear()
{
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

void main()
{
    int choice;
    printf("\033[1;33m");
    printf("\n---------------------------------------------------------Welcome to Our Key-Cricket Game----------------------------------------------------");
    printf("\n\nKey Cricket is a game designed by students of DIST to help students overcome stress and have fun!");
    printf("\n\nThe name Key-Cricket is so because you will be playing using your computer/laptop keyboard vs our super intelligent computer!!");
    printf("\n\n--------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n\n");
    printf("\nLet's Goo!!!\n");
    printf("\033[0;m");
    int countGame = 0;
    char des;
    while (1)
    {
        printf("\033[1;33m");
        if (countGame > 0)
        {
            while((getchar()!='\n'));
            printf("\nDo you wanna play again ?\nEnter Y to play again and N to exit : ");
            des=getchar();
            while (des != 'Y' && des != 'y' && des != 'N' && des != 'n')
            {
                printf("\033[1;31m");
                while((getchar()!='\n'));
                printf("\nPlease enter either Y or N !\n\nDo you wanna play again ?\nEnter Y to play again and N to exit : ");
                des=getchar();
            }
            printf("\033[1;33m");
            if (des == 'Y' || des == 'y')
                clear();
            else if (des == 'N' || des == 'n')
            {
                printf("\033[1;32m");
                printf("\nThanks for playing !\n");
                printf("\033[0;m");
                break;
                exit(0);
            }
        }
        printf("\033[1;33m");
        printf("\n\n1.Rules of the Game");
        printf("\n2.Start The Game");
        printf("\n3.EXIT");
        printf("\n\nEnter your Choice : ");
        scanf("%d", &choice);
        printf("\033[0;m");
        switch (choice)
        {
        case 1:
            printf("\033[1;33m");
            printf("Let's Jump on to the Rules of The game");
            printf("\033[0;m");
            print_rules();
            countGame = 0;
            break;

        case 2:
            clear();
            start();
            toss();
            countGame++;
            break;

        case 3:
            printf("\033[1;33m");
            printf("\nExiting....\n");
            printf("\nThanks for playing !!\n");
            printf("\033[0;m");
            exit(0);
            break;

        default:
            printf("\033[1;33m");
            printf("\nEnter a valid option next time!!!\n");
            printf("\033[0;m");
        }
    }
}

