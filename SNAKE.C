#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>

char key;
struct loc   //for storing x and y coordinates
{
	int x,y;
};
struct snake     //for increasing the length of snake
{
	struct loc sloc;
	struct snake *link;
	char dir;
};
struct game_data  // for storing score and food consumed
{
	int score;
	int no_food;
};
struct game_data gd={0,0}; //initializing the score and food to 0
struct limit //for defining the boundary of rectangle in which snake moves
{
       int lx1,ly1,lx2,ly2;
};
struct limit l={100,100,400,400};//initializing the values oflimits

struct food  //for location of food
{
       struct loc floc;
       int number;
};
int n=0; //initializing no. of food to 0


void game(struct snake *head, struct food *f) //creating the snake
{
       struct snake *temp, pre, nxt;
       temp=head;//pointing temp to head

       while(key!='p')	  //while the game is not paused
       {      //checking whether snake hits boundary
	 if(head->sloc.x==l.ly1||head->sloc.x==l.ly2||head->sloc.y==l.ly1||head->sloc.y==l.ly2)
	 { gameover();}//if hits the boundary then gameover

	 if(head->sloc.x>=f->floc.x-10&&head->sloc.x<=f->floc.x+10&&head->sloc.y>=f->floc.y-10&&head->sloc.y<=f->floc.y+10)
	 {   //if snake consumes food
		   temp=head;
		   sound(420); //for beep sound
		   f->floc.x=101+rand()%(294); //generating new food
		   f->floc.y=101+rand()%(294);
		   gd.score+=100;//increaing score
		   gd.no_food+=1; //increasing no.of food consumed




		     while(temp->link!=NULL)
		     {temp=temp->link;}

		     temp->link=(struct snake *)malloc(sizeof(struct snake)); //adding a new node
		     temp->link->link=NULL;
		     temp->link->sloc.x=temp->sloc.x; //changing the x-coordinate of new node to that of previous node
		     temp->link->sloc.y=temp->sloc.y; //changing y coordinate
		     temp->link->dir=temp->dir; //changing the direction


	 }

       switch(key)  //for changing the direction of snake
       {
       case 'a': if(head->dir!='d') //to check if it is not moving in opposite direction
		 {
		    head->dir='a';
		    head->sloc.x-=2; //for moving leftwards
		 }
		 else{key=head->dir;}
		 break;
       case 'w': if(head->dir!='s')
		 {head->dir='w';
		  head->sloc.y-=2; //for moving upwards
		 }
		 else{key=head->dir;}
		 break;
       case 'd': if(head->dir!='a')
		 {head->dir='d';
		  head->sloc.x+=2;  //for moving rightwards
		 }
		 else{key=head->dir;}
		 break;
       case 's': if(head->dir!='w')
		 {head->dir='s';
		  head->sloc.y+=2; //for moving downwards
		 }
		 else{key=head->dir;}
		 break;
       }

       cleardevice();
       draw (head,f); //calling the draw function
       nosound(); //stoping the sound
       temp=head;
       pre=*temp;

       while(temp->link!=NULL)//for motion of snake
       {
	      nxt.sloc.x=temp->link->sloc.x;
	      nxt.sloc.y=temp->link->sloc.y;
	      nxt.dir=temp->link->dir;
	      temp->link->sloc.x=pre.sloc.x;
	      temp->link->sloc.y=pre.sloc.y;
	      temp->link->dir=pre.dir;

	      temp=temp->link;
	      pre=nxt;
       }
     }
}

gameover(void)
{
     cleardevice(); //clearing the screen
     outtextxy(100,100,"-------------GAME OVER-------------"); //displaying game over

     printf("\n\n\n\n\n\n\n\n");
     printf("\t\t#Score - %d",gd.score); //displays score
     printf("\n\t\t#No. of food  - %d",gd.no_food);//display food consumed
     s1: //sound after game is over
     sound(300);delay(300);sound(450);delay(150);sound(500);delay(150);
     sound(300);delay(200);sound(450);delay(100);sound(450);delay(200);
     while(!kbhit())
     {goto s1;}
      nosound();

     exit(0); //stop the program
     return 0; //returning to main
}
draw(struct snake *head,struct food *f) //for creating snake
{
     struct snake *temp;
     temp=head;

     rectangle(96,96,404,404); //outermost boundary
     rectangle(98,98,402,402); //middle boundary
     rectangle(100,100,400,400); //innermost boundary
     setfillstyle(9,13);//pattern and colour of snake's mouth
     bar(temp->sloc.x-6,temp->sloc.y-6,temp->sloc.x+6,temp->sloc.y+6);//rectangle for snakes body
     temp=temp->link;
     setfillstyle(9,2);//pattern and colour for snake's body
     while(temp!=NULL)
     {                      //addition of body
	     bar(temp->sloc.x-5,temp->sloc.y-5,temp->sloc.x+5,temp->sloc.y+5);
	     temp=temp->link;
     }

     circle(f->floc.x-2,f->floc.y-2,5); //for drawing food
     circle(f->floc.x+2,f->floc.y+2,5);
     circle(f->floc.x-2,f->floc.y+2,5);
     circle(f->floc.x+2,f->floc.y-2,5);

     delay(20);  //for speed of snake
     while(!kbhit()){goto e;}
     key=getch();//taking input of directions
     e:
     cleardevice();
     return 0;
}

void main(void)
{
      struct snake *s;
      struct food f;
      int gdriver=DETECT, gmode;//for accessing graphics mode

      clrscr();

      s=(struct snake *)malloc(sizeof(struct snake)); //creating head of snake
      s->dir='w'; //initializing direction of snake to upwards
      s->link=NULL;
      s->sloc.x=s->sloc.y=300;//initializing location of snake
      f.floc.x=150+rand()%(250); //initializing location of food
      f.floc.y=150+rand()%(250);

      initgraph(&gdriver, &gmode, "C:\\TurboC3\\BGI");//initializes graphic mode

      outtextxy(300,50,"SNAKE");
      outtextxy(100,160,"#Instructions:");
      outtextxy(100,200,"1.Press 'w' to go upward");
      outtextxy(100,220,"2.Press 's' to go downward");
      outtextxy(100,240,"3.Press 'a' to go to the left");
      outtextxy(100,260,"4.Press 'd' to go to the right");
      outtextxy(100,280,"5.Press 'p' to pause the game");
      s:
      sound(400);delay(200);sound(100);delay(120);sound(120);delay(20);
      sound(110);delay(100);sound(200);delay(180);sound(400);delay(150);
      while(!kbhit()){goto s;}

      nosound();
      getch();
      pause:
      draw(s,&f);
      game(s,&f);
      rectangle(60,60,600,200);//rectangle for displaying game is paused
      outtextxy(260,100,"GAME PAUSED");
      s1:
      sound(400);delay(500);sound(450);delay(250);sound(300);delay(200);
      sound(400);delay(300);sound(450);delay(250);sound(300);delay(200);
      while(!kbhit()){goto s1;}
      goto pause;
      closegraph();


}

