#include <iostream>
#include "../items.h"
#include "../equipment.h"
#include "../points.h"
#include "../champions.h"
#include "../fight.h"

template<typename Eq>
void test(){
    using MissFortune=MissFortune<8,Eq,Points<4,2,1,1>>;
    using DefendingTwitch=Twitch<8,Equipment<DoransBlade,KrakenSlayer>,Points<2,1,4,1>>;
    using fight=Fight<MissFortune,DefendingTwitch>;
    std::cout<<"Cost: "<<MissFortune::eq::cost<<std::endl;
    fight::template UseSkill<typename MissFortune::BasicAttack>();
    fight::template UseSkill<typename MissFortune::template Q<>>();
    fight::template waitTicks<9>();
    fight::template UseSkill<typename MissFortune::BasicAttack>();
    std::cout<<"Short combo damage:\t"<<fight::def::DamageReceived()<<std::endl;
    fight::reset();
    fight::template UseSkill<typename MissFortune::W>();
    fight::template UseSkill<typename MissFortune::E>();
    fight::template UseSkill<typename MissFortune::BasicAttack>();
    fight::template UseSkill<typename MissFortune::template Q<>>();
    fight::template waitTicks<9>();
    fight::template UseSkill<typename MissFortune::BasicAttack>();
    fight::template UseSkill<typename MissFortune::R>();
    fight::template waitTicks<10>();
    std::cout<<"Long combo damage:\t"<<fight::def::DamageReceived()<<std::endl<<std::endl;
    fight::reset();
}

int main(){
    using Equipment1=Equipment<DoransBlade,KrakenSlayer,LongSword>;
    using Equipment2=Equipment<DoransBlade,BladeOfTheRuinedKing>;
    using Equipment3=Equipment<DoransBlade,InfinityEdge>;
    using Equipment4=Equipment<DoransBlade,YoumuusGhostblade,LongSword,LongSword>;
    using Equipment5=Equipment<DoransBlade,TheCollector,LongSword>;
    using Equipment6=Equipment<DoransBlade,NavoriQuickblades>;

    std::cout<<"Kraken Slayer build"<<std::endl;
    test<Equipment1>();
    std::cout<<"BoTRK build"<<std::endl;
    test<Equipment2>();
    std::cout<<"Infinity Edge build"<<std::endl;
    test<Equipment3>();
    std::cout<<"Youmuu's build"<<std::endl;
    test<Equipment4>();
    std::cout<<"Collector build"<<std::endl;
    test<Equipment5>();
    std::cout<<"Navori build"<<std::endl;
    test<Equipment6>();
    return 0;
}

/*
Output:

Kraken Slayer build
Cost: 3800
Short combo damage:     464.438
Long combo damage:      931.669

BoTRK build
Cost: 3650
Short combo damage:     530.301
Long combo damage:      975.929

Infinity Edge build
Cost: 3750
Short combo damage:     492.616
Long combo damage:      1008.58

Youmuu's build
Cost: 3850
Short combo damage:     471.065
Long combo damage:      1067.72

Collector build
Cost: 3900
Short combo damage:     470.944
Long combo damage:      1046.76

Navori build
Cost: 3750
Short combo damage:     412.187
Long combo damage:      906.798

 */