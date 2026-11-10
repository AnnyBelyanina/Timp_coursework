#include <UnitTest++/UnitTest++.h>
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
    TEST_FIXTURE(DBFixture, SuccessfulAuth) { // Тест 1.1
        UserDatabase db(TEST_DB_FILE);
        db.load();
        Authenticator auth(db);
        
        std::string msg = "admin" + std::string("4F9C429F5C6884DB") + "D3F5C0C60E6BAAABECFF0646372AD4BBFC89D3F9EDE9B908A5C5B4AD4B27A2EE";
        CHECK(auth.authenticate(msg));
    }

    TEST_FIXTURE(DBFixture, WrongHash) { // Тест 1.2
        UserDatabase db(TEST_DB_FILE); db.load();
        Authenticator auth(db);
        
        std::string msg = "admin" + std::string("4F9C429F5C6884DB") + "0000000000000000000000000000000000000000000000000000000000000000";
        CHECK(!auth.authenticate(msg));
    }

    TEST_FIXTURE(DBFixture, UnknownUserAuth) { // Тест 1.3
        UserDatabase db(TEST_DB_FILE); db.load();
        Authenticator auth(db);
        
        std::string msg = "unknown" + std::string("4F9C429F5C6884DB") + "9C67ABCFAD8E46E78F89173497800E5EE143D67C28765A60C947221E7114FF68";
        CHECK_THROW(auth.authenticate(msg), AuthError);
    }

    TEST_FIXTURE(DBFixture, ShortMessage) { // Тест 2.1 — ИСПРАВЛЕНО: добавлен DBFixture
        UserDatabase db(TEST_DB_FILE); db.load();
        Authenticator auth(db);
        CHECK_THROW(auth.authenticate("short"), AuthError);
    }

    TEST_FIXTURE(DBFixture, EmptyMessage) { // Тест 2.2 — ИСПРАВЛЕНО: добавлен DBFixture
        UserDatabase db(TEST_DB_FILE); db.load();
        Authenticator auth(db);
        CHECK_THROW(auth.authenticate(""), AuthError);
    }
}
