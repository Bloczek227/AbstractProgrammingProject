#ifndef PA_PROJ_UMBRALGLAVE_H
#define PA_PROJ_UMBRALGLAVE_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

class UmbralGlave: public Item{
public:
    constexpr static double cost=2600;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double UmbralGlave::StatValue<AD>(){return 50;}
template<> double UmbralGlave::StatValue<Lethality>(){return 15;}

#endif //PA_PROJ_UMBRALGLAVE_H
