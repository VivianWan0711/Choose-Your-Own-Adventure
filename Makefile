cyoa-step1: cyoa-step1.cpp story.h page.h
	g++ -o cyoa-step1 -std=c++98 -Wall -Werror -ggdb3 cyoa-step1.cpp


cyoa-step2: cyoa-step2.cpp story.h page.h
	g++ -o cyoa-step2 -std=c++98 -Wall -Werror -ggdb3 cyoa-step2.cpp

cyoa-step3: cyoa-step3.cpp story.h page.h
	g++ -o cyoa-step3 -std=c++98 -Wall -Werror -ggdb3 cyoa-step3.cpp

cyoa-step4: cyoa-step4.cpp story.h page.h
	g++ -o cyoa-step4 -std=c++98 -Wall -Werror -ggdb3 cyoa-step4.cpp

clean:
	rm -f *.o *~ cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
