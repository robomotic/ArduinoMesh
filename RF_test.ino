#include <SPI.h>
#include "RF24.h"
#include "MeshBase.h"

class App : public MeshBase
{
public:
    App() : MeshBase(9, 10) {}
protected:
    virtual void	HandleMessage(uint32_t sender, const void* data, uint8_t length)
    {
        Serial.print(sender, DEC);
        Serial.print(" : ");
        Serial.println((const char*)data);
    }
    virtual void OnNewPeer(Peer* p)
    {
        if (!IsReady()) return;
        char buff[255];
        int len = snprintf(buff, 255, "Hello %u from %u", p->address, GetAddress());
        Serial.print("Sending message: ");
        Serial.println(buff);
        SendMessage(p->address, buff, len + 1);
    }
};

App app;

void setup()
{
    Serial.begin(9600);
    Serial.println("Starting RF_TEST");
    randomSeed(analogRead(0));
    app.Begin();
}

void loop()
{
    app.Update();
    delay(100);
}
