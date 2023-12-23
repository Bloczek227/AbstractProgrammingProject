#ifndef PA_PROJ_EQUIPMENT_H
#define PA_PROJ_EQUIPMENT_H

#include "concepts.h"
#include "stats.h"
#include "skill.h"

template<ItemConcept...Items>
class Equipment{
public:
    template<StatConcept Stat>
    static double ItemsStatValue(){return Stat::baseValue;}
    template<ChampionConcept OffensiveChamp>
    using SkillType=Skill;
    template<ChampionConcept OffensiveChamp>
    static void reset(){}
};
template<ItemConcept FirstItem,ItemConcept... NextItems>
class Equipment<FirstItem,NextItems...>{
public:
    template<StatConcept Stat>
    static double ItemsStatValue(){return Stat::StackingMethod(FirstItem::template StatValue<Stat>(),Equipment<NextItems...>::template ItemsStatValue<Stat>());}
    template<ChampionConcept OffensiveChamp>
    using SkillType=SkillSum<typename FirstItem::template SkillType<OffensiveChamp>,typename Equipment<NextItems...>::template SkillType<OffensiveChamp>>;
    template<ChampionConcept OffensiveChamp>
    static void reset(){FirstItem::template reset<OffensiveChamp>();Equipment<NextItems...>::template reset<OffensiveChamp>();}
};

#endif //PA_PROJ_EQUIPMENT_H
