CC=gcc

%.o: %.c
	$(CC) -c -o $@ $<

all: admin_container ecs_agent_1 ecs_agent_2

admin_container: admin_container.o
	gcc -o admin_container admin_container.o

ecs_agent_1: ecs-agent_1.o
	gcc -o ecs_agent_1 ecs_agent_1.o

ecs_agent_2: ecs_agent_2.o
	gcc -o ecs_agent_2 ecs_agent_2.o
	
clean:
	rm -f *.o