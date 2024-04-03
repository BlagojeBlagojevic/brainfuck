#include<stdio.h>
#include<stdint.h>

#define LOG 0
#define MAX_SIZE 30000

static uint8_t PROGRAM[MAX_SIZE];
static uint8_t DATA[30000];
uint64_t IP = 0;
uint64_t DP = 0;

void load_bf(const char* name) {

	for(size_t i = 0; i < MAX_SIZE; i++) {
		DATA[i] = 0;
		PROGRAM[i] = 255;
		}

	FILE *f = fopen(name,"r+");
	while(!feof(f)) {
		PROGRAM[IP++] = fgetc(f);
		if(IP == MAX_SIZE)
			break;
		}
	//PROGRAM[IP] = 255;
	fclose(f);
	}
void bf_interpreter() {

	DP = 0;
	IP = 0;
	uint64_t matching = 0;

	while(PROGRAM[IP]!=255)	{

		switch(PROGRAM[IP]) {

			case '>':

				if(DP < 30000 - 1)
					DP++;
				else
					DP = 0;
				break;

			case '<':
				if(DP > 0)
					DP--;
				else
					DP = 30000 - 1;
				break;

			case '+':

				DATA[DP]++;
				break;

			case '-':

				DATA[DP]--;
				break;

			case '.':
				
				putchar(DATA[DP]);
				break;

			case ',':
				
				scanf("%c",&DATA[DP]);
				break;

			case '[':
				//matching = IP;
				if(DATA[DP] == 0) {
					int counter = 0;
					while(1) {
						IP++;
						if(PROGRAM[IP] == '[')
							counter++;
						if(PROGRAM[IP] == ']')
							counter--;
						if(PROGRAM[IP] == ']' && counter == -1)
							break;

						}
					}
				break;
			case ']':

				if(DATA[DP] != 0) {
					int counter = 0;
					while(1) {
						IP--;
						if(PROGRAM[IP] == ']')
							counter++;
						if(PROGRAM[IP] == '[')
							counter--;
						if(PROGRAM[IP] == '[' && counter == -1)
							break;
						}
					}
				break;

			}

		IP++;
#if LOG == 1

		printf("IP %d\n",(int)IP);
		printf("DATA %u\n", DATA[DP]);
		printf("DP %u\n",DP);

#endif
		}


	}


int main() {
	
	load_bf("bf.bf");
	bf_interpreter();
	return 0;

	}