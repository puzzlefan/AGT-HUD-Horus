#include "DaTa.h"

DaTa::DaTa()
{
    for(int i = 0; i<DaTaAmount;i++)
    {
        RawDaTa[i]=0;
    }
    for(int i = 0; i<ButtonAmount;i++)
    {
        Buttons[i]=0;
    }
    for (int i = 0; i < FarewellAmount; i++) {
        Farewell[i]=0;
    }
    SomeonePushedThatButton = false;
    SomeoneToSayGodbyTo = false;
}

DaTa::~DaTa()
{
    return;
}

void DaTa::boolise()
{
    for(int i = 0; i < ButtonAmount;i++)
    {
        if (RawDaTa[KNOBS]%Primfactors[i]==0) {
            Buttons[i] = true;
        }
        else
        {
            Buttons[i] = false;
        }
    }
}

int DaTa::getRawDaTa(int pos)
{
    if(pos<0||pos>DaTaAmount)
    {
        return -1;
    }
    std::lock_guard<std::mutex> lock(DaTaa);
    return RawDaTa[pos];
}
int DaTa::getWriteDaTa(int pos)
{
    if(pos<0||pos>FarewellAmount)
    {
        return -1;
    }
    std::lock_guard<std::mutex> lock(DaTaa);
    SomeoneToSayGodbyTo = false;
    return Farewell[pos];
}
bool DaTa::getButton(int pos)
{
    if(pos<0||pos>ButtonAmount)
    {
        return -1;
    }
    std::lock_guard<std::mutex> lock(DaTaa);
    SomeonePushedThatButton = false;
    return Buttons[pos];
}
bool DaTa::WriteOrDontWrite()
{
    std::lock_guard<std::mutex> lock(DaTaa);
    return SomeoneToSayGodbyTo;
}

void DaTa::setDaTa(int val, int pos)
{
    if(pos<0||pos>DaTaAmount)
    {
        return;
    }
    std::lock_guard<std::mutex> lock(DaTaa);
    if(val != RawDaTa[pos])
    {
        RawDaTa[pos] = val;
        if (pos==KNOBS) {
            boolise();
            SomeonePushedThatButton = true;
        }
    }
}
void DaTa::setSendData(int val, int pos)
{
    if(pos<0||pos>FarewellAmount)
    {
        return;
    }
    std::lock_guard<std::mutex> lock(DaTaa);
    if(val != Farewell[pos])
    {
        RawDaTa[pos] = val;
        SomeoneToSayGodbyTo = true;
    }
}
