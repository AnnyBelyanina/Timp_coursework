CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lboost_program_options -lcryptopp -lpthread

SOURCES = main.cpp \
          errors.cpp \
          logger.cpp \
          user_interface.cpp \
          user_database.cpp \
          data_processor.cpp \
          authenticator.cpp \
          communicator.cpp \
          server.cpp

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = vcalc_server

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

# Зависимости 
main.o: main.cpp server.h user_interface.h errors.h
errors.o: errors.cpp errors.h
logger.o: logger.cpp logger.h errors.h
user_interface.o: user_interface.cpp user_interface.h errors.h
user_database.o: user_database.cpp user_database.h errors.h
data_processor.o: data_processor.cpp data_processor.h
authenticator.o: authenticator.cpp authenticator.h errors.h user_database.h
communicator.o: communicator.cpp communicator.h errors.h
server.o: server.cpp server.h logger.h user_database.h authenticator.h data_processor.h communicator.h errors.h

.PHONY: all clean
