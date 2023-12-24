#include <iostream>
#include "../items.h"
#include "../equipment.h"
#include "../points.h"
#include "../champions.h"
#include "../fight.h"

template<typename Eq>
void test(){
    using MissFortune=MissFortune<8,Eq,Points<4,1,2,1>>;
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
    return 0;
}