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
    return 0;
}