//
// Created by aaa22 on 23.12.2023.
//

#ifndef PA_PROJ_THECOLLECTOR_H
#define PA_PROJ_THECOLLECTOR_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

template<ChampionConcept OffensiveChamp>
class TheCollectorPassive:public ItemSkill<OffensiveChamp>{
public:
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static void use(){
        DefendingChamp::CurrentHP=DefendingChamp::CurrentHP/DefendingChamp::TotalHP()>0.05?DefendingChamp::CurrentHP:0;
    }
};

class TheCollector: public Item{
public:
    constexpr static double cost=3000;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double TheCollector::StatValue<AD>(){return 60;}
template<> double TheCollector::StatValue<CriticalChance>(){return 20;}
template<> double TheCollector::StatValue<Lethality>(){return 16;}

#endif //PA_PROJ_THECOLLECTOR_H
