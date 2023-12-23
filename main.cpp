#include <iostream>
#include "items.h"
#include "equipment.h"
#include "points.h"
#include "Champions/MissFortune.h"
#include "fight.h"

int main() {
    using MF1=MissFortune<8,Equipment<LongSword,KrakenSlayer>,Points<4,1,2,1>>;
    using MF2=MissFortune<9,Equipment<KrakenSlayer>,Points<5,1,2,1>>;
    using fight=Fight<MF1,MF2>;
    fight::UseSkill<MF1::BasicAttack>();
    fight::UseSkill<MF1::Q<>>();
    fight::UseSkill<MF1::BasicAttack>();
    std::cout <<fight::def::DamageReceived()<< std::endl;
    fight::reset();

    fight::UseSkill<MF1::W>();
    fight::UseSkill<MF1::E>();
    fight::UseSkill<MF1::BasicAttack>();
    fight::UseSkill<MF1::Q<1>>();
    fight::waitTicks<10>();
    fight::UseSkill<MF1::BasicAttack>();
    fight::UseSkill<MF1::R>();
    fight::waitTicks<10>();
    std::cout <<fight::def::DamageReceived()<< std::endl<<std::endl;
    fight::reset();


    using MF3=MissFortune<8,Equipment<InfinityEdge>,Points<4,1,2,1>>;
    using fight2=Fight<MF3,MF2>;
    fight2::UseSkill<MF3::BasicAttack>();
    fight2::UseSkill<MF3::Q<>>();
    fight2::UseSkill<MF3::BasicAttack>();
    std::cout <<fight2::def::DamageReceived()<< std::endl;
    fight2::reset();

    fight2::UseSkill<MF3::W>();
    fight2::UseSkill<MF3::E>();
    fight2::UseSkill<MF3::BasicAttack>();
    fight2::UseSkill<MF3::Q<1>>();
    fight2::waitTicks<10>();
    fight2::UseSkill<MF3::BasicAttack>();
    fight2::UseSkill<MF3::R>();
    fight2::waitTicks<10>();
    std::cout <<fight2::def::DamageReceived()<< std::endl<<std::endl;
    fight2::reset();





    using MF4=MissFortune<8,Equipment<YoumuusGhostblade,LongSword,LongSword>,Points<4,1,2,1>>;
    using fight3=Fight<MF4,MF2>;
    fight3::UseSkill<MF4::BasicAttack>();
    fight3::UseSkill<MF4::Q<>>();
    fight3::UseSkill<MF4::BasicAttack>();
    std::cout <<fight3::def::DamageReceived()<< std::endl;
    fight3::reset();

    fight3::UseSkill<MF4::W>();
    fight3::UseSkill<MF4::E>();
    fight3::UseSkill<MF4::BasicAttack>();
    fight3::UseSkill<MF4::Q<1>>();
    fight3::waitTicks<10>();
    fight3::UseSkill<MF4::BasicAttack>();
    fight3::UseSkill<MF4::R>();
    fight3::waitTicks<10>();
    std::cout <<fight3::def::DamageReceived()<< std::endl<<std::endl;
    fight3::reset();



    using MF5=MissFortune<8,Equipment<TheCollector,LongSword>,Points<4,1,2,1>>;
    using fight4=Fight<MF5,MF2>;
    fight4::UseSkill<MF5::BasicAttack>();
    fight4::UseSkill<MF5::Q<>>();
    fight4::UseSkill<MF5::BasicAttack>();
    std::cout <<fight4::def::DamageReceived()<< std::endl;
    fight4::reset();

    fight4::UseSkill<MF5::W>();
    fight4::UseSkill<MF5::E>();
    fight4::UseSkill<MF5::BasicAttack>();
    fight4::UseSkill<MF5::Q<1>>();
    fight4::waitTicks<10>();
    fight4::UseSkill<MF5::BasicAttack>();
    fight4::UseSkill<MF5::R>();
    fight4::waitTicks<10>();
    std::cout <<fight4::def::DamageReceived()<< std::endl<<std::endl;
    fight4::reset();
    return 0;
}
