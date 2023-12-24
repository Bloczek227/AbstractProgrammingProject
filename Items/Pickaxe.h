#ifndef PA_PROJ_PICKAXE_H
#define PA_PROJ_PICKAXE_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

class Pickaxe: public Item{
public:
    constexpr static double cost=875;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double Pickaxe::StatValue<AD>(){return 25;}

#endif //PA_PROJ_PICKAXE_H
