#include "zetabot.h"
#include <ncurses.h>
#include <iostream>


int main(int, char **)
{
	ZetaBot zetabot;
	try {
		zetabot.start();
	} catch (const char* tmp) {
		fprintf(stderr,"%s\n",tmp);
		abort();
	}
	initscr();
	noecho();
	clear();
	mvaddstr(0, 0, "l): turn left, r): turn right, f): forward, SPACE=stop, ESC=end");
	refresh();
	float l = 0;
	float r = 0;
	char tmp[256];
    bool running=true;
	while (running)
	{
		// blocking so that the main program sleeps here
		int ch = getchar();
		switch (ch)
		{
		case 27:
			running = 0;
			break;

		case 'l':
			l = -1.0f;
            r=1.0f;
			sprintf(tmp, "Turning left at max speed");
            zetabot.setLeftWheelSpeed(l);
            zetabot.setRightWheelSpeed(r);
            usleep(5000000);
			mvaddstr(6, 0, tmp);
			refresh();
			break;

		case 'r':
			l = 1.0f;
            r= -1.0f;
			sprintf(tmp,  "Turning left at max speed");
            zetabot.setLeftWheelSpeed(l);
            zetabot.setRightWheelSpeed(r);
            usleep(5000000); //5 sec
			mvaddstr(6, 0, tmp);
			refresh();
			break;

		case 'f':
			l =1.0f;
			r = 1.0f;
			sprintf(tmp,"Forwards max speed for 1 minute    l=%f, r=%f                     ",l,r);
			zetabot.setLeftWheelSpeed(l);
            zetabot.setRightWheelSpeed(r);
            usleep(60000000); //1 min
            mvaddstr(6, 0, tmp);
			refresh();
			break;

		case ' ':
			l = 0;
			r = 0;
			mvaddstr(6, 0, "Stopping                            ");
			refresh();
			break;

		default:
			break;
		}
        zetabot.setLeftWheelSpeed(0);
        zetabot.setLeftWheelSpeed(0);

	}
	zetabot.stop();
	endwin();
}
