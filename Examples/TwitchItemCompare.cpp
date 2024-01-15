#include <iostream>
#include "../items.h"
#include "../equipment.h"
#include "../points.h"
#include "../champions.h"
#include "../fight.h"

template<typename Eq>
void test(){
    using Twitch=Twitch<8,Eq,Points<2,1,4,1>>;
    using DefendingMissFortune=MissFortune<8,Equipment<DoransBlade,KrakenSlayer>,Points<4,2,1,1>>;
    using fight=Fight<Twitch,DefendingMissFortune>;
    std::cout<<"Cost: "<<Twitch::eq::cost<<std::endl;
    fight::template UseSkill<typename Twitch::Q>();
    std::cout<<"Attack Speed: "<<Twitch::TotalAttackSpeed()<<std::endl;
    fight::template UseSkill<typename Twitch::R>();
    fight::template UseSkill<typename Twitch::W>();
    fight::template UseSkill<typename Twitch::template BasicAttack<>>();
    fight::template waitTicks<9>();
    fight::template UseSkill<typename Twitch::template BasicAttack<>>();
    fight::template waitTicks<9>();
    fight::template UseSkill<typename Twitch::template BasicAttack<>>();
    fight::template waitTicks<9>();
    fight::template UseSkill<typename Twitch::template BasicAttack<>>();
    fight::template UseSkill<typename Twitch::E>();
    std::cout<<"Damage after combo:\t"<<fight::def::DamageReceived()<<std::endl;
    fight::template waitTicks<60>();
    std::cout<<"Full Damage:\t\t"<<fight::def::DamageReceived()<<std::endl<<std::endl;
    fight::reset();
}

int main(){
    using Equipment1=Equipment<DoransBlade,KrakenSlayer,LongSword>;
    using Equipment2=Equipment<DoransBlade,BladeOfTheRuinedKing>;
    using Equipment3=Equipment<DoransBlade,InfinityEdge>;
    using Equipment4=Equipment<DoransRing,NashorsTooth,AmplifyingTome>;

    std::cout<<"Kraken Slayer build"<<std::endl;
    test<Equipment1>();
    std::cout<<"BoTRK build"<<std::endl;
    test<Equipment2>();
    std::cout<<"Infinity Edge build"<<std::endl;
    test<Equipment3>();
    std::cout<<"Nashor's Tooth build"<<std::endl;
    test<Equipment4>();
    return 0;
}