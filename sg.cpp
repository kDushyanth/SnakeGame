#include<bits/stdc++.h>
#include<unistd.h>
#include <termios.h>
using namespace std;

#define STDIN_FILENO 0

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"


int fx,fy;
int h,w;
set<pair<int,int>> s;
int crash=0;
int movement = 6;
int score=2;

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}


 
class Snake{
	public:
		deque<pair<int,int> > body;
		
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
	Snake(){
	 	body.push_back(make_pair(0,2));
	 	body.push_back(make_pair(0,1));
	 	body.push_back(make_pair(0,0));
	 	
	}
	
};

void generate(Snake& snake){
	score++;
	for(int i=0;i<snake.body.size();i++){
		if(s.find(make_pair(snake.body[i].first,snake.body[i].second))!=s.end()){
			s.erase(s.find(make_pair(snake.body[i].first,snake.body[i].second)));
		}
	}
	int in = rand()%(s.size());
	auto itr = s.begin();
	advance(itr,in);
	fx = (itr->second);
	fy = itr->first;
	
}
void Snake::moveUp(){
int f=0;
	if(movement!=2 || movement!=8){
		if(mod(body[0].first-1,h)!=fx || mod(body[0].second,h)!=fy){
			f=1;body.pop_back();
		}
		if(find(body.begin(),body.end(),make_pair(mod((body[0].first-1),h),body[0].second))!=body.end()){
			crash=1;
			
		}
		body.push_front(make_pair(mod((body[0].first-1),h),body[0].second));

		if(!f)generate(*this);
	}
}
void Snake::moveDown(){
int f=0;
	if(movement!=2 || movement!=8){
		if(mod(body[0].first+1,h)!=fx || mod(body[0].second,h)!=fy){
			f=1;body.pop_back();
		}
		if(find(body.begin(),body.end(),make_pair(mod((body[0].first+1),h),body[0].second))!=body.end()){
			crash=1;
		}
		body.push_front(make_pair(mod((body[0].first+1),h),body[0].second));
		
		if(!f){
			generate(*this);
		}
	}
}
void Snake::moveLeft(){
int f=0;
	if(movement!=4 || movement!=6){
		if(body[0].first!=fx || mod(body[0].second-1,h)!=fy){
			f=1;body.pop_back();
		}
		if(find(body.begin(),body.end(),make_pair(body[0].first,mod(body[0].second-1,h)))!=body.end()){
			crash=1;
		}
		body.push_front(make_pair(body[0].first,mod(body[0].second-1,h)));
		
		if(!f)generate(*this);

	}
}
void Snake::moveRight(){
int f=0;
	if(movement!=4 || movement!=6){
		if(mod(body[0].first,h)!=fx || mod(body[0].second+1,h)!=fy){
			f=1;body.pop_back();
		}
		if(find(body.begin(),body.end(),make_pair(body[0].first,mod(body[0].second+1,h)))!=body.end()){
			crash=1;
		}
		body.push_front(make_pair(body[0].first,mod(body[0].second+1,h)));
		
		if(!f)generate(*this);
	}
}

void gameZone(Snake& snake){
	system("clear");
        string str="";
	for(int i=0;i<w+2;i++){
		printf("%s_",NRM);
	}printf("\n");
	for(int i=0;i<h;i++){
		printf("|");
		for(int j=0;j<w;j++){
			if(fx==i && fy==j){
					printf("%s@",RED);
			}else{
			
				if(snake.body[0].first==i && snake.body[0].second==j){
						printf("%so",YEL);
				}
				else{
					int f=0;
					for(int k=1;k<snake.body.size();k++){
						if(snake.body[k].first==i && snake.body[k].second==j){
							printf("%sO",GRN);f=1;break;
						}
					}
					if(!f){
						printf("%s ",NRM);
					}
				}			
			}
			
			
		}
		printf("%s|\n",NRM);
	}
	for(int i=0;i<w+2;i++){
		printf("%s`",NRM);
	}
	printf("\nSCORE:%s%d%s\n",YEL,score,NRM);
	
}

int move(Snake& snake,int movement){
	
	switch(movement){
	case 4:	
			snake.moveLeft();
			break;
	case 6:	
			snake.moveRight();
			break;
	case 2:	snake.moveDown();
			break;
	case 8:	snake.moveUp();
			break;
	}	
return 1;
}
void *ip(void *vp){
    
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    while(1){
    int prev = movement;
    char c,d,e;
    cin >> c;
    cin >> d;
    cin >> e;
    if ((c==27)&&(d=91)) {
        if (e==65) { if(prev!=2)movement=8;}
        if (e==66) { if(prev!=8)movement=2;}
        if (e==67) { if(prev!=4)movement=6;}
        if (e==68) { if(prev!=6)movement=4;}
    }
    }
    return NULL;
}


int main(){

system("clear");
printf("\n\n\t\t\tWELCOME\t\t\n\n");

printf("%senter dimension of square:%s ",GRN,NRM);
scanf("%d",&h);
w=h;

int difficulty;
printf("%senter difficulty[1-10(increasing difficulty)]:%s ",GRN,NRM);
scanf("%d",&difficulty);

Snake snake;

pthread_t tid;
pthread_create(&tid,NULL,&ip,NULL);

for(int i=0;i<h;i++){
	for(int j=0;j<w;j++){
		if((i!=0 && j!=0)||(i!=0 &&j!=1) || (i!=0 && j!=2)){
			s.insert(make_pair(i,j));
		}
	}
}

generate(snake);

while(!crash){
	move(snake,movement);
	gameZone(snake);
	usleep(1000*(1000.0/difficulty));
}

printf("\n%sGameover!!!\n",RED);

pthread_cancel(tid);

}
