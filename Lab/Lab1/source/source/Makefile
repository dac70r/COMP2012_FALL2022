CPPFLAGS = -std=c++11
OBJS = battle.o main.o monster_map.o monster.o player.o shop.o skill.o 
DEPS = battle.d main.d monster_map.d monster.d player.d shop.d skill.d 

#Notes: make depend (Linux and MacOS)

#For mac
#all: Game_easy.out Game_difficult.out Game_impossible.out

#For windows
all: Game_easy.exe Game_difficult.exe Game_impossible.exe

# 3 rules 
#Game_easy.exe: $(OBJS) helper_easy.o
#g++ -o $@ $(CPPFLAGS) $^

#Game_difficult.exe: $(OBJS) helper_difficult.o
#g++ -o $@ $(CPPFLAGS) $^

#Game_impossible.exe: $(OBJS) helper_impossible.o
#g++ -o $@ $(CPPFLAGS) $^

#For mac 
#Game_%.out: $(OBJS) helper_%.o
#g++ -o $@ $(CPPFLAGS) $^

#For windows
Game_%.exe: $(OBJS) helper_%.o
	g++ -o $@ $(CPPFLAGS) $^

%.o: %.cpp
	g++ $(CPPFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

#For mac
clean:
	rm -f *.o *.exe *.d *.out

#For windows
#clean:
#del -f *.o *.exe *.d *.out

# On Windows, use: del *.o *.exe *.d
# On Linux or MacOS, use: rm -f *.o *.exe *.d

.PRECIOUS: $(OBJS) helper_easy.o helper_difficult.o helper_impossible.o