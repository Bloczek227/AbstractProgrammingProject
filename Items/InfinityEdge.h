//
// Created by aaa22 on 23.12.2023.
//

#ifndef PA_PROJ_INFINITYEDGE_H
#define PA_PROJ_INFINITYEDGE_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

class InfinityEdge: public Item{
public:
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double InfinityEdge::StatValue<AD>(){return 65;}
template<> double InfinityEdge::StatValue<CriticalChance>(){return 20;}
template<> double InfinityEdge::StatValue<CriticalBonusDamage>(){return 40;}

#endif //PA_PROJ_INFINITYEDGE_H
