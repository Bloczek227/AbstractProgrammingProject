#ifndef PA_PROJ_STORMRAZOR_H
#define PA_PROJ_STORMRAZOR_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

template<ChampionConcept OffensiveChamp>
class StormrazorPassive:public ItemSkill<OffensiveChamp>{
public:
    static int energize;
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double MagicDamage(){return (energize==100&&ChampionSkill::onAttack)*(90+0.25*OffensiveChamp::TotalAD());}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static void use(){
        energize=(energize==100&&ChampionSkill::onAttack)?0:
        energize+ChampionSkill::onAttack*6+ChampionSkill::dashRange/24>100?100:energize+ChampionSkill::onAttack*6+ChampionSkill::dashRange/24;
    }
};
template<ChampionConcept OffensiveChamp> int StormrazorPassive<OffensiveChamp>::energize=100;

class Stormrazor: public Item{
public:
    constexpr static double cost=3100;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=StormrazorPassive<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double Stormrazor::StatValue<AD>(){return 60;}
template<> double Stormrazor::StatValue<AttackSpeed>(){return 15;}
template<> double Stormrazor::StatValue<CriticalChance>(){return 20;}

#endif //PA_PROJ_STORMRAZOR_H
