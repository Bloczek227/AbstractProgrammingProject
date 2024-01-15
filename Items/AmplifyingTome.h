#ifndef PA_PROJ_AMPLIFYINGTOME_H
#define PA_PROJ_AMPLIFYINGTOME_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

class AmplifyingTome: public Item{
public:
    constexpr static double cost=400;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double AmplifyingTome::StatValue<AP>(){return 20;}

#endif //PA_PROJ_AMPLIFYINGTOME_H
