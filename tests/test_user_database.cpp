#include <UnitTest++/UnitTest++.h>
#include <fstream>
#include <iostream>
#include <string>
#include "user_database.h"
#include "errors.h"

#define TEST_DB_FILE "test_db.conf"

struct DBFixture {
    DBFixture() {
        std::ofstream f(TEST_DB_FILE);
        f << "admin:pass123\nuser1:qwerty\n";
    }
    ~DBFixture() { std::remove(TEST_DB_FILE); }
};

struct EmptyDBFixture {
    EmptyDBFixture() { std::ofstream f(TEST_DB_FILE); }
    ~EmptyDBFixture() { std::remove(TEST_DB_FILE); }
};

struct InvalidDBFixture {
    InvalidDBFixture() {
        std::ofstream f(TEST_DB_FILE);
        f << "invalidline\nadmin:pass123\n";
    }
    ~InvalidDBFixture() { std::remove(TEST_DB_FILE); }
};

SUITE(UserDatabaseTest) {
    TEST_FIXTURE(DBFixture, LoadCorrectFile) { // Тест 1.1
        UserDatabase db(TEST_DB_FILE);
        bool result = db.load();
        std::cout << "Тест 1.1: load() вернул " << (result ? "true" : "false") << std::endl;
        CHECK(result);
    }

    TEST(LoadSingleRecord) { // Тест 1.2
        std::ofstream f(TEST_DB_FILE);
        f << "test:test\n"; f.close();
        UserDatabase db(TEST_DB_FILE);
        bool result = db.load();
        std::cout << "Тест 1.2: load() вернул " << (result ? "true" : "false") << std::endl;
        CHECK(result);
        std::remove(TEST_DB_FILE);
    }

    TEST_FIXTURE(EmptyDBFixture, LoadEmptyFile) { // Тест 1.3
        UserDatabase db(TEST_DB_FILE);
        bool result = db.load();
        std::cout << "Тест 1.3: load() вернул " << (result ? "true" : "false") << std::endl;
        CHECK(result);
    }

    TEST(LoadNotFoundFile) { // Тест 1.4
        UserDatabase db("notfound.conf");
        try {
            db.load();
            std::cout << "Тест 1.4: ОШИБКА - исключение не брошено!" << std::endl;
        } catch (const IOError& e) {
            std::cout << "Тест 1.4: Исключение IOError: " << e.what() << std::endl;
        }
        CHECK_THROW(db.load(), IOError);
    }

    TEST_FIXTURE(InvalidDBFixture, LoadInvalidFormat) { // Тест 1.5
        UserDatabase db(TEST_DB_FILE);
        bool result = db.load();
        std::cout << "Тест 1.5: load() вернул " << (result ? "true" : "false") << std::endl;
        CHECK(result);
    }

    TEST_FIXTURE(DBFixture, FindExistingUser) { // Тест 2.1
        UserDatabase db(TEST_DB_FILE); db.load();
        std::string pass;
        bool found = db.findUser("admin", pass);
        std::cout << "Тест 2.1: findUser вернул " << (found ? "true" : "false") 
                  << ", пароль='" << pass << "'" << std::endl;
        CHECK(found);
        CHECK_EQUAL("pass123", pass);
    }

    TEST_FIXTURE(DBFixture, FindSecondUser) { // Тест 2.2
        UserDatabase db(TEST_DB_FILE); db.load();
        std::string pass;
        bool found = db.findUser("user1", pass);
        std::cout << "Тест 2.2: findUser вернул " << (found ? "true" : "false") 
                  << ", пароль='" << pass << "'" << std::endl;
        CHECK(found);
        CHECK_EQUAL("qwerty", pass);
    }

    TEST_FIXTURE(DBFixture, FindUnknownUser) { // Тест 2.3
        UserDatabase db(TEST_DB_FILE); db.load();
        std::string pass;
        bool found = db.findUser("unknown", pass);
        std::cout << "Тест 2.3: findUser вернул " << (found ? "true" : "false") << std::endl;
        CHECK(!found);
    }

    TEST_FIXTURE(DBFixture, FindEmptyLogin) { // Тест 2.4
        UserDatabase db(TEST_DB_FILE); db.load();
        std::string pass;
        bool found = db.findUser("", pass);
        std::cout << "Тест 2.4: findUser вернул " << (found ? "true" : "false") << std::endl;
        CHECK(!found);
    }
}
