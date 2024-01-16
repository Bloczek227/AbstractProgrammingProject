#include <iostream>
#include "../items.h"
#include "../equipment.h"
#include "../points.h"
#include "../champions.h"
#include "../fight.h"

template<typename Eq>
void test(){
    using Draven=Draven<8,Eq,Points<4,1,2,1>>;
    using DefendingTwitch=Twitch<8,Equipment<DoransBlade,KrakenSlayer>,Points<2,1,4,1>>;
    using fight=Fight<Draven,DefendingTwitch>;
    std::cout<<"Cost: "<<Draven::eq::cost<<std::endl;
    fight::template UseSkill<typename Draven::Q>();
    fight::template UseSkill<typename Draven::Q>();
    fight::template UseSkill<typename Draven::BasicAttack>();
    fight::template UseSkill<typename Draven::E>();
    fight::template waitTicks<9>();
    fight::template UseSkill<typename Draven::BasicAttack>();
    fight::template waitTicks<9>();
    fight::template UseSkill<typename Draven::template R<>>();
    fight::off::Q::grabAxe();
    fight::template UseSkill<typename Draven::BasicAttack>();
    std::cout<<"Combo damage:\t"<<fight::def::DamageReceived()<<std::endl<<std::endl;
    fight::reset();
}

int main(){
    using Equipment1=Equipment<DoransBlade,KrakenSlayer,LongSword>;
    using Equipment2=Equipment<DoransBlade,TrinityForce>;
    using Equipment3=Equipment<DoransBlade,InfinityEdge>;
    using Equipment4=Equipment<DoransBlade,YoumuusGhostblade,LongSword,LongSword>;
    using Equipment5=Equipment<DoransBlade,TheCollector,LongSword>;
    using Equipment6=Equipment<DoransBlade,EssenceReaver,LongSword>;
    using Equipment7=Equipment<DoransBlade,Eclipse,LongSword>;
    using Equipment8=Equipment<DoransBlade,UmbralGlave,LongSword,LongSword>;
    using Equipment9=Equipment<DoransBlade,Stormrazor,LongSword>;

    std::cout<<"Kraken Slayer build"<<std::endl;
    test<Equipment1>();
    std::cout<<"Trinity build"<<std::endl;
    test<Equipment2>();
    std::cout<<"Infinity Edge build"<<std::endl;
    test<Equipment3>();
    std::cout<<"Youmuu's build"<<std::endl;
    test<Equipment4>();
    std::cout<<"Collector build"<<std::endl;
    test<Equipment5>();
    std::cout<<"Essence Reaver build"<<std::endl;
    test<Equipment6>();
    std::cout<<"Eclipse build"<<std::endl;
    test<Equipment7>();
    std::cout<<"Umbral Glave build"<<std::endl;
    test<Equipment8>();
    std::cout<<"Stormrazor build"<<std::endl;
    test<Equipment9>();
    return 0;
}

/*
Output:

Kraken Slayer build
Cost: 3800
Combo damage:   934.979

Trinity build
Cost: 3783
Combo damage:   962.467

Infinity Edge build
Cost: 3750
Combo damage:   917.983

Youmuu's build
Cost: 3850
Combo damage:   1047.52

Collector build
Cost: 3900
Combo damage:   1028.89

Essence Reaver build
Cost: 3700
Combo damage:   1066.04

Eclipse build
Cost: 3600
Combo damage:   958.811

Umbral Glave build
Cost: 3750
Combo damage:   967.576

Stormrazor build
Cost: 3900
Combo damage:   1015.1

 */