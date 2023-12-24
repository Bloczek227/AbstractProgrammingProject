#ifndef PA_PROJ_NAVORIQUICKBLADES_H
#define PA_PROJ_NAVORIQUICKBLADES_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

template<ChampionConcept OffensiveChamp>
class NavoriQuickbladesPassive:public ItemSkill<OffensiveChamp>{
public:
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double PhysDamage(){return ChampionSkill::template PhysDamage<DefendingChamp,ChampionSkill>()*0.2*OffensiveChamp::TotalCriticalChance()/100;}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double MagicDamage(){return ChampionSkill::template MagicDamage<DefendingChamp,ChampionSkill>()*0.2*OffensiveChamp::TotalCriticalChance()/100;}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double TrueDamage(){return ChampionSkill::template TrueDamage<DefendingChamp,ChampionSkill>()*0.2*OffensiveChamp::TotalCriticalChance()/100;}
};

class NavoriQuickblades: public Item{
public:
    constexpr static double cost=3300;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=NavoriQuickbladesPassive<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double NavoriQuickblades::StatValue<AD>(){return 60;}
template<> double NavoriQuickblades::StatValue<CriticalChance>(){return 20;}

#endif //PA_PROJ_NAVORIQUICKBLADES_H
