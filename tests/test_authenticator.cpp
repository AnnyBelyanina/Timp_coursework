#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <fstream>
#include <string>
#include "authenticator.h"
#include "user_database.h"
#include "errors.h"

#define TEST_DB_FILE "test_db.conf"

struct DBFixture {
    DBFixture() {
        std::ofstream f(TEST_DB_FILE);
        f << "admin:SupErP@$$w0rd\n";
    }
    ~DBFixture() { std::remove(TEST_DB_FILE); }
};

SUITE(AuthenticatorTest) {
    TEST_FIXTURE(DBFixture, SuccessfulAuth) { // 1.1
        UserDatabase db(TEST_DB_FILE);
        db.load();
        Authenticator auth(db);
        
        std::string msg = "admin" + std::string("4F9C429F5C6884DB") + "D3F5C0C60E6BAAABECFF0646372AD4BBFC89D3F9EDE9B908A5C5B4AD4B27A2EE";
        std::cout << "=== Модуль Authenticator ===" << std::endl;
        std::cout << "Тест 1.1: ";
        bool result = auth.authenticate(msg);
        std::cout << "authenticate() вернул " << (result ? "true" : "false") << std::endl;
        CHECK(result);
    }

    TEST_FIXTURE(DBFixture, WrongHash) { // 1.2
        UserDatabase db(TEST_DB_FILE); db.load();
        Authenticator auth(db);
        
        std::string msg = "admin" + std::string("4F9C429F5C6884DB") + "0000000000000000000000000000000000000000000000000000000000000000";
        std::cout << "Тест 1.2: ";
        bool result = auth.authenticate(msg);
        std::cout << "authenticate() вернул " << (result ? "true" : "false") << std::endl;
        CHECK(!result);
    }

    TEST_FIXTURE(DBFixture, UnknownUserAuth) { // 1.3
        UserDatabase db(TEST_DB_FILE); db.load();
        Authenticator auth(db);
        
        std::string msg = "unknown" + std::string("4F9C429F5C6884DB") + "9C67ABCFAD8E46E78F89173497800E5EE143D67C28765A60C947221E7114FF68";
        std::cout << "Тест 1.3: ";
        bool threw = false;
        try { auth.authenticate(msg); } catch (...) { threw = true; }
        std::cout << "Исключение AuthError" << std::endl;
        CHECK(threw);
    }

    TEST_FIXTURE(DBFixture, ShortMessage) { // 2.1
        UserDatabase db(TEST_DB_FILE); db.load();
        Authenticator auth(db);
        
        std::cout << "Тест 2.1: ";
        bool threw = false;
        try { auth.authenticate("short"); } catch (...) { threw = true; }
        std::cout << "Исключение AuthError" << std::endl;
        CHECK(threw);
    }

    TEST_FIXTURE(DBFixture, EmptyMessage) { // 2.2
        UserDatabase db(TEST_DB_FILE); db.load();
        Authenticator auth(db);
        
        std::cout << "Тест 2.2: ";
        bool threw = false;
        try { auth.authenticate(""); } catch (...) { threw = true; }
        std::cout << "Исключение AuthError" << std::endl;
        CHECK(threw);
    }
}
