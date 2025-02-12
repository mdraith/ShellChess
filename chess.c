// Shell Chess 1.00

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

clock_t one,two;
FILE *infile,*outfile;
short ply,mate,k,cst,pvfollow,rnd,king1,king2,endtime,side,fx,fy;
short kx,ky,max1,max2,ep,depth,maxdepth,book,cntdepth;
short y,ok,x,best,material,value,mat1,mat2,ml,alpha,extension;
short beta,cnt,z,i,j,draw,view,eval,take,alrm;
char temp;
unsigned long hsh,hashside,maxtime,nodes,xnodes,movetime;
char board[121]={0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
					8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
					8, 4, 2, 3, 5, 6, 3, 2, 4, 8,
					8, 1, 1, 1, 1, 1, 1, 1, 1, 8,
					8, 7, 7, 7, 7, 7, 7, 7, 7, 8,
					8, 7, 7, 7, 7, 7, 7, 7, 7, 8,
					8, 7, 7, 7, 7, 7, 7, 7, 7, 8,
					8, 7, 7, 7, 7, 7, 7, 7, 7, 8,
					8, 9, 9, 9, 9, 9, 9, 9, 9, 8,
					8,12,10,11,13,14,11,10,12, 8,
					8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
					8, 8, 8, 8, 8, 8, 8, 8, 8, 8
				};
char fw[121]={0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		 		 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				 8, 0, 0, 0, 0, 0, 0, 0, 0, 8,
				 8, 0, 1, 1, 1, 1, 1, 1, 0, 8,
				 8, 0, 1, 3, 3, 3, 3, 1, 0, 8,
				 8, 0, 1, 3, 5, 5, 3, 1, 0, 8,
				 8, 0, 1, 3, 5, 5, 3, 1, 0, 8,
				 8, 0, 1, 3, 3, 3, 3, 1, 0, 8,
				 8, 0, 1, 1, 1, 1, 1, 1, 0, 8,
				 8, 0, 0, 0, 0, 0, 0, 0, 0, 8,
				 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
			 };
char pe1[121]={0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				  8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				  8, 0, 0, 0, 0, 0, 0, 0, 0, 8,
				  8, 5, 5, 5, 5, 5, 5, 5, 5, 8,
				  8, 4, 4, 4, 4, 4, 4, 4, 4, 8,
				  8, 3, 3, 3, 3, 3, 3, 3, 3, 8,
				  8, 2, 2, 2, 2, 2, 2, 2, 2, 8,
				  8, 1, 1, 1, 1, 1, 1, 1, 1, 8,
				  8, 0, 0, 0, 0, 0, 0, 0, 0, 8,
				  8, 0, 0, 0, 0, 0, 0, 0, 0, 8,
				  8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				  8, 8, 8, 8, 8, 8, 8, 8, 8, 8
			  };
char pe2[121]={0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				  8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				  8, 0, 0, 0, 0, 0, 0, 0, 0, 8,
				  8, 0, 0, 0, 0, 0, 0, 0, 0, 8,
				  8, 1, 1, 1, 1, 1, 1, 1, 1, 8,
				  8, 2, 2, 2, 2, 2, 2, 2, 2, 8,
				  8, 3, 3, 3, 3, 3, 3, 3, 3, 8,
				  8, 4, 4, 4, 4, 4, 4, 4, 4, 8,
				  8, 5, 5, 5, 5, 5, 5, 5, 5, 8,
				  8, 0, 0, 0, 0, 0, 0, 0, 0, 8,
				  8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				  8, 8, 8, 8, 8, 8, 8, 8, 8, 8
			  };
char pt1[121]={0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				  8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				  8, 0, 0, 0, 0, 0, 0, 0, 0, 8,
				  8, 0, 1, 2, 7, 7, 2, 1, 0, 8,
				  8, 0, 0, 1, 6, 6, 1, 0, 0, 8,
				  8, 0, 0, 0, 5, 5, 0, 0, 0, 8,
				  8, 0, 0, 0, 4, 4, 0, 0, 0, 8,
				  8, 0, 0, 0, 3, 3, 0, 0, 0, 8,
				  8, 0, 0, 0, 0, 0, 0, 0, 0, 8,
				  8, 0, 0, 0, 0, 0, 0, 0, 0, 8,
				  8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				  8, 8, 8, 8, 8, 8, 8, 8, 8, 8
			  };
char pt2[121]={0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				  8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				  8, 0, 0, 0, 0, 0, 0, 0, 0, 8,
				  8, 0, 0, 0, 0, 0, 0, 0, 0, 8,
				  8, 0, 0, 0, 3, 3, 0, 0, 0, 8,
				  8, 0, 0, 0, 4, 4, 0, 0, 0, 8,
				  8, 0, 0, 0, 5, 5, 0, 0, 0, 8,
				  8, 0, 0, 1, 6, 6, 1, 0, 0, 8,
				  8, 0, 1, 2, 7, 7, 2, 1, 0, 8,
				  8, 0, 0, 0, 0, 0, 0, 0, 0, 8,
				  8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				  8, 8, 8, 8, 8, 8, 8, 8, 8, 8
			  };
short piecevalue[15]={0,100,325,325,500,900,10000,0,0,100,325,325,500,900,10000};
char enpassant[300],movefrom[1000],moveto[1000],ki[100],kj[100],ki2[100],kj2[100],randtab[100],bi[300],bj[300];
char fs1[17],fs2[17],fs[121],pvi[10][10],pvj[10][10],promotion[300],fj[100],mlfrom[300],mlto[300],castle[300];
char obi[2100],obj[2100],lj[100],ob[43490];
short moveval[1000],counter[100];
unsigned long hashpiece[121][15],hashep[121],hashtable[1000];
char inp[5],filename[41];
const char version[]="Shell Chess 1.00";

void moves();
void xmoves();
void addmove(char* ptr_board_i,char* ptr_board_j);
void xaddmove(char* ptr_board_i,char* ptr_board_j);
void xxaddmove(char* ptr_board_i,char* ptr_board_j);
short nsearch(short alpha,short beta,short depth);
short xsearch(short alpha,short beta);
short evaluate();
void pvfind();
short sort();
void pvupdate(short i,short j);
void makemove(short i,short j);
void backmove(short i,short j);
void xmakemove(short i,short j);
void xbackmove(short i,short j);
short check(short king,short side);
short makematerial();
short opening();
void showboard();
void makehash();
short repetition(short pos);
void switchboard();
void loadgame();
void savegame();
void newgame();

int main(int argc,char *argv[])
{
	printf("\e[2J\e[H%s - Type help for available commands\n\n",version);
	infile=fopen("opening.bok","rb");
	if(infile==NULL)
	{
		printf("File opening.bok not found!\n");
		return 0;
	}
	printf("Reading opening book...\n");
	fread(ob,1,43489,infile);
	fclose(infile);
	showboard();
	srand(time(NULL));
	for(i=1;i<=120;i++)
	{
		if(board[i]!=8)
		{
			for(j=1;j<=14;j++)
			{
				hashpiece[i][j]=rand();
			}
			hashep[i]=rand();
		}
	}
	cst=15;
	maxdepth=99;
	maxtime=10*CLOCKS_PER_SEC;
	book=1;
	rnd=1;
	hashside=rand();
	makehash();
	take=17;
	alrm=1;
	extension=1;
	do
	{
		printf("\n");
		do
		{
			printf("Your move: ");
			scanf("%4s",inp);
			if(!strcmp(inp,"vers"))
			{
				printf("%s - Copyright 2025 by Thomas Starke\n\n",version);
				strcpy(inp,"back");
				continue;
			}
			if(!strcmp(inp,"game"))
			{
				if(ml)
				{
					newgame();
					view=0;
					showboard();
					printf("\n");
				}
				strcpy(inp,"back");
				continue;
			}
			if(!strcmp(inp,"take"))
			{
				do
				{
					printf("Percentage [%d]: ",take);
					scanf("%3lu",&movetime);
					if(movetime<0 || movetime>100)
					{
						if(alrm)
						{
							printf("\a");
						}
						printf("Illegal percentage!\n\n");
					}
				} while(movetime<0 || movetime>100);
				printf("\n");
				take=movetime;
				strcpy(inp,"back");
				continue;
			}
			if(!strcmp(inp,"dpth"))
			{
				do
				{
					printf("Halfmoves [%d]: ",maxdepth);
					scanf("%2lu",&movetime);
					if(movetime<1 || movetime>99)
					{
						if(alrm)
						{
							printf("\a");
						}
						printf("Illegal halfmoves!\n\n");
					}
				} while(movetime<1 || movetime>99);
				printf("\n");
				maxdepth=movetime;
				maxtime=999999999;
				strcpy(inp,"back");
				continue;
			}
			if(!strcmp(inp,"book"))
			{
				book=!book;
				if(book)
				{
					printf("Book is on");
				}
				else
				{
					printf("Book is off");
				}
				printf("\n\n");
				strcpy(inp,"back");
				continue;
			}
			if(!strcmp(inp,"rand"))
			{
				rnd=!rnd;
				if(rnd)
				{
					printf("Random is on");
				}
				else
				{
					printf("Random is off");
				}
				printf("\n\n");
				strcpy(inp,"back");
				continue;
			}
			if(!strcmp(inp,"extn"))
			{
				extension=!extension;
				if(extension)
				{
					printf("Extension is on");
				}
				else
				{
					printf("Extension is off");
				}
				printf("\n\n");
				strcpy(inp,"back");
				continue;
			}
			if(!strcmp(inp,"alrm"))
			{
				alrm=!alrm;
				if(alrm)
				{
					printf("Alarm is on");
				}
				else
				{
					printf("Alarm is off");
				}
				printf("\n\n");
				strcpy(inp,"back");
				continue;
			}
			if(!strcmp(inp,"help"))
			{
				printf("\nEnter the coordinates of your move e.g. e2e4\n");
				printf("alrm - Toggle alarm on/off\n");
				printf("back - Take back a halfmove\n");
				printf("book - Toggle book on/off\n");
				printf("dpth - Enter depth in halfmoves (1-99)\n");
				printf("extn - Toggle extension on/off\n");
				printf("game - Start a new game\n");
				printf("help - Display this information\n");
				printf("load - Load the specified game\n");
				printf("quit - Exit the chess program\n");
				printf("rand - Toggle random on/off\n");
				printf("save - Save the actual game\n");
				printf("side - Let the computer make a move\n");
				printf("take - Enter take percentage (0-100)\n");
				printf("test - Perform a benchmark test\n");
				printf("time - Enter time in seconds (1-9999)\n");
				printf("vers - Display the version number\n");
				printf("\n\n");
				strcpy(inp,"back");
				continue;
			}
			if(!strcmp(inp,"time"))
			{
				do
				{
					printf("Seconds [%lu]: ",maxtime/CLOCKS_PER_SEC);
					scanf("%4lu",&movetime);
					if(movetime<1 || movetime>9999)
					{
						if(alrm)
						{
							printf("\a");
						}
						printf("Illegal seconds!\n\n");
					}
				} while(movetime<1 || movetime>9999);
				printf("\n");
				maxtime=movetime*CLOCKS_PER_SEC;
				maxdepth=99;
				strcpy(inp,"back");
				continue;
			}
			if(!strcmp(inp,"load"))
			{
				printf("Filename: ");
				scanf("%40s",filename);
				if(strlen(filename))
				{
					loadgame();
					if(infile)
					{
						showboard();
						printf("\n");
					}
				}
				strcpy(inp,"back");
				continue;
			}
			if(!strcmp(inp,"save"))
			{
				if(ml)
				{
					printf("Filename: ");
					scanf("%40s",filename);
					if(strlen(filename))
					{
						savegame();
					}
				}
				strcpy(inp,"back");
				continue;
			}
			if(!strcmp(inp,"test"))
			{
				strcpy(filename,"benchmar.gam");
				loadgame();
				if(infile)
				{
					strcpy(inp,"e1g1");
				}
				else
				{
					strcpy(inp,"back");
					continue;
				}
			}
			if(!strcmp(inp,"back"))
			{
				if(ml)
				{
					ply=1;
					x=mlfrom[ml];
					y=mlto[ml];
					backmove(x,y);
					bi[0]=bi[ml];
					bj[0]=bj[ml];
					castle[0]=castle[ml];
					enpassant[0]=enpassant[ml];
					promotion[0]=promotion[ml];
					view=!view;
					showboard();
					printf("\n");
				}
			}
			if(strcmp(inp,"side") && strcmp(inp,"back"))
			{
				if(!strcmp(inp,"quit"))
				{
					return 0;
				}
				x=(inp[0]-95)+(inp[1]-47)*10;
				y=(inp[2]-95)+(inp[3]-47)*10;
				ply=1;
				cnt=0;
				cntdepth=99;
				material=makematerial();
				moves();
				printf("%d\n",cnt);
				ok=0;
				for(z=1;z<=cnt;z++)
				{
					printf("%c%c%c%c ",(char)((movefrom[z]%10)+95),(char)((movefrom[z]/10)+47),(char)((moveto[z]%10)+95),(char)((moveto[z]/10)+47));
					if(x==movefrom[z] && y==moveto[z])
					{
						ply=0;
						makemove(x,y);
						if((side==0 && check(king1,1-side)==0) || (side==1 && check(king2,1-side)==0))
						{
							ok=1;
							if(promotion[ml])
							{
								printf("\n\nPawn promotion (Q)ueen (R)ook (B)ishop K(N)ight: ");
								scanf("%1c",inp);
								printf("\n");
								if(!strcmp(inp,"R") || !strcmp(inp,"r"))
								{
									board[y]--;
								}
								if(!strcmp(inp,"B") || !strcmp(inp,"b"))
								{
									board[y]-=2;
								}
								if(!strcmp(inp,"N") || !strcmp(inp,"n"))
								{
									board[y]-=3;
								}
							}
						}
						else
						{
							backmove(x,y);
						}
					}
				}
				printf("\n");
				if(!ok)
				{
					if(alrm)
					{
						printf("\a");
					}
					printf("Illegal move!\n\n");
				}
			}
		} while((!ok && strcmp(inp,"side")) || !strcmp(inp,"back"));
		if(!strcmp(inp,"side"))
		{
			view=!view;
		}
		showboard();
		if(ml)
		{
			if(repetition(ml-1)>1 || ((mat1==0 || mat1==325) && (mat2==0 || mat2==325)) || draw==100)
			{
				if(alrm)
				{
					printf("\a");
				}
				printf("Draw!\n");
				return 0;
			}
		}
		if(maxdepth==99)
		{
			movetime=maxtime;
			movetime+=(float)maxtime*((rand()%30)/100.0);
			movetime-=(float)maxtime*((rand()%30)/100.0);
		}
		else
		{
			movetime=999999999;
		}
		ply=1;
		alpha=-30000;
		beta=30000;
		pvfollow=0;
		best=-32768;
		depth=0;
		nodes=0;
		xnodes=0;
		endtime=0;
		cntdepth=0;
		material=makematerial();
		for(j=0;j<10;j++)
		{
			for(i=0;i<10;i++)
			{
				pvi[i][j]=0;
			}
		}
		for(j=0;j<100;j++)
		{
			ki[j]=0;
			ki2[j]=0;
		}
		if(rnd)
		{
			for(i=1;i<100;i++)
			{
				randtab[i]=rand()%4;
			}
		}
		printf("\nDepth:");
		one=clock();
		movetime+=one;
		if(book && opening())
		{
			best=0;
			cnt=0;
			printf(" book");
		}
		else
		{
			do
			{
				cnt=0;
				depth++;
				lj[depth]=0;
				printf(" %d",depth);
				fflush(stdout);
				value=nsearch(alpha,beta,depth);
				pvfollow=1;
			} while(depth<maxdepth && !endtime && best<29000 && best>-29000);
		}
		two=clock();
		printf("\n");
		if(best==-29998)
		{
			if(alrm)
			{
				printf("\a");
			}
			printf("Checkmate!\n");
			return 0;
		}
		i=pvi[1][1];
		j=pvj[1][1];
		ply=0;
		makemove(i,j);
		printf("\n");
		if(alrm)
		{
			printf("\a");
		}
		printf("My move: %c%c",(char)((i%10)+63),(char)((i/10)+47));
		if(bj[ml]==7)
		{
			printf("-");
		}
		else
		{
			printf("x");
		}
		printf("%c%c",(char)((j%10)+63),(char)((j/10)+47));
		if(side)
		{
			if(check(king1,side))
			{
				printf("+");
			}
		}
		else
		{
			if(check(king2,side))
			{
				printf("+");
			}
		}
		printf("\n");
		printf("%d\n",cnt);
		for(z=1;z<=cnt;z++)
		{
			printf("%c%c%c%c ",(char)((movefrom[z]%10)+95),(char)((movefrom[z]/10)+47),(char)((moveto[z]%10)+95),(char)((moveto[z]/10)+47));
		}
		printf("\n");
		printf("Value: %d\n",best);
		printf("Time: ");
		printf("%1.2f",(double)(two-one)/CLOCKS_PER_SEC);
		printf(" sec\n");
		printf("Nodes: %lu %lu\n",nodes,xnodes);
		showboard();
		if(best==29997)
		{
			if(alrm)
			{
				printf("\a");
			}
			printf("Checkmate!\n");
			return 0;
		}
		if(repetition(ml-1)>1 || ((mat1==0 || mat1==325) && (mat2==0 || mat2==325)) || draw==100)
		{
			if(alrm)
			{
				printf("\a");
			}
			printf("Draw!\n");
			return 0;
		}
	} while(1);
}

void moves()
{
	if(side)
	{
		char* ptr_fs1=fs1+1;
		char* ptr_fs1_max=fs1+max1;
		char* ptr_board_i;
		char* ptr_board_j;
		do
		{
			ptr_board_i=board+(*ptr_fs1);
			switch(*ptr_board_i)
			{
			case 9 :
				ptr_board_j=ptr_board_i-9;
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j==7)
				{
					if(enpassant[ml]==ptr_board_j-board+10)
					{
						addmove(ptr_board_i,ptr_board_j);
					}
				}
				ptr_board_j-=2;
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j==7)
				{
					if(enpassant[ml]==ptr_board_j-board+10)
					{
						addmove(ptr_board_i,ptr_board_j);
					}
				}
				ptr_board_j++;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					if(ptr_board_i-board>81)
					{
						ptr_board_j-=10;
						if(*ptr_board_j==7)
						{
							addmove(ptr_board_i,ptr_board_j);
						}
					}
				}
				break;
			case 10 :
				ptr_board_j=ptr_board_i+8;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=4;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=7;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=2;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=29;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=4;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=7;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=2;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 11 :
				ptr_board_j=ptr_board_i+9;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j+=9;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+11;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j+=11;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-9;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j-=9;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-11;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j-=11;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 12 :
				ptr_board_j=ptr_board_i+1;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j++;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+10;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j+=10;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-1;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j--;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-10;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j-=10;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 13 :
				ptr_board_j=ptr_board_i+9;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j+=9;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+11;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j+=11;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-9;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j-=9;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-11;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j-=11;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+1;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j++;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+10;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j+=10;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-1;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j--;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-10;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j-=10;
				}
				if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 14 :
				ptr_board_j=ptr_board_i+1;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=8;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j++;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j++;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=12;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=8;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j--;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j--;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j<7)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				if(cst&1)
				{
					char i=ptr_board_i-board;
					if(board[i+1]==7)
					{
						if(board[i+2]==7)
						{
							if(check(i,side)==0)
							{
								board[i+1]=14;
								board[i]=7;
								if(check(i+1,side)==0)
								{
									board[i+2]=14;
									board[i+1]=7;
									if(check(i+2,side)==0)
									{
										ptr_board_j=ptr_board_i+2;
										addmove(ptr_board_i,ptr_board_j);
									}
									board[i+2]=7;
									board[i+1]=14;
								}
								board[i+1]=7;
								board[i]=14;
							}
						}
					}
				}
				if(cst&2)
				{
					char i=ptr_board_i-board;
					if(board[i-1]==7)
					{
						if(board[i-2]==7)
						{
							if(board[i-3]==7)
							{
								if(check(i,side)==0)
								{
									board[i-1]=14;
									board[i]=7;
									if(check(i-1,side)==0)
									{
										board[i-2]=14;
										board[i-1]=7;
										if(check(i-2,side)==0)
										{
											ptr_board_j=ptr_board_i-2;
											addmove(ptr_board_i,ptr_board_j);
										}
										board[i-2]=7;
										board[i-1]=14;
									}
									board[i-1]=7;
									board[i]=14;
								}
							}
						}
					}
				}
			}
			ptr_fs1++;
		} while(ptr_fs1<=ptr_fs1_max);
	}
	else
	{
		char* ptr_fs2=fs2+1;
		char* ptr_fs2_max=fs2+max2;
		char* ptr_board_i;
		char* ptr_board_j;
		do
		{
			ptr_board_i=board+(*ptr_fs2);
			switch(*ptr_board_i)
			{
			case 1 :
				ptr_board_j=ptr_board_i+9;
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j==7)
				{
					if(enpassant[ml]==ptr_board_j-board-10)
					{
						addmove(ptr_board_i,ptr_board_j);
					}
				}
				ptr_board_j+=2;
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j==7)
				{
					if(enpassant[ml]==ptr_board_j-board-10)
					{
						addmove(ptr_board_i,ptr_board_j);
					}
				}
				ptr_board_j--;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					if(ptr_board_i-board<40)
					{
						ptr_board_j+=10;
						if(*ptr_board_j==7)
						{
							addmove(ptr_board_i,ptr_board_j);
						}
					}
				}
				break;
			case 2 :
				ptr_board_j=ptr_board_i+8;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=4;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=7;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=2;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=29;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=4;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=7;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=2;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 3 :
				ptr_board_j=ptr_board_i+9;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j+=9;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+11;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j+=11;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-9;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j-=9;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-11;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j-=11;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 4 :
				ptr_board_j=ptr_board_i+1;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j++;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+10;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j+=10;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-1;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j--;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-10;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j-=10;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 5 :
				ptr_board_j=ptr_board_i+9;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j+=9;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+11;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j+=11;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-9;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j-=9;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-11;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j-=11;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+1;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j++;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+10;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j+=10;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-1;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j--;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-10;
				while(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
					ptr_board_j-=10;
				}
				if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 6 :
				ptr_board_j=ptr_board_i+1;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=8;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j++;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j++;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=12;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=8;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j--;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j--;
				if(*ptr_board_j==7)
				{
					addmove(ptr_board_i,ptr_board_j);
				}
				else if(*ptr_board_j>8)
				{
					xaddmove(ptr_board_i,ptr_board_j);
				}
				if(cst&4)
				{
					char i=ptr_board_i-board;
					if(board[i+1]==7)
					{
						if(board[i+2]==7)
						{
							if(check(i,side)==0)
							{
								board[i+1]=6;
								board[i]=7;
								if(check(i+1,side)==0)
								{
									board[i+2]=6;
									board[i+1]=7;
									if(check(i+2,side)==0)
									{
										ptr_board_j=ptr_board_i+2;
										addmove(ptr_board_i,ptr_board_j);
									}
									board[i+2]=7;
									board[i+1]=6;
								}
								board[i+1]=7;
								board[i]=6;
							}
						}
					}
				}
				if(cst&8)
				{
					char i=ptr_board_i-board;
					if(board[i-1]==7)
					{
						if(board[i-2]==7)
						{
							if(board[i-3]==7)
							{
								if(check(i,side)==0)
								{
									board[i-1]=6;
									board[i]=7;
									if(check(i-1,side)==0)
									{
										board[i-2]=6;
										board[i-1]=7;
										if(check(i-2,side)==0)
										{
											ptr_board_j=ptr_board_i-2;
											addmove(ptr_board_i,ptr_board_j);
										}
										board[i-2]=7;
										board[i-1]=6;
									}
									board[i-1]=7;
									board[i]=6;
								}
							}
						}
					}
				}
			}
			ptr_fs2++;
		} while(ptr_fs2<=ptr_fs2_max);
	}
}

void xmoves()
{
	if(side)
	{
		char* ptr_fs1=fs1+1;
		char* ptr_fs1_max=fs1+max1;
		char* ptr_board_i;
		char* ptr_board_j;
		do
		{
			ptr_board_i=board+(*ptr_fs1);
			switch(*ptr_board_i)
			{
			case 9 :
				ptr_board_j=ptr_board_i-9;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=2;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 10 :
				ptr_board_j=ptr_board_i+8;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=4;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=7;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=2;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=29;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=4;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=7;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=2;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 11 :
				ptr_board_j=ptr_board_i+9;
				while(*ptr_board_j==7)
				{
					ptr_board_j+=9;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+11;
				while(*ptr_board_j==7)
				{
					ptr_board_j+=11;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-9;
				while(*ptr_board_j==7)
				{
					ptr_board_j-=9;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-11;
				while(*ptr_board_j==7)
				{
					ptr_board_j-=11;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 12 :
				ptr_board_j=ptr_board_i+1;
				while(*ptr_board_j==7)
				{
					ptr_board_j++;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+10;
				while(*ptr_board_j==7)
				{
					ptr_board_j+=10;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-1;
				while(*ptr_board_j==7)
				{
					ptr_board_j--;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-10;
				while(*ptr_board_j==7)
				{
					ptr_board_j-=10;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 13 :
				ptr_board_j=ptr_board_i+9;
				while(*ptr_board_j==7)
				{
					ptr_board_j+=9;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+11;
				while(*ptr_board_j==7)
				{
					ptr_board_j+=11;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-9;
				while(*ptr_board_j==7)
				{
					ptr_board_j-=9;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-11;
				while(*ptr_board_j==7)
				{
					ptr_board_j-=11;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+1;
				while(*ptr_board_j==7)
				{
					ptr_board_j++;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+10;
				while(*ptr_board_j==7)
				{
					ptr_board_j+=10;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-1;
				while(*ptr_board_j==7)
				{
					ptr_board_j--;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-10;
				while(*ptr_board_j==7)
				{
					ptr_board_j-=10;
				}
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 14 :
				ptr_board_j=ptr_board_i+1;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=8;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j++;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j++;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=12;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=8;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j--;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j--;
				if(*ptr_board_j<7)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
			}
			ptr_fs1++;
		} while(ptr_fs1<=ptr_fs1_max);
	}
	else
	{
		char* ptr_fs2=fs2+1;
		char* ptr_fs2_max=fs2+max2;
		char* ptr_board_i;
		char* ptr_board_j;
		do
		{
			ptr_board_i=board+(*ptr_fs2);
			switch(*ptr_board_i)
			{
			case 1 :
				ptr_board_j=ptr_board_i+9;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=2;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 2 :
				ptr_board_j=ptr_board_i+8;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=4;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=7;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=2;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=29;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=4;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=7;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=2;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 3 :
				ptr_board_j=ptr_board_i+9;
				while(*ptr_board_j==7)
				{
					ptr_board_j+=9;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+11;
				while(*ptr_board_j==7)
				{
					ptr_board_j+=11;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-9;
				while(*ptr_board_j==7)
				{
					ptr_board_j-=9;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-11;
				while(*ptr_board_j==7)
				{
					ptr_board_j-=11;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 4 :
				ptr_board_j=ptr_board_i+1;
				while(*ptr_board_j==7)
				{
					ptr_board_j++;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+10;
				while(*ptr_board_j==7)
				{
					ptr_board_j+=10;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-1;
				while(*ptr_board_j==7)
				{
					ptr_board_j--;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-10;
				while(*ptr_board_j==7)
				{
					ptr_board_j-=10;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 5 :
				ptr_board_j=ptr_board_i+9;
				while(*ptr_board_j==7)
				{
					ptr_board_j+=9;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+11;
				while(*ptr_board_j==7)
				{
					ptr_board_j+=11;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-9;
				while(*ptr_board_j==7)
				{
					ptr_board_j-=9;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-11;
				while(*ptr_board_j==7)
				{
					ptr_board_j-=11;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+1;
				while(*ptr_board_j==7)
				{
					ptr_board_j++;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i+10;
				while(*ptr_board_j==7)
				{
					ptr_board_j+=10;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-1;
				while(*ptr_board_j==7)
				{
					ptr_board_j--;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j=ptr_board_i-10;
				while(*ptr_board_j==7)
				{
					ptr_board_j-=10;
				}
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				break;
			case 6 :
				ptr_board_j=ptr_board_i+1;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j+=8;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j++;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j++;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=12;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j-=8;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j--;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
				ptr_board_j--;
				if(*ptr_board_j>8)
				{
					xxaddmove(ptr_board_i,ptr_board_j);
				}
			}
			ptr_fs2++;
		} while(ptr_fs2<=ptr_fs2_max);
	}
}

short check(short king,short side)
{
	char* ptr_board_i=board+king;
	char* ptr_board_j;
	if(side)
	{
		if(*(ptr_board_i+8)==2)
		{
			return 1;
		}
		if(*(ptr_board_i+12)==2)
		{
			return 1;
		}
		if(*(ptr_board_i+19)==2)
		{
			return 1;
		}
		if(*(ptr_board_i+21)==2)
		{
			return 1;
		}
		if(*(ptr_board_i-8)==2)
		{
			return 1;
		}
		if(*(ptr_board_i-12)==2)
		{
			return 1;
		}
		if(*(ptr_board_i-19)==2)
		{
			return 1;
		}
		if(*(ptr_board_i-21)==2)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i+9;
		if(*ptr_board_j==6)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j+=9;
		}
		if(*ptr_board_j==3)
		{
			return 1;
		}
		if(*ptr_board_j==5)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i+11;
		if(*ptr_board_j==6)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j+=11;
		}
		if(*ptr_board_j==3)
		{
			return 1;
		}
		if(*ptr_board_j==5)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i-9;
		if(*ptr_board_j==1)
		{
			return 1;
		}
		if(*ptr_board_j==6)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j-=9;
		}
		if(*ptr_board_j==3)
		{
			return 1;
		}
		if(*ptr_board_j==5)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i-11;
		if(*ptr_board_j==1)
		{
			return 1;
		}
		if(*ptr_board_j==6)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j-=11;
		}
		if(*ptr_board_j==3)
		{
			return 1;
		}
		if(*ptr_board_j==5)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i+1;
		if(*ptr_board_j==6)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j++;
		}
		if(*ptr_board_j==4)
		{
			return 1;
		}
		if(*ptr_board_j==5)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i+10;
		if(*ptr_board_j==6)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j+=10;
		}
		if(*ptr_board_j==4)
		{
			return 1;
		}
		if(*ptr_board_j==5)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i-1;
		if(*ptr_board_j==6)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j--;
		}
		if(*ptr_board_j==4)
		{
			return 1;
		}
		if(*ptr_board_j==5)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i-10;
		if(*ptr_board_j==6)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j-=10;
		}
		if(*ptr_board_j==4)
		{
			return 1;
		}
		if(*ptr_board_j==5)
		{
			return 1;
		}
	}
	else
	{
		if(*(ptr_board_i+8)==10)
		{
			return 1;
		}
		if(*(ptr_board_i+12)==10)
		{
			return 1;
		}
		if(*(ptr_board_i+19)==10)
		{
			return 1;
		}
		if(*(ptr_board_i+21)==10)
		{
			return 1;
		}
		if(*(ptr_board_i-8)==10)
		{
			return 1;
		}
		if(*(ptr_board_i-12)==10)
		{
			return 1;
		}
		if(*(ptr_board_i-19)==10)
		{
			return 1;
		}
		if(*(ptr_board_i-21)==10)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i+9;
		if(*ptr_board_j==9)
		{
			return 1;
		}
		if(*ptr_board_j==14)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j+=9;
		}
		if(*ptr_board_j==11)
		{
			return 1;
		}
		if(*ptr_board_j==13)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i+11;
		if(*ptr_board_j==9)
		{
			return 1;
		}
		if(*ptr_board_j==14)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j+=11;
		}
		if(*ptr_board_j==11)
		{
			return 1;
		}
		if(*ptr_board_j==13)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i-9;
		if(*ptr_board_j==14)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j-=9;
		}
		if(*ptr_board_j==11)
		{
			return 1;
		}
		if(*ptr_board_j==13)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i-11;
		if(*ptr_board_j==14)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j-=11;
		}
		if(*ptr_board_j==11)
		{
			return 1;
		}
		if(*ptr_board_j==13)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i+1;
		if(*ptr_board_j==14)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j++;
		}
		if(*ptr_board_j==12)
		{
			return 1;
		}
		if(*ptr_board_j==13)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i+10;
		if(*ptr_board_j==14)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j+=10;
		}
		if(*ptr_board_j==12)
		{
			return 1;
		}
		if(*ptr_board_j==13)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i-1;
		if(*ptr_board_j==14)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j--;
		}
		if(*ptr_board_j==12)
		{
			return 1;
		}
		if(*ptr_board_j==13)
		{
			return 1;
		}
		ptr_board_j=ptr_board_i-10;
		if(*ptr_board_j==14)
		{
			return 1;
		}
		while(*ptr_board_j==7)
		{
			ptr_board_j-=10;
		}
		if(*ptr_board_j==12)
		{
			return 1;
		}
		if(*ptr_board_j==13)
		{
			return 1;
		}
	}
	return 0;
}

void addmove(char* ptr_board_i,char* ptr_board_j)
{
	cnt++;
	char i=ptr_board_i-board;
	char j=ptr_board_j-board;
	movefrom[cnt]=i;
	moveto[cnt]=j;
	moveval[cnt]=0;
	if(i==ki[ply])
	{
		if(j==kj[ply])
		{
			moveval[cnt]+=2000;
		}
	}
	if(i==ki2[ply])
	{
		if(j==kj2[ply])
		{
			moveval[cnt]+=1000;
		}
	}
}

void xaddmove(char* ptr_board_i,char* ptr_board_j)
{
	if(side)
	{
		if(*ptr_board_j==6)
		{
			mate=1;
			return;
		}
	}
	else
	{
		if(*ptr_board_j==14)
		{
			mate=1;
			return;
		}
	}
	cnt++;
	char i=ptr_board_i-board;
	char j=ptr_board_j-board;
	movefrom[cnt]=i;
	moveto[cnt]=j;
	moveval[cnt]=10000+piecevalue[*ptr_board_j]-piecevalue[*ptr_board_i];
	if(i==ki[ply])
	{
		if(j==kj[ply])
		{
			moveval[cnt]+=2000;
		}
	}
	if(i==ki2[ply])
	{
		if(j==kj2[ply])
		{
			moveval[cnt]+=1000;
		}
	}
}

void xxaddmove(char* ptr_board_i,char* ptr_board_j)
{
	if(side)
	{
		if(*ptr_board_j==6)
		{
			mate=1;
			return;
		}
	}
	else
	{
		if(*ptr_board_j==14)
		{
			mate=1;
			return;
		}
	}
	char j=ptr_board_j-board;
	cnt++;
	movefrom[cnt]=ptr_board_i-board;
	moveto[cnt]=j;
	if(j==lj[ply-1])
	{
		moveval[cnt]=10000+piecevalue[*ptr_board_j]-piecevalue[*ptr_board_i];
	}
	else
	{
		moveval[cnt]=piecevalue[*ptr_board_j]-piecevalue[*ptr_board_i];
	}
}

short nsearch(short alpha,short beta,short depth)
{
	short y,x,oldbeta,isdepth;
	isdepth=0;
	if(clock()>movetime)
	{
		if(best>-32768)
		{
			endtime=1;
			return alpha;
		}
	}
	nodes++;
	cnt=counter[ply-1];
	mate=0;
	moves();
	if(mate)
	{
		return 30000-ply;
	}
	counter[ply]=cnt;
	if(pvfollow)
	{
		pvfind();
	}
	oldbeta=beta;
	for(y=counter[ply-1]+1;y<=counter[ply];y++)
	{
		x=sort();
		makemove(movefrom[x],moveto[x]);
		if(repetition(ml)>1 || draw==100)
		{
			value=0;
			beta=oldbeta;
		}
		else
		{
			if(extension)
			{
				if(cntdepth<4)
				{
					if(bj[ml]!=7 && rand()%100<take && piecevalue[bj[ml]]>100 && piecevalue[bj[ml]]>=piecevalue[bi[ml]])
					{
						cntdepth++;
						depth++;
						isdepth=1;
					}
					else
					{
						if(side)
						{
							if(check(king1,side))
							{
								cntdepth++;
								depth++;
								isdepth=1;
							}
						}
						else
						{
							if(check(king2,side))
							{
								cntdepth++;
								depth++;
								isdepth=1;
							}
						}
					}
				}
			}
			if(ply==2)
			{
				if(rnd)
				{
					if(x<100)
					{
						material+=randtab[x];
					}
				}
			}
			if(depth==1)
			{
				if(material+300>alpha)
				{
					eval=evaluate();
					material+=eval;
					if(material>alpha)
					{
						material=-material;
						value=-xsearch(-beta,-alpha);
						if(value>=beta)
						{
							if(beta!=oldbeta)
							{
								beta=oldbeta;
								value=-xsearch(-beta,-alpha);
							}
						}
						material=-material;
					}
					else
					{
						value=alpha;
					}
					material-=eval;
				}
				else
				{
					value=alpha;
				}
			}
			else
			{
				material=-material;
				value=-nsearch(-beta,-alpha,depth-1);
				if(value>=beta)
				{
					if(beta!=oldbeta)
					{
						beta=oldbeta;
						value=-nsearch(-beta,-alpha,depth-1);
					}
				}
				material=-material;
			}
			if(ply==2)
			{
				if(rnd)
				{
					if(x<100)
					{
						material-=randtab[x];
					}
				}
			}
			if(isdepth)
			{
				cntdepth--;
				depth--;
				isdepth=0;
			}
			if(value==29999-ply)
			{
				if(side)
				{
					if(check(king1,side)==0)
					{
						value=0;
					}
				}
				else
				{
					if(check(king2,side)==0)
					{
						value=0;
					}
				}
			}
		}
		backmove(movefrom[x],moveto[x]);
		if(value>alpha && !endtime)
		{
			if(value>=beta)
			{
				if(movefrom[x]!=ki[ply] || moveto[x]!=kj[ply])
				{
					ki2[ply]=ki[ply];
					kj2[ply]=kj[ply];
					ki[ply]=movefrom[x];
					kj[ply]=moveto[x];
				}
				return beta;
			}
			alpha=value;
			oldbeta=beta;
			beta=alpha+1;
			if(ply==1)
			{
				best=value;
			}
			pvupdate(movefrom[x],moveto[x]);
		}
	}
	return alpha;
}

short xsearch(short alpha,short beta)
{
	short y,x;
	xnodes++;
	cnt=counter[ply-1];
	mate=0;
	xmoves();
	if(mate)
	{
		return 30000-ply;
	}
	counter[ply]=cnt;
	value=material;
	if(value>alpha)
	{
		if(value>=beta)
		{
			return beta;
		}
		alpha=value;
	}
	for(y=counter[ply-1]+1;y<=counter[ply];y++)
	{
		x=sort();
		xmakemove(movefrom[x],moveto[x]);
		if(material>alpha)
		{
			material=-material;
			value=-xsearch(-beta,-alpha);
			material=-material;
		}
		else
		{
			value=alpha;
		}
		xbackmove(movefrom[x],moveto[x]);
		if(value>alpha)
		{
			if(value>=beta)
			{
				return beta;
			}
			alpha=value;
		}
	}
	return alpha;
}

short evaluate()
{
	short i,c,fi,value1,value2,eg1,eg2;
	char npawn1[10]={0},npawn2[10]={0},nrook1[10]={0},nrook2[10]={0};
	value1=0;
	value2=0;
	if(mat1<2000)
	{
		eg1=1;
		if(mat2>=mat1+500)
		{
			value2-=fw[king1]*10;
		}
		else
		{
			value1+=fw[king1];
		}
	}
	else
	{
		eg1=0;
	}
	if(mat2<2000)
	{
		eg2=1;
		if(mat1>=mat2+500)
		{
			value1-=fw[king2]*10;
		}
		else
		{
			value2+=fw[king2];
		}
	}
	else
	{
		eg2=0;
	}
	for(i=1;i<=max1;i++)
	{
		fi=fs1[i];
		switch(board[fi])
		{
		case 9 :
			if(eg1)
			{
				value1+=pe1[fi];
			}
			else
			{
				value1+=pt1[fi];
			}
			c=fi%10;
			npawn1[c]++;
			if(npawn1[c]>1)
			{
				value1-=10;
			}
			break;
		case 12:
			if(eg1==0)
			{
				c=fi%10;
				nrook1[c]++;
				if(nrook1[c]>1)
				{
					value1+=10;
				}
			}
		}
	}
	for(i=1;i<=max2;i++)
	{
		fi=fs2[i];
		switch(board[fi])
		{
		case 1 :
			if(eg2)
			{
				value2+=pe2[fi];
			}
			else
			{
				value2+=pt2[fi];
			}
			c=fi%10;
			npawn2[c]++;
			if(npawn2[c]>1)
			{
				value2-=10;
			}
			break;
		case 4:
			if(eg2==0)
			{
				c=fi%10;
				nrook2[c]++;
				if(nrook2[c]>1)
				{
					value2+=10;
				}
			}
		}
	}
	for(i=1;i<=max1;i++)
	{
		fi=fs1[i];
		if(eg2)
		{
			if(board[fi]>11)
			{
				if(mat1>=mat2+500)
				{
					fy=fi/10-1;
					fx=fi%10-1;
					ky=king2/10-1;
					kx=king2%10-1;
					if(board[fi]==14)
					{
						value1-=(abs(fy-ky)+abs(fx-kx))*10;
					}
					else
					{
						value1-=(abs(fy-ky)+abs(fx-kx))*7;
					}
				}
			}
		}
		switch(board[fi])
		{
		case 10 :
		case 11 :
			if(eg1==0)
			{
				value1+=fw[fi];
			}
			break;
		case 12 :
			if(eg1==0)
			{
				c=fi%10;
				if(npawn1[c]==0)
				{
					value1+=20;
					if(npawn2[c]==0)
					{
						value1+=10;
					}
				}
			}
		}
	}
	if(board[85]==9)
	{
		if(board[75]!=7)
		{
			value1-=10;
		}
	}
	if(board[86]==9)
	{
		if(board[76]!=7)
		{
			value1-=10;
		}
	}
	for(i=1;i<=max2;i++)
	{
		fi=fs2[i];
		if(eg1)
		{
			if(board[fi]>3)
			{
				if(mat2>=mat1+500)
				{
					fy=fi/10-1;
					fx=fi%10-1;
					ky=king1/10-1;
					kx=king1%10-1;
					if(board[fi]==6)
					{
						value2-=(abs(fy-ky)+abs(fx-kx))*10;
					}
					else
					{
						value2-=(abs(fy-ky)+abs(fx-kx))*7;
					}
				}
			}
		}
		switch(board[fi])
		{
		case 2 :
		case 3 :
			if(eg2==0)
			{
				value2+=fw[fi];
			}
			break;
		case 4 :
			if(eg2==0)
			{
				c=fi%10;
				if(npawn2[c]==0)
				{
					value2+=20;
					if(npawn1[c]==0)
					{
						value2+=10;
					}
				}
			}
		}
	}
	if(board[35]==1)
	{
		if(board[45]!=7)
		{
			value2-=10;
		}
	}
	if(board[36]==1)
	{
		if(board[46]!=7)
		{
			value2-=10;
		}
	}
	if(side)
	{
		return value2-value1;
	}
	else
	{
		return value1-value2;
	}
}

void pvfind()
{
	short z;
	pvfollow=0;
	if(ply<10)
	{
		for(z=counter[ply-1]+1;z<=counter[ply];z++)
		{
			if(movefrom[z]==pvi[1][ply])
			{
				if(moveto[z]==pvj[1][ply])
				{
					pvfollow=1;
					moveval[z]=32767;
				}
			}
		}
	}
}

short sort()
{
	short* ptr_index=moveval+counter[ply-1]+1;
	short* ptr_index_max=moveval+counter[ply];
	short* ptr_index_maxind=ptr_index;
	short maxval=*ptr_index;
	while(++ptr_index<=ptr_index_max)
	{
		if(*ptr_index>maxval)
		{
			maxval=*ptr_index;
			ptr_index_maxind=ptr_index;
		}
	}
	*ptr_index_maxind=-32768;
	return ptr_index_maxind-moveval;
}

void makemove(short i,short j)
{
	ep=0;
	ml++;
	mlfrom[ml]=i;
	mlto[ml]=j;
	material+=piecevalue[board[j]];
	castle[ml]=cst;
	promotion[ml]=0;
	enpassant[ml]=0;
	hashtable[ml]=hsh;
	draw++;
	if(side)
	{
		fs1[fs[i]]=j;
		if(board[j]<7)
		{
			fs2[fs[j]]=0;
			fj[ply]=fs[j];
			mat2-=piecevalue[board[j]];
		}
		if(board[i]==9)
		{
			draw=0;
			if(board[j]==7)
			{
				if(j==i-20)
				{
					enpassant[ml]=j;
				}
				else
				{
					if(j==i-11 || j==i-9)
					{
						material+=100;
						ep=j+10;
						board[ep]=7;
						fj[ply]=fs[ep];
						fs2[fs[ep]]=0;
					}
				}
			}
		}
		if(board[i]==14)
		{
			if(cst&3)
			{
				material-=10;
			}
			if(j==i+2)
			{
				board[97]=12;
				board[99]=7;
				fs[97]=fs[99];
				fs1[fs[97]]=97;
				material+=40-ply;
				hsh^=hashpiece[99][12];
				hsh^=hashpiece[97][12];
			}
			if(j==i-2)
			{
				board[95]=12;
				board[92]=7;
				fs[95]=fs[92];
				fs1[fs[95]]=95;
				material+=30-ply;
				hsh^=hashpiece[92][12];
				hsh^=hashpiece[95][12];
			}
			cst&=252;
			king1=j;
		}
		if(board[i]==12)
		{
			if(i==99)
			{
				cst&=254;
			}
			if(i==92)
			{
				cst&=253;
			}
		}
		if(cst&4)
		{
			if(j==29)
			{
				cst&=251;
			}
		}
		if(cst&8)
		{
			if(j==22)
			{
				cst&=247;
			}
		}
	}
	else
	{
		fs2[fs[i]]=j;
		if(board[j]>8)
		{
			fs1[fs[j]]=0;
			fj[ply]=fs[j];
			mat1-=piecevalue[board[j]];
		}
		if(board[i]==1)
		{
			draw=0;
			if(board[j]==7)
			{
				if(j==i+20)
				{
					enpassant[ml]=j;
				}
				else
				{
					if(j==i+11 || j==i+9)
					{
						material+=100;
						ep=j-10;
						board[ep]=7;
						fj[ply]=fs[ep];
						fs1[fs[ep]]=0;
					}
				}
			}
		}
		if(board[i]==6)
		{
			if(cst&12)
			{
				material-=10;
			}
			if(j==i+2)
			{
				board[27]=4;
				board[29]=7;
				fs[27]=fs[29];
				fs2[fs[27]]=27;
				material+=40-ply;
				hsh^=hashpiece[29][4];
				hsh^=hashpiece[27][4];
			}
			if(j==i-2)
			{
				board[25]=4;
				board[22]=7;
				fs[25]=fs[22];
				fs2[fs[25]]=25;
				material+=30-ply;
				hsh^=hashpiece[22][4];
				hsh^=hashpiece[25][4];
			}
			cst&=243;
			king2=j;
		}
		if(board[i]==4)
		{
			if(i==29)
			{
				cst&=251;
			}
			if(i==22)
			{
				cst&=247;
			}
		}
		if(cst&1)
		{
			if(j==99)
			{
				cst&=254;
			}
		}
		if(cst&2)
		{
			if(j==92)
			{
				cst&=253;
			}
		}
	}
	hsh^=hashpiece[i][board[i]];
	hsh^=hashpiece[j][board[i]];
	if(board[j]!=7)
	{
		hsh^=hashpiece[j][board[j]];
		draw=0;
	}
	hsh^=hashside;
	if(ep)
	{
		hsh^=hashep[ep];
	}
	fs[j]=fs[i];
	bi[ml]=board[i];
	bj[ml]=board[j];
	board[j]=board[i];
	board[i]=7;
	if(side)
	{
		if(board[j]==9)
		{
			if(j<30)
			{
				board[j]=13;
				material+=800-ply*10;
				promotion[ml]=13;
				hsh^=hashpiece[j][9];
				hsh^=hashpiece[j][13];
			}
		}
	}
	else
	{
		if(board[j]==1)
		{
			if(j>91)
			{
				board[j]=5;
				material+=800-ply*10;
				promotion[ml]=5;
				hsh^=hashpiece[j][1];
				hsh^=hashpiece[j][5];
			}
		}
	}
	ply++;
	side=!side;
}

void backmove(short i,short j)
{
	ply--;
	hsh=hashtable[ml];
	side=!side;
	board[i]=board[j];
	board[j]=bj[ml];
	cnt=counter[ply];
	cst=castle[ml];
	fs[i]=fs[j];
	if(draw)
	{
		draw--;
	}
	if(side)
	{
		fs1[fs[i]]=i;
		if(board[j]<7)
		{
			fs[j]=fj[ply];
			fs2[fs[j]]=j;
			mat2+=piecevalue[board[j]];
		}
		if(board[i]==9)
		{
			if(board[j]==7)
			{
				if(j==i-20)
				{
					enpassant[ml]=0;
				}
				else
				{
					if(j==i-11 || j==i-9)
					{
						material-=100;
						ep=j+10;
						board[ep]=1;
						fs[ep]=fj[ply];
						fs2[fs[ep]]=ep;
					}
				}
			}
		}
		if(board[i]==14)
		{
			if(cst&3)
			{
				material+=10;
			}
			if(j==i+2)
			{
				board[97]=7;
				board[99]=12;
				fs[99]=fs[97];
				fs1[fs[99]]=99;
				material-=40-ply;
			}
			if(j==i-2)
			{
				board[95]=7;
				board[92]=12;
				fs[92]=fs[95];
				fs1[fs[92]]=92;
				material-=30-ply;
			}
			king1=i;
		}
	}
	else
	{
		fs2[fs[i]]=i;
		if(board[j]>8)
		{
			fs[j]=fj[ply];
			fs1[fs[j]]=j;
			mat1+=piecevalue[board[j]];
		}
		if(board[i]==1)
		{
			if(board[j]==7)
			{
				if(j==i+20)
				{
					enpassant[ml]=0;
				}
				else
				{
					if(j==i+11 || j==i+9)
					{
						material-=100;
						ep=j-10;
						board[ep]=9;
						fs[ep]=fj[ply];
						fs1[fs[ep]]=ep;
					}
				}
			}
		}
		if(board[i]==6)
		{
			if(cst&12)
			{
				material+=10;
			}
			if(j==i+2)
			{
				board[27]=7;
				board[29]=4;
				fs[29]=fs[27];
				fs2[fs[29]]=29;
				material-=40-ply;
			}
			if(j==i-2)
			{
				board[25]=7;
				board[22]=4;
				fs[22]=fs[25];
				fs2[fs[22]]=22;
				material-=30-ply;
			}
			king2=i;
		}
	}
	if(promotion[ml])
	{
		if(side)
		{
			board[i]=9;
		}
		else
		{
			board[i]=1;
		}
		material-=(800-ply*10);
		promotion[ml]=0;
	}
	ml--;
	material-=piecevalue[board[j]];
}

void xmakemove(short i,short j)
{
	ml++;
	material+=piecevalue[board[j]];
	if(side)
	{
		fs1[fs[i]]=j;
		fs2[fs[j]]=0;
	}
	else
	{
		fs2[fs[i]]=j;
		fs1[fs[j]]=0;
	}
	fj[ply]=fs[j];
	fs[j]=fs[i];
	bj[ml]=board[j];
	board[j]=board[i];
	board[i]=7;
	lj[ply]=j;
	ply++;
	side=!side;
}

void xbackmove(short i,short j)
{
	ply--;
	side=!side;
	board[i]=board[j];
	board[j]=bj[ml];
	cnt=counter[ply];
	fs[i]=fs[j];
	fs[j]=fj[ply];
	if(side)
	{
		fs1[fs[i]]=i;
		fs2[fs[j]]=j;
	}
	else
	{
		fs2[fs[i]]=i;
		fs1[fs[j]]=j;
	}
	ml--;
	material-=piecevalue[board[j]];
}

short makematerial()
{
	mat1=0;
	mat2=0;
	max1=0;
	max2=0;
	for(i=22;i<100;i++)
	{
		if(board[i]>8)
		{
			if(board[i]==14)
			{
				king1=i;
			}
			else
			{
				mat1+=piecevalue[board[i]];
			}
			max1++;
			fs1[max1]=i;
			fs[i]=max1;
		}
		if(board[i]<7)
		{
			if(board[i]==6)
			{
				king2=i;
			}
			else
			{
				mat2+=piecevalue[board[i]];
			}
			max2++;
			fs2[max2]=i;
			fs[i]=max2;
		}
	}
	if(side)
	{
		return mat1-mat2;
	}
	else
	{
		return mat2-mat1;
	}
}

void pvupdate(short i,short j)
{
	short z;
	if(ply<10)
	{
		pvi[ply][ply]=i;
		pvj[ply][ply]=j;
		for(z=ply+1;z<10;z++)
		{
			pvi[ply][z]=pvi[ply+1][z];
			pvj[ply][z]=pvj[ply+1][z];
		}
	}
}

short opening()
{
	unsigned short a,b,of,ro;
	a=0;
	of=0;
	if(ml==0)
	{
		do
		{
			of++;
			obi[of]=ob[a];
			obj[of]=ob[a+1];
			while(ob[a])
			{
				a+=2;
			}
			a++;
		} while(a<43489);
	}
	else
	{
		do
		{
			b=1;
			while(b<=ml && ob[a]==mlfrom[b] && ob[a+1]==mlto[b])
			{
				b++;
				a+=2;
			}
			if(b>ml && ob[a])
			{
				of++;
				obi[of]=ob[a];
				obj[of]=ob[a+1];
			}
			while(ob[a])
			{
				a+=2;
			}
			a++;
		} while(a<43489);
	}
	if(of)
	{
		ro=rand()%of+1;
		pvi[1][1]=obi[ro];
		pvj[1][1]=obj[ro];
		return 1;
	}
	else
	{
		return 0;
	}
}

void makehash()
{
	hsh=rand();
	for(i=1;i<=max1;i++)
	{
		if(board[fs1[i]]>8)
		{
			hsh^=hashpiece[fs1[i]][board[fs1[i]]];
		}
	}
	for(i=1;i<=max2;i++)
	{
		if(board[fs2[i]]<7)
		{
			hsh^=hashpiece[fs2[i]][board[fs2[i]]];
		}
	}
	hashtable[0]=hsh;
}

short repetition(short pos)
{
	short r,s;
	r=0;
	for(s=1;s<=pos;s++)
	{
		if(hashtable[s]==hsh)
		{
			r++;
		}
	}
	return r;
}

void showboard()
{
	if(view)
	{
		printf("\n\e[7m  H G F E D C B A  \e[0m");
		for(j=2;j<10;j++)
		{
			printf("\n\e[7m%c\e[0m ",(char)(j+47));
			for(i=10;i>1;i--)
			{
				switchboard();
			}
			printf("\e[7m%c\e[0m",(char)(j+47));
		}
		printf("\n\e[7m  H G F E D C B A  \e[0m\n\n");
	}
	else
	{
		printf("\n\e[7m  A B C D E F G H  \e[0m");
		for(j=9;j>1;j--)
		{
			printf("\n\e[7m%c\e[0m ",(char)(j+47));
			for(i=2;i<11;i++)
			{
				switchboard();
			}
			printf("\e[7m%c\e[0m",(char)(j+47));
		}
		printf("\n\e[7m  A B C D E F G H  \e[0m\n\n");
	}
}

void switchboard()
{
	switch(board[j*10+i])
   {
	case 7 :
		printf("· ");
		break;
	case 1 :
		printf("♟ ");
		break;
	case 2 :
		printf("♞ ");
		break;
	case 3 :
		printf("♝ ");
		break;
	case 4 :
		printf("♜ ");
		break;
	case 5 :
		printf("♛ ");
		break;
	case 6 :
		printf("♚ ");
		break;
	case 9 :
		printf("♙ ");
		break;
	case 10 :
		printf("♘ ");
		break;
	case 11 :
		printf("♗ ");
		break;
	case 12 :
		printf("♖ ");
		break;
	case 13 :
		printf("♕ ");
		break;
	case 14 :
		printf("♔ ");
	}
}

void loadgame()
{
	infile=fopen(filename,"rb");
	if(infile==NULL)
	{
		if(alrm)
		{
			printf("\a");
		}
		printf("File %s not found!\n\n",filename);
		return;
	}
	newgame();
	printf("Reading %s...\n",filename);
	fread(&view,2,1,infile);
	fread(&j,2,1,infile);
	for(i=1;i<=j;i++)
	{
		mlfrom[i]=fgetc(infile);
		mlto[i]=fgetc(infile);
		bj[i]=fgetc(infile);
		castle[i]=fgetc(infile);
		enpassant[i]=fgetc(infile);
		promotion[i]=fgetc(infile);
		ply=0;
		temp=promotion[i];
		makemove(mlfrom[i],mlto[i]);
		if(promotion[i])
		{
			board[mlto[i]]=temp;
		}
	}
	fclose(infile);
	makematerial();
}

void savegame()
{
	outfile=fopen(filename,"wb");
	if(outfile==NULL)
	{
		if(alrm)
		{
			printf("\a");
		}
		printf("File %s could not be written!\n\n",filename);
		return;
	}
	printf("Writing %s...\n\n",filename);
	fwrite(&view,2,1,outfile);
	fwrite(&ml,2,1,outfile);
	for(i=1;i<=ml;i++)
	{
		fputc(mlfrom[i],outfile);
		fputc(mlto[i],outfile);
		fputc(bj[i],outfile);
		fputc(castle[i],outfile);
		fputc(enpassant[i],outfile);
		fputc(promotion[i],outfile);
	}
	fclose(outfile);
}

void newgame()
{
	for(i=ml;i>0;i--)
	{
		ply=1;
		x=mlfrom[i];
		y=mlto[i];
		backmove(x,y);
		bj[0]=bj[i];
		castle[0]=castle[i];
		enpassant[0]=enpassant[i];
		promotion[0]=promotion[i];
	}
}
