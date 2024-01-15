#ifndef PA_PROJ_FIGHT_H
#define PA_PROJ_FIGHT_H

#include "concepts.h"
#include "skill.h"

template<class Fight,SkillConcept Skill,int Ticks>
class WaitTicks{
public:
    static void tick(){
        using result=SkillSum<typename Fight::off::WaitTick,typename Fight::off::eq::template WaitTick<typename Fight::off>>;
        double flatDamage= result::template PhysDamage<typename Fight::def,Skill>() *
                           ((Fight::def::TotalArmor()*(1-Fight::off::TotalArmorPenetration()/100)-Fight::off::TotalLethality()>0)?
                           (100/(100+Fight::def::TotalArmor()*(1-Fight::off::TotalArmorPenetration()/100)-Fight::off::TotalLethality())):
                           (2-100/(100-Fight::def::TotalArmor()*(1-Fight::off::TotalArmorPenetration()/100)+Fight::off::TotalLethality())))+
                           result::template MagicDamage<typename Fight::def,Skill>() *
                           ((Fight::def::TotalMR()*(1-Fight::off::TotalPercentageMagicPenetration()/100)-Fight::off::TotalFlatMagicPenetration()>0)?
                           (100/(100+Fight::def::TotalMR()*(1-Fight::off::TotalPercentageMagicPenetration()/100)-Fight::off::TotalFlatMagicPenetration())):
                           1)+
                          result::template TrueDamage<typename Fight::def,Skill>();
        Fight::def::CurrentHP-=flatDamage;
        Fight::def::CurrentHP=Fight::def::CurrentHP>0?Fight::def::CurrentHP:0;
        result::template use<typename Fight::def,Skill>();
        WaitTicks<Fight,Skill, Ticks - 1>::tick();
    }
};
template<class Fight, SkillConcept Skill>
class WaitTicks<Fight,Skill,0> {
public:
    static void tick(){};
};

template<ChampionConcept OffensiveChamp,ChampionConcept DefendingChamp>
class Fight{
public:
    using off=OffensiveChamp;
    using def=DefendingChamp;
    template<ChampionSkillConcept ChampionSkill>
    static void UseSkill(){
        using result=SkillSum<ChampionSkill,typename OffensiveChamp::eq:: template SkillType<OffensiveChamp>>;
        double flatDamage=result::template PhysDamage<DefendingChamp,ChampionSkill>()*
                          ((DefendingChamp::TotalArmor()*(1-OffensiveChamp::TotalArmorPenetration()/100)-OffensiveChamp::TotalLethality()>0)?
                           (100/(100+DefendingChamp::TotalArmor()*(1-OffensiveChamp::TotalArmorPenetration()/100)-OffensiveChamp::TotalLethality())):
                           (2-100/(100-DefendingChamp::TotalArmor()*(1-OffensiveChamp::TotalArmorPenetration()/100)+OffensiveChamp::TotalLethality())))+
                          result::template MagicDamage<DefendingChamp,ChampionSkill>()*
                          ((DefendingChamp::TotalMR()*(1-OffensiveChamp::TotalPercentageMagicPenetration()/100)-OffensiveChamp::TotalFlatMagicPenetration()>0)?
                           (100/(100+DefendingChamp::TotalMR()*(1-OffensiveChamp::TotalPercentageMagicPenetration()/100)-OffensiveChamp::TotalFlatMagicPenetration())):
                           1)+
                          result::template TrueDamage<DefendingChamp,ChampionSkill>();
        DefendingChamp::CurrentHP-=flatDamage;
        DefendingChamp::CurrentHP=DefendingChamp::CurrentHP>0?DefendingChamp::CurrentHP:0;
        result::template use<DefendingChamp,ChampionSkill>();
    }

    template<int Ticks>
    static void waitTicks(){
        WaitTicks<Fight,typename off::WaitTick,Ticks>::tick();
    }
    static void reset(){
        Fight::off::reset();
        Fight::def::reset();
    }
};

#endif //PA_PROJ_FIGHT_H
