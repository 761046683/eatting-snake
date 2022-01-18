#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
/*这是一个特立独行的分割线*/
void gotoxy(int x, int y);
void gotoprint(int x, int y);
void gotodelete(int x, int y);
void cfood();
void change(int a,int b);
void moving();
void eating();
int judge();
int control();
void beginning();
void working();
void ending();
/*全局变量及其预处理*/ 
typedef struct snake           //贪食蛇的链表
{
	int x;
	int y;
	struct snake *next;
}snake;
snake *head,*tail;             //定义蛇的头指针和尾指针
struct food                    //食物的结构体全局变量 
{
	int x;
	int y;
}food;
char name[20];                 //定义名字 
int score=0;                   //定义分数 
char click=1;                  //定义键盘输入字符 (w,s,a,d) 
int speed;                     //定义速度 (ms)
/*主函数*/
int main()
{
	system("color 0B");
	beginning();
	working();
	cfood();
	if(control()==0)
		return 0;
} 
/*自定义函数的定义*/
void gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hOutput; 
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}
void gotoprint(int x, int y)
{
	gotoxy(x, y);
	printf("■");
}
void gotodelete(int x, int y)
{
	gotoxy(x, y);
	printf("  ");
}
/*食物的创建函数*/
void cfood()
{
	srand(time(NULL));
	loop:
		food.x=rand()%53+2;
		food.y=rand()%25+1;
		if(food.x%2!=0)
			food.x+=1;
		snake *j=head;
	while(j->next!=NULL)
	{
		if(j->x==food.x&&j->y==food.y)
			goto loop;
		j=j->next;
	}
	gotoxy(food.x,food.y);
	printf("●");
}
/*蛇的移动函数*/
void change(int a,int b)
{
	snake *p=head->next;
	int t1,t2,t_1,t_2;
	t1=p->x;
	t2=p->y;
	while(p->next->next!=NULL)
	{
		t_1=p->next->x;
		t_2=p->next->y;
		p->next->x=t1;
		p->next->y=t2;
		t1=t_1;
		t2=t_2;
		p=p->next;
	}
	p=head->next;
	p->x=a;
	p->y=b;
}
void moving()
{
	int count,a=head->x,b=head->y;
	snake *p=head;
	while(p->next!=NULL)
	{
		gotodelete(p->x,p->y);
		count++;
		p=p->next;
	}
	switch(click)
	{
		case 'w':head->y-=1;change(a,b);break;
		case 's':head->y+=1;change(a,b);break;
		case 'a':head->x-=2;change(a,b);break;
		case 'd':head->x+=2;change(a,b);break;
		case 'p':getch();break;
	}
	p=head;
	while(1)
	{
		if(p->next==NULL)
			break;
		gotoprint(p->x,p->y);
		p=p->next;
	}
	p=head;
	if(count<=500)
		speed=200;
	else if(count>500&&count<=1000)
		speed=150;
	else if(count>1000&&count<=1500)
		speed=100;
	else speed=50;
	gotoxy(75,20);
	printf("%d",speed);
	Sleep(speed);
} 
/*吃食物函数*/
void eating()
{
	if(head->x==food.x&&head->y==food.y)
	{
		cfood();
		snake *n=(snake*)malloc(sizeof(snake));
		snake *p;
		p=head;
		while (p->next->next!=NULL)
			p=p->next;
		p->next=n;
		n->next=tail;
		score+=10;
		gotoxy(75,15);
		printf("%d",score);
	}
} 
/*游戏结束判断函数*/
int judge()
{
	if (head->x==0||head->x==60||head->y==0||head->y==30)
	{
		ending();
		return 0;
	}
	snake *p = head->next;
	while (p->next!=NULL)
	{
		if (head->x==p->x&&head->y==p->y)
		{
			ending();
			return 0;
		}
		p = p->next;
	}
	return 1;
} 
/*键盘控制函数*/
int control()
{
	char c;
	while(1)
	{
		if(judge()==0)
			return 0;
		if(kbhit())
			click=getch();
		moving();
		eating();
	}
	return 1;
}
/*开始界面*/
void beginning()
{
	gotoxy(10,20);
	printf("--------------------------------------------------------------------------------");
	gotoxy(10,48);
	printf("--------------------------------------------------------------------------------");
	gotoxy(13,25);
	printf("欢迎来到明泽贪食蛇！");
	gotoxy(13,30);
	printf("本游戏由刘明泽出品，未经许可请勿转载");
	gotoxy(13,35);
	printf("请在英文输入法中操作，反向移动等同于吃到自己，wasd控制蛇的移动，p暂停");
	gotoxy(13,40);
	printf("来者请留名：");
	scanf("%s",name);
	system("cls");
} 
/*游戏界面*/
void working()
{
	int i;
	for(i=0;i<58;i+=2)
	{
		gotoprint(i,0);
		gotoprint(i,26);
	}
	for(i=1;i<26;i++)
	{
		gotoprint(0,i);
		gotoprint(56,i);
	}
	gotoxy(63,10);
	printf("%s，你好！",name); 
	gotoxy(63,15);
	printf("当前得分为：%d        ，加油(o°ω°o)!",score);
	gotoxy(63,20);
	printf("当前速度为：%d      ms",speed);
	head=(snake*)malloc(sizeof(snake));
	head->x=16;
	head->y=15;
	tail=(snake*)malloc(sizeof(snake));
	snake *p=(snake*)malloc(sizeof(snake));
	snake *q=(snake*)malloc(sizeof(snake));
	p->x=16;
	p->y=16;
	q->x=16;
	q->y=17;
	tail->x=4;
	tail->y=2;
	head->next=p;
	p->next=q;
	q->next=tail;
	tail->next=NULL;
}
/*结束界面*/
void ending()
{
	system("cls");
	gotoxy(10,20);
	printf("--------------------------------------------------------------------------------");
	gotoxy(10,48);
	printf("--------------------------------------------------------------------------------");
	gotoxy(13,25);
	printf("游戏结束！");
	gotoxy(13,30);
	printf("你的最终得分为：%d 分，继续努力哦~~",score); 
	gotoxy(20,40);
	printf("明泽出品\n");
	system("pause"); 
} 
