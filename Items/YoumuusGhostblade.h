#ifndef PA_PROJ_YOUMUUSGHOSTBLADE_H
#define PA_PROJ_YOUMUUSGHOSTBLADE_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

class YoumuusGhostblade: public Item{
public:
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double YoumuusGhostblade::StatValue<AD>(){return 60;}
template<> double YoumuusGhostblade::StatValue<Lethality>(){return 18;}

#endif //PA_PROJ_YOUMUUSGHOSTBLADE_H
