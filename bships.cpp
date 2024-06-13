#include <iostream.h>
#include <conio.h>
#include <process.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int bships_score=0;

void inputfield();  //to input values into battlefield
void printfield();  //to print field
void printships();  //to print ships
void place(int);    //to position ships according to loaction entered by user
void bomb();        //to locate and bomb ships

char a[11][11],     //Battlefield 2D Array
     one[11][11],   //Battleship1 2D Array
     two[11][11],   //Battleship2 2D Array
     three[11][11], //Battleship3 2D Array
     user[11][11],  //User Battlefield Array
     comp[11][11],  //Computer Battlefield Array
     empty[11][11]; //Empty field to display

char x=254, tl=201, tr=187, bl=200, br=188, v=186, h=205;
  /*
  x: special character
  special charcters to display battlefield:
  tl: top left
  tr: top right
  bl: bottom left
  br: bottom right
  v: vertical
  h: horizontal
  */
int y, //size of battlefield
    lx1, ly1,  //variables to save values of battleship location
    lx2, ly2,
    lx3, ly3,
    g=0, q=0,
    w=0;

int mainships()
{
  clrscr();
  textcolor(LIGHTBLUE);
  int i, j, flag=0;

  cout<<endl<<endl<<"WELCOME TO BATTLESHIPS"<<endl<<endl;

  textcolor(GREEN);
  l:
  cprintf("Enter field size(5-9):");

  cout<<endl;
  cin>>y;
  if(y==0)
    exit(0);
  if(y<5 || y>9)
  {
    cout<<"invalid size";
    goto l;
  }

  inputfield();      //to create field for y(field size)
  for(i=0; i<=y+1; i++)
    for(j=0; j<=y+1; j++)
      empty[i][j]=a[i][j];  //assigning values to the empty battlefield
			     //(empty array will only consist of x characters)

  printfield();
  printships();

  place(flag);
  for(i=0; i<=y+1; i++)
    for(j=0; j<=y+1; j++)
      user[i][j]=a[i][j];  //assigning values to the user's battlefield

  flag=1;         //flag=1 for the computer's battlefield placements
  inputfield();
  place(flag);

  for(i=0; i<=y+1; i++)
    for(j=0; j<=y+1; j++)
      comp[i][j]=a[i][j];  //assigning values to the computer's battlefield

  for(i=0; i<=y+1; i++)
    for(j=0; j<=y+1; j++)
      a[i][j]=user[i][j]; //assigning values of user's battlefield to print

  bomb();
  getch();
  return (bships_score);

}

void inputfield()
{
  int i, j;
  char c;

  clrscr();

  //inputting characters in battleship matrices
  for(i=0; i<y-2; i++)  //Battleship 1
    for(j=0; j<y-2; j++)
      if(j==y-3 || i==y-3)
	one[i][j]='p';
      else
	one[i][j]=' ';
  one[y-3][y-3]='*';

  for(i=0; i<y-1; i++)  //Battleship 2
   two[0][i]='q';
  two[0][0]='*';

  for(i=0; i<y-2; i++)  //Battleship 3
   three[0][i]='r';
  three[0][0]='*';


  //Inputting characters in Battlefield matrix
  for(i=0; i<=y+1; i++)
    for(j=0; j<=y+1; j++)
     if(i==0 || i==y+1)
       a[i][j]=h;
     else
       if(j==0 || j==y+1)
	a[i][j]=v;
       else
	a[i][j]='-';

  a[0][0]=tl;     //assigning the special characters to create a box
  a[0][y+1]=tr;
  a[y+1][0]=bl;
  a[y+1][y+1]=br;

  getch();
}

void printships()   //To print battleships
{
  int i, j;

  cprintf("Following are your battleships:");
  cout<<endl<<endl;

  for(i=0; i<y-3; i++) //to create appropriate space according to size of ship
   cout<<" ";
  cout<<"1       ";
  for(i=0; i<y/2-1; i++)
   cout<<" ";
  cout<<"2       ";
  for(i=0; i<y-2; i++)
   cout<<" ";
  cout<<"3";

  cout<<endl<<endl;

  for(i=0; i<y-2; i++)  //printing Battleship1
   {
    for(j=0; j<y-2; j++)
      if(one[i][j]=='p')
       cout<<x;
      else
       cout<<one[i][j];
    if(i==0)
     {
       cout<<"       ";   //printing Battleship 2
       for(j=0; j<y-1; j++)
	if(two[i][j]=='q')
	cout<<x;
	else
	cout<<two[i][j];

       cout<<"       ";   //printing Battleship 3
       for(j=0; j<y-2; j++)
	if(three[i][j]=='r')
	cout<<x;
	else
	cout<<three[i][j];     }
    cout<<endl;
   }
  cout<<endl;

}

void printfield() //to print the battle field
{
  int i,j;

  cout<<endl<<"    ";
  for(i=65; i<64+y+1; i++) //printing coordinates
    cout<<char(i)<<" ";
  cout<<endl;
  for(i=0; i<=y+1; i++)  //printing field
   {
    if(i!=0 && i!=y+1)  //accomodating space for coordinates
     cout<<i<<" ";
    else
     cout<<"  ";
    for(j=0; j<=y+1; j++)
     {
      if((i==0 || i==y+1) && j!=y+1 )
	cout<<a[i][j]<<h;
      else
       {
	if(a[i][j]=='p' || a[i][j]=='q' || a[i][j]=='r')
	 cout<<x<<" ";
	else
	 cout<<a[i][j]<<" ";
       }
     }
    cout<<endl;
   }
  getch();
}

void place(int flag) //to place the battleships in the field
{
  int i, j, sno=9, ly, lx, k, l, n, v, count1=0, count2=0, count3=0;
  char cx, x=254;

  input:
  clrscr();
  if(flag==0)    //flag=0 indicates that it is the user placing ships
  {
   printfield();
   printships();
  }

  if(flag)      //battle ships of computer matrix are placed one by one
  {
    if(sno==9)
     sno=1;
    else
     if(sno==1)
       sno=2;
     else
      if(sno==2)
       sno=3;
      else
       if(sno==3)
	sno=0;
  }
  else
  {
    textcolor(LIGHTBLUE);
    cprintf("Enter Battleship number to place or press 0 to finish (identified by '*'):");
     textcolor(WHITE);
    cin>>sno;
    if(sno==0)
       goto finish;
    textcolor(LIGHTBLUE);
    cprintf("Enter location to place ship (eg: H 9)");
    cout<<endl;
    textcolor(WHITE);
    cin>>cx>>ly;

    cx=tolower(cx);     //to convert alphabet to numeric location
    lx=cx;
    lx-=96;
  }

  if(sno==0)   //to finsh placing ships
   goto finish;

  if(flag)    //inputing the computer's field randomly
  {
    flaginput:
    randomize();

    if(sno==1)   //randomly placing first battleship
    {
      switch(y)
      {
	case 4: n=2;  break;  //values of location(n) according to y
	case 5: n=3;  break;
	case 6: n=3;  break;
	case 7: n=4;  break;
	case 8: n=4;  break;
	case 9: n=5;  break;
      }
      lx=random(n)+((y/2)+1);
      ly=y-1;
    }

    if(sno==2)  //randomly placing second battleship
    {
      lx=random(2)+1;
      ly=random(y)+1;
      v=ly;
    }

    if(sno==3)  //randomly placing third battleship
    {
      lx=random(3)+1;
      ly=random(y)+1;
      while(ly==v)
       ly=random(y)+1;
    } //end of computer field placements

    exit:
    getch();

  }

  switch(sno)
  {
    case  1: if(flag==0 && (lx<=y-3 || ly<=y-3 || a[ly][lx]==x
		||a[ly][lx]=='q' || a[ly][lx]=='r'))//to check if location is valid
	      {
		cout<<"Invalid Location"<<endl;
		getch();
		goto input;
	      }
	     if(flag==0)  //to delete the old ship
	     {
	       if(count1)
		{
		  for(i=ly1-(y-3); i<=ly1; i++)
		  {
		   for(j=lx1-(y-3); j<=lx1; j++)
		   {
		     if(a[i][j]!='q' && a[ly3][j]!='r')
		      a[i][j]='-';
		   }
		  }
		}
	     }
	     for(i=ly-(y-3), k=0; i<=ly; i++, k++)    //to place the ship
		  {
		    for(j=lx-(y-3), l=0; j<=lx; j++, l++)
		     {
		       if(one[k][l]==' ')
			 continue;
		       if(one[k][l]=='*')
			{
			 a[i][j]=x;
			 continue;
			}
		       a[i][j]=one[k][l];
		     }
		  }
	     lx1=lx; ly1=ly;
	     count1=1;
	     goto input;

    case  2: if(flag==0 && (a[ly][lx]=='p'||a[ly][lx]=='r'||a[ly][lx]==x ||lx>y-3))//to check if location is valid
	      {
		cout<<"Invalid Location"<<endl;
		getch();
		goto input;
	      }

	     if(flag==0)
	     {
	       if(count2)    //to delete the old ship
	       for(j=lx2; j<lx+y-1; j++)
		if(a[ly2][j]!='p' && a[ly2][j]!='r')
		 a[ly2][j]='-';
	     }

	     for(j=lx, k=0; j<lx+y-1; j++, k++)  //placing the ship
	      if(a[ly][j]!='p' && a[ly][j]!='r')
		a[ly][j]=two[0][k];

	     if(a[ly][j]!='p' && a[ly][j]!='r')
	       a[ly][lx]='q';

	     count2=1;
	     lx2=lx; ly2=ly;
	     goto input;

    case  3: if(flag==0 && (a[ly][lx]==x || a[ly][lx]=='p' || a[ly][lx]=='q' || lx>y-2))//to check if location is valid
	      {
		cout<<"Invalid Location"<<endl;
		getch();
		goto input;
	      }

	     if(flag==0)
	     {
	       if(count3)    //erasing old ship
	       for(j=lx3; j<lx3+y-2; j++)
		a[ly3][j]='-';
	     }

	     for(j=lx, k=0; j<lx+y-2; j++, k++)   //to place the ship
	      if(a[ly][j]!='p' && a[ly][j]!='q')
		 a[ly][j]=three[0][k];

	     if(a[ly][j]!='p' && a[ly][j]!='q')
	       a[ly][lx]='r';

	     lx3=lx; ly3=ly;
	     count3=1;
	     goto input;

    default: cout<<"Invalid Battleship Number"<<endl;
	     getch();
	     goto input;
  }
   finish: getch();

}

void bomb()
{
 char c;
 int score1=0, score2=0, z,n,i,j,flag=0, flag2=0;

 l:
 flag=0; flag2=0;
 clrscr();
 for (i=0;i<=y+1;i++)
  for (j=0;j<=y+1;j++)
   a[i][j]=user[i][j];

 textcolor(LIGHTBLUE);
 cprintf("Your field:");    //printing user's field
 textcolor(WHITE);
 printfield();

 for (i=0;i<=y+1;i++)
  for (j=0;j<=y+1;j++)
   a[i][j]=empty[i][j];

 textcolor(LIGHTBLUE);
 cprintf("Computer's field:");   //printing computer's field
 textcolor(WHITE);
 printfield();

  for (i=0;i<=y+1;i++)
  for (j=0;j<=y+1;j++)
   a[i][j]=comp[i][j];

 textcolor(LIGHTBLUE);
 cprintf("Your score= ");
 cout<<score1;


 cprintf("   Computer's score= ");
 cout<<score2<<endl;
 textcolor(WHITE);
 cout<<"Enter position to bomb or press 0 to exit: "; //inputting location to bomb
   cin>>c;
   if(c=='0')
      exit(0);
   cin>>n;

   toupper(c);  //to convert alphabet to numeric location
    z=c;
    z-=96;
 if(z<0 || z>y || n<0 || n>y)
  {
    cout<<"Invalid option1";
    getch();
    goto l;
  }

  if (comp[n][z]!='-') //to check if battleship is present at location
  {
    score1+=10;
    cout<<"You got em!"<<endl;
    getch();
    empty[n][z]='#';
    comp[n][z]='-';
    }
  else
  {
    cout<<"Missed :(";
    score1-=5;
    getch();
  }

  flag=0;
  for (i=1;i<=y;i++) //to check if user has won (comp field is empty)
  {
    for (j=1;j<=y;j++)
     if (comp[i][j]!='-')
      {
	flag=1;
	break;
      }
    if(flag)
     break;
  }

  if(flag==0)
  {
    clrscr();
    cout<<endl<<endl<<endl<<"Winner!"<<endl<<endl;
    cout<<"Your Score: "<<score1<<"  Computer Score: "<<score2;
    bships_score=score1;
    getch();
    goto endd;

  }

  //computer bombing user's field randomly
  z=random(y)+1;
  n=random(y)+1;
  getch();

  if (user[z][n]!='-')//to check if battleship is present at location
  {
    score2+=10;
    user[z][n]='#';
  }
  else
    score2-=5;

  flag2=0;
  for (i=1;i<=y;i++)   //to check if computer has won (user's field is empty)
  {
    for (j=1;j<=y;j++)
     if (user[i][j]!='-'&&user[i][j]!='#')
      {
	flag2=1;
	break;
      }
    if(flag2)
     break;

  }
  if (flag2)
   goto l;
  else
  {
    clrscr();
    cout<<endl<<endl<<endl<<"You lost. Better luck next time!"<<endl<<endl;
    cout<<"Your Score: "<<score1<<"  Computer Score: "<<score2;
    bships_score=score1;
    getch();

  }
  endd:
 getch();
}
