// Copyright 2017 Yahoo Holdings. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.
#include <vespa/vespalib/testkit/testapp.h>
#include <vespa/searchcore/proton/common/feedtoken.h>
#include <vespa/vespalib/util/exceptions.h>

using namespace proton;

class LocalTransport : public FeedToken::ITransport {
private:
    size_t _receivedCount;

public:
    LocalTransport()
        : _receivedCount(0)
    { }

    void send(ResultUP, bool) override {
        _receivedCount++;
    }

    size_t getReceivedCount() const { return _receivedCount; }
};

class Test : public vespalib::TestApp {
private:
    void testAck();
    void testFail();
    void testHandover();

public:
    int Main() override {
        TEST_INIT("feedtoken_test");

        testAck();       TEST_FLUSH();
        testFail();      TEST_FLUSH();
        testHandover();  TEST_FLUSH();

        TEST_DONE();
    }
};

TEST_APPHOOK(Test);

void
Test::testAck()
{
    LocalTransport transport;
    FeedToken token(transport);
    token.ack();
    EXPECT_EQUAL(1u, transport.getReceivedCount());
}

void
Test::testFail()
{
    LocalTransport transport;
    FeedToken token(transport);
    token.fail();
    EXPECT_EQUAL(1u, transport.getReceivedCount());
}

void
Test::testHandover()
{
    struct MyHandover {
        static FeedToken handover(FeedToken token) {
            return token;
        }
    };

    LocalTransport transport;

    FeedToken token(transport);
    token = MyHandover::handover(token);
    token.ack();
    EXPECT_EQUAL(1u, transport.getReceivedCount());
}


