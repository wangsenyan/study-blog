serv05:serv05.o util.o sock_ntop.o child05.o web_child.o pr_cpu_time.o
	cc -o serv05.out serv05.o util.o sock_ntop.o child05.o web_child.o pr_cpu_time.o

serv05.o: serv05.c util.h child.h
	cc -c serv05.c 
util.o:util.c util.h
	cc -c util.c
sock_ntop.o:sock_ntop.c sock_ntop.h
	cc -c sock_ntop.c 
child05.o:child05.c util.h
	cc -c child05.c 
web_child.o:web_child.c util.h
	cc -c web_child.c 
pr_cpu_time.o:pr_cpu_time.c util.h
	cc -c pr_cpu_time.c