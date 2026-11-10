CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lboost_program_options -lcryptopp 

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

# Модульные тесты
TEST_SOURCES = tests/test_user_interface.cpp \
               tests/test_user_database.cpp \
               tests/test_authenticator.cpp \
               tests/test_data_processor.cpp \
               tests/test_logger.cpp \
               tests/main.cpp

TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_TARGET = run_tests

# Объекты основного проекта БЕЗ main.o 
LIB_OBJECTS = $(filter-out main.o, $(OBJECTS))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

# Правило сборки тестов
$(TEST_TARGET): $(TEST_OBJECTS) $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJECTS) $(LIB_OBJECTS) /usr/lib/x86_64-linux-gnu/libUnitTest++.so $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
tests/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET) $(TEST_OBJECTS) $(TEST_TARGET) test_db.conf test_run.log

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

.PHONY: all clean test
