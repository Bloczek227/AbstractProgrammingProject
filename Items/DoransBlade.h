#ifndef PA_PROJ_DORANSBLADE_H
#define PA_PROJ_DORANSBLADE_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

class DoransBlade: public Item{
public:
    constexpr static double cost=450;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double DoransBlade::StatValue<AD>(){return 10;}
template<> double DoransBlade::StatValue<HP>(){return 100;}

#endif //PA_PROJ_DORANSBLADE_H
