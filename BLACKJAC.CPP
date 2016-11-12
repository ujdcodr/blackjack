/*Version 1.1
Ultimate BlackJack:Play or Be Played
Conceived,Conceptualised & Coded ENTIRELY by Ujjwal Pasupulety
Updates:1.Advanced betting system; allows players to increase their
	  bet with a strong hand.Nifty huh??
	2.Player statistics added; Currently stored in RAM resulting in
	  collapse after program termination.Hmmmm...gotta do something
	  about it.
	  */
/*UPDATE 2.0
Finally after lots of struggle and a silly directory related problem
WE HAVE GRAPHICS!!!!!
*/
/*Update 2.1
1.Thanks to Mr. Nischal T and some getch() magic, the option entry problem has
finally been solved.
2.Filters added to input;
 (out of[Y/N],only Y/y or N/n can be entered.Entry of other charcters
 redirects back to input request).
3.Extra Graphical Features added;Credits have been extended to everyone who
  was instrumental in the creation of this game.
4.Not really worried about the temporary memory storage.Actually it's better
  as a player can view his stats alone as long as he remains in the game.
5.Probably the most AWESOME "Graphical" ELEMENT in the game:
  Randomly selects colors within a loop and keeps printing multicolored text.
  while(!kbhit())
  {x=rand()%16;
   settextstyle(1,0,4);
   setcolor(x);
    outtextxy(170,350,"Play Or be Played");
   delay(200);
  }

*/
#include<iostream.h>
#include<conio.h>
#include<iomanip.h>
#include<process.h>
#include<stdlib.h>
#include<stdio.h>
#include<dos.h>
#include<time.h>
#include<fstream.h>
#include<graphics.h>
#include<ctype.h>

/*Variables that require to be available to all functions
 throughout a session*/
int card,player_score=0,c=0,dealer_score=0;
float win=0,lose=0,game=0;
long unsigned int chips=5000,bets,extra_bet;
char choice;
int face[4]={75,81,74,10};//Face card Letters using ASCII(K=75,Q=81,J=74)

//prototypes
void start_game();
void player_hand();
void dealer_reveal();
char suit();
void check(int&);

//It all starts here!!!

void main()
{//Epic Loading screen

int driver=DETECT,mode,i,j,x;
 initgraph(&driver,&mode,"C:\\Turboc3\\BGI");
cleardevice();

settextstyle(0,0,2);
setcolor(2);
outtextxy(200,200,"UniQomp Studios");
delay(800);
cleardevice();

setcolor(3);
outtextxy(220,200,"nthacks.com");
delay(800);
cleardevice();

setcolor(4);
outtextxy(200,200,"LOL Media Group");
delay(800);

cleardevice();
 setcolor(4);
 settextstyle(1,0,3);
 outtextxy(250,50,"LOADING");

 for(i=100;i<=500;++i)
  {for(j=100;j<=110;++j)
  if(i%2==1)
  putpixel(i,j,10);
  else
  putpixel(i,j,2);
  delay(4);
  }

//Sweet Graphics!!

menu:cleardevice();
int menu;

setbkcolor(0);
setcolor(15);
  settextstyle(4,0,5);
  outtextxy(150,10,"Ultimate BlackJack");

delay(500);

//Multicolored chips

 settextstyle(0,0,0);
 setcolor(15);
  setfillstyle(INTERLEAVE_FILL,2);
  fillellipse(100,100,30,30);
  setcolor(15);
  setcolor(15);
  outtextxy(95, 96, "1$");
  ellipse(100,100,0,360,20,20);

  setcolor(15);
  setfillstyle(INTERLEAVE_FILL,5);
  fillellipse(100,170,30,30);
  setcolor(15);
  setcolor(15);
  outtextxy(90, 166, "25$");
  ellipse(100,170,0,360,20,20);


  setcolor(15);
  setfillstyle(INTERLEAVE_FILL,1);
  fillellipse(100,240,30,30);
  setcolor(15);
  setcolor(15);
  outtextxy(90, 236, "50$");
  ellipse(100,240,0,360,20,20);

  setcolor(15);
  setfillstyle(INTERLEAVE_FILL,3);
  fillellipse(510,100,30,30);
  setcolor(15);
  setcolor(15);
  outtextxy(496, 96, "100$");
  ellipse(510,100,0,360,20,20);

setcolor(15);
  setfillstyle(INTERLEAVE_FILL,9);
  fillellipse(510,170,30,30);
  setcolor(15);
  setcolor(15);
  outtextxy(496, 166, "250$");
  ellipse(510,170,0,360,20,20);

  setcolor(15);
  setfillstyle(INTERLEAVE_FILL,4);
  fillellipse(510,240,30,30);
  setcolor(15);
  setcolor(15);
  outtextxy(496, 236, "500$");
  ellipse(510,240,0,360,20,20);


 //Main Menu 
  
  settextstyle(1,0,4);
  setcolor(4);
  outtextxy(200,80,"1.Start Game");
  setcolor(2);
  outtextxy(200,120,"2.How to Play");
  setcolor(5);
  outtextxy(200,160,"3.Credits");
  setcolor(6);
  outtextxy(200,200,"4.Stats");
  setcolor(14);
  outtextxy(200,240,"5.Exit");

delay(500);
  setcolor(10);
    outtextxy(170,350,"Play Or be Played");


setcolor(15);
settextstyle(2,0,0);
outtextxy(160,450,"Copyright,2013. A Uniqomp Production. All Rights Reserved");

while(!kbhit())
{x=rand()%16;
settextstyle(1,0,4);
setcolor(x);
    outtextxy(170,350,"Play Or be Played");
delay(200);
}

menu=getch();
check(menu);

//Game Begins
if(menu=='1')
	{clrscr();
	cleardevice();
	 cout<<"You start with "<<chips<<"$ in chips.Go Ahead and Make your fortune!!";
	delay(2100);
	start_game();
	goto menu;
	}

//List of rules
else if(menu=='2')
{clrscr();
cleardevice();
setcolor(2);
settextstyle(0,0,2);
outtextxy(60,1,"Rules of BlackJack:Beat The Dealer");
settextstyle(2,0,5);
outtextxy(1,40,"1.The rules are very simple.You start with an initial account of 5000$.");
outtextxy(1,60,"2.On starting the game you must enter the amount of money you want to bet.");
outtextxy(1,80,"3.You will be given 2 cards drawn at random.The sum of the numerical value held");
outtextxy(20,90,"by the cards is your score.");
outtextxy(1,110,"4.Ace holds a value of 1 or 11. King,Queen and Jack hold a value of 10.The");
outtextxy(20,120,"other cards hold the same numerical value.");
outtextxy(1,140,"5.The aim is to get a score LESSER THAN OR EQUAL TO 21.Suits have NO MEANING.");
outtextxy(1,160,"6.You can either choose to hit(draw another card) or stand(conclude your hand)");
outtextxy(20,170,"depending on your points.");
outtextxy(1,190,"7.If you overshoot 21,you lose your bet.If you get a 21 with 2 cards:BLACKJACK!!");
outtextxy(20,200,"If you decide to stand,the dealer's round begins.");
outtextxy(1,220,"8.The dealer has to keep hitting until he reaches a score equal to or greater");
outtextxy(20,230,"than 17.If the dealer overshoots,you have a MONKEY and double your bet.");
outtextxy(1,250,"9.The one with more points WINS!!.Happy Gambling!!");

setcolor(15);
settextstyle(2,0,0);
outtextxy(160,450,"Copyright,2013. A UniQomp Production. All Rights Reserved");

while(!kbhit())
{x=rand()%16;
settextstyle(1,0,3);
setcolor(x);
	outtextxy(40,300,"Press any key to return to the main menu");
delay(200);
}

getch();
goto menu;
}

//Credits page
else if(menu=='3')
{clrscr();
cleardevice();
settextstyle(3,0,3);
setcolor(2);
outtextxy(250,1,"Credits");
settextstyle(2,0,7);
setcolor(3);
outtextxy(1,40,"Concept & Design");
outtextxy(1,60,"Ujjwal Pasupulety");
setcolor(6);
outtextxy(1,90,"Graphics & Visuals");
outtextxy(1,110,"Ujjwal Pasupulety");
setcolor(2);
outtextxy(1,140,"A.I. Infrastructure");
outtextxy(1,160,"Ujjwal Pasupulety");
setcolor(4);
outtextxy(1,190,"U.I. & Game Mechanics");
outtextxy(1,210,"Ujjwal Pasupulety");
setcolor(5);
outtextxy(300,40,"BETA Testers");
outtextxy(300,60,"Nischal Tonthanahal");
outtextxy(300,80,"Idris Shariff");
outtextxy(300,100,"Akhil T Srinath");
setcolor(14);
outtextxy(300,130,"Debugging & Improvisation");
outtextxy(300,150,"Nischal Tonthanahal");
outtextxy(300,170,"Nishanth");
setcolor(15);
outtextxy(1,300,"Rules of the game taken from www.blackjack.info");
settextstyle(2,0,0);
outtextxy(160,450,"Copyright,2013. A UniQomp Production. All Rights Reserved");

while(!kbhit())
{x=rand()%16;
settextstyle(1,0,3);
setcolor(x);
    outtextxy(40,350,"Press any key to return to the main menu");
delay(200);
}
 getch();
 goto menu;
}

//Stats screen
else if(menu=='4')
{clrscr();
cleardevice();
float draw=game-(win+lose);
float deal_adv=((lose+(draw)/2)/game)*100;
float play_adv=((win+(draw)/2)/game)*100;

setcolor(5);
settextstyle(0,0,3);
outtextxy(260,1,"Stats");

cout<<"\n\n\nGames Played:"<<game;
cout<<"\nGames Won:"<<win;
cout<<"\nGames Lost:"<<lose;
cout<<"\nGames Drawn:"<<draw;
cout<<"\nPlayer adavntage:"<<play_adv<<"%";
cout<<"\nDealer adavntage:"<<deal_adv<<"%";

if(play_adv>deal_adv)
cout<<"\nYour luck is pretty strong today!!";
else if(play_adv<deal_adv)
cout<<"\nWell,You've heard the saying"<<"\"The House Always Wins!!\"";
else if(play_adv==deal_adv)
cout<<"\nEqual Odds?? Not for long!!";

setcolor(15);
settextstyle(2,0,0);
outtextxy(160,450,"Copyright,2013. A UniQomp Production. All Rights Reserved");

while(!kbhit())
{x=rand()%16;
settextstyle(1,0,3);
setcolor(x);
     outtextxy(40,300,"\nPress any key to return to the main menu");
delay(200);
}
 getch();
 goto menu;
}

//EXIT
else if(menu=='5')
{clrscr();
cleardevice();
  initgraph(&driver,&mode,"C:\\Turboc3\\BGI");

settextstyle(1,0,3);
 setcolor(5);
 outtextxy(240,50,"GOOD BYE");

 for(i=100;i<=500;++i)
  {for(j=100;j<=110;++j)
  if(i%2==1)
  putpixel(i,j,10);
  else
  putpixel(i,j,2);
  delay(4);
  }
outtextxy(211,120,"Have a Nice Day");
delay(500);
closegraph();
exit(0);

}

//In case our user doesn't know his numbers
else
{clrscr();
cleardevice();
settextstyle(1,0,1);
outtextxy(150,200,"Wrong choice.Please enter from 1 to 4");
 delay(1000);
 goto menu;
}
closegraph();
getch();

}

//Game Starts Here

void start_game()
{
start:
++game;
clrscr();
cleardevice();
int j,x,i;
char ch,bet_again;
//A simple global counter keeps track of the number of games
cout<<"Game:"<<game;
cout<<"\nPlace your bets(must be lesser than/equal to chips:"<<chips<<")\n";
bet:
cin>>bets;  //Placing BETS!!
if(bets>chips)
	{cout<<"\nYou must enter a VALID value lesser than your chip amount"<<"("<<chips<<")";
	goto bet;
	}

else
{//Loading Screen......delay loops add the element of suspense:)
clrscr();
cleardevice();
cout<<"Clearing Table\n";
	for(j=0;j<4;++j)
	{delay(100);
	cout<<(char)3<<" ";
	}
delay(250);

clrscr();
cleardevice();
cout<<"Placing Bets\n";
	for(j=0;j<4;++j)
	{delay(100);
	cout<<(char)4<<" ";
	}
delay(250);

clrscr();
cleardevice();
cout<<"Shuffling deck\n";
	for(j=0;j<4;++j)
	{delay(100);
	cout<<(char)5<<" ";
	}
delay(250);

clrscr();
cleardevice();
cout<<"Starting Game\n";
	for(j=0;j<4;++j)
	{delay(100);
	cout<<(char)6<<" ";
	}
delay(250);

//Beginning Call for Player round
clrscr();
cleardevice();
cout<<"Press any key to start the Player's Hand";
       getch();
       player_hand();

       
	   //It's Natural for anyone to increase their bets with a good hand
	   if(player_score>=19 && player_score<21)
       {again:cout<<"\n\nYour hand is pretty strong"<<"\nWould you like to increase your bet?(Y/N)";
       bet_again=getch();
	 if(bet_again=='y'||bet_again=='Y')
	 {repeat:cout<<"\nPlace your extra bets\n";
	 cin>>extra_bet;
		if(extra_bet>chips)
		{cout<<"\nPlese Enter a Valid Choice";
		delay(200);
		goto repeat;
		}

	 bets+=extra_bet;
	 goto next;
	 }
	 else if(bet_again=='n'||bet_again=='N')
	 goto next;

	 else
	 {cout<<"\nPlese Enter a Valid Choice";
		delay(200);
		goto again;
	 }
       }

       
	   //That's a bummer
	   else if(player_score>21)
	{cout<<"\nYour Points:"<<player_score<<"\nYou Lose!!";
	 chips-=bets;
	 ++lose;
	 cout<<"\nYour chips:"<<chips;
	 if(chips==0)
	  goto exit;
	 else
	 goto replay;
	}

       
	   //Now you just got lucky....and DOUBLE YOUR MONEY!!
	   else if(player_score==21)
       {
	   if(c==2)
	   {cout<<"\nBlackJack!!!\n"<<"You Win!!";
	   chips+=bets;
	   ++win;
	   cout<<"\nYour chips:"<<chips;
	   goto replay;
	   }
	   else
	   goto again;

       }

	else
	{
	   next:cout<<"\n\nEnd of Player Hand";

//Beginning call for Dealer Card reveal

	   cout<<"\n\nPress any key to reveal the dealer's cards";
	   getch();
	   dealer_reveal();

	//The best feeling ever
	if(dealer_score>21)
	{cout<<"\nIt's a Monkey!!!"<<"\nYou Win!!";
	 chips+=bets;
	 ++lose;
	 cout<<"\nYour chips:"<<chips;
	 goto replay;
	}

	else
	{
	cout<<"\n\nEnd of Dealer Reveal";
	delay(500);

//Result estimator

if(player_score>dealer_score)
	{cout<<"\nYou Win!!";
	 chips+=bets;
	 ++win;
	}

else if(player_score==dealer_score)
	cout<<"\nDraw";

else if(player_score<dealer_score)
	{cout<<"\nThe house wins!! Better Luck Next time.";
	 chips-=bets;
	 cout<<"Your chips:"<<chips<<"\n";
	 ++lose;
	 if(chips==0)
	  goto exit;
	 else
	 goto replay;
	}

cout<<"\nYour chips:"<<chips<<"$";
	exit:
	//When you bet more than you can lose....AND LOSE!!!
	if(chips==0)
	{cout<<"\nYour BROKE!!Better luck next time."
	     <<"\nPress any key to exit";
	 getch();
	 cleardevice();
	 settextstyle(1,0,3);
	 setcolor(10);
	 outtextxy(240,50,"GOOD BYE");

	 for(i=100;i<=500;++i)
	  {for(j=100;j<=110;++j)
	  if(i%2==1)
	  putpixel(i,j,10);
	  else
	  putpixel(i,j,2);
	  delay(4);
	  }
	  outtextxy(211,120,"Have a Nice Day");
		delay(500);
		closegraph();

	  delay(100);
	 exit(0);
	}

//Replay point

    else
	{replay:delay(500);
	cout<<"\nPlay Again?(Y/N)";
	ch=getch();
	if(ch=='y'||ch=='Y')
	goto start;
	else if(ch=='n'||ch=='N')
	    {cleardevice();

	     settextstyle(1,0,3);
	     setcolor(3);
		 outtextxy(210,50,"Returning To Menu");

		 for(i=100;i<=500;++i)
		  {for(j=100;j<=110;++j)
		  if(i%2==1)
		  putpixel(i,j,10);
		  else
		  putpixel(i,j,2);
		  delay(4);
		  }

		delay(100);
	    goto end;
	    }
	else
	  {cout<<"\nPlease Enter a Valid Choice";
	   delay(200);
	   goto replay;
	  }
	}
end:
}
}
}
}


//Player's HAND BEGINS

void player_hand()
{clrscr();
cleardevice();
int i;
::c=0;
::player_score=0;
cout<<"Player Hand Begins Now\n";

//Random Number Generator....Ensures game isn't rigged
randomize();
second:delay(300);
card=rand()%12;
       if(card==0)
       goto second;
	  else
       {  ++c;
			/*Implicit decision making system
			Decides whether an Ace should be treated as 1 or 11*/
			switch(card)
			{case 1:if(c==1)
				{  card=11;
				   cout<<"A"<<suit()<<" ";
				   player_score+=card;
				   break;
				}
				else
				{  if(player_score+11<=21)
				     {card=11;
				     cout<<"A"<<suit()<<" ";
				     }
				   else
				   cout<<"A"<<suit()<<" ";
				player_score+=card;
				break;
				}

			 case 10:/*Random face value assigned to a value of 10
				   using ASCII values*/
				 i=rand()%4;
				 if(face[i]==10)
				 cout<<10<<suit()<<" ";
				 else
				 cout<<(char)face[i]<<suit()<<" ";
				 player_score+=card;
				 break;

			 case 11:if(c==1)
				   cout<<"A"<<suit()<<" ";
				 else
				{if(player_score+card>21)
				card=1;
				cout<<"A"<<suit()<<" ";
				}
				player_score+=card;
				break;

			default:cout<<card<<suit()<<" ";
				player_score+=card;

			}
	if(c!=2)
	goto second;
       }
delay(400);
//BLACKJACK Confirmation
if(player_score==21)
goto end;
else
goto hit_stand;


hit_stand:cout<<"\nYour Points:"<<player_score<<"\n"<<21-player_score<<" more to win";
	  cout<<"\nWould you like to Hit or Stand?(H/S)";
     choice=getch();
     if(choice=='h'||choice=='H')
     goto next_round;
     else if(choice=='s'||choice=='S')
     goto end;
     else
     {cout<<"\nPlease Enter a Valid Choice";
      delay(200);
      goto hit_stand;
     }


//User can hit as many times desired
next_round:
++c;
cout<<"\n\n";
randomize();
again:card=rand()%12;
       if(card==0)
       goto again;
	  else
       {
			switch(card)
			{case 1:{ if(player_score+11<=21)
				     {card=11;
				     cout<<"A"<<suit()<<" ";
				     }
				   else
				   cout<<"A"<<suit()<<" ";
				}
				player_score+=card;
				break;

			 case 10:i=rand()%4;
				 if(face[i]==10)
				 cout<<10<<suit()<<" ";
				 else
				 cout<<(char)face[i]<<suit()<<" ";
				 player_score+=card;
				 break;


			 case 11:{if(player_score+card>21)
					{card=1;
					cout<<"A"<<suit()<<" ";
					}
				  else
				  cout<<"A"<<suit()<<" ";
				}
				player_score+=card;
				break;

			default:cout<<card<<suit()<<" ";
				player_score+=card;

			}
       if(player_score>21)
	goto end;

       else if(player_score==21)
       {cout<<"\nYour Points:"<<player_score;
       goto end;
       }
	else
	goto hit_stand;
       }
end:
}

//Dealer Card Reveal

void dealer_reveal()
{clrscr();
cleardevice();
int cnt=0,i,prevdealer_score,hit=0;
::dealer_score=0;
cout<<"Dealer's Cards Revealing Now\n";
randomize();
second:delay(300);
card=rand()%12;
       if(card==0)
       goto second;
	  else
       {  ++cnt;
			//Ace can be treated as 1 or 11 implicitly
			switch(card)
			{case 1:if(c==1)
				{  card=11;
				   cout<<"A"<<suit()<<" ";
				   dealer_score+=card;
				   break;
				}
				else
				{  if(dealer_score+11<=21)
				     {card=11;
				     cout<<"A"<<suit()<<" ";
				     }
				   else
				   cout<<"A"<<suit()<<" ";
				dealer_score+=card;
				break;
				}

			 case 10:i=rand()%4;
				 if(face[i]==10)
				 cout<<10<<suit()<<" ";
				 else
				 cout<<(char)face[i]<<suit()<<" ";
				 dealer_score+=card;
				 break;

			 case 11:if(c==1)
				   cout<<"A"<<suit()<<" ";
				 else
				{if(dealer_score+card>21)
				card=1;
				cout<<"A"<<suit()<<" ";
				}
				dealer_score+=card;
				break;

			default:cout<<card<<suit()<<" ";
				dealer_score+=card;

			}
	if(cnt!=2)
	goto second;
       }

//Previous score saved.Will be used at the choke point in "dealer_hit"
prevdealer_score=dealer_score;
delay(400);
	if(dealer_score<17)
	{ randomize();
	   test:if(dealer_score<17)
		goto dealer_hit;
		else
		goto game_over;

	}
	else
	    goto game_over;

dealer_hit:
++hit;
cout<<"\n\n";
randomize();
repeat:card=rand()%12;
       if(card==0)
       goto repeat;

       //Choke point:Makes Sure that no two cards drawn are the same
       else if(hit!=1 && card==dealer_score-prevdealer_score)
	  goto repeat;

       else
       {
			switch(card)
			{case 1:{ if(dealer_score+11<=21)
				     {card=11;
				     cout<<"A"<<suit()<<" ";
				     }
				   else
				   cout<<"A"<<suit()<<" ";
				}
				dealer_score+=card;
				cout<<"\nDealer's Points:"<<dealer_score<<"\n";
				break;

			 case 10:i=rand()%4;
				 if(face[i]==10)
				 cout<<10<<suit()<<" ";
				 else
				 cout<<(char)face[i]<<suit()<<" ";
				 dealer_score+=card;
				 cout<<"\nDealer's Points:"<<dealer_score<<"\n";
				 break;


			 case 11:{if(dealer_score+card>21)
					{card=1;
					cout<<"A"<<suit()<<" ";
					}
				  else
				  cout<<"A"<<suit()<<" ";
				}
				dealer_score+=card;
				cout<<"\nDealer's Points:"<<dealer_score<<"\n";
				break;

			default:cout<<card<<suit()<<" ";
				dealer_score+=card;
				cout<<"\nDealer's Points:"<<dealer_score<<"\n";

			}
	    goto test;
	game_over:
	}
}

//Assignes a random suit to a card
char suit()
{int n;
randomize();
again:
n=rand() %7;
if(n==3||n==4||n==5||n==6)
	return n;
	else
	goto again;
}

//Checks Validity of Integer Inputs
void check(int &x)
{
	while(!cin)
	{	cin.clear();
		cin.ignore(90,'\n');
	cout<<"Invalid choice.Please input again\n";
	cin>>x;
	}
}