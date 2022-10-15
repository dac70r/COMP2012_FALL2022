CPPFLAGS = -std=c++11
OBJECTS = course_database.o course.o main.o student_database.o student.o swap_list.o system.o wait_list.o

all: pa1.out

pa1.out: $(OBJECTS)
	g++ -o $@ $(CPPFLAGS) $^

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@

clean:
	rm  -f  *.o *.out *.zip
