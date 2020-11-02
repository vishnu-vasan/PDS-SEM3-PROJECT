#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>

int wickets, overs,currover=0;

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
}team;
typedef struct score score;//Both team and score are the instances of the structure score


player* createPlayer()
{
    player* p=(player *)malloc(sizeof(struct player));
    p->ind_runs= p->ind_wickets = 0;
    return p;
}

struct node
{
    player *data;//data part
    struct node* next;//Pointer to the next node
};

struct queue
{
    struct node* front;
    struct node* rear;
};

typedef struct node node;
typedef struct queue queue;
queue* batting_order;

node* createNode(player *p)
{
    node* newNode=(node * )malloc(sizeof(struct node));
    newNode->data=p;
    newNode->next=NULL;
    return newNode;
}

void createQueue()
{
    batting_order=(queue *)malloc(sizeof(struct queue));
    batting_order->rear=NULL;
    batting_order->front=NULL;
}

int allOut()//isEmpty() func
{
    return batting_order->front==NULL;
}

void enqueueBatsman(player *p)
{
    node* newNode=createNode(p);
    if(allOut())
        batting_order->front=batting_order->rear=newNode;
    else
    {
        batting_order->rear->next=newNode;
        batting_order->rear=newNode;
    }
}

void dequeueBatsman()
{
    node* temp=batting_order->front;
    batting_order->front=batting_order->front->next;
    printf("\n%s is OUT!!\n",temp->data->player_name);
    printf("Runs scored : %d\n\n",temp->data->ind_runs);
    free(temp);

}

void currentBatsman()//peek() func
{
    printf("\nThe batsman on strike : %s\n\n",batting_order->front->data->player_name);
}

void battingLineUp()//display() func of queue
{
    if(allOut())
    {
        printf("\nALL OUT !!\n");
        return;
    }
    node* curr=batting_order->front;
    printf("\nNext to bat :\n");
    printf("----------------------------\n");
    printf("PLAYER ID\tBATSMAN NAME\n");
    printf("----------------------------\n");
    while(curr!=batting_order->rear)
    {
        printf("%d\t\t%s\t\n",curr->data->playerno,curr->data->player_name);
        curr=curr->next;
    }
    printf("%d\t\t%s\t\n",curr->data->playerno,curr->data->player_name);
    printf("----------------------------\n");
}

void acceptPlayerDetails(player *p,int num)
{
    printf("\nEnter the details of PLAYER %d\n",num);
    printf("----------------------------------\n");
    printf("Enter the player's name : ");
    scanf("%s",p->player_name);
    printf("Enter the player's role (batsman/bowler/all-rounder) : ");
    scanf("%s",p->player_type);
    p->playerno=num;
    printf("\n");
}

int print_rules()
{
    int n;
    printf("\033[1;33m");
    printf("\n---------------------------------------------------------Welcome to Our Key-Cricket Game------------------------------------------------------------");
    printf("\n\nKey Cricket is a game designed by students of DIST students to help students overcome stress and have fun!");
    printf("\n\nThe name Key-Cricket is so because you will be playing using your computer/laptop keyboard vs our super intelligent computer!!");
    printf("\n\n\n");
    printf("Let's Jump on to the Rules of The game");
    printf("\033[1;32m");
    printf("\n\nRules of the Game:\n");
    printf("\033[1;31m");
    printf("\n\n1.The User has to spin a coin during the toss,based on the outcome of the toss, the user will bat or field first!");
    printf("\n\n3.The User can choose the total number of overs and wickets for the respective match after the toss.");
    printf("\n\n4.The User can enter scores only between 0 to 6.");
    printf("\n\n5.If the User and computer land up on the same number while batting, the batsman is declared out.");
    printf("\n\n6.The team is considered ALL OUT after losing all the wickets during batting.");
    printf("\n\n7.If the batsman inputs a 0 and the computer generates any number other than 0,those runs will be added to the batsman's score.");
    printf("\n\n8.In case of a 0 by both the batsman and the computer, then the batsman is declared out.");
    printf("\n\n9.A batsman is considered to be out when he inputs the same number as that of the number generated by the opponent.");
    printf("\033[1;35m");
    printf("\n\nARE YOU READY FOR THE GAME?If yes, Please enter 1.");
    printf("\033[0;m");
    printf("\n\n");
    printf("START THE GAME?PRESS 1\n");
    scanf("%d", &n);
    return n;
}

void start()
{
    printf("\nEnter the No of wickets(1-5):");
    scanf("%d", &wickets);
    while (wickets > 5)
    {
        printf("\nEnter the No of wickets in the given range : 1-5 :");
        scanf("%d", &wickets);
    }
    printf("Enter the No of Overs(1-6):");
    scanf("%d", &overs);
    while (overs > 6)
    {
        printf("\nEnter the No of overs in the given range : 1-6 :");
        scanf("%d", &overs);
    }
}

int printRandoms(int lower, int upper)
{
        int num = (rand() %(upper - lower + 1)) + lower;
        return num;
}

void toss()
{
    printf("\nTossss!!\n");
}

void displayPlayerScore(int wickets,player *p[wickets])
{
    printf("\n-------INDIVIDUAL SCORES IN THE MATCH-------\n");
    printf("\n------------------------------------------------\n");
    printf("PLAYER NO.\tPLAYER NAME\tRUNS SCORED");
    printf("\n------------------------------------------------\n");
    for(int i=0;i<wickets;i++)
    {
        printf("%d\t\t%-3s\t\t%d\n",p[i]->playerno,p[i]->player_name,p[i]->ind_runs);
    }
     printf("-------------------------------------------------\n\n");
}

void addBalls(){
    currover+=1;
    if(currover%6==0){
        currover=0;
        team.total_overs+=1;
    }
}

void addScore(int n){
    team.team_score+=n;
    batting_order->front->data->ind_runs+=n;
}

void addWicket(){
    team.total_wickets+=1;
}

void batting(){
    int n;
    printf("%.1fth ball\n",team.total_overs+(currover/10.0+0.1));
    printf("Enter a number (0-6) : ");
    scanf("%d",&n);
    while(n>=7 || n<0)
    {
        printf("Please enter a number in the range 0-6 : ");
        scanf("%d",&n);
    }
    int computer_random=printRandoms(0,6);
    printf("Computer generated number : %d\n",computer_random);
    if(n==computer_random){
        dequeueBatsman();
	addBalls();
        addWicket();
        if(!allOut())
        {
            battingLineUp();
            currentBatsman();
        }
    }
    else{
        addScore(n);
        addBalls();
        printf("%d added to the Score! Score now is: %d/%d\n\n",n,team.team_score,team.total_wickets);
        if(currover==0)
            printf("OVER UP!!!\t %d overs finished\n\n",team.total_overs);
    }
}

void main()
{
    /*int t = print_rules();
    if (t == 1)
        printf("\nStarting...\n");*/
    start();
    printf("\nNo of Wickets in this Match : %d", wickets);
    printf("\nNo of Overs in this Match : %d\n", overs);

    printf("\nIt's Toss Time!!\n");
    toss();
    player *players[wickets];
    createQueue();
    for(int i=0;i<wickets;i++)
    {
        players[i]=createPlayer();
        acceptPlayerDetails(players[i],i+1);
        enqueueBatsman(players[i]);
    }
    printf("Start Batting!!!\n");
    currentBatsman();

    printf("%d/%d %.1f overs up\n",team.team_score,team.total_wickets,team.total_overs+(currover/10.0));
    int f=0;
    while(team.total_overs+(currover/10.0)<overs){
        batting();
        if(allOut()){
            printf("\nALL OUT!!!\n");
            f++;
            break;
        }
    }
    if(f==0)
        printf("1st Innings finished!!!\n\n");
    printf("-------TEAM SCORE-------\n");
    printf("%d/%d   in   %.1f overs\n",team.team_score,team.total_wickets,team.total_overs+(currover/10.0));
    displayPlayerScore(wickets,players);

}



