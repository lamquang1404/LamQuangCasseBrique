/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>
using namespace std;

/* retourne 0 si aucune touche n'est appuyée, 
 * sinon retourne le code ASCII de la touche */
int read_keybord();

/******************************************************************************/
#define H 20
#define L 31
int barreA=(L/2)-5,barreD=(L/2)+5;
char screen[H][L];

void screen_display() {
  system("clear");
  for (int i=0; i<H; i++) {
    for (int j=0; j<L; j++) {
      cout << screen[i][j];
    }
    cout << endl;
  }
}

void clear_screen()
{
  for (int i=0; i<H; i++)
   
    for (int j=0; j<L; j++)
      screen[i][j]=' ';
}

void bord()
{
  for(int i=0; i<H; i++)
    {
      for(int j=0; j<L; j++)
	{
	  if( i==0 || j==0 || j==L-1)
	    {
	      screen[i][j] = '*'; //screen
	    }
	  else 
	    {
	      screen[i][j] = ' ';
	    }
	  
	  if (i==H-2 && j>barreA && j<barreD)
	    {
	      screen[i][j]='='; //barre
	    }
	}
    }
}


/******************************************************************************/
int x=17,y=15;
bool mx=true,my=true;
void update_game(int key)
{
 
  //mouvenment de la barre
  if (key=='a')
    {
      if (barreA>=1)
	{
	  barreA=barreA-2;
	  barreD=barreD-2;
	}
    }
  if (key=='d')
    {
      if (barreD<L-1)
	{
	  barreA=barreA+2;
	  barreD=barreD+2;
	}
    }
 
}



void ball()
{
  screen[x][y]='o';
  if (mx){
    x++;
    if (x == H-2)
      mx = false;
  }
  if (mx==false){
     x--;
     if (x == 1)
       mx = true;
  }
  if (my){
    y++;
    if (y == L-1)
      my = false;
  }
  if (my==false){
    y--;
    if (y == 1)
      my = true;
  }


}
/******************************************************************************/


/******************************************************************************/

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

int read_keybord() {
  int key;
  if (kbhit())
    key = getc(stdin);
  else
    key = 0;
  return key;
}

/******************************************************************************/
/******************************************************************************/
int main()
{
  int key;
  do {
    key = read_keybord();
    clear_screen();
    bord();
    ball(); 
    update_game(key);
    screen_display();
    usleep(100 * 1000);
  } while (key != 'q');
}
